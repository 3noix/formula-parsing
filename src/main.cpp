#include <iostream>
#include <QApplication>
#include <QFile>
#include <QtDebug>

#include "gui/MainWindow.h"

#define DEBUG_MODE


#ifdef DEBUG_MODE
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	Q_UNUSED(context)
	
	QByteArray localMsg1 = msg.toLocal8Bit();
	QByteArray localMsg2 = (msg + '\n').toLocal8Bit();
	if (type == QtDebugMsg)
	{
		// sur la sortie standard
		fprintf(stderr, "%s\r\n", localMsg1.constData());
		
		// dans un fichier
		QFile debugFile{QCoreApplication::applicationDirPath() + "/debug.txt"};
		debugFile.open(QIODevice::Append);
		debugFile.write(localMsg2.constData());
		debugFile.close();
	}
}

#endif


int main(int argc, char *argv[])
{
	QApplication app{argc,argv};
	
	#ifdef DEBUG_MODE
	qInstallMessageHandler(myMessageOutput);
	QFile debugFile{QCoreApplication::applicationDirPath() + "/debug.txt"};
	debugFile.remove();
	#endif
	
	MainWindow w;
	w.resize(600,500);
	w.show();
	return app.exec();
}


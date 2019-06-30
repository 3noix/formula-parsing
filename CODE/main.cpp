#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QtDebug>

#include "FORMULA_INTERPRETER/FormulaInterpreter.h"
#include "ExceptionInterpreter.h"

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
	QCoreApplication app{argc,argv};
	QStringList args = app.arguments();
	Q_UNUSED(args)
	
	#ifdef DEBUG_MODE
	qInstallMessageHandler(myMessageOutput);
	QFile debugFile{QCoreApplication::applicationDirPath() + "/debug.txt"};
	debugFile.remove();
	#endif
	
	FormulaInterpreter interpreter;
	SimuData sd;
	sd.addParameter("a",1000.0);
	sd.addParameter("x",100.0);
	sd.addParameter("c",3.0);
	
	try
	{
		QString formula1 = "a + 2.0 - x*3.0 + 5.0*(c-2.0)";
		qDebug() << formula1;
		
		QStringList errors1;
		bool b1 = interpreter.prepare(formula1,&errors1);
		if (!b1) {qDebug() << "ERRORS:\n    " << errors1.join("\n    ");};
		
		Any result1 = interpreter.eval(formula1,&sd);
		qDebug() << "result1 = " << toString(result1);
		qDebug() << "";
	}
	catch (const ExceptionInterpreter &e)
	{
		qDebug() << e.text();
		qDebug() << "";
	}
	
	try
	{
		QString formula2 = "a/2 - x*3 + cos(c)";
		qDebug() << formula2;
		
		QStringList errors2;
		bool b2 = interpreter.prepare(formula2,&errors2);
		if (!b2) {qDebug() << "ERRORS:\n    " << errors2.join("\n    ");};
		
		Any result2 = interpreter.eval(formula2,&sd);
		qDebug() << "result1 = " << toString(result2);
		qDebug() << "";
	}
	catch (const ExceptionInterpreter &e)
	{
		qDebug() << e.text();
		qDebug() << "";
	}
	
	qDebug() << "Press Enter to terminate";
	std::cin.get();
	return 0;
}


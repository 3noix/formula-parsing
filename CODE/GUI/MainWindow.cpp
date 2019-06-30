#include "MainWindow.h"
#include "TextEdit.h"
#include "LineEdit.h"
#include "../ExceptionInterpreter.h"
#include <QVBoxLayout>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  CREATE ACTIONS
//  CREATE MENUS
//  CREATE TOOLBAR
//  SETUP WIDGET
//
//  SLOT COMPUTE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}
{
	m_bFirstFormula = true;
	
	this->createActions();
	this->createMenus();
	this->createToolBar();
	this->setupWidget();
	
	// connections
	QObject::connect(lineCommand, &QLineEdit::returnPressed, this, &MainWindow::slotCompute);
	
	// end
	lineCommand->setFocus(Qt::OtherFocusReason);
}






// CREATE ACTIONS /////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
}

// CREATE MENUS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createMenus()
{
}

// CREATE TOOLBAR //////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createToolBar()
{
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	// main widget and layout
	mainWidget = new QWidget{this};
	layout = new QVBoxLayout{mainWidget};
	mainWidget->setLayout(layout);
	this->setCentralWidget(mainWidget);
	
	textEdit = new TextEdit{this};
	lineCommand = new LineEdit{this};
	
	layout->addWidget(textEdit);
	layout->addWidget(lineCommand);
	
	// end
	this->resize(600,500);
	this->setWindowIcon(QIcon{":/RESOURCES/ICONES/calculator.png"});
	this->setWindowTitle("Formula interpreter");
}





#include <QtDebug>
// SLOT COMPUTE ///////////////////////////////////////////////////////////////
void MainWindow::slotCompute()
{
	QString formula = lineCommand->text().trimmed();
	lineCommand->clear();
	if (formula.isEmpty()) {return;}
	
	QString msg = "\n>> " + formula;
	if (m_bFirstFormula)
	{
		msg = msg.right(msg.size()-1);
		m_bFirstFormula = false;
	}
	textEdit->slotAddMessage(msg,Qt::black);
	
	// formula preration
	QStringList prepErrors;
	bool bPrepa = m_interpreter.prepare(formula,&prepErrors);
	
	/*qDebug() << "--------------------------------------------------";
	qDebug() << "INFIX   = " + m_interpreter.debugInfixTokens(formula).join(" ");
	qDebug() << "POSTFIX = " + m_interpreter.debugPostfixTokens(formula).join(" ");
	qDebug() << "TREE    = ";
	for (const QString &str : m_interpreter.debugSyntaxicTree(formula).split("\n")) {qDebug() << str;}
	qDebug() << "";*/
	
	if (!bPrepa)
	{
		for (const QString &error : prepErrors) {textEdit->slotAddMessage(error,Qt::red);}
		return;
	}
	
	// formula evaluation
	try
	{
		Any result = m_interpreter.eval(formula);
		textEdit->slotAddMessage(::toString(result),Qt::black);
	}
	catch (const ExceptionInterpreter &e)
	{
		textEdit->slotAddMessage(e.text(),Qt::red);
	}
}


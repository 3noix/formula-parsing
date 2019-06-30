#include <QMenu>
#include <QTime>
#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>

#include "TextEdit.h"
#include "ExceptionInterpreter.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//
//  CREATE ACTIONS
//  CONTEXT MENU EVENT
//  KEY PRESS EVENT
//
//  SHOW RESULTS
//  SLOT ADD CHEVRON
//  SLOT SHOW ERROR
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
TextEdit::TextEdit(QWidget *parent) : QTextEdit{parent}
{
	this->setReadOnly(false);
	
	// actions
	this->createActions();
	
	// menu
	m_menu = new QMenu{this};
	m_menu->addAction(actionClear);
	m_menu->addSeparator();
	m_menu->addAction(actionCopy);
	m_menu->addAction(actionSelectAll);
	
	// connections
	connect(actionClear,     SIGNAL(triggered()), this, SLOT(clear()));
	connect(actionCopy,      SIGNAL(triggered()), this, SLOT(copy()));
	connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(selectAll()));
}






// CREATE ACTIONS /////////////////////////////////////////////////////////////
void TextEdit::createActions()
{
	// action clear
	actionClear = new QAction{"Clear",this};
	actionClear->setStatusTip("Clear the content of the message box");
	actionClear->setIcon(QIcon{":/RESOURCES/ICONES/corbeille.png"});
	
	// action copy
	actionCopy = new QAction{"Copy",this};
	actionCopy->setShortcut(QKeySequence{"Ctrl+C"});
	actionCopy->setStatusTip("Copy the content of the message box");
	actionCopy->setIcon(QIcon{":/RESOURCES/ICONES/copy.png"});
	
	// action select all
	actionSelectAll = new QAction{"Select all",this};
	actionSelectAll->setShortcut(QKeySequence{"Ctrl+A"});
	actionSelectAll->setStatusTip("Select all the content of the message box");
	actionSelectAll->setIcon(QIcon{":/RESOURCES/ICONES/select.png"});
}

// CONTEXT MENU EVENT /////////////////////////////////////////////////////////
void TextEdit::contextMenuEvent(QContextMenuEvent *event)
{
	QPoint position = event->pos();
	m_menu->exec(this->mapToGlobal(position + QPoint(0,-10)));
}

// KEY PRESS EVENT ////////////////////////////////////////////////////////////
void TextEdit::keyPressEvent(QKeyEvent *event)
{
	QTextEdit::keyPressEvent(event);
	bool bEnter = (event->key() & (Qt::Key_Enter | Qt::Key_Return));
	if (!bEnter) {return;}
	
	// if enter or return was pressed, we resume
	QString text = this->toPlainText();
	QString lastLine = text.split("\n",QString::SkipEmptyParts).takeLast();
	if (!lastLine.startsWith(">> ")) {return;}
	lastLine.right(lastLine.size()-3);
	lastLine = lastLine.trimmed();
	if (lastLine.isEmpty()) {return;}
	
	// formula preration
	QStringList prepErrors;
	bool bPrepa = m_interpreter.prepare(lastLine,&prepErrors);
	if (!bPrepa)
	{
		for (const QString &error : prepErrors) {this->slotShowError(error);}
		return;
	}
	
	// formula computation
	try
	{
		Any result = m_interpreter.eval(lastLine);
		this->showResult(result);
	}
	catch (const ExceptionInterpreter &e)
	{
		this->slotShowError(e.text());
	}
	
	// the end
	this->slotAddChevron();
}






// SHOW RESULTS ///////////////////////////////////////////////////////////////
void TextEdit::showResult(const Any &a)
{
	this->setTextColor(Qt::black);
	this->append(::toString(a));
	this->repaint();
}

// SLOT ADD CHEVRON ///////////////////////////////////////////////////////////
void TextEdit::slotAddChevron()
{
	this->setTextColor(Qt::black);
	this->append("");
	this->append(">> ");
	this->repaint();
}

// SLOT SHOW ERROR ////////////////////////////////////////////////////////////
void TextEdit::slotShowError(const QString &errorMessage)
{
	this->setTextColor(Qt::red);
	this->append(errorMessage);
	this->repaint();
}


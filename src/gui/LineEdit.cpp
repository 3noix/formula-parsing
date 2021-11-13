#include "LineEdit.h"
#include <QKeyEvent>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  KEY PRESS EVENT
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
LineEdit::LineEdit(QWidget *parent) : QLineEdit{parent}
{
	m_cmdIndex = -1;
}

// KEY PRESS EVENT ////////////////////////////////////////////////////////////
void LineEdit::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Enter || key == Qt::Key_Return)
	{
		if (!this->text().isEmpty())
		{
			m_cmdHistory << this->text();
			m_cmdIndex = m_cmdHistory.size();
			cmdInProgress = "";
		}
	}
	else if (key == Qt::Key_Up)
	{
		if (m_cmdIndex > 0)
		{
			if (m_cmdIndex == m_cmdHistory.size()) {cmdInProgress = this->text();}
			--m_cmdIndex;
			this->setText(m_cmdHistory[m_cmdIndex]);
		}
	}
	else if (key == Qt::Key_Down)
	{
		if (m_cmdIndex < m_cmdHistory.size()-1)
		{
			++m_cmdIndex;
			this->setText(m_cmdHistory[m_cmdIndex]);
		}
		else if (m_cmdIndex == m_cmdHistory.size()-1)
		{
			++m_cmdIndex;
			this->setText(cmdInProgress);
		}
	}
	
	QLineEdit::keyPressEvent(event);
}


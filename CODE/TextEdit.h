#ifndef TEXT_EDIT
#define TEXT_EDIT


#include <QTextEdit>
#include "DATA_AND_OPERATORS/ProjectData.h"
#include "FORMULA_INTERPRETER/FormulaInterpreter.h"
class QMenu;


class TextEdit : public QTextEdit
{
	Q_OBJECT
	
	public:
		explicit TextEdit(QWidget *parent = nullptr);
		TextEdit(const TextEdit &other) = delete;
		TextEdit(TextEdit &&other) = delete;
		TextEdit& operator=(const TextEdit &other) = delete;
		TextEdit& operator=(TextEdit &&other) = delete;
		virtual ~TextEdit() = default;
		
		void showResult(const Any &a);
		
		
	public slots:
		void slotAddChevron();
		void slotShowError(const QString &errorMessage);
		
		
	private:
		void createActions();
		virtual void contextMenuEvent(QContextMenuEvent *event) override;
		virtual void keyPressEvent(QKeyEvent *event) override;
		
		QAction *actionClear, *actionCopy, *actionSelectAll;
		QMenu *m_menu;
		
		FormulaInterpreter m_interpreter;
};


#endif


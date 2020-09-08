#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QMainWindow>
#include "../FORMULA_INTERPRETER/FormulaInterpreter.h"
#include "../DATA_AND_OPERATORS/WorkspaceData.h"
class TextEdit;
class LineEdit;
class QVBoxLayout;


class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = nullptr);
		MainWindow(const MainWindow &other) = delete;
		MainWindow(MainWindow &&other) = delete;
		MainWindow& operator=(const MainWindow &other) = delete;
		MainWindow& operator=(MainWindow &&other) = delete;
		virtual ~MainWindow() = default;
		
		
	private slots:
		void slotCompute();
		
		
	private:
		void createActions();
		void createMenus();
		void createToolBar();
		void setupWidget();
		
		QWidget *mainWidget;
		QVBoxLayout *layout;
		TextEdit *textEdit;
		LineEdit *lineCommand;
		
		FormulaInterpreter m_interpreter;
		WorkspaceData m_workspace;
		bool m_bFirstFormula;
};


#endif


#ifndef MAIN_WINDOW
#define MAIN_WINDOW


#include <QMainWindow>
#include "FORMULA_INTERPRETER/FormulaInterpreter.h"
class TextEdit;
class QVBoxLayout;
class QLineEdit;


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
		QLineEdit *lineCommand;
		
		FormulaInterpreter m_interpreter;
		bool m_bFirstFormula;
};


#endif


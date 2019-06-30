#ifndef LINE_EDIT
#define LINE_EDIT


#include <QLineEdit>
#include <QKeyEvent>


class LineEdit : public QLineEdit
{
	Q_OBJECT
	
	public:
		explicit LineEdit(QWidget *parent = nullptr);
		LineEdit(const LineEdit &other) = delete;
		LineEdit(LineEdit &&other) = delete;
		LineEdit& operator=(const LineEdit &other) = delete;
		LineEdit& operator=(LineEdit &&other) = delete;
		virtual ~LineEdit() = default;
		
		
	protected:
		void keyPressEvent(QKeyEvent *event);
		
		
	private:
		QStringList m_cmdHistory;
		int m_cmdIndex;
		QString cmdInProgress;
};


#endif


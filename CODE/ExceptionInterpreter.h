#ifndef EXCEPTION_INTERPRETER
#define EXCEPTION_INTERPRETER


#include <exception>
#include <QString>


class ExceptionInterpreter : public std::exception
{
	public:
		ExceptionInterpreter(const QString &text) :
			std::exception{},
			m_text{text}
		{};
		
		~ExceptionInterpreter() = default;
		
		const char* what() const noexcept
		{
			return m_text.toStdString().c_str();
		};
		
		QString text() const
		{
			return m_text;
		};
		
		
	private:
		QString m_text;
};


#endif


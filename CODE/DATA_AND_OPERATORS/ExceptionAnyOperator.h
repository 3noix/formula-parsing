#ifndef EXCEPTION_ANY_OPERATOR
#define EXCEPTION_ANY_OPERATOR


#include <exception>
#include <string>


class ExceptionAnyOperator : public std::exception
{
	public:
		ExceptionAnyOperator(const std::string &text) :
			std::exception{},
			m_text{text}
		{};
		
		~ExceptionAnyOperator() = default;
		
		const char* what() const noexcept
		{
			return m_text.c_str();
		};
		
		
	private:
		std::string m_text;
};


#endif


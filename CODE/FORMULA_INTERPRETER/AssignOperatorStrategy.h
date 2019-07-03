#ifndef ASSIGN_OPERATOR_STRATEGY
#define ASSIGN_OPERATOR_STRATEGY


#include "Token.h"
#include <QVector>


class AssignOperatorStrategy
{
	public:
		AssignOperatorStrategy();
		AssignOperatorStrategy(const AssignOperatorStrategy &other) = delete;
		AssignOperatorStrategy(AssignOperatorStrategy &&other) = delete;
		AssignOperatorStrategy& operator=(const AssignOperatorStrategy &other) = delete;
		AssignOperatorStrategy& operator=(AssignOperatorStrategy &&other) = delete;
		virtual ~AssignOperatorStrategy() = default;
		
		QString assignmentTo(QVector<Token> &infixTokens);
		bool hasError() const;
		QString errorMessage() const;
		
		
	private:
		bool m_bError;
		QString m_errorMessage;
};


#endif


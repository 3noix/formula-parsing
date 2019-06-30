#ifndef FORMULA_INTERPRETER
#define FORMULA_INTERPRETER


#include <QString>
#include <QMap>

#include "Token.h"
#include "../DATA_AND_OPERATORS/ProjectData.h"
class AbstractSyntaxicNode;


class FormulaInterpreter
{
	public:
		FormulaInterpreter() = default;
		FormulaInterpreter(const FormulaInterpreter &other) = delete;
		FormulaInterpreter(FormulaInterpreter &&other) = delete;
		FormulaInterpreter& operator=(const FormulaInterpreter &other) = delete;
		FormulaInterpreter& operator=(FormulaInterpreter &&other) = delete;
		virtual ~FormulaInterpreter();
		
		Any eval(const QString &formula, const SimuData &sd);                // do throw exceptions
		bool prepare(const QString &formula, QStringList *errors = nullptr); // do not throw exceptions
		
		
	private:
		// parsing
		static QString normalizeFormula(const QString &formula1);
		static QStringList computeTokens(const QString &formula);
		static Token stringToToken(const QString &str);
		
		// shunting yard algo
		static QVector<Token> infixToPostfix(QVector<Token> infix);
		static int operatorPrecedence(const QString &opStr);
		static bool operatorAssociativeLeft(const QString &opStr);
		
		// the tree
		AbstractSyntaxicNode* postfixToSyntaxicTree(QVector<Token> postfixTokens);
		
		// list of availables operators, functions and how to use them
		static const QStringList operatorsString;
		static const QList<QChar> operatorsChars;
		static const QList<QChar> opCharFirstOf2;
		static const QMap<QString,int> functions;
		
		// syntaxic trees
		QMap<QString,AbstractSyntaxicNode*> m_syntaxicTrees;
};


#endif


#include "FormulaInterpreter.h"
#include "AbstractSyntaxicNode.h"
#include "../ExceptionInterpreter.h"

#include "SyntaxicNodeFactory.h"
#include "../stringVerifications.h"
#include <QStack>


const QStringList  FormulaInterpreter::operatorsString = {"+","-","*","/","**","^","<","<=",">",">=","==","!=","!","%","&","&&","|","||","~","<<",">>"};
const QList<QChar> FormulaInterpreter::operatorsChars  = {'+','-','*','/','^','<','=','>','!','%','&','|','~'};
const QList<QChar> FormulaInterpreter::opCharFirstOf2  = {'*','<','>','=','!','&','|'};
const QMap<QString,int> FormulaInterpreter::functions  = {
	{"abs",1},{"pow",2},{"sqrt",1},{"exp",1},{"log",1},{"log10",1},
	{"cos",1},{"sin",1},{"tan",1},{"tan2",2},{"acos",1},{"asin",1},{"atan",1},{"atan2",2}
};


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  DESTRUCTEUR
//  EVAL
//  PREPARE
//  HAS PREPARED
//
//  POSTFIX TO SYNTAXIC TREE
//
//  NORMALIZE FORMULA
//  COMPUTE TOKENS
//  STRING TO TOKEN
//  INFIX TO POSTFIX
//  OPERATOR PRECEDENCE
//  OPERATOR ASSOCIATIVE LEFT
//
//  DEBUG INFIX TOKENS
//  DEBUG POSTFIX TOKENS
//  DEBUG SYNTAXIC TREE
///////////////////////////////////////////////////////////////////////////////


// DESTRUCTEUR ////////////////////////////////////////////////////////////////
FormulaInterpreter::~FormulaInterpreter()
{
	qDeleteAll(m_syntaxicTrees);
}

// EVAL ///////////////////////////////////////////////////////////////////////
Any FormulaInterpreter::eval(const QString &formula, SimuData *sd)
{
	// normalize formula
	QString formula2 = FormulaInterpreter::normalizeFormula(formula);
	
	// prepare the tree if it was not already built
	if (!m_syntaxicTrees.contains(formula2))
	{
		if (!this->prepare(formula2))
			return {};
	}
	
	// compute the formula
	AbstractSyntaxicNode *root = m_syntaxicTrees[formula2];
	if (!root) {return {};}
	return root->eval(sd);
}

// PREPARE ////////////////////////////////////////////////////////////////////
bool FormulaInterpreter::prepare(const QString &formula, QStringList *errors, bool bForce)
{
	// normalize formula and test if it was already prepared
	QString formula2 = FormulaInterpreter::normalizeFormula(formula);
	if (m_syntaxicTrees.contains(formula2) && !bForce) {return true;}
	
	// 1st: we compute the tokens from the formula string, as strings at first
	QStringList tokenStrings;
	try
	{
		tokenStrings = FormulaInterpreter::computeTokens(formula2);
	}
	catch (const ExceptionInterpreter &e)
	{
		if (errors) {*errors << e.text();}
		return false;
	}
	m_debugInfixTokensList[formula2] = tokenStrings;
	
	
	// we convert "string tokens" to "structure tokens"
	QStringList unknownTokens;
	QVector<Token> infixTokens;
	for (const QString &str : tokenStrings)
	{
		Token t = FormulaInterpreter::stringToToken(str);
		if (t.type == TokenType::Unknown) {unknownTokens << str;}
		infixTokens << t;
	}
	if (unknownTokens.size() > 0)
	{
		if (errors) {*errors << QString::number(unknownTokens.size()) + " unknown tokens detected";}
		return false;
	}
	
	
	// 2nd: apply Shunting-Yard algo
	QVector<Token> postfixTokens;
	try
	{
		postfixTokens = FormulaInterpreter::infixToPostfix(infixTokens);
	}
	catch (const ExceptionInterpreter &e)
	{
		if (errors) {*errors << e.text();}
		return false;
	}
	QStringList temp;
	for (const Token &t : postfixTokens) {temp << t.value;}
	m_debugPostfixTokensList[formula2] = temp;
	
	
	// 3rd: build the syntaxic tree
	AbstractSyntaxicNode *root = nullptr;
	try
	{
		root = this->postfixToSyntaxicTree(postfixTokens);
	}
	catch (const ExceptionInterpreter &e)
	{
		if (errors) {*errors << e.text();}
		return false;
	}
	
	// the end
	if (!root) {return false;}
	m_syntaxicTrees.insert(formula2,root);
	return true;
}

// HAS PREPARED ///////////////////////////////////////////////////////////////
bool FormulaInterpreter::hasPrepared(const QString &formula) const
{
	return m_syntaxicTrees.contains(FormulaInterpreter::normalizeFormula(formula));
}






// POSTFIX TO SYNTAXIC TREE ///////////////////////////////////////////////////
AbstractSyntaxicNode* FormulaInterpreter::postfixToSyntaxicTree(QVector<Token> postfixTokens)
{
	// special case
	if (postfixTokens.size() == 0) {return nullptr;}
	
	// init
	SyntaxicNodeFactory factory;
	AbstractSyntaxicNode *root = factory.createNode(postfixTokens.takeLast(),nullptr);
	if (!root) {throw ExceptionInterpreter{"Failed to create root"};}
	AbstractSyntaxicNode *currentNode = root;
	if (currentNode->allChildrenSpecified()) {return root;}
	
	while (!postfixTokens.isEmpty())
	{
		// get the next node that is not full of children
		currentNode = currentNode->getNext();
		if (!currentNode)
		{
			delete root;
			throw ExceptionInterpreter{"Tree is full but there are tokens left"};
		}
		
		// create the new children, append it to current node and make it the new current one if it needs children
		Token t = postfixTokens.takeLast();
		AbstractSyntaxicNode *node = factory.createNode(t,currentNode);
		if (!node)
		{
			delete root;
			throw ExceptionInterpreter{"Impossible to create node: "+t.value};
		}
		currentNode->appendChild(node);
		if (!node->allChildrenSpecified()) {currentNode = node;}
	}
	
	// verify that the tree is valid (no undefined children)
	if (!root->allChildrenSpecifiedRecursive()) {throw ExceptionInterpreter{"Tree is not valid"};}
	return root;
}






// NORMALIZE FORMULA //////////////////////////////////////////////////////////
QString FormulaInterpreter::normalizeFormula(const QString &formula1)
{
	// a few modifications before anything else!
	QString formula2 = formula1;
	formula2.replace(" ","");
	// to avoid to deal with unary minus
	formula2.replace("(-","(0-");
	formula2.replace(",-",",0-");
	if (formula2.startsWith("-")) {formula2 = "0" + formula2;}
	// to avoid to deal with unary plus
	formula2.replace("(+","(0+");
	formula2.replace(",+",",0+");
	if (formula2.startsWith("+")) {formula2 = "0" + formula2;}
	
	return formula2;
}

// COMPUTE TOKENS /////////////////////////////////////////////////////////////
QStringList FormulaInterpreter::computeTokens(const QString &formula)
{
	// just strings calculations to isolate the different tokens in the formula
	if (formula.size() == 0) {return {};}
	if (formula.size() == 1) {return {formula};}
	
	// initialisation and first char verification
	QStringList result;
	int indexStart = 0;
	while (formula[indexStart] == '(')
	{
		result << "(";
		++indexStart;
	}
	
	QString buffer = formula.mid(indexStart,1);
	QChar firstChar = formula[indexStart];
	bool bMaybe1stOf2CharsOp = opCharFirstOf2.contains(firstChar);
	if (!firstChar.isDigit() && !firstChar.isLetter() && firstChar != '(')
		throw ExceptionInterpreter{"First character must be a letter or a digit or a left parenthesis"};
	
	// loop
	for (int index=indexStart+1; index<formula.size(); ++index)
	{
		QChar lastChar = formula[index-1];
		QChar currentChar = formula[index];
		
		if (currentChar == '(' || currentChar == ')' || currentChar == ',')
		{
			if (!buffer.isEmpty())
			{
				result << buffer;
				buffer = "";
			}
			result << currentChar;
			bMaybe1stOf2CharsOp = false;
		}
		else if (currentChar.isLetter())
		{
			if (bMaybe1stOf2CharsOp)
			{
				bMaybe1stOf2CharsOp = false;
				result << lastChar;
				buffer = currentChar;
				continue;
			}
			
			bool bJustAddToBuffer1 = (buffer.isEmpty());
			bool bJustAddToBuffer2 = (!buffer.isEmpty() && buffer.front().isLetter());
			
			if (bJustAddToBuffer1 || bJustAddToBuffer2) {buffer += currentChar;}
			else
			{
				QString msg = "Wrong beginning for token: " + buffer + currentChar;
				throw ExceptionInterpreter{msg};
			}
			bMaybe1stOf2CharsOp = false;
		}
		else if (currentChar.isDigit())
		{
			if (bMaybe1stOf2CharsOp)
			{
				bMaybe1stOf2CharsOp = false;
				result << lastChar;
				buffer = currentChar;
				continue;
			}
			
			buffer += currentChar;
			bMaybe1stOf2CharsOp = false;
		}
		else if (currentChar == ".")
		{
			if (lastChar.isDigit()) {buffer += currentChar;}
			else
			{
				QString msg = "Wrong use of \".\" character";
				throw ExceptionInterpreter{msg};
			}
			bMaybe1stOf2CharsOp = false;
		}
		else if (operatorsChars.contains(currentChar))
		{
			QString temp = QString{lastChar} + currentChar;
			bool b2charOperator = (buffer.size() == 1 && operatorsChars.contains(lastChar));
			bool b2charOperatorOk = (b2charOperator && operatorsString.contains(temp));
			bool b2charOperatorKo = (b2charOperator && !operatorsString.contains(temp));
			bool bMaybeFirstOf2   = (opCharFirstOf2.contains(currentChar));
			
			if (b2charOperatorKo)
			{
				QString msg = "Unknown operator \"" + temp + "\"";
				throw ExceptionInterpreter{msg};
			}
			else if (b2charOperatorOk)
			{
				result << temp;
				buffer = "";
				bMaybe1stOf2CharsOp = false;
			}
			else if (bMaybeFirstOf2)
			{
				if (!buffer.isEmpty())
				{
					result << buffer;
					buffer = "";
				}
				buffer = currentChar;
				bMaybe1stOf2CharsOp = true;
			}
			else
			{
				if (!buffer.isEmpty())
				{
					result << buffer;
					buffer = "";
				}
				result << currentChar;
				bMaybe1stOf2CharsOp = false;
			}
		}
		else
		{
			QString msg = QString{"Character not supported: "} + currentChar;
			throw ExceptionInterpreter{msg};
		}
	}
	
	if (!buffer.isEmpty()) {result << buffer;}
	return result;
}

// STRING TO TOKEN ////////////////////////////////////////////////////////////
Token FormulaInterpreter::stringToToken(const QString &str)
{
	if (isInt(str) || isDouble(str) || isBool(str)) {return Token{str,TokenType::RValue};}
	else if (functions.contains(str))               {return Token{str,TokenType::Function};}
	else if (isParamName(str))                      {return Token{str,TokenType::LValue};}
	else if (operatorsString.contains(str))         {return Token{str,TokenType::Operator};}
	else if (str == "(")                            {return Token{str,TokenType::LeftParenthesis};}
	else if (str == ")")                            {return Token{str,TokenType::RightParenthesis};}
	else if (str == ",")                            {return Token{str,TokenType::ArgumentSeparator};}
	return Token{str,TokenType::Unknown};
}

// INFIX TO POSTFIX ///////////////////////////////////////////////////////////
QVector<Token> FormulaInterpreter::infixToPostfix(QVector<Token> infix)
{
	QStack<Token> stack;
	QVector<Token> output;
	QStack<int> nbArguments;
	
	// shunting-yard algorithm
	while (!infix.isEmpty())
	{
		Token current = infix.takeFirst();
		if (current.type == TokenType::LValue || current.type == TokenType::RValue)
		{
			output << current;
			if (!nbArguments.isEmpty() && nbArguments.top() == 0) {nbArguments.top() = 1;}
		}
		else if (current.type == TokenType::Function)
		{
			stack.push(current);
			if (!nbArguments.isEmpty() && nbArguments.top() == 0) {nbArguments.top() = 1;}
			nbArguments.push(0);
		}
		else if (current.type == TokenType::ArgumentSeparator)
		{
			if (stack.isEmpty()) {throw ExceptionInterpreter{"Wrong parenthesing"};}
			if (nbArguments.isEmpty()) {throw ExceptionInterpreter{"Use of argument separator , but there is no function name before"};}
			nbArguments.top()++;
			while (stack.top().type != TokenType::LeftParenthesis)
			{
				output << stack.pop();
				if (stack.isEmpty()) {throw ExceptionInterpreter{"Wrong parenthesing"};}
			}
		}
		else if (current.type == TokenType::Operator)
		{
			if (stack.isEmpty()) {stack.push(current); continue;}
			while (true)
			{
				Token &top = stack.top();
				bool b1 = (top.type != TokenType::LeftParenthesis);
				bool b2a = (top.type == TokenType::Function);
				bool b2b = (top.type == TokenType::Operator && operatorPrecedence(top.value) < operatorPrecedence(current.value));
				bool b2c = (top.type == TokenType::Operator && operatorPrecedence(top.value) == operatorPrecedence(current.value) && operatorAssociativeLeft(top.value));
				bool bContinue = (b1 && (b2a || b2b || b2c));
				
				if (!bContinue) {break;}
				output << stack.pop();
				if (stack.isEmpty()) {break;}
			}
			stack.push(current);
			if (!nbArguments.isEmpty() && nbArguments.top() == 0) {nbArguments.top() = 1;}
		}
		else if (current.type == TokenType::LeftParenthesis)
		{
			stack.push(current);
		}
		else if (current.type == TokenType::RightParenthesis)
		{
			if (stack.isEmpty()) {throw ExceptionInterpreter{"Wrong parenthesing"};}
			while (stack.top().type != TokenType::LeftParenthesis)
			{
				output << stack.pop();
				if (stack.isEmpty()) {throw ExceptionInterpreter{"Wrong parenthesing"};}
			}
			stack.pop(); // we remove the left parenthesis
			if (!stack.isEmpty() && stack.top().type == TokenType::Function)
			{
				Token fct = stack.pop();
				output << fct;
				QString fctName = fct.value;
				if (!functions.contains(fctName)) {throw ExceptionInterpreter{"Unknown function: "+fctName};}
				int nArgsFctEff = nbArguments.pop();
				int nArgsFctReq = functions[fctName];
				if (nArgsFctEff != nArgsFctReq)
				{
					QString msg = "Function " + fctName + ": " + QString::number(nArgsFctEff) + " args provided, " + QString::number(nArgsFctReq) + " expected";
					throw ExceptionInterpreter{msg};
				}
			}
		}
	}
	
	// stack to output
	while (!stack.isEmpty())
	{
		Token t = stack.pop();
		if (t.type == TokenType::LeftParenthesis || t.type == TokenType::LeftParenthesis) {throw ExceptionInterpreter{"Wrong parenthesing"};}
		output << t;
	}
	return output;
}

// OPERATOR PRECEDENCE ////////////////////////////////////////////////////////
int FormulaInterpreter::operatorPrecedence(const QString &opStr)
{
	if (opStr == "!" || opStr == "~") {return 3;}
	else if (opStr == "**") {return 4;} // puissance
	else if (opStr == "*" || opStr == "/" || opStr == "%") {return 5;}
	else if (opStr == "+" || opStr == "-") {return 6;}
	else if (opStr == "<<" || opStr == ">>") {return 7;}
	else if (opStr == "<" || opStr == "<=" || opStr == ">" || opStr == ">=") {return 8;}
	else if (opStr == "==" || opStr == "!=") {return 9;}
	else if (opStr == "&") {return 10;}
	else if (opStr == "^") {return 10;} // xor binaire, pas puissance
	else if (opStr == "|") {return 12;}
	else if (opStr == "&&") {return 13;}
	else if (opStr == "||") {return 14;}
	
	return 0;
}

// OPERATOR ASSOCIATIVE LEFT //////////////////////////////////////////////////
bool FormulaInterpreter::operatorAssociativeLeft(const QString &opStr)
{
	if (opStr == "!" || opStr == "~") {return false;} // (unary + and - are transformed into binary ones by adding 0)
	return true;
}






// DEBUG INFIX TOKENS /////////////////////////////////////////////////////////
QStringList FormulaInterpreter::debugInfixTokens(const QString &formula)
{
	QString formula2 = FormulaInterpreter::normalizeFormula(formula);
	if (!m_debugInfixTokensList.contains(formula2)) {return {};}
	return m_debugInfixTokensList[formula2];
}

// DEBUG POSTFIX TOKENS ///////////////////////////////////////////////////////
QStringList FormulaInterpreter::debugPostfixTokens(const QString &formula)
{
	QString formula2 = FormulaInterpreter::normalizeFormula(formula);
	if (!m_debugPostfixTokensList.contains(formula2)) {return {};}
	return m_debugPostfixTokensList[formula2];
}

// DEBUG SYNTAXIC TREE ////////////////////////////////////////////////////////
QString FormulaInterpreter::debugSyntaxicTree(const QString &formula)
{
	QString formula2 = FormulaInterpreter::normalizeFormula(formula);
	if (!m_syntaxicTrees.contains(formula2)) {return {};}
	AbstractSyntaxicNode *root = m_syntaxicTrees[formula2];
	if (!root) {return {};}
	return root->toString();
}


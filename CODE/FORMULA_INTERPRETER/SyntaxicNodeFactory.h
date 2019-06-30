#ifndef SYNTAXIC_NODE_FACTORY
#define SYNTAXIC_NODE_FACTORY


#include "Token.h"
class AbstractSyntaxicNode;


class SyntaxicNodeFactory
{
	public:
		SyntaxicNodeFactory() = default;
		SyntaxicNodeFactory(const SyntaxicNodeFactory &other) = delete;
		SyntaxicNodeFactory(SyntaxicNodeFactory &&other) = delete;
		SyntaxicNodeFactory& operator=(const SyntaxicNodeFactory &other) = delete;
		SyntaxicNodeFactory& operator=(SyntaxicNodeFactory &&other) = delete;
		virtual ~SyntaxicNodeFactory() = default;
		
		AbstractSyntaxicNode* createNode(const Token &t, AbstractSyntaxicNode *parent);
		
		
	private:
		AbstractSyntaxicNode* createFunction(const QString &fctName, AbstractSyntaxicNode *parent);
		AbstractSyntaxicNode* createOperator(const QString &op, AbstractSyntaxicNode *parent);
};


#endif


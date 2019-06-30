#ifndef SYNTAXIC_NODE_RVALUE
#define SYNTAXIC_NODE_RVALUE


#include "AbstractSyntaxicNode.h"


class SyntaxicNodeRValue : public AbstractSyntaxicNode
{
	public:
		SyntaxicNodeRValue(const QString &rValueStr, AbstractSyntaxicNode *parent = nullptr);
		SyntaxicNodeRValue(const SyntaxicNodeRValue &other) = delete;
		SyntaxicNodeRValue(SyntaxicNodeRValue &&other) = delete;
		SyntaxicNodeRValue& operator=(const SyntaxicNodeRValue &other) = delete;
		SyntaxicNodeRValue& operator=(SyntaxicNodeRValue &&other) = delete;
		virtual ~SyntaxicNodeRValue() = default;
		
		virtual Any eval(const SimuData &sd) const override final;
		virtual QString toStringHelper(int offset) const override final;
		
		
	private:
		Any m_rValue;
};


#endif


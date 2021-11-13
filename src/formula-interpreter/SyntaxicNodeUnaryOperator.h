#ifndef SYNTAXIC_NODE_UNARY_OPERATOR
#define SYNTAXIC_NODE_UNARY_OPERATOR


#include "AbstractSyntaxicNode.h"
#include "../data-and-operators/UnaryOperator.h"


class SyntaxicNodeUnaryOperator : public AbstractSyntaxicNode
{
	public:
		SyntaxicNodeUnaryOperator(const UnaryOperator &uo, AbstractSyntaxicNode *parent = nullptr);
		SyntaxicNodeUnaryOperator(const SyntaxicNodeUnaryOperator &other) = delete;
		SyntaxicNodeUnaryOperator(SyntaxicNodeUnaryOperator &&other) = delete;
		SyntaxicNodeUnaryOperator& operator=(const SyntaxicNodeUnaryOperator &other) = delete;
		SyntaxicNodeUnaryOperator& operator=(SyntaxicNodeUnaryOperator &&other) = delete;
		virtual ~SyntaxicNodeUnaryOperator() = default;
		
		virtual Any eval(WorkspaceData *sd) const override final;
		virtual QString toStringHelper(int offset) const override final;
		
		
	private:
		UnaryOperator m_uo;
};


#endif


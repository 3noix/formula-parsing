#ifndef SYNTAXIC_NODE_BINARY_OPERATOR
#define SYNTAXIC_NODE_BINARY_OPERATOR


#include "AbstractSyntaxicNode.h"
#include "../DATA_AND_OPERATORS/BinaryOperator.h"


class SyntaxicNodeBinaryOperator : public AbstractSyntaxicNode
{
	public:
		SyntaxicNodeBinaryOperator(const BinaryOperator &bo, AbstractSyntaxicNode *parent = nullptr);
		SyntaxicNodeBinaryOperator(const SyntaxicNodeBinaryOperator &other) = delete;
		SyntaxicNodeBinaryOperator(SyntaxicNodeBinaryOperator &&other) = delete;
		SyntaxicNodeBinaryOperator& operator=(const SyntaxicNodeBinaryOperator &other) = delete;
		SyntaxicNodeBinaryOperator& operator=(SyntaxicNodeBinaryOperator &&other) = delete;
		virtual ~SyntaxicNodeBinaryOperator() = default;
		
		virtual Any eval(SimuData *sd) const override final;
		virtual QString toStringHelper(int offset) const override final;
		
		
	private:
		BinaryOperator m_bo;
};


#endif


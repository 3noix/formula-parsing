#ifndef SYNTAXIC_NODE_LVALUE
#define SYNTAXIC_NODE_LVALUE


#include "AbstractSyntaxicNode.h"


class SyntaxicNodeLValue : public AbstractSyntaxicNode
{
	public:
		SyntaxicNodeLValue(const QString &varName, AbstractSyntaxicNode *parent = nullptr);
		SyntaxicNodeLValue(const SyntaxicNodeLValue &other) = delete;
		SyntaxicNodeLValue(SyntaxicNodeLValue &&other) = delete;
		SyntaxicNodeLValue& operator=(const SyntaxicNodeLValue &other) = delete;
		SyntaxicNodeLValue& operator=(SyntaxicNodeLValue &&other) = delete;
		virtual ~SyntaxicNodeLValue() = default;
		
		virtual Any eval(WorkspaceData *sd) const override final;
		virtual QString toStringHelper(int offset) const override final;
		
		
	private:
		QString m_varName;
};


#endif


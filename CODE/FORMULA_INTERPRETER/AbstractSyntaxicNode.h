#ifndef ABSTRACT_SYNTAXIC_NODE
#define ABSTRACT_SYNTAXIC_NODE


#include "../DATA_AND_OPERATORS/ProjectData.h"
#include <QVector>


class AbstractSyntaxicNode
{
	public:
		AbstractSyntaxicNode(int nbChildren, AbstractSyntaxicNode *parent);
		AbstractSyntaxicNode(const AbstractSyntaxicNode &other) = delete;
		AbstractSyntaxicNode(AbstractSyntaxicNode &&other) = delete;
		AbstractSyntaxicNode& operator=(const AbstractSyntaxicNode &other) = delete;
		AbstractSyntaxicNode& operator=(AbstractSyntaxicNode &&other) = delete;
		virtual ~AbstractSyntaxicNode();
		
		virtual Any eval(SimuData *sd) const = 0;
		virtual QString toStringHelper(int offset) const = 0;
		
		AbstractSyntaxicNode* parent() const;
		bool appendChild(AbstractSyntaxicNode *child);
		bool allChildrenSpecified() const;
		bool allChildrenSpecifiedRecursive() const;
		AbstractSyntaxicNode* getNext();
		
		QString toString() const;
		
		
	protected:
		QVector<AbstractSyntaxicNode*> m_children;
		int m_nbExpectedChildren;
		
		
	private:
		AbstractSyntaxicNode *m_parent;
};


#endif


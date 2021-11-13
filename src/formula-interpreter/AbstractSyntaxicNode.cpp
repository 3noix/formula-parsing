#include "AbstractSyntaxicNode.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR ET DESTRUCTEUR
//
//  PARENT
//  APPEND CHILD
//  ALL CHILDREN SPECIFIED
//  GET NEXT
//  TO STRING
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
AbstractSyntaxicNode::AbstractSyntaxicNode(int nbChildren, AbstractSyntaxicNode *parent) : m_parent{parent}
{
	m_nbExpectedChildren = nbChildren;
}

AbstractSyntaxicNode::~AbstractSyntaxicNode()
{
	qDeleteAll(m_children);
}




// PARENT /////////////////////////////////////////////////////////////////////
AbstractSyntaxicNode* AbstractSyntaxicNode::parent() const
{
	return m_parent;
}

// APPEND CHILD ///////////////////////////////////////////////////////////////
bool AbstractSyntaxicNode::appendChild(AbstractSyntaxicNode *child)
{
	if (!child) {return false;}
	if (m_children.size() >= m_nbExpectedChildren) {return false;}
	m_children << child;
	return true;
}

// ALL CHILDREN SPECIFIED /////////////////////////////////////////////////////
bool AbstractSyntaxicNode::allChildrenSpecified() const
{
	return (m_children.size() >= m_nbExpectedChildren);
}

// ALL CHILDREN SPECIFIED RECURSIVE ///////////////////////////////////////////
bool AbstractSyntaxicNode::allChildrenSpecifiedRecursive() const
{
	if (!this->allChildrenSpecified()) {return false;}
	for (AbstractSyntaxicNode *child : m_children)
	{
		if (!child->allChildrenSpecifiedRecursive())
		{return false;}
	}
	
	return true;
}

// GET NEXT ///////////////////////////////////////////////////////////////////
AbstractSyntaxicNode* AbstractSyntaxicNode::getNext()
{
	AbstractSyntaxicNode *n = this;
	while (n->allChildrenSpecified())
	{
		n = n->parent();
		if (!n) {return nullptr;}
	}
	return n;
}

// TO STRING //////////////////////////////////////////////////////////////////
QString AbstractSyntaxicNode::toString() const
{
	return this->toStringHelper(0);
}


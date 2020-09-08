#include "WorkspaceData.h"
#include "../otherFunctions.h"


// TO STRING //////////////////////////////////////////////////////////////////
QString toString(const Any &a)
{
	if (isa<bool>(a))         {return (convertTo<bool>(a) ? "true" : "false");}
	else if (isa<int>(a))     {return QString::number(convertTo<int>(a));}
	else if (isa<double>(a))  {return QString::number(convertTo<double>(a));}
	else if (isa<QString>(a)) {return convertTo<QString>(a);}
	else {return {};}
}




// WORKSPACE DATA /////////////////////////////////////////////////////////////
void WorkspaceData::clear()
{
	m_map.clear();
}

int WorkspaceData::nbParameters() const 
{
	return m_map.size();
}

QStringList WorkspaceData::parameters() const
{
	return m_map.keys();
}

bool WorkspaceData::hasParameter(const QString &param) const
{
	return m_map.contains(param);
}

Any& WorkspaceData::operator[](const QString &param)
{
	return m_map[param];
}

const Any WorkspaceData::operator[](const QString &param) const
{
	return m_map[param];
}

void WorkspaceData::addParameter(const QString &param, const Any &data)
{
	m_map.insert(param,data);
}

bool WorkspaceData::removeParameter(const QString &param)
{
	if (!m_map.contains(param)) {return false;}
	m_map.remove(param);
	return true;
}


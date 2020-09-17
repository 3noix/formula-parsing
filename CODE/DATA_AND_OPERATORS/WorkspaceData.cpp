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
	QStringList params;
	for (auto pair : m_map) {params << pair.first;}
	return params;
}

bool WorkspaceData::hasParameter(const QString &param) const
{
	return m_map.count(param) > 0;
}

Any& WorkspaceData::operator[](const QString &param)
{
	return m_map[param];
}

const Any& WorkspaceData::operator[](const QString &param) const
{
	return m_map.at(param);
}

bool WorkspaceData::removeParameter(const QString &param)
{
	return m_map.erase(param) > 0;
}


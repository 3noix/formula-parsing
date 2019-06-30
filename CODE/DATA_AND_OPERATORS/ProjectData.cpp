#include "ProjectData.h"
//#include "VectorsOperators.h"
#include "../otherFunctions.h"


///////////////////////////////////////////////////////////////////////////////
//  LENGTH
//  TO STRING
//
//  SIMU DATA
//  RECORD
//  PROJECT DATA
///////////////////////////////////////////////////////////////////////////////


// LENGTH /////////////////////////////////////////////////////////////////////
int length(const Any &a)
{
	if (isa<bool>(a))         {return 1;}
	else if (isa<int>(a))     {return 1;}
	else if (isa<double>(a))  {return 1;}
	else if (isa<QString>(a)) {return 1;}
	else if (isa<QVector<bool>>(a))   {return convertTo<QVector<bool>>(a).size();}
	else if (isa<QVector<int>>(a))    {return convertTo<QVector<int>>(a).size();}
	else if (isa<QVector<double>>(a)) {return convertTo<QVector<double>>(a).size();}
	else if (isa<QStringList>(a))     {return convertTo<QStringList>(a).size();}
	else {return -1;}
}

// TO STRING //////////////////////////////////////////////////////////////////
QString toString(const Any &a)
{
	if (isa<bool>(a))         {return (convertTo<bool>(a) ? "true" : "false");}
	else if (isa<int>(a))     {return QString::number(convertTo<int>(a));}
	else if (isa<double>(a))  {return QString::number(convertTo<double>(a));}
	else if (isa<QString>(a)) {return convertTo<QString>(a);}
	else {return {};}
}




// SIMU DATA //////////////////////////////////////////////////////////////////
void SimuData::clear()
{
	m_map.clear();
}

int SimuData::nbParameters() const 
{
	return m_map.size();
}

QStringList SimuData::parameters() const
{
	return m_map.keys();
}

bool SimuData::hasParameter(const QString &param) const
{
	return m_map.contains(param);
}

Any& SimuData::operator[](const QString &param)
{
	return m_map[param];
}

const Any SimuData::operator[](const QString &param) const
{
	return m_map[param];
}

void SimuData::addParameter(const QString &param, const Any &data)
{
	m_map.insert(param,data);
}

bool SimuData::removeParameter(const QString &param)
{
	if (!m_map.contains(param)) {return false;}
	m_map.remove(param);
	return true;
}

int SimuData::getNbpas() const
{
	if (this->hasParameter("time"))       {return convertTo<QVector<double>>(m_map["time"]).size();}
	else if (this->hasParameter("TIME"))  {return convertTo<QVector<double>>(m_map["TIME"]).size();}
	else if (this->hasParameter("temps")) {return convertTo<QVector<double>>(m_map["temps"]).size();}
	else if (this->hasParameter("TEMPS")) {return convertTo<QVector<double>>(m_map["TEMPS"]).size();}
	else {return 0;}
}






// RECORD /////////////////////////////////////////////////////////////////////
Record::Record(const QString &recordName) : m_name{recordName}
{
}

Record::~Record()
{
	qDeleteAll(m_data);
	m_data.clear();
}

QString Record::recordName() const
{
	return m_name;
}

int Record::nbSimus() const
{
	return m_data.size();
}

SimuData& Record::operator[](int i)
{
	return *(m_data.at(i));
}

const SimuData& Record::operator[](int i) const
{
	return *(m_data.at(i));
}

void Record::operator<<(SimuData *sd)
{
	m_data << sd;
}

void Record::appendSimu(SimuData *sd)
{
	m_data << sd;
}

bool Record::removeRecord(int i)
{
	if (i < 0 || i >= m_data.size()) {return false;}
	delete m_data.takeAt(i);
	return true;
}

Record* Record::mergeRecords(Record *rec1, Record *rec2, const QString &name)
{
	Record *rec = new Record{name};
	rec->m_data << rec1->m_data << rec2->m_data;
	rec1->m_data.clear();
	rec2->m_data.clear();
	delete rec1;
	delete rec2;
	rec1 = nullptr;
	rec2 = nullptr;
	return rec;
}






// PROJECT DATA ///////////////////////////////////////////////////////////////
ProjectData::~ProjectData()
{
	this->clear();
}

void ProjectData::clear()
{
	qDeleteAll(m_recordedData);
	m_recordedData.clear();
}

SimuData& ProjectData::commonData()
{
	return m_commonData;
}

const SimuData& ProjectData::commonData() const
{
	return m_commonData;
}

int ProjectData::nbRecords() const
{
	return m_recordedData.size();
}

Record& ProjectData::operator[](int i)
{
	return *(m_recordedData.at(i));
}

const Record& ProjectData::operator[](int i) const
{
	return *(m_recordedData.at(i));
}

void ProjectData::operator<<(Record *newRec)
{
	m_recordedData << newRec;
}

void ProjectData::appendRecord(Record *newRec)
{
	m_recordedData << newRec;
}

bool ProjectData::removeRecord(int i)
{
	if (i < 0 || i >= m_recordedData.size()) {return false;}
	delete m_recordedData.takeAt(i);
	return true;
}

QString ProjectData::projectDirPath() const
{
	if (!m_commonData.hasParameter("projectFilePath")) {return {};}
	return dirName(convertTo<QString>(m_commonData["projectFilePath"]));
}


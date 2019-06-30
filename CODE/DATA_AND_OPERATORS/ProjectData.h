#ifndef PROJECT_DATA
#define PROJECT_DATA


#include <QVector>
#include <QMap>
#include <QString>
#include <boost/any.hpp>
using Any = boost::any;


// ISA ////////////////////////////////////////////////////////////////////////
template <typename T>
bool isa(const Any &a)
{
	return boost::any_cast<T>(&a);
};


// CONVERT TO /////////////////////////////////////////////////////////////////
template <typename T>
T convertTo(const Any &a, bool *ok = nullptr)
{
	try
	{
		T t = boost::any_cast<T>(a);
		if (ok) {*ok = true;}
		return t;
	}
	catch (const boost::bad_any_cast &)
	{
		if (ok) {*ok = false;}
		return T{};
	}
};


int length(const Any &a);
QString toString(const Any &a);


class SimuData
{
	public:
		SimuData()= default;
		SimuData(const SimuData &other) = delete;
		SimuData(SimuData &&other) = default;
		SimuData& operator=(const SimuData &other) = delete;
		SimuData& operator=(SimuData &&other) = default;
		~SimuData() = default;
		
		void clear();
		int getNbpas() const;
		
		int nbParameters() const;
		QStringList parameters() const;
		bool hasParameter(const QString &param) const;
		Any& operator[](const QString &param);
		const Any operator[](const QString &param) const;
		void addParameter(const QString &param, const Any &data);
		bool removeParameter(const QString &param);
		
		
	private:
		QMap<QString,Any> m_map;
};


class Record
{
	public:
		Record(const QString &recordName);
		Record(const Record &other) = delete;
		Record(Record &&other) = default;
		Record& operator=(const Record &other) = delete;
		Record& operator=(Record &&other) = default;
		~Record();
		
		QString recordName() const;
		
		int nbSimus() const;
		SimuData& operator[](int i);
		const SimuData& operator[](int i) const;
		void operator<<(SimuData *sd);
		void appendSimu(SimuData *sd);
		bool removeRecord(int i);
		
		static Record* mergeRecords(Record *rec1, Record *rec2, const QString &name);
		
		
	private:
		QString m_name;
		QVector<SimuData*> m_data;
};


class ProjectData
{
	public:
		ProjectData() = default;
		ProjectData(const ProjectData &other) = delete;
		ProjectData(ProjectData &&other) = delete;
		ProjectData& operator=(const ProjectData &other) = delete;
		ProjectData& operator=(ProjectData &&other) = delete;
		~ProjectData();
		
		void clear();
		
		SimuData& commonData();
		const SimuData& commonData() const;
		
		int nbRecords() const;
		Record& operator[](int i);
		const Record& operator[](int i) const;
		void operator<<(Record *newRec);
		void appendRecord(Record *newRec);
		
		bool removeRecord(int i);
		
		QString projectDirPath() const;
		
		
	private:
		SimuData m_commonData;
		QVector<Record*> m_recordedData;
};


#endif


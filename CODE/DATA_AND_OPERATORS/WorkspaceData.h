#ifndef WORKSPACE_DATA
#define WORKSPACE_DATA


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


QString toString(const Any &a);


class WorkspaceData
{
	public:
		WorkspaceData()= default;
		WorkspaceData(const WorkspaceData &other) = delete;
		WorkspaceData(WorkspaceData &&other) = default;
		WorkspaceData& operator=(const WorkspaceData &other) = delete;
		WorkspaceData& operator=(WorkspaceData &&other) = default;
		~WorkspaceData() = default;
		
		void clear();
		
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


#endif


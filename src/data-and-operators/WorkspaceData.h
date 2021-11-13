#ifndef WORKSPACE_DATA
#define WORKSPACE_DATA


#include <map>
#include <QString>
#include <any>
using Any = std::any;


// ISA ////////////////////////////////////////////////////////////////////////
template <typename T>
bool isa(const Any &a)
{
	return std::any_cast<T>(&a);
};


// CONVERT TO /////////////////////////////////////////////////////////////////
template <typename T>
T convertTo(const Any &a, bool *ok = nullptr)
{
	try
	{
		T t = std::any_cast<T>(a);
		if (ok) {*ok = true;}
		return t;
	}
	catch (const std::bad_any_cast &)
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
		const Any& operator[](const QString &param) const;
		bool removeParameter(const QString &param);
		
		
	private:
		std::map<QString,Any> m_map;
};


#endif


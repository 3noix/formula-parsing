#ifndef OTHER_FUNCTIONS
#define OTHER_FUNCTIONS


#include <QString>
#include <QList>


bool isDebug();
bool isRelease();
QString debugOrRelease();

QString shortName(QString longName);
QString dirName(QString longName);

QString absolute2relative(QString refPath, QString absPath);
QString relative2absolute(QString refPath, QString relPath);



// REMOVE DUPLICATES //////////////////////////////////////////////////////////
template <typename T> void removeDuplicates(QList<T> &list)
{
	int nbElements = list.size();
	for (int i=nbElements-1; i>0; --i)
	{
		if (list[i] == list[i-1])
		{list.removeAt(i);}
	}
};


#endif


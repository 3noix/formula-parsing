#include "otherFunctions.h"
#include <QCoreApplication>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  IS DEBUG
//  IS RELEASE
//  DEBUG OR RELEASE
//
//  SHORT NAME
//  DIR NAME
//
//  ABSOLUTE TO RELATIVE
//  RELATIVE TO ABSOLUTE
//  COMPUTE PATH
///////////////////////////////////////////////////////////////////////////////


// IS DEBUG ///////////////////////////////////////////////////////////////////
bool isDebug()
{
	QString path = QCoreApplication::applicationDirPath();
	bool b = (path.endsWith("/debug") || path.endsWith("/debug/"));
	return b;
}

// IS RELEASE /////////////////////////////////////////////////////////////////
bool isRelease()
{
	QString path = QCoreApplication::applicationDirPath();
	bool b = (path.endsWith("/release") || path.endsWith("/release/"));
	return b;
}

// DEBUG OR RELEASE ///////////////////////////////////////////////////////////
QString debugOrRelease()
{
	QStringList list = QCoreApplication::applicationDirPath().split('/',QString::SkipEmptyParts);
	if (list.size() == 0) {return "release";}
	
	QString s = list.last();
	if (s == "debug") {return "debug";}
	return "release";
}




// SHORT NAME /////////////////////////////////////////////////////////////////
QString shortName(QString path)
{
	path = path.replace('\\','/');
	QStringList list = path.split('/',QString::SkipEmptyParts);
	if (list.size() == 0) {return {};}
	return list.last();
}

// DIR NAME ///////////////////////////////////////////////////////////////////
QString dirName(QString path)
{
	path = path.replace('\\','/');
	QStringList list = path.split('/',QString::SkipEmptyParts);
	if (list.size() == 0) {return {};}
	list.removeLast();
	return list.join("/");
}




// ABSOLUTE TO RELATIVE ///////////////////////////////////////////////////////
QString absolute2relative(QString refPath, QString absPath)
{
	refPath.replace('\\','/');
	absPath.replace('\\','/');
	
	if (!absPath.startsWith('/') && !absPath.contains(':'))
	{
		// in fact "absPath" must be a relative path
		return absPath;
	}
	
	bool bDoubleSlashRef = refPath.startsWith("//");
	bool bDoubleSlashAbs = absPath.startsWith("//");
	if (bDoubleSlashRef != bDoubleSlashAbs)
	{
		// one is a windows UNC path and the other a Unix absolute path
		return absPath;
	}
	
	QStringList refList = refPath.split('/',QString::SkipEmptyParts);
	QStringList absList = absPath.split('/',QString::SkipEmptyParts);
	if (bDoubleSlashRef && bDoubleSlashAbs && refList[0] != absList[0])
	{
		// both are windows UNC paths but not from the same root
		return absPath;
	}
	
	int n = qMin(refList.size(),absList.size());
	int indexDiff = n;
	for (int i=0; i<n; ++i)
	{
		if (refList[i] != absList[i])
		{
			indexDiff = i;
			break;
		}
	}
	
	QString longerCommonPath;
	for (int i=0; i<indexDiff; ++i) {longerCommonPath += refList[i] + "/";}
	longerCommonPath.resize(longerCommonPath.size()-1);
	if (bDoubleSlashRef) {longerCommonPath = "/" + longerCommonPath;}
	
	int stepsBackwards = refList.size() - indexDiff;
	QString relPath = "$PROJECT_DIR";
	for (int i=0; i<stepsBackwards; ++i) {relPath += "/..";}
	relPath += absPath.replace(longerCommonPath,"");
	
	return relPath;
}

// RELATIVE TO ABSOLUTE ///////////////////////////////////////////////////////
QString relative2absolute(QString refPath, QString relPath)
{
	refPath.replace('\\','/');
	relPath.replace('\\','/');
	
	if (relPath.startsWith('/') || relPath.contains(':'))
	{
		// in fact "relPath" must be an absolute path
		return relPath;
	}
	else if (relPath.startsWith("$PROJECT_DIR/"))
	{
		return refPath + "/" + relPath.mid(13);
	}
	else if (relPath.startsWith("./"))
	{
		return refPath + "/" + relPath.mid(2);
	}
	else
	{
		return refPath + "/" + relPath;
	}
}

// COMPUTE PATH ///////////////////////////////////////////////////////////////
QString computePath(const ProjectData &data, QString path, bool bAbsolute)
{
	if (bAbsolute) {return path;}
	return path.replace("$PROJECT_DIR",data.projectDirPath());
}


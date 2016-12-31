#include "FinderImpl.h"
#include <QDir>
FinderImpl::FinderImpl(QObject *parent)
	: QObject(parent)
{

}

FinderImpl::~FinderImpl()
{

}

void FinderImpl::getAllFiles( std::string sRoot, std::list<Info>& lstNames )
{
    findFiles(sRoot, lstNames);
}

void FinderImpl::findFiles( std::string sRoot, std::list<Info>& lstNames)
{
	QDir oDir(sRoot.c_str());
	QStringList ofilters ;


	QFileInfoList ofileInfo = oDir.entryInfoList(ofilters, QDir::Files);
	Q_FOREACH(QFileInfo ofileInf , ofileInfo)
	{
        std::string sfileName = qPrintable(ofileInf.fileName());
		std::string spath = qPrintable(ofileInf.absoluteFilePath());
		Info oinfo(sfileName , spath, sRoot);
		lstNames.push_back(oinfo);
	}
	QFileInfoList ochildDirs = oDir.entryInfoList( QDir::AllDirs);
	int i = 0;
	Q_FOREACH(QFileInfo ofileInf ,ochildDirs)
	{
		if(i == 0 || i == 1)
		{
			i++;
			continue;
		}
		i++;
		std::string sdirName = qPrintable(ofileInf.absoluteFilePath());
	

        findFiles(sdirName, lstNames);
	}
}

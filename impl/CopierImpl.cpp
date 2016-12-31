/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 by Kanishka Weerasekara                          *
 *                                                                         *
 *   kkgweerasekara@gmail.com                                              *
 *                                                                         *
 ***************************************************************************/
#include "CopierImpl.h"
#include <QFile>
#include <QDir>
CopierImpl::CopierImpl()
{

}
void CopierImpl::copy(QString sroot, std::list<Info> &lstNames, ProgressCallback *pprogress)
{
    int i = 0;
    for(Info info : lstNames)
    {
        pprogress->onUpdate(++i);
        pprogress->onUpdate(info.s_name);
        QFile file(info.s_path.c_str());
        QString sdestinationPath = sroot + QString(QDir::separator()) + info.s_name.c_str();
        file.copy(sdestinationPath);
    }
}

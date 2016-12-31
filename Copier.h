/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 by Kanishka Weerasekara                          *
 *                                                                         *
 *   kkgweerasekara@gmail.com                                              *
 *                                                                         *
 ***************************************************************************/
#ifndef COPIER_H
#define COPIER_H

#include <Common.h>
#include <QString>
#include <list>
class Copier
{
public:
    virtual ~Copier(){}

    virtual void copy(QString sroot, std::list<Info>& lstNames, ProgressCallback* pprogress) = 0;
};

#endif // COPIER_H

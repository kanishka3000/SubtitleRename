/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 by Kanishka Weerasekara                          *
 *                                                                         *
 *   kkgweerasekara@gmail.com                                              *
 *                                                                         *
 ***************************************************************************/
#ifndef COPIERIMPL_H
#define COPIERIMPL_H
#include <Copier.h>
#include <list>
class CopierImpl: public Copier
{
public:
    CopierImpl();

    // Copier interface
public:
    void copy(QString sroot, std::list<Info> &lstNames, ProgressCallback* pprogress) override;
};

#endif // COPIERIMPL_H

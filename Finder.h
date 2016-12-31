#pragma once

#include <list>
#include <string>
#include <Common.h>
class Finder
{
public:

    virtual void getAllFiles(std::string sRoot, std::list<Info>& lstNames) = 0;
};

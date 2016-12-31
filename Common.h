/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2016 by Kanishka Weerasekara                          *
 *                                                                         *
 *   kkgweerasekara@gmail.com                                              *
 *                                                                         *
 ***************************************************************************/
#ifndef COMMON_H
#define COMMON_H
#include <string>

#define SOURCE_PATH  "sourcepath"
#define DEST_PATH  "destpath"

class Info
{
public:
    Info(std::string name, std::string path, std::string dir):
      s_name(name), s_path(path), s_dir(dir){}
    std::string s_name;
    std::string s_path ;
    std::string s_dir;
};
class ProgressCallback
{
public:
    virtual void onUpdate(int iprogress) = 0;
    virtual void onUpdate(std::string supdate) = 0;
};

#endif // COMMON_H

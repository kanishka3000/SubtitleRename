#include "stdafx.h"
#include <Subrename.h>
#include <impl/CopierImpl.h>
#include <impl/FinderImpl.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SubRename oRename;
    CopierImpl copier;
    FinderImpl finder(&oRename);
    oRename.init(&finder, &copier);
	oRename.show();
	
	return a.exec();
}

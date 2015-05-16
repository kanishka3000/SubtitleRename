#include "stdafx.h"
#include <Subrename.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SubRename oRename;
	oRename.show();
	
	return a.exec();
}
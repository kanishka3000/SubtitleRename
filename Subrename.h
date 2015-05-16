#ifndef SUBRENAME_H
#define SUBRENAME_H
#include<QFileDialog>
#include <QtWidgets/QMainWindow>
#include "ui_Subrename.h"
#include <QFileSystemModel>
class SubRename : public QMainWindow
{
	Q_OBJECT

public:
	SubRename(QWidget *parent = 0);
	~SubRename();
	public slots:
		void OnButtonClick();
		void OnRename();
private:
	Ui::SubRenameClass ui;
	QFileSystemModel oModel;
	QFileDialog oDialog;
	QString s_Dir;
};

#endif // SUBRENAME_H

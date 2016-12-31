#ifndef SUBRENAME_H
#define SUBRENAME_H
#include<QFileDialog>
#include <QtWidgets/QMainWindow>
#include "ui_Subrename.h"
#include <QFileSystemModel>
#include <Copier.h>
#include <Finder.h>
class SubRename : public QMainWindow, public ProgressCallback
{
	Q_OBJECT

public:
	SubRename(QWidget *parent = 0);
    void init(Finder* pfinder, Copier* pcopier);
	~SubRename();
	public slots:
		void OnButtonClick();
		void OnRename();
        void onSource();
        void onDest();
        void onCopy();
private:
    bool getDirectoyPath(QLineEdit* lineEdit, QString ssettingsName, QString& spath);
	Ui::SubRenameClass ui;
	QFileSystemModel oModel;
	QFileDialog oDialog;
	QString s_Dir;
    Copier* p_copier;
    Finder* p_finder;

    QString s_source;
    QString s_dest;

    // ProgressCallback interface
public:
    void onUpdate(int iprogress) override;
    void onUpdate(std::__cxx11::string supdate) override;
};

#endif // SUBRENAME_H

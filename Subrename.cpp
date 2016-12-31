#include "stdafx.h"
#include "Subrename.h"
#include <QMessageBox>
#include <QSettings>
SubRename::SubRename(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    p_finder = nullptr;
    p_copier = nullptr;
	//oModel.setRootPath(QDir::currentPath());
    connect(ui.btnSource, SIGNAL(clicked(bool)),this, SLOT(onSource()));
    connect(ui.btnDest, SIGNAL(clicked(bool)),this, SLOT(onDest()));
    connect(ui.btncopy, SIGNAL(clicked(bool)), this, SLOT(onCopy()));
}

void SubRename::init(Finder *pfinder, Copier *pcopier)
{
   p_finder = pfinder;
   p_copier = pcopier;
}

SubRename::~SubRename()
{

}
void SubRename::OnButtonClick()
{
	s_Dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                QDir::homePath(),
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

	oModel.setRootPath(s_Dir);
	ui.listFilms->setModel(&oModel);
	ui.listSubs->setModel(&oModel);

	ui.listFilms->setRootIndex(oModel.index(s_Dir));
	ui.listSubs->setRootIndex(oModel.index(s_Dir));
}
void SubRename::OnRename()
{
    QModelIndexList oSelectedItems = ui.listFilms->selectionModel()->selectedIndexes();
    if(oSelectedItems.size() == 0)
        return;

    oSelectedItems = ui.listSubs->selectionModel()->selectedIndexes();
    if(oSelectedItems.size() == 0)
        return;

    QString sFirstFile = oModel.filePath(ui.listFilms->selectionModel()->selectedIndexes().at(0));
    QModelIndex oSecondIndex = ui.listSubs->selectionModel()->selectedIndexes().at(0);
    QString sSecondFileName = oModel.fileName(oSecondIndex);
    QString sSecondFile = oModel.filePath(oSecondIndex);
    QString sFirstExtenstion = sFirstFile.split(".").takeLast();
    QString sSecondExtenstion = sSecondFileName.split(".").takeLast();
    sFirstFile.replace(sFirstExtenstion,sSecondExtenstion);

 

    if(ui.chkConfirm->checkState() == Qt::Checked)
    {
		QString sMsg = QString("Change %1 to %2 ?").arg(sSecondFile).arg(sFirstFile);
		if(QMessageBox::question(this,"",sMsg) != QMessageBox::Yes)
		{
			return;
		}
    }

    QFile oFile(sSecondFile);



    oFile.rename(sFirstFile);


}

void SubRename::onSource()
{
    getDirectoyPath(ui.txtSource, SOURCE_PATH, s_source);
}

void SubRename::onDest()
{
    getDirectoyPath(ui.txtDest, DEST_PATH, s_dest);
}

void SubRename::onCopy()
{
    if(s_source.isEmpty() || s_dest.isEmpty())
        return;


    std::list<Info> lstNames;
    p_finder->getAllFiles(qPrintable(s_source), lstNames);
     ui.prog_progress->setMaximum(lstNames.size());
    p_copier->copy(s_dest, lstNames, this);
}

bool SubRename::getDirectoyPath(QLineEdit *lineEdit, QString ssettingsName, QString &spath)
{
    QString sRoot = QDir::homePath();
        if(lineEdit->text() != "")
        {
            sRoot = lineEdit->text();
        }
        QString path = QFileDialog::getExistingDirectory(this, "Select Root", sRoot);
        if(path.isEmpty())
        {
            QMessageBox::critical(this, "Invalid path", "Invalid path, Select a root directory");
            return false;
        }
        lineEdit->setText(path);
        QSettings osettings("launcher.dat");
        osettings.setValue(ssettingsName, path);

        spath = path;

        return true;
}


void SubRename::onUpdate(int iprogress)
{
    ui.prog_progress->setValue(iprogress);
}

void SubRename::onUpdate(std::__cxx11::string supdate)
{
}

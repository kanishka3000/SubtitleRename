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


    renameFile(sFirstFile, sSecondFile, sSecondFileName);
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

void SubRename::onAuto()
{
    if(ui.txt_FromExt->text() == "" || ui.txt_ToExt->text() == "")
    {
        QMessageBox::information(this, "Empty", "Extension Empty");
        return;
    }

    QDir oMovieFiles(s_Dir);

    QString sFromExt = ui.txt_FromExt->text();

    QFileInfoList oMovies = oMovieFiles.entryInfoList(QStringList(ui.txt_FromExt->text()),
                                                      QDir::NoFilter, QDir::Name);

    QFileInfoList oSubs = oMovieFiles.entryInfoList(QStringList(ui.txt_ToExt->text()),
                                                    QDir::NoFilter, QDir::Name);



    if(oMovies.size() != oSubs.size())
    {
        QMessageBox::information(this, "Unequal size", "Unequal size");
    }
    QFileInfoList::iterator itrMov = oMovies.begin();
    QFileInfoList::iterator itrSubs = oSubs.begin();

    for(; itrMov != oMovies.end(); itrMov++, itrSubs++)
    {
        QFileInfo oMovFile = *itrMov;
        QFileInfo oSubFile = *itrSubs;
        QString sfirstFile = oMovFile.filePath();
        QString ssecondFile = oSubFile.fileName();
        QString ssecondPath = oSubFile.filePath();

        renameFile(sfirstFile, ssecondPath, ssecondFile);
    }

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

void SubRename::renameFile(QString sFirstFile, QString ssecondFile , QString sSecondFileName)
{
    QString sFirstExtenstion = sFirstFile.split(".").takeLast();
    QString sSecondExtenstion = sSecondFileName.split(".").takeLast();
    sFirstFile.replace(sFirstExtenstion,sSecondExtenstion);

    if(ui.chkConfirm->checkState() == Qt::Checked)
    {
        QString sMsg = QString("Change %1 to %2 ?").arg(sSecondFileName).arg(sFirstFile);
        if(QMessageBox::question(this,"",sMsg) != QMessageBox::Yes)
        {
            return;
        }
    }

    QFile oFile(ssecondFile);

    oFile.rename(sFirstFile);
}


void SubRename::onUpdate(int iprogress)
{
    ui.prog_progress->setValue(iprogress);
}

void SubRename::onUpdate(std::__cxx11::string supdate)
{
}

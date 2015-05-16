#include "stdafx.h"
#include "Subrename.h"
#include <QMessageBox>
SubRename::SubRename(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//oModel.setRootPath(QDir::currentPath());
	
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

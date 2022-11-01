#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "string"
#include <vector>
#include <QDir>
#include <QDebug>
#include <QInputDialog>
#include <QListWidget>

#include "commands.h"
#include "catwindow.h"
#include "movedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filepathLeft = "/home/ilya/UCU/Grade3/OS/VI Commander/VICommander";
    filepathRight = "/home/ilya";

    // All Connects would be there
//    connect(touchDialog, SIGNAL(valueChanged(QString)), this, SLOT());
    connect(ui->leftFiles, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onDirItemClicked(QListWidgetItem*)));

    // End of Connects

    dirL.setPath(filepathLeft);
    dirR.setPath(filepathRight);

    ui->pathL->setText(dirL.path());
    ui->pathR->setText(dirR.path());

    loadFilesL(dirL);
    loadFilesR(dirR);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDirItemClicked(QListWidgetItem* item) {
    QString fileName = dirL.path() + "/" + item->text();
    QFileInfo fi(fileName);
    if(fi.isDir()) {
        ui->leftFiles->clear();
        dirL.setPath(fileName);
        ui->pathL->setText(dirL.path());
        filepathLeft = fileName;
        loadFilesL(dirL);
    }
}

void MainWindow::loadFilesL(QDir filepath)
{
    foreach(QFileInfo var, filepath.entryInfoList()) {
        ui->leftFiles->addItem(var.fileName());
    }
}

void MainWindow::loadFilesR(QDir filepath)
{
    foreach(QFileInfo var, filepath.entryInfoList()) {
        ui->rightFiles->addItem(var.fileName());
    }
}


void MainWindow::on_changePathL_clicked()
{
    QString curPL = ui->pathL->text();
    if(dirL.exists(curPL)) {
//        Empty the files list
        ui->leftFiles->clear();
//        Add new files
        dirL.setPath(curPL);
        filepathLeft = dirL.path();
        loadFilesL(dirL);
    } else {
        ui->statusbar->showMessage("No such path: " + curPL, 5000);
    }
}


void MainWindow::on_changePathR_clicked()
{
    QString curPR = ui->pathR->text();
    if(dirR.exists(curPR)) {
//        Empty the files list
        ui->rightFiles->clear();
//        Add new files
        dirR.setPath(curPR);
        filepathRight = dirR.path();
        loadFilesR(dirR);
    } else {
        ui->statusbar->showMessage("No such path: " + curPR, 5000);
    }
}


void MainWindow::on_actionCreate_file_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new file"),
                                             tr("File name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        // check if text is a normal name
        std::vector<std::string> filenames;
        filenames.push_back((dirL.path() + "/" + text).toStdString());

        vi_touch(filenames);


        ui->leftFiles->clear();
        loadFilesL(filepathLeft);
    }

}

void MainWindow::on_actionCreate_directory_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new directory"),
                                             tr("Folder name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {
        // check if text is a normal name
        std::vector<std::string> filenames;
        filenames.push_back((dirL.path() + "/" + text).toStdString());

        vi_mkdir(filenames);


        ui->leftFiles->clear();
        loadFilesL(filepathLeft);
    }
}


void MainWindow::on_actionCat_triggered()
{
    if (!ui->leftFiles->currentItem()){
        return;
    }

    std::string output;
    std::vector<std::string> outputV;
    std::vector catfile{(dirL.path() + "/" + ui->leftFiles->currentItem()->text()).toStdString()};

    vi_cat(catfile, &outputV);
    for(auto s : outputV) {
        output += s;
    }

    catWindow = new CatWindow(QString::fromStdString(output), this);
    catWindow->show();
}

void MainWindow::on_actionRename_triggered()
{
    // make my_rename
    if (!ui->leftFiles->currentItem()){
        ui->statusbar->showMessage("The target file is not selected", 5000);
        return;
    }

    bool ok;
    QString oldName = dirL.path() + "/" + ui->leftFiles->currentItem()->text();
    QString text = QInputDialog::getText(this, tr("Create new directory"),
                                             tr("Folder name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()) {

        QFileInfo fi(oldName);
        if (fi.exists() && fi.isFile())
        {
            if(!QFile::rename(oldName, dirL.path() + "/" + text))
                ui->statusbar->showMessage("Error while renaming the file", 5000);
        }  else {
            ui->statusbar->showMessage("No such file: " + oldName, 5000);
        }

        ui->leftFiles->clear();
        loadFilesL(filepathLeft);
    }
}


void MainWindow::on_actionMove_triggered()
{
    moveDialog = new MoveDialog(dirL.path(), this);
    moveDialog->show();
}


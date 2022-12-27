#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "string"
#include <vector>
#include <QDir>
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>

#include "commands.h"
#include "catwindow.h"
#include "movedialog.h"
#include "copydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filepathLeft = "/home/ilya/UCU/Grade3/OS/VI Commander/VICommander";
    filepathRight = "/home/ilya";

    dirL.setPath(filepathLeft);
    dirR.setPath(filepathRight);

    ui->pathL->setText(dirL.path());
    ui->pathR->setText(dirR.path());

    loadFilesL(dirL);
    loadFilesR(dirR);

    // Create dialogs here
    moveDialog = new MoveDialog("", this);
    copyDialog = new CopyDialog("", this);
    linkDialog = new LinkDialog("", this);


    // All Connects would be there
    connect(moveDialog, SIGNAL(ok()), this, SLOT(mvOk()));
    connect(moveDialog, SIGNAL(cmv()), this, SLOT(mvCmv()));
    connect(moveDialog, SIGNAL(dirne()), this, SLOT(mvDne()));
    connect(moveDialog, SIGNAL(pathie()), this, SLOT(mvPie()));

    connect(copyDialog, SIGNAL(ok()), this, SLOT(cpOk()));
    connect(copyDialog, SIGNAL(ccp()), this, SLOT(cpCmv()));
    connect(copyDialog, SIGNAL(dirne()), this, SLOT(cpDne()));
    connect(copyDialog, SIGNAL(pathie()), this, SLOT(cpPie()));

    connect(linkDialog, SIGNAL(ok()), this, SLOT(lnOk()));
    connect(linkDialog, SIGNAL(ccl()), this, SLOT(lnCcl()));
    connect(linkDialog, SIGNAL(dirne()), this, SLOT(lnDne()));
    connect(linkDialog, SIGNAL(pathie()), this, SLOT(lnPie()));

    connect(ui->leftFiles, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onDirItemClicked(QListWidgetItem*)));


    // End of Connects


    // Shortcuts

    QAction *SCquit = new QAction(this);
    SCquit->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(SCquit, SIGNAL(triggered()), this, SLOT(close()));
    this->addAction(SCquit);

    QAction *SCmove = new QAction(this);
    SCmove->setShortcut(Qt::Key_F6);
    connect(SCmove, SIGNAL(triggered()), this, SLOT(on_actionMove_triggered()));
    this->addAction(SCmove);

    QAction *SCopen = new QAction(this);
    SCopen->setShortcut(Qt::Key_F3);
    connect(SCopen, SIGNAL(triggered()), this, SLOT(on_actionCat_triggered()));
    this->addAction(SCopen);

    QAction *SCcrtF = new QAction(this);
    SCcrtF->setShortcut(Qt::SHIFT | Qt::Key_F4);
    connect(SCcrtF, SIGNAL(triggered()), this, SLOT(on_actionCreate_file_triggered()));
    this->addAction(SCcrtF);

    QAction *SCcrtD = new QAction(this);
    SCcrtD->setShortcut(Qt::SHIFT | Qt::Key_F5);
    connect(SCcrtD, SIGNAL(triggered()), this, SLOT(on_actionCreate_directory_triggered()));
    this->addAction(SCcrtD);

    QAction *SCrename = new QAction(this);
    SCrename->setShortcut(Qt::Key_F1);
    connect(SCrename, SIGNAL(triggered()), this, SLOT(on_actionRename_triggered()));
    this->addAction(SCrename);

    QAction *SCdel = new QAction(this);
    SCdel->setShortcut(Qt::Key_F8);
    connect(SCdel, SIGNAL(triggered()), this, SLOT(on_actionRename_triggered()));
    this->addAction(SCdel);

    QAction *SCedit = new QAction(this);
    SCedit->setShortcut(Qt::Key_F4);
    connect(SCedit, SIGNAL(triggered()), this, SLOT(on_actionEdit_file_triggered()));
    this->addAction(SCedit);

    QAction *SCzip = new QAction(this);
    SCzip->setShortcut(Qt::Key_F2);
    connect(SCzip, SIGNAL(triggered()), this, SLOT(on_actionWatch_zip_triggered()));
    this->addAction(SCzip);

    QAction *SClink = new QAction(this);
    SClink->setShortcut(Qt::CTRL | Qt::Key_L);
    connect(SClink, SIGNAL(triggered()), this, SLOT(on_actionCreate_link_triggered()));
    this->addAction(SClink);

    QAction *SCright = new QAction(this);
    SCright->setShortcut(Qt::CTRL | Qt::Key_C);
    connect(SCright, SIGNAL(triggered()), this, SLOT(on_actionChange_rights_triggered()));
    this->addAction(SCright);

    // end of shortcuts
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDirItemClicked(QListWidgetItem* item) {
    QString fileName = QDir::cleanPath(dirL.path() + "/" + item->text());
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
    QIcon icon;
    foreach(QFileInfo var, filepath.entryInfoList()) {
        if(var.isDir()) {
            icon = QIcon(":/resourses/dirIcon.png");
        } else {
            icon = QIcon(":/resourses/fileIcon.png");
        }

        QListWidgetItem *item = new QListWidgetItem(icon, var.fileName());
        ui->leftFiles->addItem(item);
    }
}

void MainWindow::loadFilesR(QDir filepath)
{
    QIcon icon;
    foreach(QFileInfo var, filepath.entryInfoList()) {
        if(var.isDir()) {
            icon = QIcon(":/resourses/dirIcon.png");
        } else {
            icon = QIcon(":/resourses/fileIcon.png");
        }

        QListWidgetItem *item = new QListWidgetItem(icon, var.fileName());
        ui->rightFiles->addItem(item);
    }
}


// SLOTS

void MainWindow::mvOk() {
    // active part
    ui->leftFiles->clear();
    dirL.setPath(QDir::cleanPath(dirL.path()));
    loadFilesL(dirL);

}

void MainWindow::mvCmv() {
    print("Can not move");
}

void MainWindow::mvDne() {
    print("Dir does not exist");
}

void MainWindow::mvPie() {
    print("Path is empty");
}

void MainWindow::cpOk() {
    // active part
    ui->leftFiles->clear();
    dirL.setPath(QDir::cleanPath(dirL.path()));
    loadFilesL(dirL);

}

void MainWindow::cpCmv() {
    print("Can not copy");
}

void MainWindow::cpDne() {
    print("Dir does not exist");
}

void MainWindow::cpPie() {
    print("Path is empty");
}

void MainWindow::lnOk() {
    // active part
    ui->leftFiles->clear();
    dirL.setPath(QDir::cleanPath(dirL.path()));
    loadFilesL(dirL);

}

void MainWindow::lnCcl() {
    print("Can not create link");
}

void MainWindow::lnDne() {
    print("Dir does not exist");
}

void MainWindow::lnPie() {
    print("Path is empty");
}

//end of SLOTS


void MainWindow::on_changePathL_clicked()
{
    QString curPL = QDir::cleanPath(ui->pathL->text());
    if(dirL.exists(curPL)) {
//        Empty the files list
        ui->leftFiles->clear();
//        Add new files
        dirL.setPath(curPL);
        filepathLeft = dirL.path();
        loadFilesL(dirL);
    } else {
        ui->pathL->setText(filepathLeft);
        print("No such path: " + curPL);
    }
}


void MainWindow::on_changePathR_clicked()
{
    QString curPR = QDir::cleanPath(ui->pathR->text());
    if(dirR.exists(curPR)) {
//        Empty the files list
        ui->rightFiles->clear();
//        Add new files
        dirR.setPath(curPR);
        filepathRight = dirR.path();
        loadFilesR(dirR);
    } else {
        print("No such path: " + curPR);
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
    std::vector catfile{(QDir::cleanPath(dirL.path() + "/" + ui->leftFiles->currentItem()->text())).toStdString()};

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
        print("The target file is not selected");
        return;
    }

    bool ok;
    QString oldName = QDir::cleanPath(dirL.path() + "/" + ui->leftFiles->currentItem()->text());
    QFileInfo fi(oldName);

    if (fi.exists() && fi.isFile()) {

        QString text = QInputDialog::getText(this, tr("Create new directory"),
                                             tr("Folder name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty()) {
            if(!QFile::rename(oldName, dirL.path() + "/" + text))
                print("Error while renaming the file");
        }  else {
            print("No such file: " + oldName);
        }

        ui->leftFiles->clear();
        loadFilesL(filepathLeft);
    } else {
        print("Not a file");
    }
}

void MainWindow::print(QString s) {
    ui->statusbar->showMessage(s, 5000);
}

void MainWindow::on_actionMove_triggered()
{
    QString fromPath;
    if (!ui->leftFiles->currentItem()){
        fromPath = dirL.path();
    } else {
        fromPath = dirL.path() + "/" + ui->leftFiles->currentItem()->text();
    }
    moveDialog->updatePath(QDir::cleanPath(fromPath));

    moveDialog->show();
}


void MainWindow::on_actionCopy_triggered()
{
    QString fromPath;
    void on_buttonBox_accepted();
    if (!ui->leftFiles->currentItem()){
        fromPath = dirL.path();
    } else {
        fromPath = dirL.path() + "/" + ui->leftFiles->currentItem()->text();
    }
    copyDialog->updatePath(QDir::cleanPath(fromPath));

    copyDialog->show();
}


void MainWindow::on_actionDelete_triggered()
{
    if (!ui->leftFiles->currentItem()) {
        print("No files are chosen");
    } else {
        QString last_part = ui->leftFiles->currentItem()->text();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete '" + last_part + "'",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QString fileName = QDir::cleanPath(dirL.path() + "/" + ui->leftFiles->currentItem()->text());
            QFileInfo fi(fileName);
            if(fi.isDir()) {
                QDir dir(fileName);
                dir.removeRecursively();
                dirL.setPath(QDir::cleanPath(dirL.path() + "/.."));
            }
            if(fi.isFile()) {
                QFile fl(fileName);
                fl.remove();
                dirL.setPath(QDir::cleanPath(dirL.path()));
            }
            ui->leftFiles->clear();
            ui->pathL->setText(dirL.path());
            loadFilesL(dirL);

        }
    }
}


void MainWindow::on_actionEdit_file_triggered()
{
    if (!ui->leftFiles->currentItem()){
        print("No file is chosen");
        return;
    }
    QString p = QDir::cleanPath(dirL.path() + "/" + ui->leftFiles->currentItem()->text());
    QFileInfo fi(p);
    if (!fi.isFile()) {
        print("Choose a file");
        return;
    }

    std::string output;
    std::vector<std::string> outputV;
    std::vector catfile{p.toStdString()};

    vi_cat(catfile, &outputV);
    for(auto s : outputV) {
        output += s;
    }

    editDialog = new EditDialog(QString::fromStdString(output), p, this);
    editDialog->show();
}


void MainWindow::on_actionWatch_zip_triggered()
{
    if (!ui->leftFiles->currentItem()){
        print("No file is chosen");
        return;
    }

    QString p = QDir::cleanPath(dirL.path() + "/" + ui->leftFiles->currentItem()->text());
    QFileInfo fi(p);
    if (!fi.isFile()) {
        print("Choose a file");
        return;
    }

    if (fi.completeSuffix() == "zip") {
        std::vector<std::string> args = {};
        std::vector<file_archive> inside_zip;
        std::vector<file_archive>* inside_zip_ptr = &inside_zip;
        const std::filesystem::path path = p.toStdString();

        vi_archive(args, path, inside_zip_ptr);

        zipContent = new zpContent(inside_zip, this);
        zipContent->show();



    } else {
        print("Choose a zip");
    }
}

void MainWindow::on_actionCreate_link_triggered()
{
    QString fromPath;
    if (!ui->leftFiles->currentItem()) {
        fromPath = dirL.path();
    } else {
        fromPath = dirL.path() + "/" + ui->leftFiles->currentItem()->text();
    }

    linkDialog->updatePath(QDir::cleanPath(fromPath));
    linkDialog->show();
}

void MainWindow::on_actionChange_rights_triggered()
{
    if (!ui->leftFiles->currentItem()){
        print("No file is chosen");
        return;
    }

    rgtDialog = new rightsDialog(QDir::cleanPath(dirL.path() + "/" + ui->leftFiles->currentItem()->text()), this);
    rgtDialog->show();
}


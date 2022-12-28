#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "catwindow.h"
#include "copydialog.h"
#include "editdialog.h"
#include "movedialog.h"
#include "rightsdialog.h"
#include "zpcontent.h"
#include "linkdialog.h"
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_changePathL_clicked();

    void on_changePathR_clicked();

    void on_actionCreate_file_triggered();

    void on_actionCat_triggered();

    void on_actionCreate_directory_triggered();

    void on_actionRename_triggered();

    void onDirItemClickedL(QListWidgetItem* item);
    void onDirItemClickedR(QListWidgetItem* item);

    void on_actionMove_triggered();

    void on_actionCopy_triggered();

    void on_actionDelete_triggered();

    void on_actionEdit_file_triggered();

    void on_actionWatch_zip_triggered();

    void on_actionCreate_link_triggered();

    void on_actionChange_rights_triggered();


    void on_filesL_itemClicked(QListWidgetItem *item);

    void on_filesR_itemClicked(QListWidgetItem *item);

    void changeSide();

public slots:
    // move dialog
    void mvOk();
    void mvCmv();
    void mvDne();
    void mvPie();

    // copy dialog
    void cpOk();
    void cpCmv();
    void cpDne();
    void cpPie();

    // link dialog
    void lnOk();
    void lnCcl();
    void lnDne();
    void lnPie();

private:
    Ui::MainWindow *ui;
    CatWindow *catWindow;
    EditDialog *editDialog;
    MoveDialog *moveDialog;
    CopyDialog *copyDialog;
    zpContent *zipContent;
    LinkDialog *linkDialog;
    rightsDialog *rgtDialog;

    QDir dirL;
    QDir dirR;

    QString side;
    QLineEdit *curPath;
    QLineEdit *secPath;
    QListWidget *curFiles;
    QListWidget *secFiles;
    QDir curDir;
    QDir secDir;

    void loadFiles(QString sd, QDir filepath);
    void loadFilesR(QDir filepath);
    void print(QString s);

};
#endif // MAINWINDOW_H

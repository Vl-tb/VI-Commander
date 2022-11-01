#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include "catwindow.h"
#include "movedialog.h"
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

    void onDirItemClicked(QListWidgetItem* item);

    void on_actionMove_triggered();

private:
    Ui::MainWindow *ui;
    CatWindow *catWindow;
    MoveDialog *moveDialog;

    QDir dirL;
    QDir dirR;

    QString filepathLeft;
    QString filepathRight;

    void loadFilesL(QDir filepath);
    void loadFilesR(QDir filepath);

};
#endif // MAINWINDOW_H

#ifndef CATWINDOW_H
#define CATWINDOW_H

#include <QDialog>

namespace Ui {
class CatWindow;
}

class CatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CatWindow(QString text, QWidget *parent = nullptr);
    ~CatWindow();

private slots:
    void on_closeButton_clicked();

private:
    Ui::CatWindow *ui;
    QString catText;
};

#endif // CATWINDOW_H

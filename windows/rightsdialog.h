#ifndef RIGHTSDIALOG_H
#define RIGHTSDIALOG_H

#include <QDialog>

namespace Ui {
class rightsDialog;
}

class rightsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rightsDialog(QString file, QWidget *parent = nullptr);
    ~rightsDialog();

private slots:
    void on_Cancel_clicked();

    void on_OK_clicked();

private:
    Ui::rightsDialog *ui;
    QString filename;
    void loadRights();
};

#endif // RIGHTSDIALOG_H

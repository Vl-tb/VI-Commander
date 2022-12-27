#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QString text, QString fn, QWidget *parent = nullptr);
    ~EditDialog();

private slots:
    void on_Cancel_clicked();

    void on_OK_clicked();

private:
    Ui::EditDialog *ui;
    QString editText;
    QString filename;
};

#endif // EDITDIALOG_H

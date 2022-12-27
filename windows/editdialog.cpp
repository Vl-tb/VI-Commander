#include "editdialog.h"
#include "ui_editdialog.h"
#include <fstream>

EditDialog::EditDialog(QString text, QString fn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    editText = text;
    filename = fn;
    ui->text->setPlainText(editText);
}

EditDialog::~EditDialog()
{
    delete ui;
}


void EditDialog::on_Cancel_clicked()
{
    close();
}


void EditDialog::on_OK_clicked()
{
    editText = ui->text->toPlainText();
    std::ofstream out(filename.toStdString());
    out << editText.toStdString();
    out.close();
    close();
}


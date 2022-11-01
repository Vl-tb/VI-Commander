#include "movedialog.h"
#include "ui_movedialog.h"

MoveDialog::MoveDialog(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoveDialog)
{
    ui->setupUi(this);
    fromPath = path;
    ui->lineEdit->setText(fromPath);
}

MoveDialog::~MoveDialog()
{
    delete ui;
}

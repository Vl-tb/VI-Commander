#include "catwindow.h"
#include "ui_catwindow.h"

CatWindow::CatWindow(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatWindow)
{
    ui->setupUi(this);
    catText = text;
    ui->catText->setPlainText(catText);
}

CatWindow::~CatWindow()
{
    delete ui;
}

void CatWindow::on_closeButton_clicked()
{
    close();
}


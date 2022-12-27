#include "zpcontent.h"
#include "ui_zpcontent.h"

zpContent::zpContent(const std::vector<file_archive> &iz, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zpContent)
{
    ui->setupUi(this);
    ui->infoTable->setColumnWidth(0, 270);
    ui->infoTable->setColumnWidth(1, 100);
    ui->infoTable->setColumnWidth(2, 150);

    loadContent(iz);
}

zpContent::~zpContent()
{
    delete ui;
}

void zpContent::on_CloseB_clicked()
{
    close();
}

void zpContent::loadContent(const std::vector<file_archive> &iz) {
    size_t row = 0;
    ui->infoTable->setRowCount(iz.size());
    for (auto el:iz) {
        ui->infoTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(el.name)));
        ui->infoTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(el.comp_size + " bytes")));
        ui->infoTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(el.date)));
        ++row;
    }
}

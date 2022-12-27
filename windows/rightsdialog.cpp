#include "rightsdialog.h"
#include "commands.h"
#include "ui_rightsdialog.h"
#include <QFileInfo>
#include <QDebug>

rightsDialog::rightsDialog(QString file, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rightsDialog)
{
    filename = file;
    ui->setupUi(this);

    loadRights();
}

rightsDialog::~rightsDialog()
{
    delete ui;
}

void rightsDialog::on_Cancel_clicked()
{
    close();
}

void rightsDialog::loadRights() {
    const QFileInfo info(filename);

    ui->ownerWrite->setChecked(info.permission(QFile::WriteOwner));
    ui->groupWrite->setChecked(info.permission(QFile::WriteGroup));
    ui->otherWrite->setChecked(info.permission(QFile::WriteOther));
    ui->ownerRead->setChecked(info.permission(QFile::ReadOwner));
    ui->groupRead->setChecked(info.permission(QFile::ReadGroup));
    ui->otherRead->setChecked(info.permission(QFile::ReadOther));
    ui->ownerExec->setChecked(info.permission(QFile::ExeOwner));
    ui->groupExec->setChecked(info.permission(QFile::ExeGroup));
    ui->otherExec->setChecked(info.permission(QFile::ExeOther));
}

void rightsDialog::on_OK_clicked()
{
    std::vector<std::string> input = {filename.toStdString()};
    if (ui->ownerRead->isChecked()) {
        input.push_back("r");
    } else input.push_back("-");
    if (ui->ownerWrite->isChecked()) {
        input.push_back("w");
    } else input.push_back("-");
    if (ui->ownerExec->isChecked()) {
        input.push_back("x");
    } else input.push_back("-");

    if (ui->groupRead->isChecked()) {
        input.push_back("r");
    } else input.push_back("-");
    if (ui->groupWrite->isChecked()) {
        input.push_back("w");
    } else input.push_back("-");
    if (ui->groupExec->isChecked()) {
        input.push_back("x");
    } else input.push_back("-");

    if (ui->otherRead->isChecked()) {
        input.push_back("r");
    } else input.push_back("-");
    if (ui->otherWrite->isChecked()) {
        input.push_back("w");
    } else input.push_back("-");
    if (ui->otherExec->isChecked()) {
        input.push_back("x");
    } else input.push_back("-");

    vi_chmod(input);
    close();
}


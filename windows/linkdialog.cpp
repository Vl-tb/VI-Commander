#include "linkdialog.h"
#include "commands.h"
#include "ui_linkdialog.h"

LinkDialog::LinkDialog(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);
    fromPath = path;
    ui->sfilepath->setText(fromPath);
}

LinkDialog::~LinkDialog()
{
    delete ui;
}

void LinkDialog::on_Cancel_clicked()
{
    reset();
    close();
}

void LinkDialog::updatePath(QString newP) {
    fromPath = newP;
    ui->sfilepath->setText(fromPath);
}

void LinkDialog::on_OK_clicked()
{
    if(!((ui->lfilepath->text()).isEmpty()) || !((ui->sfilepath->text()).isEmpty())) {

        QString curLP = ui->lfilepath->text();
        QString curSP = ui->sfilepath->text();
        QFileInfo fi(curLP);
        if(dir.exists(fi.absolutePath()) && dir.exists(curSP)) {

            std::vector<std::string> args = {curSP.toStdString(), curLP.toStdString()};
            if(ui->symL->isChecked()) {
                if(vi_symlink(args)) {
                    emit ccl();
                }
            }
            if(ui->hardL->isChecked()) {
                if(vi_hardlink(args)) {
                    emit ccl();
                }
            }

            emit ok();
            reset();
            close();
        } else {
            // dir does not exist
            emit dirne();
        }
    } else {
        // path to is empty
        emit pathie();
    }
}

void LinkDialog::reset() {
    ui->lfilepath->setText("");
    ui->symL->setAutoExclusive(false);
    ui->hardL->setAutoExclusive(false);
    ui->symL->setChecked(false);
    ui->hardL->setChecked(false);
    ui->symL->setAutoExclusive(true);
    ui->hardL->setAutoExclusive(true);
}


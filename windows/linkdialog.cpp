#include "linkdialog.h"
#include "commands.h"
#include "ui_linkdialog.h"

LinkDialog::LinkDialog(QString fpath, QString tpath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);
    fromPath = fpath;
    toPath = tpath;
    ui->sfilepath->setText(fromPath);
    ui->lfilepath->setText(toPath);
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

void LinkDialog::updatePath(QString newPf, QString newPt) {
    fromPath = newPf;
    toPath = newPt;
    ui->sfilepath->setText(fromPath);
    ui->lfilepath->setText(toPath);
}

void LinkDialog::on_OK_clicked()
{
    if(!((ui->lfilepath->text()).isEmpty()) || !((ui->sfilepath->text()).isEmpty())) {

        QString curLP = ui->lfilepath->text();
        QString curSP = ui->sfilepath->text();
        QFileInfo fi(curLP);
        if(dir.exists(fi.absolutePath()) && dir.exists(curSP)) {
            if(fi.isDir()) return;
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


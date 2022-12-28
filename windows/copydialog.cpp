#include "copydialog.h"
#include "ui_copydialog.h"

CopyDialog::CopyDialog(QString fpath, QString tpath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyDialog)
{
    ui->setupUi(this);
    fromPath = fpath;
    toPath = tpath;
    ui->path_from->setText(fromPath);
    ui->path_to->setText(toPath);
}

CopyDialog::~CopyDialog()
{
    delete ui;
}

void CopyDialog::on_Cancel_clicked()
{
    close();
}

void CopyDialog::updatePath(QString newPf, QString newPt) {
    fromPath = newPf;
    toPath = newPt;
    ui->path_from->setText(fromPath);
    ui->path_to->setText(toPath);
}

void CopyDialog::on_OK_clicked()
{
    if(!((ui->path_to->text()).isEmpty()) || !((ui->path_from->text()).isEmpty())) {

        QString curPT = ui->path_to->text();
        QString curPF = ui->path_from->text();
        if(dir.exists(curPT) && dir.exists(curPF)) {
            // move
            QString last_part = curPF.section(QDir::separator(), -1);
            if(!QFile::copy(curPF, curPT + "/"+ last_part)) {
                // can`t copy
                emit ccp();
            }

            emit ok();
            ui->path_to->setText("");
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


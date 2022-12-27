#include "movedialog.h"
#include "ui_movedialog.h"

MoveDialog::MoveDialog(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoveDialog)
{
    ui->setupUi(this);
    fromPath = path;
    ui->path_from->setText(fromPath);
}

MoveDialog::~MoveDialog()
{
    delete ui;
}


void MoveDialog::on_Cancel_clicked()
{
    ui->path_to->setText("");
    close();
}

void MoveDialog::updatePath(QString newP) {
    fromPath = newP;
    ui->path_from->setText(fromPath);
}

void MoveDialog::on_OK_clicked()
{
    if(!((ui->path_to->text()).isEmpty()) || !((ui->path_from->text()).isEmpty())) {

        QString curPT = ui->path_to->text();
        QString curPF = ui->path_from->text();
        if(dir.exists(curPT) && dir.exists(curPF)) {
            // move
            QString last_part = curPF.section(QDir::separator(), -1);
            if(!QFile::rename(curPF, curPT + "/"+ last_part)) {
                // can`t move
                emit cmv();
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


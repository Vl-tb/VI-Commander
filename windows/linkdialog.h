#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDir>
#include <QDialog>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinkDialog(QString fpath, QString tpath, QWidget *parent = nullptr);
    ~LinkDialog();

    void updatePath(QString newPf, QString newPt);

signals:
    void ok();
    void ccl();
    void dirne();
    void pathie();

private slots:
    void on_Cancel_clicked();

    void on_OK_clicked();

private:
    Ui::LinkDialog *ui;
    QString fromPath;
    QString toPath;
    QDir dir;
    void reset();
};

#endif // LINKDIALOG_H

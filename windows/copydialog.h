#ifndef COPYDIALOG_H
#define COPYDIALOG_H

#include <QDir>
#include <QDialog>

namespace Ui {
class CopyDialog;
}

class CopyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CopyDialog(QString path, QWidget *parent = nullptr);
    ~CopyDialog();

    void updatePath(QString newP);

signals:
    void ok();
    void ccp();
    void dirne();
    void pathie();

private slots:
    void on_Cancel_clicked();

    void on_OK_clicked();

private:
    Ui::CopyDialog *ui;
    QString fromPath;
    QDir dir;
};

#endif // COPYDIALOG_H

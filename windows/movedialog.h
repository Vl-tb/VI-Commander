#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

#include <QDir>
#include <QDialog>

namespace Ui {
class MoveDialog;
}

class MoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoveDialog(QString path, QWidget *parent = nullptr);
    ~MoveDialog();

    void updatePath(QString newP);

signals:
    void ok();
    void cmv();
    void dirne();
    void pathie();

private slots:
    void on_Cancel_clicked();

    void on_OK_clicked();

private:
    Ui::MoveDialog *ui;
    QString fromPath;
    QDir dir;
};

#endif // MOVEDIALOG_H

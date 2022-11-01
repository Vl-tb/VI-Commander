#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

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

private:
    Ui::MoveDialog *ui;
    QString fromPath;
};

#endif // MOVEDIALOG_H

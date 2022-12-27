#ifndef ZPCONTENT_H
#define ZPCONTENT_H

#include "commands.h"
#include <QDialog>

namespace Ui {
class zpContent;
}

class zpContent : public QDialog
{
    Q_OBJECT

public:
    explicit zpContent(const std::vector<file_archive> &iz, QWidget *parent = nullptr);
    ~zpContent();

private slots:
    void on_CloseB_clicked();

private:
    Ui::zpContent *ui;
    void loadContent(const std::vector<file_archive> &iz);

};

#endif // ZPCONTENT_H

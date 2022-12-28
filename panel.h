#ifndef PANEL_H
#define PANEL_H

#include <QDir>
#include <QLineEdit>
#include <QListWidget>

class panel
{
public:
    panel(QString sd, QWidget *wgt = nullptr);

    void loadFiles(QDir filepath);

private:
    QString side;
    QString filepath;
    QDir dir; //dirL

    QWidget *widget;

};

#endif // PANEL_H

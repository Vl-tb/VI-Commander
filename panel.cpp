#include "panel.h"
#include <QIcon>
#include <QListWidget>

panel::panel(QString sd, QWidget *wgt)
{
    side = sd, widget = wgt;
}

void panel::loadFiles(QDir filepath) {
    QIcon icon;
    foreach(QFileInfo var, filepath.entryInfoList()) {
        if(var.isDir()) {
            icon = QIcon(":/resourses/dirIcon.png");
        } else {
            icon = QIcon(":/resourses/fileIcon.png");
        }

        QListWidgetItem *item = new QListWidgetItem(icon, var.fileName());
//        widget->findChild<QListWidget>("files" + side).addItem(item);
    }
}

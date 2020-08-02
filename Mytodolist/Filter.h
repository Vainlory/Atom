#ifndef FILTER_H
#define FILTER_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QString>
#include <QHeaderView>
#include <QDir>
#include <QDebug>
#include <QAction>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
class Filter : public QTreeWidget
{
public:
    Filter();
    void buildtree();
    void rebuildtree();
    QAction* openAct;
    QString currentDir;
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent *event);

signals:
private slots:
    void openAction(QTreeWidgetItem*,int);

};

#endif // FILTER_H

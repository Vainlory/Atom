﻿#ifndef FILTER_H
#define FILTER_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QString>
#include <QHeaderView>
#include <QDir>
#include <QDebug>
#include <QAction>
class Filter : public QTreeWidget
{
public:
    Filter();
    void buildtree();
    void rebuildtree();
    QAction* openAct;
    QString currentDir;
signals:
private slots:
    void openAction(QTreeWidgetItem*,int);
};

#endif // FILTER_H
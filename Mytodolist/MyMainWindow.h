﻿#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include <QStatusBar>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QCursor>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QCloseEvent>
#include <QPushButton>
#include <QBitmap>
#include <QColor>
#include <QMessageBox>
#include "mainwindow.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QDesktopServices>
#include "Filter.h"
#include "StickyNote.h"
class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    QSystemTrayIcon* _sysicon;
    QMenu* son_menu,*parent_menu,*_menu;
    QTreeWidgetItem* new_item;
    QPushButton* _add_;
    QAction* min;
    QAction* max;
    QAction* Exit;
    QAction* OpenAct;
    QAction* NewAct;
    QAction* RenameAct;
    QAction* DeleteAct;
    QAction* CopyAct;
    QAction* PasteAct;
    QAction* CutAct;
    QAction* OpenInUrlAct;
    QAction* StickyAct;
    MainWindow* w;
    Filter* filter;
    QStringList copyboard;
    QString prename;
    void closeEvent(QCloseEvent*);

signals:
    void addnew(QTreeWidgetItem*,int);
public slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void slotnotepad();
    void on_pressedTreeWidgetItem(QTreeWidgetItem*, int);
    void OpenAction();
    void OpenAction(QTreeWidgetItem*, int);
    void RenameAction();
    void NewAction();
    void DeleteAction();
    void AddNew(QTreeWidgetItem*,int);
    void nameChanged(QTreeWidgetItem*, int);
    void OpenInUrlAction();
    void CopyAction();
    void PasteAction();
    void CutAction();
    void StickyAction();
};

#endif // MYMAINWINDOW_H

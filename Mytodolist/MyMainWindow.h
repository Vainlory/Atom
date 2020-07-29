#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QDialog>
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
#include "Filter.h"
class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    QSystemTrayIcon* _sysicon;
    QMenu* right_menu,*_menu;
    QPushButton* _add_;
    QAction* min;
    QAction* max;
    QAction* Exit;
    QAction* OpenAct;
    MainWindow* w;
    Filter* filter;
    void closeEvent(QCloseEvent*);

signals:

public slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void slotnotepad();
    void on_pressedTreeWidgetItem(QTreeWidgetItem*, int);
    void OpenAction();
};

#endif // MYMAINWINDOW_H

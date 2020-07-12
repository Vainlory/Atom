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
class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    QSystemTrayIcon* _sysicon;
    QMenu* _menu1,*_menu;
    QPushButton* _add_;
    void closeEvent(QCloseEvent*);
    void paintEvent(QPaintEvent*);
signals:
public slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
};

#endif // MYMAINWINDOW_H

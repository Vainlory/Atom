#ifndef NEW_DIARY_H
#define NEW_DIARY_H

#include <QWidget>
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
class New_diary : public QWidget
{
    Q_OBJECT
public:
    explicit New_diary(QWidget *parent = nullptr);
    QMenuBar* _menubar;
    QMenu* _file,*_edit,*_style,*_help,*_tool;
signals:
public slots:
    void slotfileout();
};

#endif // NEW_DIARY_H

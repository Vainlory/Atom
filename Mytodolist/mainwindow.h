#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDebug>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QLabel>
#include <QString>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:

    //新建
    QMenu *fileMenu, *editMenu, *helpMenu,*viewMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;        //新建两个工具栏，用以存放四个菜单动作
    QStatusBar * statusbar;
    QLabel* status;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveasAct;
    QAction *printAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *aboutQtAct;
    QAction *exitAct;
    QAction *selectallAct;
    QAction *swStatusAct;
    QTextEdit *textEdit;
    QLineEdit *title;
    QVBoxLayout *vboxlayout;
    QString currentFile;
    QAction* printpreviewAct;
signals:
private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();
    void cutAction();
    void copyAction();
    void pasteAction();
    void undoAction();
    void redoAction();
    void exitAction();
    void printpreviewAction();
    void printrequest(QPrinter*);
    void showStatusAction();
    void slottextchanged();
};

#endif // MAINWINDOW_H

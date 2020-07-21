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
#include <QFontDialog>
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
#include <QTextCharFormat>
#include <QColorDialog>
#include <QTextFormat>
#include <QTextTable>
#include <QTcpServer>
#include <AskTable.h>
#include <QTextTableFormat>
#include <QTextTableCell>
#include <QComboBox>
#include <QFontDatabase>
#include <QFontComboBox>
#include <QComboBox>
#include "ColorCombox.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:

    //新建
    QMenu *fileMenu, *editMenu, *helpMenu,*viewMenu,*styleMenu,*paragraphMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;        //新建两个工具栏，用以存放四个菜单动作
    QToolBar *styleToolBar;
    QFontComboBox* fontBox;
    QComboBox* sizeBox;
    ColorCombox* colorBox;
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
    QAction *fontAct;
    QAction *colorAct;
    QAction *incindAct;
    QAction *decindAct;
    QAction *leftAct;
    QAction *centerAct;
    QAction *rightAct;
    QAction *justifyAct;
    QAction *incfsizeAct;
    QAction *decfsizeAct;
    QAction *instableAct;
    QAction *insruleAct;
    QPushButton* boldbutton;
    QPushButton* italicbutton;
    QTextEdit *textEdit;
    QLineEdit *title;
    QVBoxLayout *vboxlayout;
    QString currentFile;
    QAction* printpreviewAct;
    QTcpServer* tcpserver;
    QTcpSocket* tcpsocket;

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
    void fontAction();
    void slotselectionchanged();
    void leftAction();
    void centerAction();
    void rightAction();
    void justifyAction();
    void colorAction();
    void incindAction();
    void decindAction();
    void incfsizeAction();
    void decfsizeAction();
    void instableAction();
    void insruleAction();
    void slotNetConnection();
    void slotreadyread();
    void slotfontchanged(const QFont &);
    void slotcursorchanged();
    void slotsizechanged(const QString &);
    void slotcolorchanged(const QColor&);
    void slotboldclicked(const bool&);
    void slotitalicclicked();
};
#endif // MAINWINDOW_H

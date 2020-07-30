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
#include <QToolButton>
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
#include <QCheckBox>
#include <QRadioButton>
#include <QDateTime>
#include "ColorCombox.h"
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QString path,QWidget *parent = nullptr);


    //新建

    QMenu *fileMenu, *editMenu, *helpMenu,*viewMenu,*styleMenu,*paragraphMenu;
    QToolBar *fileToolBar;
            //新建两个工具栏，用以存放四个菜单动作
    QToolBar *styleToolBar;
    QFontComboBox* fontBox;
    QComboBox* sizeBox;
    ColorCombox* colorBox;
    QStatusBar * statusbar;
    QLabel* status;
    QLabel* lasttime;
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
    QAction *swStyleAct;
    QAction *swFileAct;
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
    QAction *inslistAct;
    QPushButton* boldbutton;
    QPushButton* italicbutton;
    QPushButton* underlinebutton;
    QPushButton* overlinebutton;
    QPushButton* highlightbutton;
    QPushButton* alignmentbutton;
    QMenu* alignmentmenu;
    QTextEdit *textEdit;
    QLineEdit *title;
    QVBoxLayout *vboxlayout;
    QHBoxLayout *hboxlayout;
    QString currentFile;
    QString currentDir;
    QAction* printpreviewAct;
    QTcpServer* tcpserver;
    QTcpSocket* tcpsocket;
    QDateTime lastedit;

signals:
public slots:
    void newFile();
    void openFile();
    void openFile(QString);
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
    void swStyleAction();
    void swFileAction();
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
    void inslistAction();
    void slotNetConnection();
    void slotreadyread();
    void slotfontchanged(const QFont &);
    void slotcursorchanged();
    void slotsizechanged(const QString &);
    void slotcolorchanged(const QColor&);
    void slotboldclicked(const bool&);
    void slotitalicclicked();
    void slotunderlineclicked();
    void slotoverlineclicked();
    void slothighlightclicked();

};
#endif // MAINWINDOW_H

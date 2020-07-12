#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->resize(1000,800);
    this->setWindowTitle("notepad");
    this->setWindowIcon(QIcon("../icon/atom_128px.ico"));        //设置应用显示图标
    QWidget* widget = new QWidget();
    //实例菜单和控件
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    helpMenu = new QMenu(this);
    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText(tr(u8"开始书写、拖动文件或选择"));
    statusbar = new QStatusBar(this);
    status = new QLabel("",this);
    statusbar->addWidget(status);
    title = new QLineEdit(this);
    title->setPlaceholderText(tr(u8"标题"));
    //使用layout设置内部布局
    vboxlayout = new QVBoxLayout();
    vboxlayout->addWidget(title);
    vboxlayout->addWidget(textEdit);
    vboxlayout->addWidget(statusbar);
    this->setCentralWidget(widget);
    centralWidget()->setLayout(vboxlayout);
    //textEdit 信号和槽
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(slottextchanged()));
    //填充菜单子节点
    newAct = new QAction(QIcon( "../icon/NewEvent.png" ), tr( u8"新建" ), this );
    newAct->setShortcut(tr("Ctrl+N" ));       					 //快捷键
    newAct->setStatusTip(tr(u8"新建文件" ));     					 //底部状态提示
    openAct = new QAction(QIcon( "../icon/open.png" ), tr( u8"打开" ), this );
    openAct->setShortcut(tr(u8"Ctrl+O" ));
    openAct->setStatusTip(tr(u8"打开文件" ));
    saveAct = new QAction(QIcon( "../icon/save.png" ), tr( u8"保存" ), this );
    saveAct->setShortcut(tr("Ctrl+S" ));
    saveAct->setStatusTip(tr(u8"保存文件" ));
    saveasAct = new QAction(QIcon( "../icon/save-as.png" ), tr( u8"另存为" ), this );
    saveasAct->setShortcut(tr("Ctrl+Shift+S" ));
    saveasAct->setStatusTip(tr(u8"另存为文件" ));
    printAct = new QAction(QIcon( "../icon/print.png" ), tr( u8"打印" ), this );
    printAct->setShortcut(tr("Ctrl+P" ));
    printAct->setStatusTip(tr(u8"打印" ));
    printpreviewAct = new QAction(QIcon("../icon/print-preview.png"),tr(u8"打印预览"),this);
    exitAct = new QAction(QIcon( "../icon/exit.png" ), tr( u8"退出" ), this );
    exitAct->setShortcut(tr("Ctrl+E"));
    exitAct->setStatusTip(tr(u8"关闭"));

    //信号与槽
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(saveasAct,SIGNAL(triggered()),this,SLOT(saveasFile()));
    connect(printAct,SIGNAL(triggered()),this,SLOT(printFile()));
    connect(printpreviewAct,SIGNAL(triggered()),this,SLOT(printpreviewAction()));
    cutAct = new QAction(QIcon( "../icon/cut.png" ), tr( u8"剪切" ), this );
    cutAct->setShortcut(tr("Ctrl+X" ));
    cutAct->setStatusTip(tr(u8"剪切内容" ));
    copyAct = new QAction(QIcon( "../icon/copy.png" ), tr( u8"复制" ), this );
    copyAct->setShortcut(tr("Ctrl+C" ));
    copyAct->setStatusTip(tr(u8"复制内容" ));
    pasteAct = new QAction(QIcon( "../icon/paste.png" ), tr( u8"粘贴" ), this );
    pasteAct->setShortcut(tr("Ctrl+V" ));
    pasteAct->setStatusTip(tr(u8"粘贴内容" ));
    undoAct = new QAction(QIcon( "../icon/undo.png" ), tr( u8"撤销" ), this );
    undoAct->setShortcut(tr("Ctrl+Z" ));
    undoAct->setStatusTip(tr(u8"向后一步" ));
    redoAct = new QAction(QIcon( "../icon/redo.png" ), tr( u8"重做" ), this );
    redoAct->setShortcut(tr("Ctrl+Y" ));
    redoAct->setStatusTip(tr(u8"向前一步" ));
    aboutQtAct = new QAction(QIcon("../icon/aboutus.png"),tr( u8"关于 Qt" ), this );
    aboutQtAct->setStatusTip(tr(u8"关于 Qt 信息" ));
    selectallAct = new QAction(QIcon("../icon/select-all.png"),tr(u8"全选"),this);
    selectallAct->setStatusTip(tr(u8"全选"));
    selectallAct->setShortcut(tr("Ctrl+A"));

    swStatusAct = new QAction(tr(u8"查看状态栏"),this);
    swStatusAct->setStatusTip(tr(u8"开关底部状态栏"));
    swStatusAct->setIcon(QIcon("../icon/bingo.png"));

    //信号与槽
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copyAction()));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cutAction()));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(pasteAction()));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undoAction()));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redoAction()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exitAction()));
    connect(selectallAct,SIGNAL(triggered()),textEdit,SLOT(selectAll()));
    connect(swStatusAct,SIGNAL(triggered()),this,SLOT(showStatusAction()));
    //填充菜单
    fileMenu = menuBar()->addMenu(tr( u8"文件" ));
    fileMenu->addAction(newAct);
    fileMenu->addSeparator();
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printpreviewAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr(u8"编辑" ));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(selectallAct);
    menuBar()->addSeparator();
    viewMenu = menuBar()->addMenu(tr(u8"查看"));
    viewMenu->addAction(swStatusAct);
    menuBar()->addSeparator();
    helpMenu = menuBar()->addMenu(tr(u8"帮助" ));
    helpMenu->addAction(aboutQtAct);


    //toolBar 工具条
    //fileTooBar添加
    fileToolBar = addToolBar(tr(u8"新建"));     //右键添加改变
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveasAct);
    fileToolBar->addAction(printAct);
    //editToolBar添加
    editToolBar = addToolBar(tr(u8"修改"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(exitAct);



}



/*
void MainWindow::showMainwindow2()
{
    w2.show();
}
*/

/*槽函数实现*/

//子菜单事件
void MainWindow::showStatusAction()
{
    if(statusbar->isVisible())
    {
        statusbar->hide();
        swStatusAct->setIconVisibleInMenu(false);
    }
    else
    {

        statusbar->show();
        swStatusAct->setIconVisibleInMenu(true);
    }
}
void MainWindow::newFile()
{

    currentFile.clear();
    textEdit->setText(QString());
}
void MainWindow::printpreviewAction()
{
    QPrintPreviewDialog dlg;
    connect(&dlg,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printrequest(QPrinter*)));
    dlg.exec();
}
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, u8"打开文件");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setText(text);
    file.close();
}

void MainWindow::saveFile()
{
    QString fileName;
    // 若没有文件,重新创建一个
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::saveasFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, u8"另存为");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::printrequest(QPrinter* printer)
{
    QPainter painter(printer);

    textEdit->render(&painter);

}
void MainWindow::printFile()
{
    QPrintDialog dlg;
    connect(&dlg,SIGNAL(accepted(QPrinter*)),this,SLOT(printrequest(QPrinter*)));
    dlg.exec();

}


void MainWindow::cutAction()
{
    textEdit->cut();
}

void MainWindow::pasteAction()
{
    textEdit->paste();
}

void MainWindow::copyAction()
{
    textEdit->copy();
}

void MainWindow::undoAction()
{
    textEdit->undo();
}

void MainWindow::redoAction()
{
    textEdit->redo();
}

void MainWindow::exitAction()
{
    this->close();
}
void MainWindow::slottextchanged()
{
    if(textEdit->toPlainText().isEmpty())
    {
        status->clear();
    }
    else
    {
        QString st(tr(u8"单词:  "));
        st += QString::number(textEdit->toPlainText().simplified().count(QLatin1Char(' '))+1);
        st += tr(u8"字符数:  ");
        st += QString::number(textEdit->toPlainText().count());
        status->setText(st);
    }
}



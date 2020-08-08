/*
* 版权声明: 暂无
* 文件名称 : mainwindow.cpp
* 创建者 : 徐梓凯
* 创建日期: 2020/7
* 文件描述: 存放项目中编辑器的类
* 历史记录: 2020/7/29 添加时间戳功能，每次修改后状态栏中的时间将会改变，一开始创建时为创建时间，此后相关合理性再行修改
*/

#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QDir>
MainWindow::MainWindow(QString path,QWidget *parent): QMainWindow(parent)
{
    MainWindow();
    currentFile = path;
    qDebug() << currentFile;
    currentDir = path.mid(0,path.lastIndexOf('/'))+'/';
    openFile(currentFile);
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    lastedit = QDateTime::currentDateTime();
    currentDir = QDir::currentPath();
    currentDir += "/locals/Unedit/";
    currentFile = "";
    this->resize(1000,800);
    this->setWindowTitle("notepad");
    this->setWindowIcon(QIcon("./icon/atom_128px.ico"));        //设置应用显示图标
    QWidget* widget = new QWidget();
    //实例菜单和控件
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    helpMenu = new QMenu(this);
    textEdit = new QTextEdit(this);
    textEdit->setFontPointSize(10);
    textEdit->setPlaceholderText(tr(u8"开始书写、拖动文件或选择"));
    statusbar = new QStatusBar(this);
    status = new QLabel("",this);
    lasttime = new QLabel(lastedit.toString(),this);
    statusbar->addWidget(status);
    statusbar->addWidget(lasttime);
    title = new QLineEdit(this);
    title->setPlaceholderText(tr(u8"标题"));
    //使用layout设置内部布局

    //textEdit 信号和槽
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(slottextchanged()));
    connect(textEdit,SIGNAL(selectionChanged()),this,SLOT(slotselectionchanged()));
    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(slotcursorchanged()));

    //填充菜单子节点
    newAct = new QAction(QIcon( "./icon/NewEvent.png" ), tr( u8"新建" ), this );
    newAct->setShortcut(tr("Ctrl+N" ));       					 //快捷键
    newAct->setStatusTip(tr(u8"新建文件" ));     					 //底部状态提示
    openAct = new QAction(QIcon( "./icon/open.png" ), tr( u8"打开" ), this );
    openAct->setShortcut(tr(u8"Ctrl+O" ));
    openAct->setStatusTip(tr(u8"打开文件" ));
    saveAct = new QAction(QIcon( "./icon/save.png" ), tr( u8"保存" ), this );
    saveAct->setShortcut(tr("Ctrl+S" ));
    saveAct->setStatusTip(tr(u8"保存文件" ));
    saveasAct = new QAction(QIcon( "./icon/save-as.png" ), tr( u8"另存为" ), this );
    saveasAct->setShortcut(tr("Ctrl+Shift+S" ));
    saveasAct->setStatusTip(tr(u8"另存为文件" ));
    printAct = new QAction(QIcon( "./icon/print.png" ), tr( u8"打印" ), this );
    printAct->setShortcut(tr("Ctrl+P" ));
    printAct->setStatusTip(tr(u8"打印" ));
    printpreviewAct = new QAction(QIcon("./icon/print-preview.png"),tr(u8"打印预览"),this);
    exitAct = new QAction(QIcon( "./icon/exit.png" ), tr( u8"退出" ), this );
    exitAct->setShortcut(tr("Ctrl+E"));
    exitAct->setStatusTip(tr(u8"关闭"));

    //信号与槽
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAct,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(saveasAct,SIGNAL(triggered()),this,SLOT(saveasFile()));
    connect(printAct,SIGNAL(triggered()),this,SLOT(printFile()));
    connect(printpreviewAct,SIGNAL(triggered()),this,SLOT(printpreviewAction()));
    cutAct = new QAction(QIcon( "./icon/cut.png" ), tr( u8"剪切" ), this );
    cutAct->setShortcut(tr("Ctrl+X" ));
    cutAct->setStatusTip(tr(u8"剪切内容" ));
    copyAct = new QAction(QIcon( "./icon/copy.png" ), tr( u8"复制" ), this );
    copyAct->setShortcut(tr("Ctrl+C" ));
    copyAct->setStatusTip(tr(u8"复制内容" ));
    pasteAct = new QAction(QIcon( "./icon/paste.png" ), tr( u8"粘贴" ), this );
    pasteAct->setShortcut(tr("Ctrl+V" ));
    pasteAct->setStatusTip(tr(u8"粘贴内容" ));
    undoAct = new QAction(QIcon( "./icon/undo.png" ), tr( u8"撤销" ), this );
    undoAct->setShortcut(tr("Ctrl+Z" ));
    undoAct->setStatusTip(tr(u8"向后一步" ));
    redoAct = new QAction(QIcon( "./icon/redo.png" ), tr( u8"重做" ), this );
    redoAct->setShortcut(tr("Ctrl+Y" ));
    redoAct->setStatusTip(tr(u8"向前一步" ));
    aboutQtAct = new QAction(QIcon("./icon/aboutus.png"),tr( u8"关于 Qt" ), this );
    aboutQtAct->setStatusTip(tr(u8"关于 Qt 信息" ));
    selectallAct = new QAction(QIcon("./icon/select-all.png"),tr(u8"全选"),this);
    selectallAct->setStatusTip(tr(u8"全选"));
    selectallAct->setShortcut(tr("Ctrl+A"));

    swStatusAct = new QAction(tr(u8"查看状态栏"),this);
    swStatusAct->setStatusTip(tr(u8"开关底部状态栏"));
    swStatusAct->setIcon(QIcon("./icon/bingo.png"));
    swStyleAct = new QAction(tr(u8"查看格式栏"),this);
    swStyleAct->setStatusTip(tr(u8"开关格式编辑栏"));
    swStyleAct->setIcon(QIcon("./icon/bingo.png"));
    swFileAct = new QAction(tr(u8"查看文件栏"),this);
    swFileAct->setStatusTip(tr(u8"开关文件编辑栏"));
    swFileAct->setIcon(QIcon("./icon/bingo.png"));
    fontAct = new QAction(tr(u8"字体"),this);
    fontAct->setStatusTip(tr(u8"设置字体"));
    fontAct->setEnabled(false);
    fontAct->setShortcut(tr("Ctrl+D"));
    leftAct = new QAction(tr(u8"左对齐"));
    leftAct->setShortcut(tr("Ctrl+L"));
    centerAct = new QAction(tr(u8"居中对齐"));
    centerAct->setShortcut(tr(u8"Ctrl+C"));
    rightAct = new QAction(tr(u8"右对齐"));
    rightAct->setShortcut(tr(u8"Ctrl+R"));
    justifyAct = new QAction(tr(u8"两端对齐"));
    justifyAct->setShortcut(tr(u8"Ctrl+J"));
    colorAct = new QAction(tr(u8"颜色"));
    incindAct = new QAction(tr(u8"增加缩进"));
    incindAct->setShortcut(tr(u8"Ctrl+M"));
    incindAct->setIcon(QIcon(tr(u8"./icon/inc.png")));
    decindAct = new QAction(tr(u8"减少缩进"));
    decindAct->setShortcut(tr(u8"Ctrl+Shift+M"));
    decindAct->setIcon(QIcon(tr(u8"./icon/dec.png")));
    incfsizeAct = new QAction(tr(u8"增大字体"));
    incfsizeAct->setShortcut(tr(u8"Ctrl+Shift+."));
    decfsizeAct = new QAction(tr(u8"减小字体"));
    decfsizeAct->setShortcut(tr(u8"Ctrl+Shift+,"));
    instableAct = new QAction(tr(u8"插入表格"));
    instableAct->setStatusTip(tr(u8"创建表格"));
    instableAct->setIcon(QIcon(tr("./icon/table.png")));
    inslistAct = new QAction(tr(u8"插入列表"));
    inslistAct->setShortcut(tr(u8"Ctrl+Shift+-"));
    inslistAct->setIcon(QIcon(tr(u8"./icon/streamlist.png")));
    paragraphMenu = new QMenu(tr(u8"段落"));
    paragraphMenu->setStatusTip(tr(u8"设置段落"));

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
    connect(swStyleAct,SIGNAL(triggered()),this,SLOT(swStyleAction()));
    connect(swFileAct,SIGNAL(triggered()),this,SLOT(swFileAction()));
    connect(fontAct,SIGNAL(triggered()),this,SLOT(fontAction()));
    connect(leftAct,SIGNAL(triggered()),this,SLOT(leftAction()));
    connect(centerAct,SIGNAL(triggered()),this,SLOT(centerAction()));
    connect(rightAct,SIGNAL(triggered()),this,SLOT(rightAction()));
    connect(justifyAct,SIGNAL(triggered()),this,SLOT(justifyAction()));
    connect(colorAct,SIGNAL(triggered()),this,SLOT(colorAction()));
    connect(incindAct,SIGNAL(triggered()),this,SLOT(incindAction()));
    connect(decindAct,SIGNAL(triggered()),this,SLOT(decindAction()));
    connect(incfsizeAct,SIGNAL(triggered()),this,SLOT(incfsizeAction()));
    connect(decfsizeAct,SIGNAL(triggered()),this,SLOT(decfsizeAction()));
    connect(instableAct,SIGNAL(triggered()),this,SLOT(instableAction()));
    connect(inslistAct,SIGNAL(triggered()),this,SLOT(inslistAction()));
    //填充菜单
    fileMenu = menuBar()->addMenu(tr( u8"文件" ));
    //fileMenu->addAction(newAct);
    // 考虑到文件操作关系，暂时取消掉新建操作
    //fileMenu->addSeparator();
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
    viewMenu->addAction(swStyleAct);
    viewMenu->addAction(swFileAct);
    menuBar()->addSeparator();

    styleMenu = menuBar()->addMenu(tr(u8"格式"));
    styleMenu->addAction(fontAct);
    styleMenu->addAction(colorAct);
    styleMenu->addMenu(paragraphMenu);
    paragraphMenu->addAction(leftAct);
    paragraphMenu->addAction(centerAct);
    paragraphMenu->addAction(rightAct);
    paragraphMenu->addAction(justifyAct);
    paragraphMenu->addSeparator();
    paragraphMenu->addAction(incindAct);
    paragraphMenu->addAction(decindAct);
    paragraphMenu->addSeparator();
    paragraphMenu->addAction(incfsizeAct);
    paragraphMenu->addAction(decfsizeAct);
    styleMenu->addSeparator();
    styleMenu->addAction(instableAct);
    styleMenu->addAction(inslistAct);
    menuBar()->addSeparator();


    helpMenu = menuBar()->addMenu(tr(u8"帮助" ));
    helpMenu->addAction(aboutQtAct);

    //toolBar 工具条
    //fileTooBar添加
    fileToolBar = addToolBar(tr(u8"编辑"));     //右键添加改变
    //fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveasAct);
    fileToolBar->addAction(printAct);
    //fileToolBar->addSeparator();
    fileToolBar->addAction(cutAct);
    fileToolBar->addAction(copyAct);
    fileToolBar->addAction(pasteAct);
    fileToolBar->addAction(undoAct);
    fileToolBar->addAction(redoAct);
    fileToolBar->addAction(exitAct);

    styleToolBar = addToolBar(tr(u8"格式"));
    styleToolBar->addWidget(fontBox = new QFontComboBox());
    styleToolBar->addWidget(sizeBox = new QComboBox());
    styleToolBar->addWidget(colorBox = new ColorCombox());
    styleToolBar->addWidget(boldbutton = new QPushButton());
    styleToolBar->addWidget(italicbutton = new QPushButton());
    styleToolBar->addWidget(underlinebutton = new QPushButton());
    styleToolBar->addWidget(overlinebutton = new QPushButton());
    styleToolBar->addWidget(highlightbutton = new QPushButton());
    styleToolBar->addSeparator();
    styleToolBar->addWidget(alignmentbutton = new QPushButton());
    styleToolBar->addAction(incindAct);
    styleToolBar->addAction(decindAct);
    styleToolBar->addSeparator();
    styleToolBar->addAction(instableAct);
    styleToolBar->addAction(inslistAct);
    alignmentmenu = new QMenu;
    alignmentbutton->setFlat(true);
    alignmentbutton->setIcon(QIcon(tr("./icon/la.png")));
    alignmentbutton->setMenu(alignmentmenu);
    alignmentmenu->addAction(leftAct);
    alignmentmenu->addAction(centerAct);
    alignmentmenu->addAction(rightAct);
    italicbutton->setCheckable(true);
    italicbutton->setIcon(QIcon("./icon/italic.png"));
    italicbutton->setToolTip(tr(u8"斜体(Ctrl+I)"));
    italicbutton->setShortcut(tr(u8"Ctrl+I"));
    italicbutton->setFlat(true);
    italicbutton->setFocusPolicy(Qt::NoFocus);
    boldbutton->setFlat(true);
    boldbutton->setIcon(QIcon("./icon/bold.png"));
    boldbutton->setToolTip(tr(u8"加粗(Ctrl+B)"));
    boldbutton->setShortcut(tr(u8"Ctrl+B"));
    boldbutton->setCheckable(true);
    boldbutton->setFocusPolicy(Qt::NoFocus);
    underlinebutton->setFlat(true);
    underlinebutton->setCheckable(true);
    underlinebutton->setIcon(QIcon("./icon/under-line.png"));
    underlinebutton->setShortcut(tr(u8"Ctrl+U"));
    underlinebutton->setToolTip(tr(u8"下划线(Ctrl+U)"));
    underlinebutton->setFocusPolicy(Qt::NoFocus);
    overlinebutton->setFlat(true);
    overlinebutton->setCheckable(true);
    overlinebutton->setIcon(QIcon("./icon/tt_deleteline.png"));
    overlinebutton->setShortcut(tr(u8"Ctrl+T"));
    overlinebutton->setToolTip(tr(u8"上划线(Ctrl+T)"));
    overlinebutton->setFocusPolicy(Qt::NoFocus);
    highlightbutton->setFlat(true);
    highlightbutton->setCheckable(true);
    highlightbutton->setIcon(QIcon("./icon/highlight.png"));
    highlightbutton->setShortcut(tr(u8"Ctrl+Shift+H"));
    highlightbutton->setToolTip(tr(u8"高亮(Ctrl+Shift+H)"));
    highlightbutton->setFocusPolicy(Qt::NoFocus);
    /*
    addcheckboxbutton->setFlat(true);
    addcheckboxbutton->setIcon(QIcon("../icon/check-box.png"));
    addcheckboxbutton->setShortcut(tr(u8"Ctrl+Shift+C"));
    addcheckboxbutton->setToolTip(tr(u8"添加复选框(Ctrl+Shift+C"));
    addcheckboxbutton->setCursor(Qt::PointingHandCursor);
    addcheckboxbutton->setFocusPolicy(Qt::NoFocus);
    */
    sizeBox->addItem("6");
    sizeBox->addItem("7");
    sizeBox->addItem("8");
    sizeBox->addItem("9");
    sizeBox->addItem("10");
    sizeBox->addItem("11");
    sizeBox->addItem("12");
    sizeBox->addItem("14");
    sizeBox->addItem("16");
    sizeBox->addItem("18");
    sizeBox->addItem("20");
    sizeBox->addItem("22");
    sizeBox->addItem("24");
    sizeBox->addItem("26");
    sizeBox->addItem("28");
    sizeBox->addItem("36");
    sizeBox->addItem("48");
    sizeBox->addItem("72");
    sizeBox->setCurrentText(QString::number(textEdit->fontPointSize()));
    fontBox->setEditable(false);
    fontBox->setCursor(Qt::PointingHandCursor);
    fontBox->setFocusPolicy(Qt::NoFocus);
    colorBox->setButtonIcon("./icon/font.png",textEdit->textColor());


    connect(colorBox,SIGNAL(sigColorChanged(QColor)),this,SLOT(slotcolorchanged(const QColor)));
    connect(sizeBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slotsizechanged(const QString &)));
    connect(fontBox,SIGNAL(currentFontChanged(QFont)),this,SLOT(slotfontchanged(const QFont &)));
    connect(boldbutton,SIGNAL(toggled(bool)),this,SLOT(slotboldclicked(const bool&)));
    connect(italicbutton,SIGNAL(clicked()),this,SLOT(slotitalicclicked()));
    connect(overlinebutton,SIGNAL(clicked()),this,SLOT(slotoverlineclicked()));
    connect(underlinebutton,SIGNAL(clicked()),this,SLOT(slotunderlineclicked()));
    connect(highlightbutton,SIGNAL(clicked()),this,SLOT(slothighlightclicked()));

    vboxlayout = new QVBoxLayout();
    hboxlayout = new QHBoxLayout();
    hboxlayout->addWidget(title);
    QToolButton* printbutton = new QToolButton;
    QToolButton* stickbutton = new QToolButton;
    printbutton->setStyleSheet("QToolButton{border:0px}");
    stickbutton->setStyleSheet("QToolButton{border:0px}");
    stickbutton->setIcon(QIcon(tr("./icon/sticky-note-line.png")));
    printbutton->setIcon(QIcon(tr("./icon/print.png")));
    printbutton->setToolTip(tr(u8"打印"));
    stickbutton->setToolTip(tr(u8"贴上"));
    printbutton->setFocusPolicy(Qt::NoFocus);
    stickbutton->setFocusPolicy(Qt::NoFocus);


    hboxlayout->addWidget(printbutton);
    hboxlayout->addWidget(stickbutton);
    vboxlayout->addWidget(fileToolBar);
    vboxlayout->addLayout(hboxlayout);
    vboxlayout->addWidget(styleToolBar);
    vboxlayout->addWidget(textEdit);
    vboxlayout->addWidget(statusbar);
    this->setCentralWidget(widget);
    centralWidget()->setLayout(vboxlayout);

    connect(stickbutton,SIGNAL(clicked()),this,SLOT(slotsticky()));
    connect(printbutton,SIGNAL(clicked()),this,SLOT(printFile()));

}
void MainWindow::slotsticky()
{
    saveFile();
    StickyNote* s = new StickyNote(currentFile,this);
    s->show();

}
void MainWindow::slotcolorchanged(const QColor &c)
{
    textEdit->setTextColor(c);
    colorBox->setButtonIcon("./icon/font.png",c);
}
void MainWindow::slotfontchanged(const QFont &f)
{
    QTextCharFormat fmt = textEdit->textCursor().charFormat();
    fmt.setFont(f);
    textEdit->setCurrentCharFormat(fmt);
}

void MainWindow::slotsizechanged(const QString& s)
{
    textEdit->setFontPointSize(s.toInt());
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
void MainWindow::swStyleAction()
{
    if(styleToolBar->isVisible())
    {
        styleToolBar->hide();
        swStyleAct->setIconVisibleInMenu(false);
    }
    else
    {
        styleToolBar->show();
        swStyleAct->setIconVisibleInMenu(true);
    }
}
void MainWindow::swFileAction()
{
    if(fileToolBar->isVisible())
    {
        fileToolBar->hide();
        swFileAct->setIconVisibleInMenu(false);
    }
    else
    {
        fileToolBar->show();
        swFileAct->setIconVisibleInMenu(true);
    }
}
void MainWindow::newFile()
{


}
void MainWindow::printpreviewAction()
{
    QPrintPreviewDialog dlg;
    connect(&dlg,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printrequest(QPrinter*)));
    dlg.exec();
}
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, u8"打开文件",NULL,tr("XML files(*xml)"));
    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setHtml(text);
    file.close();
}
void MainWindow::openFile(QString path)
{
    QFile file(path);
    currentFile = path;
    qDebug() << currentFile;
    currentDir = path.mid(0,path.lastIndexOf('/'))+'/';
    setWindowTitle(path);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    QTextStream in(&file);

    QStringList textlist = in.readAll().split("@#4.");
    qDebug()<<textlist.at(0);
    qDebug()<<textlist.at(1);
    textEdit->blockSignals(true);
    textEdit->setHtml(textlist.at(0));
    title->setText(textlist.at(1));
    lastedit = QDateTime::fromString(textlist.at(2));
    lasttime->setText(lastedit.toString());
    textEdit->blockSignals(false);
    file.close();
}
void MainWindow::saveFile()
{
    QString fileName;
    QFile file;
    qDebug() <<currentFile;
    if(currentFile == "")
    {
        fileName = currentDir;
        if(title->text().isEmpty())
            fileName+="unamed";
        else
            fileName+=title->text();
        fileName+=".xml";
        file.setFileName(fileName);
        uint count = 1;
        while(file.exists())
        {
            QString new_fileName = fileName;
            new_fileName.insert(fileName.lastIndexOf('.'),"("+QString::number(count)+")");
            count++;
            file.setFileName(new_fileName);
        }
        currentFile = file.fileName();
    }
    else
    {
        file.setFileName(currentFile);
    }
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    setWindowTitle(file.fileName());
    QTextStream out(&file);
    QString text = textEdit->toHtml();
    text.append("@#4.");
    text.append(title->text());
    text.append("@#4.");
    text.append(lastedit.toString());
    out << text;
    file.close();
}

void MainWindow::saveasFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, u8"另存为",NULL,tr("XML files(*xml)"));
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, u8"警告", u8"无法打开文件: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = textEdit->toHtml();
    text.append("@#4.");
    text.append(title->text());
    text.append("@#4.");
    text.append(lastedit.toString());
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
        st += tr(u8"   字符数:  ");
        st += QString::number(textEdit->toPlainText().count());
        status->setText(st);
    }
    lastedit = QDateTime::currentDateTime();
    lasttime->setText(lastedit.toString());
}
void MainWindow::slotselectionchanged()
{
    if(textEdit->textCursor().selectedText().isEmpty())
    {
        fontAct->setEnabled(false);

    }
    else
    {
        fontAct->setEnabled(true);

    }
}
void MainWindow::fontAction()
{
    bool ok;
    QTextCharFormat fmt= textEdit->textCursor().charFormat();
    QFont font = QFontDialog::getFont(&ok,textEdit->textCursor().charFormat().font());
    fmt.setFont(font);
    textEdit->textCursor().setCharFormat(fmt);

}
void MainWindow::leftAction()
{
    textEdit->setAlignment(Qt::AlignLeft);
}
void MainWindow::centerAction()
{
    textEdit->setAlignment(Qt::AlignCenter);
}
void MainWindow::rightAction()
{
    textEdit->setAlignment(Qt::AlignRight);
}
void MainWindow::justifyAction()
{
    textEdit->setAlignment(Qt::AlignJustify);
}
void MainWindow::colorAction()
{
    QColor col = QColorDialog::getColor(textEdit->textColor());
    textEdit->setTextColor(col);
}
void MainWindow::incindAction()
{
    QTextBlockFormat bf;
    bf= textEdit->textCursor().blockFormat();
    bf.setLeftMargin(bf.leftMargin()+40);
    textEdit->textCursor().setBlockFormat(bf);
}
void MainWindow::decindAction()
{
    QTextBlockFormat bf;
    bf= textEdit->textCursor().blockFormat();
    if(bf.leftMargin()>=40)
        bf.setLeftMargin(bf.leftMargin()-40);

    textEdit->textCursor().setBlockFormat(bf);
}
void MainWindow::incfsizeAction()
{

   QTextCharFormat fmt = textEdit->textCursor().charFormat();
   fmt.setFontPointSize(fmt.fontPointSize()+10);
   textEdit->textCursor().setCharFormat(fmt);

}
void MainWindow::decfsizeAction()
{
    QTextCharFormat fmt = textEdit->textCursor().charFormat();
    fmt.setFontPointSize(fmt.fontPointSize()+1);
    textEdit->textCursor().setCharFormat(fmt);
}
void MainWindow::instableAction()
{
    AskTable x;
    x.exec();
    tcpserver = new QTcpServer;
    tcpserver->listen(QHostAddress("127.0.0.1"),9988);
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(slotNetConnection()));
}
void MainWindow::inslistAction()
{

}
void MainWindow::slotNetConnection()
{
    while(tcpserver->hasPendingConnections())
    {
        //调用nextPeddingConnection去获得连接得socket
         tcpsocket = tcpserver->nextPendingConnection();

        //为新得socket提供槽函数，来接受数据
        connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(slotreadyread()));
    }
}

void MainWindow::slotreadyread()
{
    while(tcpsocket->bytesAvailable()>0)
    {
        QByteArray ba = tcpsocket->readAll();
        QByteArrayList bl = ba.split('\n');
        QTextTableFormat fmt;
        fmt.setCellPadding(10);
        QTextTable* tt = textEdit->textCursor().insertTable(bl.begin()->toInt(),bl.back().toInt(),fmt);

    }
}
void MainWindow::slotcursorchanged()
{
    fontBox->blockSignals(true);
    sizeBox->blockSignals(true);
    colorBox->blockSignals(true);
    boldbutton->blockSignals(true);
    italicbutton->blockSignals(true);
    underlinebutton->blockSignals(true);
    overlinebutton->blockSignals(true);
    highlightbutton->blockSignals(true);
    fontBox->setCurrentFont(textEdit->textCursor().charFormat().font());
    sizeBox->setCurrentText(QString::number(textEdit->fontPointSize()));
    colorBox->setButtonIcon("./icon/font.png",textEdit->textColor());
    if(textEdit->textCursor().charFormat().fontWeight() == QFont::Bold)
    {
       boldbutton->setChecked(true);
    }
    else
        boldbutton->setChecked(false);
    if(textEdit->textCursor().charFormat().fontItalic()==true)
    {
       italicbutton->setChecked(true);
    }
    else
        italicbutton->setChecked(false);
    if(textEdit->textCursor().charFormat().fontUnderline()==true)
    {
       underlinebutton->setChecked(true);
    }
    else
        underlinebutton->setChecked(false);
    if(textEdit->textCursor().charFormat().fontOverline()==true)
    {
       overlinebutton->setChecked(true);
    }
    else
        overlinebutton->setChecked(false);
    if(textEdit->textBackgroundColor()==Qt::yellow)
    {
        highlightbutton->setChecked(true);
    }
    else
        highlightbutton->setChecked(false);
    fontBox->blockSignals(false);
    sizeBox->blockSignals(false);
    colorBox->blockSignals(false);
    boldbutton->blockSignals(false);
    italicbutton->blockSignals(false);
    underlinebutton->blockSignals(false);
    overlinebutton->blockSignals(false);
    highlightbutton->blockSignals(false);

}
void MainWindow::slotboldclicked(const bool&)
{

    QTextCharFormat f = textEdit->textCursor().charFormat();
    f.setFontWeight(boldbutton->isChecked()?QFont::Bold:QFont::Normal);
    textEdit->setCurrentCharFormat(f);
}
void MainWindow::slotitalicclicked()
{
    QTextCharFormat f = textEdit->textCursor().charFormat();
    f.setFontItalic(italicbutton->isChecked()?true:false);
    textEdit->setCurrentCharFormat(f);
}
void MainWindow::slotunderlineclicked()
{
    QTextCharFormat f = textEdit->textCursor().charFormat();
    f.setFontUnderline(underlinebutton->isChecked()?true:false);
    textEdit->setCurrentCharFormat(f);
}
void MainWindow::slotoverlineclicked()
{
    QTextCharFormat f = textEdit->textCursor().charFormat();
    f.setFontOverline(overlinebutton->isChecked()?true:false);
    textEdit->setCurrentCharFormat(f);
}
void MainWindow::slothighlightclicked()
{
    QTextCharFormat f = textEdit->textCursor().charFormat();
    textEdit->setTextBackgroundColor(highlightbutton->isChecked()?Qt::yellow:Qt::white);
}


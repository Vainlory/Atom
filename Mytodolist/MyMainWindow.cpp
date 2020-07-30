﻿/*
* 版权声明: 暂无
* 文件名称 : MyMainWindow.cpp
* 创建者 : 徐梓凯
* 创建日期: 2020/7
* 文件描述: 应用主窗口的类
* 历史记录:
*/
#include "MyMainWindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent)
{
    /* 系统托盘窗口 */

    _menu = new QMenu();
    min = new QAction(tr(u8"窗口最小化"),this);
    Exit = new QAction(tr(u8"退出"),this);
    max = new QAction(tr(u8"窗口最大化"),this);
    _sysicon = new QSystemTrayIcon();
    _add_ = new QPushButton(this);

    _sysicon->setIcon(QIcon("./icon/atom_128px.ico"));
    _sysicon->setContextMenu(_menu);
    _menu->addAction(min);
    _menu->addAction(max);
    _menu->addAction(Exit);

    //connect(max,&QAction::triggered,this,&QMainWindow::showMaximized);
    connect(Exit,SIGNAL(triggered()),this,SLOT(close()));
    connect(min,SIGNAL(triggered()),this,SLOT(showMinimized()));
    connect(_sysicon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(_add_,SIGNAL(clicked()),this,SLOT(slotnotepad()));

    this->resize(300,700);
    this->setMinimumSize(300,700);
    this->setMaximumSize(300,700);
    this->setWindowIcon(QIcon("./icon/atom_128px.ico"));


    _sysicon->show();

    /* 控件 */

    filter = new Filter;

    connect(filter,SIGNAL(itemPressed(QTreeWidgetItem*, int)),this,SLOT(on_pressedTreeWidgetItem(QTreeWidgetItem*, int)));
    connect(filter,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(OpenAction(QTreeWidgetItem*,int)));
    connect(filter,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(nameChanged(QTreeWidgetItem*, int)));

    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(filter);
    layout->addWidget(_add_);
    this->setCentralWidget(widget);
    centralWidget()->setLayout(layout);

    son_menu = new QMenu();
    parent_menu = new QMenu();

    OpenAct = new QAction();
    RenameAct = new QAction();
    NewAct = new QAction();

    OpenAct->setText(tr(u8"打开"));
    RenameAct->setText(tr(u8"重命名"));
    NewAct->setText(tr(u8"添加笔记"));

    son_menu->addAction(OpenAct);
    son_menu->addAction(RenameAct);

    parent_menu->addAction(RenameAct);
    parent_menu->addAction(NewAct);

    connect(RenameAct,SIGNAL(triggered()),this,SLOT(RenameAction()));
    connect(OpenAct,SIGNAL(triggered()),this,SLOT(OpenAction()));
    connect(NewAct,SIGNAL(triggered()),this,SLOT(NewAction()));

}
void MyMainWindow::closeEvent(QCloseEvent * event)
{
    QObject* obj =  QMainWindow::sender();
    QAction* act = qobject_cast<QAction*>(obj);
    if(act)
       {
            _sysicon->hide();
           event->accept();
       }
       else if(this->isVisible())
    {
        this->hide();
        _sysicon->showMessage(tr(u8"Qt托盘"),tr(u8"this is your first to get it"));
        event->ignore();
    }
    else
        {
            _sysicon->hide();
           event->accept();
        }

}
void MyMainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {

        case QSystemTrayIcon::Trigger:
            break;
        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;
        default:
            break;
    }
}
void MyMainWindow::slotnotepad()
{
    w = new MainWindow();
    w->show();
    filter->buildtree();
}
void MyMainWindow::on_pressedTreeWidgetItem(QTreeWidgetItem* which, int column)
{
    if(QApplication::mouseButtons() != Qt::RightButton)
        return;
    if(which->parent()==NULL)
        parent_menu->exec(QCursor::pos());
    else
        son_menu->exec(QCursor::pos());
}
void MyMainWindow::OpenAction()
{
    QTreeWidgetItem* choice = filter->currentItem();
    QString a = filter->currentDir+choice->parent()->text(0)+"/"+choice->text(0)+".xml";

    w = new MainWindow();
    w->openFile(a);
    w->show();
    filter->buildtree();
}
void MyMainWindow::OpenAction(QTreeWidgetItem* which, int column)
{
    if(which->parent() == NULL)
    {
        RenameAction();
        return;
    }
    QString a = filter->currentDir + which->parent()->text(0)+"/"+which->text(0)+".xml";

    w = new MainWindow();
    w->openFile(a);
    w->show();
    filter->buildtree();
}
void MyMainWindow::RenameAction()
{
    prename = filter->currentItem()->text(0);

    filter->editItem(filter->currentItem());



}
void MyMainWindow::nameChanged(QTreeWidgetItem* which, int)
{
    qDebug()<<"nameChanged";
    if(which == new_item)
    {
        AddNew(which,0);
        return;
    }
    if(which->text(0).isEmpty())
    {
        QMessageBox::warning(this,u8"警告",u8"不合法文件名");
        which->setText(0,prename);
        return;
    }
    if(which->parent()==NULL)
    {
       QFile::rename(filter->currentDir+prename,filter->currentDir+which->text(0));

    }
    else
    {
        QString new_name,str;
        str = filter->currentDir+which->parent()->text(0)+'/'+which->text(0);
        new_name = str+".xml";
        QFile file(new_name);
        int count =1;
        while(file.exists())
        {
           new_name = str + "("+QString::number(count)+")"+".xml";
           file.setFileName(new_name);
           count++;
        }

        QFile::rename(filter->currentDir+which->parent()->text(0)+'/'+prename+".xml",
                      new_name);


    }
    filter->buildtree();
    filter->expandAll();
}
void MyMainWindow::NewAction()
{
    filter->blockSignals(true);
    QTreeWidgetItem* pitem = new QTreeWidgetItem;
    filter->currentItem()->addChild(pitem);
    pitem->setFlags(pitem->flags() |Qt::ItemIsEditable);
    filter->currentItem()->setExpanded(true);
    filter->blockSignals(false);
    filter->editItem(pitem);
    new_item = pitem;
}
void MyMainWindow::AddNew(QTreeWidgetItem* pitem,int column)
{
    if(pitem->text(0).isEmpty())
    {
        pitem->parent()->removeChild(pitem);
    }
    else
    {
        QString new_name,str;
        str = filter->currentDir+pitem->parent()->text(0)+'/'+pitem->text(0);
        new_name = str+".xml";
        qDebug()<< str;
        QFile file(new_name);
        int count =1;
        while(file.exists())
        {
            new_name = str + "(" + QString::number(count) + ")" + ".xml";
            file.setFileName(new_name);
            count++;
        }

        file.open(QIODevice::ReadWrite);
        QTextStream out(&file);
        out<<"@#4.@#4.";
        file.close();
        qDebug() <<"open";
        filter->buildtree();
        qDebug() <<"open";
        filter->expandAll();
        qDebug() <<"open";
    }
}

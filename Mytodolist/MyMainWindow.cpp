/*
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

    QWidget* widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(filter);
    layout->addWidget(_add_);
    this->setCentralWidget(widget);
    centralWidget()->setLayout(layout);

    right_menu = new QMenu();

    OpenAct = new QAction();
    OpenAct->setText(tr(u8"打开"));

    right_menu->addAction(OpenAct);

    connect(OpenAct,SIGNAL(triggered()),this,SLOT(OpenAction()));

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
        return;
    right_menu->exec(QCursor::pos());
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

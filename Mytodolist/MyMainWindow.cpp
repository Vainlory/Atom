#include "MyMainWindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent)
{
    /* 系统托盘窗口 */
    QMenuBar* _menubar = new QMenuBar;
    _menu1 = new QMenu();
    QAction* min = new QAction("&窗口最小化",this);
    connect(min,&QAction::triggered,this,&QMainWindow::showMinimized);
    QAction* max = new QAction("&窗口最大化",this);
    connect(max,&QAction::triggered,this,&QMainWindow::showMaximized);
    QAction* Exit = new QAction("&Exit",this);
    connect(Exit,SIGNAL(triggered()),this,SLOT(close()));
    _menu->addAction(min);
    _menu->addAction(max);
    _menu->addAction(Exit);
    this->resize(300,700);
    this->setMinimumSize(300,700);
    this->setMaximumSize(300,700);
    this->setWindowIcon(QIcon("../icon/atom_128px.ico"));
    _sysicon = new QSystemTrayIcon();
    _sysicon->setIcon(QIcon("../icon/atom_128px.ico"));
    _sysicon->setContextMenu(_menu1);
    connect(_sysicon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    _sysicon->show();

    /* 控件 */
    _add_ = new QPushButton(this);
    _add_->setGeometry(225,500,60,60);
    _add_->setIcon(QIcon("../icon/increase.png"));
    _add_->setToolTip("新建");
    _add_->setStyleSheet("QPushButton{background-color:rgb(0,255,0);color: white;   border-radius: 30px;  border: 2px groove gray; border-style: outset;}" // 按键本色
            "QPushButton:hover{background-color:rgb(2,255,2); color: black;}"  // 鼠标停放时的色彩
            "QPushButton:pressed{background-color:rgb(2,255,2); border-style: inset; }" );  // 鼠标按下的色彩


}
void MyMainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawEllipse(QRectF(50,50,50,50));
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
        _sysicon->showMessage("Qt托盘","this is your first to get it");
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

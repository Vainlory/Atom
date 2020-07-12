#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    this->setGeometry(0,0,200,200);
    QTextBrowser* _browser;
    _browser = new QTextBrowser(this);
    _browser->setStyleSheet("background:transparent;border-width:0;border-style:outset;font-size:50px");
    _browser->setText("喜欢肥猪");
    //show();
}
void MyWidget::paintEvent(QPaintEvent *event)
{

}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        last_mouse_position_ = event->globalPos();
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
            return;
    const QPoint position = pos() + event->globalPos() - last_mouse_position_; //the position of mainfrmae + (current_mouse_position - last_mouse_position)
    move(position.x(), position.y());
    last_mouse_position_ = event->globalPos();
}

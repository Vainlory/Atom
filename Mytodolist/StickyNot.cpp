#include "StickyNot.h"
#include <QDialog>
StickyNot::StickyNot()
{
    LockButton = new QPushButton;
    CloseButton = new QPushButton;
    OnTopButton = new QPushButton;

    LockButton->setFlat(true);
    CloseButton->setFlat(true);
    OnTopButton->setFlat(true);
    LockButton->setIcon(QIcon(tr("./icon/lock.png")));
    CloseButton->setIcon(QIcon(tr("./icon/close.png")));
    OnTopButton->setIcon(QIcon(tr("./icon/ontop.png")));

    QHBoxLayout* subtitle = new QHBoxLayout;
    subtitle->addWidget(LockButton);
    subtitle->addWidget(CloseButton);
    subtitle->addWidget(OnTopButton);


    has_mask=false;
    startTimer(20);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    label = new QLabel;
    label->setText(tr(u8"测试效果"));
    label->setAlignment(Qt::AlignCenter);
    layout = new QVBoxLayout(this);

    layout->setContentsMargins(0,0,0,0);
    layout->addLayout(subtitle);
    layout->addWidget(label);

    this->installEventFilter(this);
}

void StickyNot::enterEvent(QEvent *event)
{
    has_mask = true;
    QWidget::enterEvent(event);
}
void StickyNot::leaveEvent(QEvent *event)
{
    has_mask = false;
    QWidget::leaveEvent(event);
}
void StickyNot::timerEvent(QTimerEvent *event)
{
    update();
    QWidget::timerEvent(event);
}
void StickyNot::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(has_mask)
    {
         painter.fillRect(rect(),QColor(50,50,50,150));
    }
    QWidget::paintEvent(event);
}
bool StickyNot::eventFilter(QObject* obj,QEvent* evt)
{
    static QPoint mousePoint;
        static bool mousePressed = false;

        QMouseEvent *event = static_cast<QMouseEvent *>(evt);
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (event->button() == Qt::LeftButton)
            {
                mousePressed = true;
                mousePoint = event->globalPos() - pos();
                return true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            mousePressed = false;
            return true;
        }
        else if (event->type() == QEvent::MouseMove)
        {
            if (mousePressed && (event->buttons() == Qt::LeftButton))
            {
                move(event->globalPos() - mousePoint);
                return true;
            }
        }
        return QObject::eventFilter(obj, evt);
}

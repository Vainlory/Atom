#include "StickyNote.h"
StickyNote::StickyNote(QWidget* parent) : QWidget(parent)
{

}
StickyNote::StickyNote(QString path,QWidget *parent) : QWidget(parent)
{
    LockButton = new QPushButton;
    CloseButton = new QPushButton;


    LockButton->setFlat(true);
    CloseButton->setFlat(true);

    LockButton->setIcon(QIcon(tr("./icon/unlock.png")));
    CloseButton->setIcon(QIcon(tr("./icon/close.png")));

    QFile file(path);

    file.open(QIODevice::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString text = in.readAll();
    QStringList textlist = text.split("@#4.");
    file.close();


    connect(LockButton,SIGNAL(clicked()),this,SLOT(LockSlot()));
    connect(CloseButton,SIGNAL(clicked()),this,SLOT(CloseAction()));


    QHBoxLayout* subtitle = new QHBoxLayout;
    subtitle->addWidget(LockButton);
    subtitle->addWidget(CloseButton);


    has_mask=false;
    startTimer(20);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);

    title = new QLabel;
    content = new QTextBrowser;

    title->setText(textlist.at(1));
    title->setAlignment(Qt::AlignCenter);
    content->setHtml(textlist.at(0));
    content->setAlignment(Qt::AlignCenter);
    content->setMouseTracking(true);
    content->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    content->setAttribute(Qt::WA_TransparentForMouseEvents);

    layout = new QVBoxLayout(this);

    layout->setContentsMargins(0,0,0,0);
    layout->addLayout(subtitle);
    layout->addWidget(title);
    layout->addWidget(content);


    this->installEventFilter(this);
}
void StickyNote::enterEvent(QEvent *event)
{
    has_mask = true;
    QWidget::enterEvent(event);
}
void StickyNote::leaveEvent(QEvent *event)
{
    has_mask = false;
    QWidget::leaveEvent(event);
}
void StickyNote::timerEvent(QTimerEvent *event)
{
    update();
    QWidget::timerEvent(event);
}
void StickyNote::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(has_mask)
    {
         painter.fillRect(rect(),QColor(50,50,50,150));
    }
    QWidget::paintEvent(event);
}
bool StickyNote::eventFilter(QObject* obj,QEvent* evt)
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
void StickyNote::LockSlot()
{
    static bool is_lock=true;
    qDebug() << is_lock;
    if(is_lock)
    {
        LockButton->setIcon(QIcon(tr(u8"./icon/lock.png")));
        CloseButton->hide();

        is_lock = false;
    }
    else
    {
        LockButton->setIcon(QIcon(tr(u8"./icon/unlock.png")));
        CloseButton->show();

        is_lock = true;

    }
}
void StickyNote::CloseAction()
{
    this->close();
}


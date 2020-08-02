#ifndef STICKYNOT_H
#define STICKYNOT_H

#include <QDialog>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QTimerEvent>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QEvent>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class StickyNot : public QWidget
{

public:
    StickyNot();
    QVBoxLayout* layout;
    QLabel* label;
    QTextBrowser* tbo;
    bool has_mask;
    QPushButton* LockButton;
    QPushButton* OnTopButton;
    QPushButton* CloseButton;
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void timerEvent(QTimerEvent * event);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject*,QEvent*);
};

#endif // STICKYNOT_H

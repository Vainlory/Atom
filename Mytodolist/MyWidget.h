#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QPalette>
#include <QMouseEvent>
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    QPoint last_mouse_position_;
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
signals:

};

#endif // MYWIDGET_H

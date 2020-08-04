#ifndef STICKYNOTE_H
#define STICKYNOTE_H

#include <QWidget>
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
#include <QFile>

class StickyNote : public QWidget
{
    Q_OBJECT
public:
    explicit StickyNote(QWidget *parent = nullptr);
    explicit StickyNote(QString file,QWidget* parent = nullptr);
    QVBoxLayout* layout;
    QLabel* title;
    QTextBrowser* content;

    bool has_mask;
    QPushButton* LockButton;
    QPushButton* CloseButton;
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void timerEvent(QTimerEvent * event);
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject*,QEvent*);
signals:

public slots:
    void LockSlot();
    void CloseAction();

};

#endif // STICKYNOTE_H

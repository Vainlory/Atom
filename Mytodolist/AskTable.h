#ifndef ASKTABLE_H
#define ASKTABLE_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QTcpServer>
#include <QPushButton>
#include <QByteArray>
#include <QDebug>
class AskTable : public QDialog
{
    Q_OBJECT
public:
    explicit AskTable(QWidget *parent = nullptr);
    QGroupBox* group;
    QTcpSocket* tcp;
    QSpinBox* lin,*col;
signals:
public slots:
    void slotbuttonclicked();
};

#endif // ASKTABLE_H

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QCryptographicHash>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QPicture>
#include <QPalette>
#include <QAction>
#include <QCheckBox>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlTableModel>
#include <QVariant>
#include <QMessageBox>
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    QLabel* autologin_text;
    QLabel* remeberpass_text;
    QLabel* pic;
    QLabel* logo;
    QAction* passwordisvisble;
    QLineEdit* account_in;
    QLineEdit* password_in;
    QCheckBox* autologin;
    QCheckBox* remeberpass;
    QPushButton* enter;
    QSqlTableModel* model;


signals:

public slots:
    void passwordvision();
    void enterslot();
};

#endif // LOGINWIDGET_H

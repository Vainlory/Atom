#include "LoginWidget.h"
#include "mainwindow.h"
#include "MyMainWindow.h"
LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent)
{

    logo = new QLabel();
    account_in = new QLineEdit();
    password_in = new QLineEdit();
    autologin = new QCheckBox();
    remeberpass = new QCheckBox();
    autologin_text = new QLabel(tr("自动登录"));
    remeberpass_text = new QLabel(tr("记住密码"));
    enter = new QPushButton();
    model = new QSqlTableModel;


    QPixmap pix,logo_p;
    QPalette palette(this->palette());
    pix.load("./picture/OIP.jfif");
    logo_p.load("./icon/atom_128px.ico");
    palette.setBrush(QPalette::Background,QBrush(pix));

    model->setTable("account_table");
    model->select();
    logo->setPixmap(logo_p);
    account_in->setPlaceholderText(tr("账号"));
    password_in->setEchoMode(QLineEdit::Password);
    password_in->setPlaceholderText(tr("密码"));
    autologin_text->setStyleSheet("color:white");
    remeberpass_text->setStyleSheet("color:white");
    enter->setIcon(QIcon("./icon/Login.png"));
    enter->setIconSize(QSize(100,50));
    enter->setFlat(true);


    this->resize(pix.size());
    this->setPalette(palette);

    QVBoxLayout* vBox1 = new QVBoxLayout(this);
    QVBoxLayout* vBox2 = new QVBoxLayout;
    QHBoxLayout* hBox1 = new QHBoxLayout;
    QHBoxLayout* hBox2 = new QHBoxLayout;
    QHBoxLayout* hBox3 = new QHBoxLayout;
    QVBoxLayout* vBox3 = new QVBoxLayout;

    vBox1->addSpacing(100);
    vBox1->addLayout(hBox2);
    vBox1->addLayout(hBox3);
    vBox3->addWidget(account_in);
    vBox3->addWidget(password_in);
    vBox3->addLayout(hBox1);
    vBox2->addWidget(logo);

    hBox2->addLayout(vBox2);
    hBox2->addLayout(vBox3);
    hBox1->addWidget(remeberpass);
    hBox1->addWidget(remeberpass_text);
    hBox1->addStretch();
    hBox1->addWidget(autologin);
    hBox1->addWidget(autologin_text);
    hBox1->addStretch();
    hBox3->addStretch();
    hBox3->addWidget(enter);
    hBox3->addStretch();

    passwordisvisble = new QAction;
    passwordisvisble->setIcon(QIcon("./icon/invisible.png"));
    password_in->addAction(passwordisvisble,QLineEdit::TrailingPosition);

    connect(passwordisvisble,SIGNAL(triggered()),this,SLOT(passwordvision()));
    connect(enter,SIGNAL(clicked()),this,SLOT(enterslot()));
}

void LoginWidget::passwordvision()
{
    static bool isvisble = true;
    if(isvisble)
    {
        passwordisvisble->setIcon(QIcon("./icon/visiblel.png"));
        password_in->setEchoMode(QLineEdit::Normal);
        isvisble = false;
    }
    else
    {
        passwordisvisble->setIcon(QIcon("./icon/invisible.png"));
        password_in->setEchoMode(QLineEdit::Password);
        isvisble = true;
    }

}
void LoginWidget::enterslot()
{
    QByteArray MD5;
    QString plain;
    bool match = false;
    plain = account_in->text() + password_in->text();
    MD5 = QCryptographicHash::hash(plain.toUtf8(),QCryptographicHash::Md5);
    for(int i=0;i<model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);
        QVariant var = record.value(1);

        if(MD5.toHex()==var.toString())
        {
            qDebug() << "match account root";
            match = true;
            MyMainWindow* a = new MyMainWindow();
            a->show();
            this->close();

        }

    }
    if(match==false)
    {
        QMessageBox::warning(this,tr(""),tr("您输入的账户名或密码有误，请确认后重试"));
    }
}

#include "AskTable.h"

AskTable::AskTable(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* mainlayout = new QVBoxLayout;
    this->setLayout(mainlayout);
    this->setMaximumSize(300,200);
    this->setMinimumSize(300,200);
    group = new QGroupBox(this);
    group->setTitle(tr(u8"表格大小"));
    mainlayout->addStretch();
    mainlayout->addWidget(group);
    mainlayout->addStretch();

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* l1 = new QHBoxLayout(),*l2 = new QHBoxLayout();


    l1->addWidget(new QLabel(tr(u8"行 :")));
    l1->addSpacing(5);
    l1->addWidget(lin = new QSpinBox(this));
    lin->setMinimum(1);
    l2->addWidget(new QLabel(tr(u8"列 :")));
    l2->addSpacing(5);
    l2->addWidget(col = new QSpinBox(this));
    col->setMinimum(1);
    group->setLayout(layout);
    layout->addLayout(l1);
    layout->addLayout(l2);
    //l2.addWidget(new QLabel("列 :"));
    //l2.addWidget(new QSpinBox(this));
    QHBoxLayout* bottom = new QHBoxLayout;
    mainlayout->addLayout(bottom);
    bottom->addSpacing(200);
    QPushButton* enter;
    bottom->addWidget(enter = new QPushButton(tr(u8"确认")));
    bottom->addWidget(new QPushButton(tr(u8"取消")));
    tcp = new QTcpSocket();
    tcp->connectToHost("127.0.0.1",9988);
    connect(enter,SIGNAL(clicked()),this,SLOT(slotbuttonclicked()));
}
void AskTable::slotbuttonclicked()
{
    qint32 x = lin->value(),y = col->value();
    QByteArray str_lin = QByteArray::number(x);
    QByteArray str_col = QByteArray::number(y);

    tcp->write(str_lin);
    tcp->write("\n");
    tcp->write(str_col);

    emit accept();
    close();

}

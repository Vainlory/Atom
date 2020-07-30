#include "Filter.h"

Filter::Filter()
{
    this->buildtree();
    this->header()->hide();
}
void Filter::rebuildtree()
{

}
void Filter::buildtree()
{
    this->clear();
    QList<QTreeWidgetItem*> listchild;
    currentDir = QDir::currentPath();

    currentDir+="/locals/";

    QDir locals(currentDir);
    QStringList booklist = locals.entryList(QDir::Dirs|QDir::NoDotAndDotDot);


    for(QString cur:booklist)
    {
        QString tmp = currentDir;
        tmp+=cur;
        QDir notebook(tmp);
        QStringList notelist = notebook.entryList(QDir::Files|QDir::NoDotAndDotDot);
        QTreeWidgetItem* pitem = new QTreeWidgetItem;

        pitem->setData(0,Qt::DisplayRole,1);
        pitem->setText(0,cur);
        pitem->setFlags(pitem->flags() |Qt::ItemIsEditable);
        listchild.append(pitem);

        for(QString notename:notelist)
        {
            QTreeWidgetItem* qitem = new QTreeWidgetItem;
            qitem->setData(0,Qt::DisplayRole,2);
            qitem->setFlags(qitem->flags() | Qt::ItemIsEditable);
            notename.remove(".xml");
            qitem->setText(0,notename);
            pitem->addChild(qitem);
        }
    }
    this->insertTopLevelItems(0,listchild);
    this->expandAll();
}

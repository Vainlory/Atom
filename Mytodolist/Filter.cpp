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
    this->setDefaultDropAction(Qt::MoveAction);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDropIndicatorShown(true);


}
void Filter::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem* target;
    if(itemAt(event->pos())==0)
    {
        qDebug()<<"0";
        event->ignore();
        return;
    }
    else
        target = itemAt(event->pos());
    QString old_name = currentDir+this->currentItem()->parent()->text(0)+"/"+
            this->currentItem()->text(0)+".xml";
    QString str = currentDir
            + (target->parent()==NULL?target->text(0):target->parent()->text(0))
            +"/"+this->currentItem()->text(0);
    QString new_name = str+".xml";
    if(new_name == old_name)
    {
        event->ignore();
    }
    QFile file(new_name);
    int count =1;
    while(file.exists())
    {
        new_name = str + "(" + QString::number(count) + ")" + ".xml";
        file.setFileName(new_name);
        count++;
    }
    file.setFileName(old_name);
    file.copy(new_name);
    file.remove();
    event->acceptProposedAction();
    buildtree();

}
void Filter::dragEnterEvent(QDragEnterEvent *event)
{
    if(this->currentItem()->parent() == NULL)
    {
        event->ignore();
        qDebug() << "NUll";

    }
    else

    {
        event->accept();
    }
}

#include "New_diary.h"

New_diary::New_diary(QWidget *parent) : QWidget(parent)
{
    _menubar = new QMenuBar(this);
    _menubar->addMenu(_file = new QMenu("&文件"));
    _menubar->addMenu(_edit = new QMenu("&编辑"));
    _menubar->addMenu(_style = new QMenu("&格式"));
    _menubar->addMenu(_help = new QMenu("&帮助"));
    _menubar->addMenu(_tool = new QMenu("&工具"));

    _file->addAction("&导出",this,SLOT(slotfileout()))->setShortcut(QKeySequence("Ctrl+E"));
    _file->addSeparator();
    _file->addAction("&附加文件",this,SLOT(slotfileout()))->setShortcut(QKeySequence("Ctrl+A"));
    _file->addAction("&保存附件",this,SLOT(slotfileout()))->setShortcut(QKeySequence("Ctrl+A"));
    _file->addSeparator();
    _file->addAction("&打印",this,SLOT(slotfileout()))->setShortcut(QKeySequence("Ctrl+P"));
    _file->addAction("&另存为PDF...",this,SLOT(slotfileout()));
    _file->addSeparator();
    _file->addAction("&关闭",this,SLOT(close()))->setShortcut(QKeySequence("Ctrl+C"));

    //_edit->addAction()

}
void New_diary::slotfileout()
{
    qDebug() << "slotfileout";
}

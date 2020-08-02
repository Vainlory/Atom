#include <QApplication>

#include "MyMainWindow.h"
#include "New_diary.h"
#include "mainwindow.h"
#include "AskTable.h"
#include "Filter.h"
#include "StickyNot.h"
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    StickyNot w;
    w.show();
    return app.exec();
}

#include <QApplication>
#include "MyWidget.h"
#include "MyMainWindow.h"
#include "New_diary.h"
#include "mainwindow.h"
#include "AskTable.h"
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    MainWindow w;
    w.show();
    return app.exec();
}

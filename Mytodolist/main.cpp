#include <QApplication>

#include "MyMainWindow.h"
#include "New_diary.h"
#include "mainwindow.h"
#include "AskTable.h"
#include "Filter.h"
#include "StickyNote.h"
#include "LoginWidget.h"
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QSqlDatabase dbconn;
    dbconn = QSqlDatabase::addDatabase("QMYSQL");
    dbconn.setHostName("");//请在这里输入您的服务器的外网ip地址默认为本机ip
    dbconn.setDatabaseName("");	//输入数据库名称	
    dbconn.setUserName("");      	//目前该数据库的建设还尚未完成，因此不将数据库的外网ip及用户与密码放在源代码中
    dbconn.setPassword("");   		//如需运行代码请自建数据库或者与我联系，数据表的数据结构将在readme中详述
    if(dbconn.open()==false)
    {
        qDebug()<<dbconn.lastError();
    }

    LoginWidget w;
    w.show();
    return app.exec();
}

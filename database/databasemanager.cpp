#include "databasemanager.h"

#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}


bool DatabaseManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mathDB");

    if (db.open())
    {
        qDebug()<<"DB open sucess";
        return true;
    }
    else
    {
        qDebug()<<"DB open fail";
        return false;
    }

}

QSqlError DatabaseManager::error()
{
    return db.lastError();
}



bool DatabaseManager::createTableVariables()
{
    bool ret = false;

    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(
                    "create table VariableTable"
                    "(id integer primary key, "
                    "variable_name varchar(250), "
                    "variable_value varchar(250) )"
                    );
    }

    qDebug()<<"create variableTable is "<<ret;

    return ret;
}

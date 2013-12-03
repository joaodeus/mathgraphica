#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);

    bool openDB();
    QSqlError error();

    bool createTableVariables();


signals:
    
public slots:
    
private:
    QSqlDatabase db;

};

#endif // DATABASEMANAGER_H

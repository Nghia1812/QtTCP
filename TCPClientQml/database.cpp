#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QMYSQL");
    myDB.setDatabaseName("message");
    myDB.setHostName("localhost");
    myDB.setUserName("root");
    myDB.setPassword("nghia1812");
    if(!myDB.open()){
        qDebug() << myDB.lastError();
    }
}

QString DataBase::getTable(QString tbName)
{
    QString message = "";
    _tbName = tbName;
    QSqlQuery query;

    QString isExistQuery = "SHOW TABLES LIKE '" + tbName + "'";
    if(query.exec(isExistQuery)){
        if(query.next()){
            QString retrieveDataQuery = QString("SELECT Content FROM %1").arg(tbName);
            if (!query.exec(retrieveDataQuery)) {
                qDebug() << "Failed to retrieve table content:" << query.lastError();
            }
            while (query.next()) {
                QString content = query.value(0).toString();
                qDebug() << "Content:" << content;
                message.append(content + "\n");

            }
        }
        else
        {
            QString createTableQuery =  "CREATE TABLE IF NOT EXISTS "+ tbName + "("
                                                                                "ID int NOT NULL AUTO_INCREMENT, "
                                                                                "Content varchar(255) NOT NULL, "
                                                                                "PRIMARY KEY (ID)"
                                                                                ")";
            if (!query.exec(createTableQuery)) {
                qDebug() << "Error: Unable to create table -" << query.lastError();
            } else {

                qDebug() << "Table created successfully";
            }
        }
    }
    else
    {
        qDebug() << "Can not check table" << query.lastError();
    }
    return message;


}

void DataBase::saveNewMessage(QString msg)
{
    QSqlQuery query;
    QString saveMessageQuery = "INSERT INTO " + _tbName + " (Content) VALUES ('" + msg + "')";
    query.prepare(saveMessageQuery);

    if (!query.exec(saveMessageQuery)) {
        qDebug() << "Error" << query.lastError();
    } else {
        qDebug() << "Successfully";
    }
}



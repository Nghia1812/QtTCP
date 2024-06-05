#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);

public slots:
    QString getTable(QString tbName);
    void saveNewMessage(QString msg);

private:
    QString _tbName;
};

#endif // DATABASE_H

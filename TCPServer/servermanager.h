#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(ushort port = 4500, QObject *parent = nullptr);
    void notifyOtherClients(QString prevName, QString name);

public slots:

signals:
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket *client);

private slots:
    //signal &QTcpServer::newConnection
    void newClientConnectionReceived();
    //signal &QTcpSocket::disconnected
    void onClientDisconnected();

private:
    QTcpServer *_server;
    QMap<QString, QTcpSocket *> _clients;

private:
    void setupServer(ushort port);

};

#endif // SERVERMANAGER_H

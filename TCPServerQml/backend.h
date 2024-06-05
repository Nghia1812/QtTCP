#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QVector>
#include <servermanager.h>
#include <clientmanager.h>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);


signals:
    //server
    void newClientConnectedTo(int id);
    void clientDisconnectedFrom(int id);

    //client
    //void isTyping(QString message);
    void clientNameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);
    void textMessageReceived(QString message);

private slots:
    //server
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket *client);

    //client
    //void textMessageReceived(QString message);
    //void onTyping();



public slots:
    void sendMessage(QString msg, int index);
    int getIdClient();



public:
    void disconnect();



private:
    ServerManager *_server;
    ClientManager *_client;
    QVector<ClientManager *> clientList;
};

#endif // BACKEND_H

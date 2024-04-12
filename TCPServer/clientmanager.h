#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "chatprotocol.h"
#include <QObject>
#include <QTcpSocket>

/*
* Allows server to change some states of clients
* Commented outs are unecessary
*/

class ClientManager : public QObject
{
    Q_OBJECT
public:
    //explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    explicit ClientManager(QTcpSocket *client, QObject *parent = nullptr); //for server side
    //void connectToServer();

    void sendMessage(QString message);
    // void sendName(QString name);
    // void sendStatus(ChatProtocol::Status status);
    QString name() const;

    void sendIsTyping();
    void disconnectFromHost();
signals:
    void connected();
    void disconnected();
    void textMessageReceived(QByteArray message);
    void isTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);


private slots:
    void readyRead();

private:
    QTcpSocket *_socket;
    //QHostAddress _ip;
    //ushort _port;
    ChatProtocol _protocol;

private:
    void setupClient();

};

#endif // CLIENTMANAGER_H

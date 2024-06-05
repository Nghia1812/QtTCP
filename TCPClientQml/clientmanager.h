#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "chatprotocol.h"
#include <QObject>
#include <QTcpSocket>


class ClientManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    void connectToServer();


    //senb message with specific types to server
    void sendMessage(QString message);
    void sendName(QString name);
    void sendStatus(ChatProtocol::Status status);
    void sendIsTyping();

signals:
    //Signals connected with slots in mainwindow class
    void connected();
    void disconnected();

    //Signals to notify ...
    void textMessageReceived(QByteArray message);
    void isTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);


private slots:
    void readyRead();

private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;

private:
    void setupClient();

};

#endif // CLIENTMANAGER_H

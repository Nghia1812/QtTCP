#include "clientmanager.h"
#include <QDebug>

// ClientManager::ClientManager(QHostAddress ip, ushort port, QObject *parent)
//     : QObject{parent}
//     , _ip(ip)
//     , _port(port)
// {
//     setupClient();

// }

ClientManager::ClientManager(QTcpSocket *client, QObject *parent)
    : QObject{parent},
    _socket(client)
{
    setupClient();
}

// void ClientManager::connectToServer()
// {
//     _socket->connectToHost(_ip, _port);
//     qDebug() << "Client connected";
// }

void ClientManager::sendMessage(QString message)
{
    _socket->write(_protocol.textMessage(message));

}

// void ClientManager::sendName(QString name)
// {
//     _socket->write(_protocol.setNameMessage(name));
// }

// void ClientManager::sendStatus(ChatProtocol::Status status)
// {
//     _socket->write(_protocol.setStatusMessage(status));
// }

QString ClientManager::name() const
{
    auto id = _socket->property("id").toInt();
    auto name = _protocol.name().length() > 0 ? _protocol.name() : QString("Client %1").arg(id);
    return name;

}

void ClientManager::sendIsTyping()
{
    _socket->write(_protocol.isTypingMessage());
}

void ClientManager::readyRead()
{
    auto data = _socket->readAll();
    _protocol.loadData(data);
    switch (_protocol.type()) {
    case ChatProtocol::Text:
        emit textMessageReceived(_protocol.message());
        break;
    case ChatProtocol::SetName:
        emit nameChanged(name());
        break;
    case ChatProtocol::SetStatus:
        emit statusChanged(_protocol.status());
        break;
    case ChatProtocol::IsTyping:
        emit isTyping();
        break;
    default:
        break;
    }

}

void ClientManager::disconnectFromHost()
{
    _socket->disconnectFromHost();
}

void ClientManager::setupClient()
{
    connect(_socket, &QTcpSocket::connected, this, &ClientManager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead);
}

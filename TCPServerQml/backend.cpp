#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent) : QObject(parent)
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &Backend::newClientConnected);
    connect(_server, &ServerManager::clientDisconnected, this, &Backend::clientDisconnected);

}

void Backend::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    qDebug() << QString("New Client added: %1").arg(id);

    _client = new ClientManager(client);

    clientList.append(_client);

    //notify
    connect(_client, &ClientManager::textMessageReceived, this, &Backend::textMessageReceived);
    //connect(_client, &ClientManager::isTyping, this, &Backend::onTyping);
    connect(_client, &ClientManager::nameChanged, this, &Backend::clientNameChanged);
    connect(_client, &ClientManager::statusChanged, this, &Backend::statusChanged);

    connect(_client, &ClientManager::textMessageReceived, this, &Backend::getIdClient);
    //connect(_client, &ClientManager::isTyping, this, &Backend::getIdClient);
    connect(_client, &ClientManager::nameChanged, this, &Backend::getIdClient);
    connect(_client, &ClientManager::statusChanged, this, &Backend::getIdClient);

    emit newClientConnectedTo(id);
}

void Backend::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    emit clientDisconnectedFrom(id);
}

// void Backend::onTyping()
// {
//     emit isTyping(QString("%1 is typing").arg(_client->name()));
// }

int Backend::getIdClient()
{
    auto client = qobject_cast<ClientManager *>(sender());
    auto idClient = client->_socket->property("id").toInt();
    qDebug() << QString("New Client send smt: %1").arg(idClient);
    return idClient;
}

void Backend::sendMessage(QString msg, int index)
{
    clientList[index]->sendMessage(msg);
}

void Backend::disconnect()
{
    _client->disconnectFromHost();
}






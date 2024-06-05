#include "backend.h"
#include <QObject>

Backend::Backend(QObject *parent) : QObject(parent) {
    _client = new ClientManager();
    connect(_client, &ClientManager::textMessageReceived, this, &Backend::dataReceived);
}

void Backend::connectClicked()
{
    _client->connectToServer();
}

void Backend::sendClicked(QString message)
{
    _client->sendMessage(message);
}

void Backend::nameEditted(QString name)
{
    _client->sendName(name);
}

void Backend::statusChanged(int index)
{
    _client->sendStatus((ChatProtocol::Status)index);
}

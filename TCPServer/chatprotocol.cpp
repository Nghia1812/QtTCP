#include "chatprotocol.h"

#include <QIODevice>

ChatProtocol::ChatProtocol() {}

QByteArray ChatProtocol::textMessage(QString message)
{
    return getData(Text, message);
}

QByteArray ChatProtocol::isTypingMessage()
{
    return getData(IsTyping, "");
}

QByteArray ChatProtocol::setNameMessage(QString name)
{
    return getData(SetName, name);
}

QByteArray ChatProtocol::setStatusMessage(Status status)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out << SetStatus << status;
    return ba;
}

void ChatProtocol::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in >> _type; //save data from &data to _type
    switch (_type) {
    case Text:
        in >> _message;
        break;
    case SetName:
        in >> _name;
        break;
    case SetStatus:
        in >>_status;
        break;
    default:
        break;
    }
}

QByteArray ChatProtocol::getData(MessageType type, QString data)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out << type << data; //write MessageType with data to ba
    return ba;
}

ChatProtocol::MessageType ChatProtocol::type() const
{
    return _type;
}

ChatProtocol::Status ChatProtocol::status() const
{
    return _status;
}

QString ChatProtocol::name() const
{
    return _name;
}

QByteArray ChatProtocol::message() const
{
    return _message;
}

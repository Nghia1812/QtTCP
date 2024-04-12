#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QString>

/*
ChatProtocol is used to process data with different Message Types
*/
class ChatProtocol
{
public:
    enum MessageType{
        Text,
        //File,
        IsTyping,
        SetName,
        SetStatus
    };
    enum Status{
        None,
        Available,
        Away,
        Busy
    };

    ChatProtocol();

    //Data handlers, messages will then be sent to server using these
    QByteArray textMessage(QString message);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);
    QByteArray setStatusMessage(Status status);

    //Data received from Server is loaded by this
    void loadData(QByteArray data);


    //Data type getters
    QByteArray message() const;

    QString name() const;

    Status status() const;

    MessageType type() const;

private:
    //helper function for data handlers
    QByteArray getData(MessageType type, QString data);

    //data type variables
    MessageType _type;
    QByteArray _message;
    QString _name;
    Status _status;

};

#endif // CHATPROTOCOL_H

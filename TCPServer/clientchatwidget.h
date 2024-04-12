#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <ClientManager.h>

/*
 * This is displayed when a new client connects to server
*/
namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client, QWidget *parent = nullptr);
    ~ClientChatWidget();

    //used for on_tbChats_tabCloseRequested slot
    void disconnect();

private:
    Ui::ClientChatWidget *ui;
    ClientManager *_client;

private slots:
    void clientDisconnected();
    void on_btnSend_clicked();
    void textMessageReceived(QString message);
    void onTyping();

signals:
    //to notify server when clients' states change
    void clientNameChanged(QString name);
    void isTyping(QString message);
    void statusChanged(ChatProtocol::Status status);
};

#endif // CLIENTCHATWIDGET_H

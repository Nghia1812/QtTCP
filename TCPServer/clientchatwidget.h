#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include <QWidget>
#include <QTcpSocket>
namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client, QWidget *parent = nullptr);
    ~ClientChatWidget();

private:
    Ui::ClientChatWidget *ui;
    QTcpSocket *_client;

private slots:
    //signal &QTcpSocket::readyRead
    void dataReceived();
    void on_btnSend_clicked();

};

#endif // CLIENTCHATWIDGET_H

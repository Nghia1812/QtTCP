#include "clientchatwidget.h"
#include "chatitemwidget.h"
#include "ui_clientchatwidget.h"
#include <QDebug>

ClientChatWidget::ClientChatWidget(QTcpSocket *client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientChatWidget)

{
    ui->setupUi(this);
    _client = new ClientManager(client, this);

    //notify slots from ClientManager signals
    connect(_client, &ClientManager::disconnected, this, &ClientChatWidget::clientDisconnected);
    connect(_client, &ClientManager::textMessageReceived, this, &ClientChatWidget::textMessageReceived);

    //notify ClientChatWidget signals from ClientManager signals
    connect(_client, &ClientManager::isTyping, this, &ClientChatWidget::onTyping);
    connect(_client, &ClientManager::nameChanged, this, &ClientChatWidget::clientNameChanged);
    connect(_client, &ClientManager::statusChanged, this, &ClientChatWidget::statusChanged);


    connect(ui->lnMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);

}

ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}


void ClientChatWidget::disconnect()
{
    _client->disconnectFromHost();
}


void ClientChatWidget::clientDisconnected()
{
    ui->sendLayout->setEnabled(false);
}

void ClientChatWidget::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message);
    ui->lnMessage->setText("");
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message, true);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessage->addItem(listItemWidget);
    ui->lstMessage->setItemWidget(listItemWidget, chatWidget);

}

void ClientChatWidget::textMessageReceived(QString message)
{
    //ui->lstMessage->addItem(message);
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessage->addItem(listItemWidget);
    ui->lstMessage->setItemWidget(listItemWidget, chatWidget);
}

void ClientChatWidget::onTyping()
{
    emit isTyping(QString("%1 is typing").arg(_client->name()));
}


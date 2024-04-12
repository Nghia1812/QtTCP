#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientchatwidget.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    qDebug() << QString("New Client added: %1").arg(id);
    ui->listClients->addItem(QString("New Client added: %1").arg(id));
    auto chatWidget = new ClientChatWidget(client, ui->tbChats);
    ui->tbChats->addTab(chatWidget, QString("Client %1").arg(id));

    //notify Mainwindow slots from ClientChatWidget signals
    connect(chatWidget, &ClientChatWidget::clientNameChanged, this, &MainWindow::setClientName);
    connect(chatWidget, &ClientChatWidget::statusChanged, this, &MainWindow::setClientStatus);

    //isTyping is emitted by ClientChatWidget::onTyping() method
    connect(chatWidget, &ClientChatWidget::isTyping, [this](QString name){
        this->statusBar()->showMessage(name, 750);
    });
}

void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->listClients->addItem(QString("Client disconnected: %1").arg(id));
}

void MainWindow::setClientName(QString name)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tbChats->indexOf(widget);
    ui->tbChats->setTabText(index, name);
}

void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tbChats->indexOf(widget);
    QString iconPath = ":/new/prefix1/icons/";
    switch (status){
    case ChatProtocol::Available:
        iconPath.append("available.png");
        break;
    case ChatProtocol::Away:
        iconPath.append("away.png");
        break;
    case ChatProtocol::Busy:
        iconPath.append("busy.png");
        break;
    case ChatProtocol::None:

        break;
    default:
        iconPath = "";
        break;
    }

    auto icon = QIcon(iconPath);
    ui->tbChats->setTabIcon(index, icon);
}


void MainWindow::setupServer()
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected);
    connect(_server, &ServerManager::clientDisconnected, this, &MainWindow::clientDisconnected);
}



void MainWindow::on_disButton_clicked()
{
    //ui->listClients->addItem(QString("All clients removed"));
    //_server->disconnectAll();
}


void MainWindow::on_tbChats_tabCloseRequested(int index)
{
    auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbChats->widget(index));
    chatWidget->disconnect();
    ui->tbChats->removeTab(index);
}


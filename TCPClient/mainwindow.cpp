#include "mainwindow.h"
#include "chatitemwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupClient();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupClient()
{
    _client = new ClientManager();
    connect(_client, &ClientManager::connected, [this](){
        ui->centralwidget->setEnabled(true);
    });
    connect(_client, &ClientManager::disconnected, [this](){
        ui->centralwidget->setEnabled(false);
    });

    connect(_client, &ClientManager::textMessageReceived, this, &MainWindow::dataReceived);
    connect(_client, &ClientManager::isTyping, this, &MainWindow::onTyping);
    connect(ui->lnMessage, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);

}

void MainWindow::dataReceived(QString message)
{
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessage->addItem(listItemWidget);
    //listItemWidget->setBackground(QColor("168, 255, 237"));
    ui->lstMessage->setItemWidget(listItemWidget, chatWidget);
}



void MainWindow::on_actionConnect_triggered()
{
    _client->connectToServer();
}



void MainWindow::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    _client->sendMessage(message);

    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message, true);

    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->lstMessage->addItem(listItemWidget);
    //listItemWidget->setBackground(QColor("99BBFF"));
    ui->lstMessage->setItemWidget(listItemWidget, chatWidget);

    ui->lnMessage->setText("");
}


void MainWindow::on_lnClientName_editingFinished()
{
    auto name = ui->lnClientName->text().trimmed();
    _client->sendName(name);
}


void MainWindow::on_cbStatus_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}

void MainWindow::onTyping()
{
    statusBar()->showMessage("Typing...", 750);
}




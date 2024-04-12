#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatprotocol.h"
#include "servermanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ServerManager *_server;

private slots:
    //receive &ServerManager::newClientConnected signal
    void newClientConnected(QTcpSocket *client);
    //signal &ServerManager::clientDisconnected
    void clientDisconnected(QTcpSocket *client);

    void setClientName(QString name);
    void setClientStatus(ChatProtocol::Status status);
    void on_disButton_clicked();
    void on_tbChats_tabCloseRequested(int index);

private:
    void setupServer();
};
#endif // MAINWINDOW_H

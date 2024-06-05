#ifndef BACKEND_H
#define BACKEND_H
#include <QObject>
#include "clientmanager.h"


class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
private:
    ClientManager *_client;


public slots:
    void sendClicked(QString message);
    void nameEditted(QString name);
    void statusChanged(int index);
    void connectClicked();

signals:
    void dataReceived(QString message);




};
#endif // BACKEND_H

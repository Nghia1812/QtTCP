#ifndef CHATITEMWIDGET_H
#define CHATITEMWIDGET_H

#include <QWidget>
#include <QDate>

/*
 * This widget gets displayed when a client sends messages to server
*/
namespace Ui {
class ChatItemWidget;
}

class ChatItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatItemWidget(QWidget *parent = nullptr);
    ~ChatItemWidget();
    //Used to decide the style of message, depending on its sources (server/client)
    void setMessage(QString message, bool isMy = false);

private:
    Ui::ChatItemWidget *ui;
};

#endif // CHATITEMWIDGET_H

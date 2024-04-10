#include "chatitemwidget.h"
#include "ui_chatitemwidget.h"

ChatItemWidget::ChatItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatItemWidget)
{
    ui->setupUi(this);
}

ChatItemWidget::~ChatItemWidget()
{
    delete ui;
}

void ChatItemWidget::setMessage(QString message, bool isMy)
{
    if(isMy){
        ui->lbMessage->setAlignment(Qt::AlignRight);
        ui->lbTime->setAlignment(Qt::AlignRight);
    }
    ui->lbMessage->setText(message);
    ui->lbTime->setText(QDateTime::currentDateTime().toString("HH:mm"));

}

#include "serverview.h"
#include "ui_serverview.h"
#include <QApplication>
#include <QMessageBox>

ServerView::ServerView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerView)
{
    ui->setupUi(this);
}

ServerView::~ServerView()
{
    delete ui;
}

void ServerView::on_pushButton_clicked()
{
    _server = ui->lineEdit->displayText();
    _porta = ui->lineEdit_2->displayText();
    if(_server.size() == 0 || _porta.size() == 0){
        QMessageBox::warning(this,"Info incorreta","Server ou Porta invalidos");
    }
    else{
        QMessageBox::information(this, "Seu IP:", _server);
        close();
    }
}

QString ServerView::server(){
    return _server;
}

QString ServerView::porta(){
    return _porta;
}

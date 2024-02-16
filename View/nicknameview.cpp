#include "nicknameview.h"
#include "ui_nicknameview.h"
#include <QApplication>
#include <QMessageBox>

NicknameView::NicknameView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NicknameView)
{
    ui->setupUi(this);
}

NicknameView::~NicknameView()
{
    delete ui;
}

void NicknameView::on_pushButton_clicked()
{
    _nome = ui->lineEdit->displayText();
    _jogadores = 4;
    if(_nome.size() == 0){
        QMessageBox::warning(this,"Nome Incorreto","Nome Invalido");
    }
    else{
        QMessageBox::information(this, "Seu Nome:", _nome);
        close();
    }
}

void NicknameView::on_pushButton_2_clicked()
{
    _nome = ui->lineEdit->displayText();
    _jogadores = 2;
    if(_nome.size() == 0){
        QMessageBox::warning(this,"Nome Incorreto","Nome Invalido");
    }
    else{
        QMessageBox::information(this, "Seu Nome:", _nome);
        close();
    }
}

QString NicknameView::nome(){
    return _nome;
}

int NicknameView::numero_jogadores(){
    return _jogadores;
}

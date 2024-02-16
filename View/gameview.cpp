#include "gameview.h"
#include "ui_gameview.h"

#include <QString>

GameView::GameView(QWidget *parent, QString n_name, unsigned int n_jogadores) :
    QMainWindow(parent),
    ui(new Ui::GameView)
{
    ui->setupUi(this);
    _truco = false;
    _jogador = n_name;
    numero_jogador = n_jogadores;

    mao11 = new ActionView(this);
    jogo_scene = new QGraphicsScene(this);
    QBrush green(Qt::darkGreen);
    jogo_scene->setBackgroundBrush(green);
    ui->graphicsView->setScene(jogo_scene);
    ui->listViewChat->setModel(model);
}

GameView::~GameView()
{

    delete ui;
}


void GameView::iniciaScene(){

    if(numero_jogador == 4){
        ui->lineEdit->setText("Computer 1");
        ui->lineEdit_2->setText("Computer 2");
        ui->lineEdit_3->setText(_jogador);
        ui->lineEdit_4->setText("Computer 3");

        //Cria uma thread para cada bot, para escreverem mensagens no chat
        std::thread(&GameView::ia_chat_jogador, this, ui->lineEdit).detach();
        std::thread(&GameView::ia_chat_jogador, this, ui->lineEdit_2).detach();
        std::thread(&GameView::ia_chat_jogador, this, ui->lineEdit_4).detach();

        ui->lineEdit_5->setText("0");
        ui->lineEdit_6->setText("0");
        ui->lineEdit_7->setText("0");
        ui->lineEdit_8->setText("0");
    }
    else if(numero_jogador == 2){
        ui->lineEdit->setText("Computer 1");
        ui->lineEdit_2->setText(_jogador);
        ui->lineEdit_3->setDisabled(true);
        ui->lineEdit_4->setDisabled(true);

        //Cria uma thread para cada bot, para escreverem mensagens no chat
        std::thread(&GameView::ia_chat_jogador, this, ui->lineEdit).detach();

        ui->lineEdit_5->setText("0");
        ui->lineEdit_6->setText("0");

        ui->lineEdit_7->setDisabled(true);
        ui->lineEdit_8->setDisabled(true);
    }
}

void GameView::ia_chat_jogador(QLineEdit *lineEdit)
{
    while(true)
    {
        //Aguarda um tempo aleatoriamente antes de escrever mensagens no chat
        int seconds = get_random_int(5, 20);
        std::this_thread::sleep_for (std::chrono::seconds(seconds));

        int message_number = get_random_int(0, 18);

        //Escreve uma mensagem aleatoria no chat
        std::string str = lineEdit->text().toStdString() + ": " + expressoes[message_number];
        send_message_to_chat(str.c_str());
    }
}

int GameView::get_random_int(int first, int last)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(first, last);
    return dis(gen);
}

void GameView::setPontuacao(QString pont, std::size_t pos){
    if(numero_jogador == 4){
        if(pos == 0){
            ui->lineEdit_6->setText(pont);
            ui->lineEdit_8->setText(pont);
        }
        else if(pos == 1){
            ui->lineEdit_5->setText(pont);
            ui->lineEdit_7->setText(pont);

        }
    }
    else if(numero_jogador == 2){
        if(pos == 0){
            ui->lineEdit_6->setText(pont);
        }
        else if(pos == 1){
            ui->lineEdit_5->setText(pont);
        }
    }
}

void GameView::mostraBaralho(std::vector<std::pair<bool, CardModel> > _monte){
    for(unsigned int i = 0; i < _monte.size(); i++){
        qbaralho.emplace_back(new CardView(_monte[i].second));
        qbaralho[i]->setPos(225+ i + 20,150);
        jogo_scene->addItem(qbaralho[i]);

    }
}

void GameView::mostraVira(CardModel _carta){
    vira = new CardView(_carta);
    vira->setPos(225+40,150);
    jogo_scene->addItem(vira);
}

void GameView::mostraMao(){
    for(unsigned int i = 0; i < qmao.size(); i++){
        if(qmao[i]->getClickable() == false){
            qmao[i]->setClickable();
        }
        if(qmao[i]->getSelectable() == false){
            qmao[i]->setSelectable();
        }
    }
}

void GameView::mostraMaoInicio(std::vector<CardModel> _mao){
    for(unsigned int i = 0; i < _mao.size(); i++){
        _mao[i].vira();
        qmao.emplace_back(new CardView(_mao[i]));
        qmao[i]->setPos(200 + i*40,290);
        jogo_scene->addItem(qmao[i]);
    }
}

void GameView::mostraMaooff(){
    for(unsigned int i = 0; i < qmao.size();i++){
        if(qmao[i]->getSelectable() == false){
            qmao[i]->setSelectable();
        }
        if(qmao[i]->getClickable() == true){
            qmao[i]->setClickable();
        }
    }
}

void GameView::outrasMaos(unsigned int pos,std::vector<CardModel> _mao){
    if(numero_jogador == 4){
        if(pos == 1){
            for(unsigned int i = 0; i < _mao.size(); i++){
                qmao1.emplace_back(new CardView(_mao[i]));
                qmao1[i]->setPos(0,180 -i*30);
                jogo_scene->addItem(qmao1[i]);
            }
        }

        else if(pos == 2){
            for(unsigned int i = 0; i < _mao.size(); i++){
                qmao2.emplace_back(new CardView(_mao[i]));
                qmao2[i]->setPos(200 +i*40,0);
                jogo_scene->addItem(qmao2[i]);
            }
        }
        else if(pos  == 3){
            for(unsigned int i = 0; i < _mao.size(); i++){
                qmao3.emplace_back(new CardView(_mao[i]));
                qmao3[i]->setPos(515,180 -i*30);
                jogo_scene->addItem(qmao3[i]);
            }
        }
        else{
            return;
        }
    }
    else if(numero_jogador == 2){
        if(pos == 1){
            for(unsigned int i = 0; i < _mao.size(); i++){
                qmao1.emplace_back(new CardView(_mao[i]));
                qmao1[i]->setPos(200 +i*40,0);
                jogo_scene->addItem(qmao1[i]);
            }
        }
        else{
            return;
        }
    }

}

void GameView::jogaCarta(unsigned int pos, unsigned int pos_carta, CardModel carta){
    if(numero_jogador == 4){
        if(pos == 0){
            jogo_scene->removeItem(qmao[pos_carta]);
            qmao.erase(qmao.begin() + pos_carta);
            qmesa.emplace(qmesa.begin(),new CardView(carta));
            qmesa[0]->setPos(255, 220);
            jogo_scene->addItem(qmesa[0]);
        }
        else if(pos == 1){
            jogo_scene->removeItem(qmao1[pos_carta]);
            qmao1.erase(qmao1.begin() + pos_carta);
            qmesa.emplace(qmesa.begin(),new CardView(carta));
            qmesa[0]->setPos(60,180-30);
            jogo_scene->addItem(qmesa[0]);
        }
        else if(pos == 2){
            jogo_scene->removeItem(qmao2[pos_carta]);
            qmao2.erase(qmao2.begin() + pos_carta);
            qmesa.emplace(qmesa.begin(),new CardView(carta));
            qmesa[0]->setPos(255,70);
            jogo_scene->addItem(qmesa[0]);
        }
        else if(pos == 3){
            jogo_scene->removeItem(qmao3[pos_carta]);
            qmao3.erase(qmao3.begin() + pos_carta);
            qmesa.emplace(qmesa.begin(),new CardView(carta));
            qmesa[0]->setPos(455,180 -30);
            jogo_scene->addItem(qmesa[0]);
        }
    }
    else if(numero_jogador == 2){
        if(pos == 0){
            jogo_scene->removeItem(qmao[pos_carta]);
            qmao.erase(qmao.begin() + pos_carta);
            qmesa.emplace(qmesa.begin(),new CardView(carta));
            qmesa[0]->setPos(255, 220);
            jogo_scene->addItem(qmesa[0]);
        }
        else if(pos == 1){
            jogo_scene->removeItem(qmao1[pos_carta]);
            qmao1.erase(qmao1.begin() + pos_carta);
            qmesa.emplace(qmesa.begin(),new CardView(carta));
            qmesa[0]->setPos(255,70);
            jogo_scene->addItem(qmesa[0]);
        }

    }

}

bool GameView::statusTruco(){
    return _truco;
}

bool GameView::maoDe11(std::vector<CardModel> mao1, std::vector<CardModel> mao2,CardModel _vira){
    if(numero_jogador == 4){
        mao11->show();
        mao11->addMao(mao1,mao2,_vira);

    }
    else{
        mao11->show();
    }
    return mao11->getAcao();


}

bool GameView::maoDe11_2(){
    mao11->show();

    return mao11->getAcao();
    return true;
}

void GameView::setTrucoFalse(){
    _truco = false;
}

bool GameView::getClick(unsigned int carta){
    return qmao[carta]->getClicked();
}

unsigned int GameView::cartaSelecionada(){
    unsigned int cont = 0;
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_4->setDisabled(true);

    QEventLoop loop;
    connect(ui->pushButton,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
    loop.exec();

    for(unsigned int i = 0; i < qmao.size(); i++ ){
        if(qmao[i]->getSelected()){
            cont = i;
        }
    }
    return cont;

}

void GameView::comeca_novo_turno(){
    comeca_nova_rodada();
    unsigned int tamanho = 0;

    tamanho = qmao.size();
    for(unsigned int i = 0; i < tamanho; i++){
        jogo_scene->removeItem(qmao[0]);
        qmao.erase(qmao.begin());
    }
    tamanho = qmao1.size();
    for(unsigned int i = 0; i < tamanho; i++){
        jogo_scene->removeItem(qmao1[0]);
        qmao1.erase(qmao1.begin());
    }
    tamanho = qbaralho.size();
    for(unsigned int i = 0; i < tamanho; i++){
        jogo_scene->removeItem(qbaralho[0]);
        qbaralho.erase(qbaralho.begin());
    }
    delete(vira);


    if(numero_jogador == 4){
        tamanho = qmao2.size();
        for(unsigned int i = 0; i < tamanho; i++){
            jogo_scene->removeItem(qmao2[0]);
            qmao2.erase(qmao2.begin());
        }
        tamanho = qmao3.size();
        for(unsigned int i = 0; i < tamanho; i++){
            jogo_scene->removeItem(qmao3[0]);
            qmao3.erase(qmao3.begin());
        }
    }

}

void GameView::comeca_nova_rodada(){
    unsigned int tamanho = 0;
    tamanho = qmesa.size();
    for(unsigned int i = 0; i < tamanho; i++){
        jogo_scene->removeItem(qmesa[0]);
        qmesa.erase(qmesa.begin());
    }
}

void GameView::jogadorGanhouRodada(CardModel carta,unsigned int pos){
    if(pos == 4){
        QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " empatou a rodada com a carta" +
                                                            QString::number(carta.numero()));
    }
    else{
        if(carta.naipe() == CardModel::Suit::Paus){
            if(carta.numero() == 10){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " K de Paus");
            }
            else if(carta.numero() == 9){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " J de Paus");

            }
            else if(carta.numero() == 8){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " Q de Paus");
            }
            else if(carta.numero() == 1){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " A de Paus");
            }
            else{
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    QString::number(carta.numero()) + " de Paus");
            }

        }
        if(carta.naipe() == CardModel::Suit::Copas){
            if(carta.numero() == 10){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " K de Copas");
            }
            else if(carta.numero() == 9){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " J de Copas");

            }
            else if(carta.numero() == 8){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " Q de Copas");
            }
            else if(carta.numero() == 1){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " A de Copas");
            }
            else{
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    QString::number(carta.numero()) + " de Copas");
            }

        }
        if(carta.naipe() == CardModel::Suit::Espadas){
            if(carta.numero() == 10){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " K de Espadas");
            }
            else if(carta.numero() == 9){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " J de Espadas");

            }
            else if(carta.numero() == 8){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " Q de Espadas");
            }
            else if(carta.numero() == 1){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " A de Espadas");
            }
            else{
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    QString::number(carta.numero()) + " de Espadas");
            }

        }
        if(carta.naipe() == CardModel::Suit::Ouros){
            if(carta.numero() == 10){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " K de Ouros");
            }
            else if(carta.numero() == 9){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " J de Ouros");

            }
            else if(carta.numero() == 8){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " Q de Ouros");
            }
            else if(carta.numero() == 1){
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    " A de Ouros");
            }
            else{
                QMessageBox::information(this,"Ganhou Rodada", "Jogador: " + QString::number(pos) + " ganhou a rodada com a Carta: " +
                                                                    QString::number(carta.numero()) + " de Ouros");
            }

        }
    }
}

void GameView::JogadoresCorreram(){
    QMessageBox::information(this,"Correram","Os Adversarios correram do truco");
}

void GameView::JogadoresAceitaram(){
    QMessageBox::information(this,"Aceitaram","Os Adversarios aceitaram o pedido de truco");
}

void GameView::on_pushButton_2_clicked()
{
    if(_truco == false){
        _truco = true;
        QMessageBox::information(this,"Truco","Pediu Truco/Aumentou !");
    }
}

void GameView::mostraValorTruco(unsigned int _valor){
    QFont helvetica("Times",18);
    ui->lineEdit_9->setFont(helvetica);
    ui->lineEdit_9->setText(QString::number(_valor));
}

void GameView::acao(unsigned int pont){
    QEventLoop loop;

    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_3->setDisabled(true);

    if(pont == 11){
        ui->pushButton_2->setDisabled(true);
    }
    connect(ui->pushButton,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),&loop,SLOT(quit()));

    loop.exec();

}

void GameView::rodadaAsCegas(std::vector<CardModel> mao){
    if(!qmao.empty()){
        for(unsigned int i = 0; i < qmao.size(); i++){
            jogo_scene->removeItem(qmao[i]);
        }
        qmao.clear();
    }
    for(unsigned int i = 0; i < mao.size(); i++){
        qmao.emplace_back(new CardView(mao[i]));
        qmao[i]->setPos(200 + i*40,290);
        jogo_scene->addItem(qmao[i]);
    }

}

void GameView::fimDeJogo(unsigned int pos){
    if(numero_jogador == 4){
        if(pos == 0 || pos == 2){
            QMessageBox::information(this,"Ganhadores","Ganhadores: " +_jogador + " e Computer2");
        }
        else if(pos == 1 || pos == 3){
            QMessageBox::information(this,"Ganhadores", "Ganhadores: Computer1 e Computer3");
        }
    }
    else{
        if(pos == 0){
            QMessageBox::information(this,"Ganhador","Ganhador: " +_jogador);
        }
        else if(pos == 1){
            QMessageBox::information(this,"Ganhador", "Ganhador: Computer1");
        }
    }
    QApplication::quit();
}

void GameView::jogadoresMaode11(){
    if(numero_jogador == 4 ){
        QMessageBox::information(this,"Jogadores Mao 11", "Jogadores Computer1 e Computer3 estao na mao de 11");
    }
    else{
        QMessageBox::information(this,"Jogador Mao 11", "Jogador Computer1 esta na mao de 11");
    }
}


void GameView::JogadoresAsCegas(){
    QMessageBox::information(this,"Jogo as Cegas", "Turno As Cegas");
}

void GameView::on_pushButton_clicked()
{
    QApplication::quit();
}

// Utiliza mecanismo de mutual exclusion pra escrita segura no chat por parte das threads
void GameView::send_message_to_chat(const char* message)
{
    mtx_chat.lock();

    stringList.append(message);
    model->setStringList(stringList);

    mtx_chat.unlock();
}

void GameView::on_lineEditChat_returnPressed()
{
    std::string str = "Eu: " + ui->lineEditChat->text().toStdString();
    send_message_to_chat(str.c_str());
    ui->lineEditChat->clear();
}

#include "mainview.h"
#include "./ui_mainview.h"

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
{
    save = new SaveController();
    ui->setupUi(this);
}

void MainView::on_pushButton_2_clicked()
{
    HelpView _help;
    _help.setModal(true);
    _help.exec();

    show();
}

void MainView::on_pushButton_4_clicked()
{
    QApplication::quit();
}

void MainView::on_pushButton_3_clicked()
{
    std::string name;
    if (save->ThereIsALoad()){
        _numero_jogadores = 4;
        save->LoadGame(&name);
        rule = new RulesController(_numero_jogadores,3,3,12,0,40);
        _jogo = new GameView(this,QString::fromStdString(name),_numero_jogadores);
        _jogadores.emplace_back((name));
        _jogadores.emplace_back("Computer1");
        _jogadores.emplace_back("Computer2");
        _jogadores.emplace_back("Computer3");

        PlayTrucoController game(rule,jogadores(),_jogo);
        game.jogar();
    }else {
        on_pushButton_clicked();
    }
}

//TODO
// Foi implementado as classes Server Socket (Controller/serversocket) e Client Socket (Controller/clientsocket),
// as classes multithreading estão em funcionamento e 4 players conseguem se conectar via rede local perfeitamente,
// faltou relacionar as regras de negocio do jogo com os sockets
void MainView::on_pushButton_5_clicked()
{
    ServerView ipconfig;
    ipconfig.setModal(true);
    ipconfig.exec();
}

//TODO
void MainView::on_pushButton_6_clicked()
{
    ServerView ipconfig;
    ipconfig.setModal(true);
    ipconfig.exec();
}

void MainView::on_pushButton_clicked()
{
    NicknameView nome;
    nome.setModal(true);
    nome.exec();

    _numero_jogadores = nome.numero_jogadores();

    if(nome.nome().size() > 0){
        save->SaveGame(nome.nome().toStdString());
        if(nome.numero_jogadores() == 4){
            rule = new RulesController(_numero_jogadores,3,3,12,0,40);
            _jogo = new GameView(this,nome.nome(),_numero_jogadores);
            _jogadores.emplace_back((nome.nome().toStdString()));
            _jogadores.emplace_back("Computer1");
            _jogadores.emplace_back("Computer2");
            _jogadores.emplace_back("Computer3");

            PlayTrucoController game(rule,jogadores(),_jogo);
            game.jogar();

        }

        if(nome.numero_jogadores() == 2){
            rule = new RulesController(_numero_jogadores,3,3,12,0,40);
            _jogo = new GameView(this,nome.nome(),_numero_jogadores);
            _jogadores.emplace_back((nome.nome().toStdString()));
            _jogadores.emplace_back("Computer1");

            PlayTrucoController game(rule,jogadores(),_jogo);
            game.jogar();

        }
    }

}

std::vector<std::string> MainView::jogadores(){
    return _jogadores;
}


int MainView::numero_jogadores(){
    return _numero_jogadores;
}

MainView::~MainView()
{
    delete ui;
}

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <vector>
#include <QEventLoop>
#include "cardview.h"
#include "actionview.h"
#include "saveview.h"

namespace Ui {
class GameView;
}

class GameView : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = 0, QString n_name = "", unsigned int n_jogadores = 4);
    ~GameView();
    void iniciaScene();
    void setPontuacao(QString = "0", std::size_t pos = 0);
    void mostraBaralho(std::vector<std::pair<bool, CardModel> > _monte);
    void mostraVira(CardModel _carta);
    void mostraMao();
    void mostraMaoInicio(std::vector<CardModel> _mao);
    void mostraMaooff();
    void outrasMaos(unsigned int pos, std::vector<CardModel> _mao);
    void jogaCarta(unsigned int pos, unsigned int pos_carta, CardModel carta);
    bool statusTruco();
    bool maoDe11(std::vector<CardModel> mao1, std::vector<CardModel> mao2, CardModel _vira);
    bool maoDe11_2();
    void setTrucoFalse();
    bool getClick(unsigned int carta);
    unsigned int cartaSelecionada();
    void comeca_novo_turno();
    void comeca_nova_rodada();
    void jogadorGanhouRodada(CardModel carta,unsigned int pos);
    void JogadorGanhouTurno(unsigned int pos);
    void JogadoresCorreram();
    void JogadoresAceitaram();
    void mostraValorTruco(unsigned int _valor = 1);
    void acao(unsigned int pont);
    void rodadaAsCegas(std::vector<CardModel> mao);
    void fimDeJogo(unsigned int pos);
    void jogadoresMaode11();
    void JogadoresAsCegas();

private slots:

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

protected:
    Ui::GameView *ui;
    QString _jogador;
    QGraphicsScene *jogo_scene;
    std::vector<CardView *> qbaralho;
    std::vector<CardView *> qmao;
    std::vector<CardView *> qmao1;
    std::vector<CardView *> qmao2;
    std::vector<CardView *> qmao3;
    std::vector<CardView *> qmesa;
    CardView *vira;
    ActionView *mao11;
    unsigned int numero_jogador;
    bool _truco;
};

#endif // GAMEVIEW_H

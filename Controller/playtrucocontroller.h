#ifndef PLAYTRUCOCONTROLLER_H
#define PLAYTRUCOCONTROLLER_H

#include "../Model/gamemodel.h"
#include "../Model/gamerulesmodel.h"
#include "../View/gameview.h"
#include <memory>

class PlayTrucoController :public Game{
public:
    enum class Compara{Maior, Menor, Igual};

    void fim_jogo();

    PlayTrucoController(GameRulesModel *regra, std::vector<std::string> nomes, GameView *_interface);
    virtual ~PlayTrucoController();

    void jogar();

    bool checa_fim_rodada();
    //Retorna true se a rodada estiver valendo truco
    bool truco();

    int valor_truco();

    int valor_pontuacao();

    std::size_t jogador_comeca();

    int compara(CardModel c1,CardModel c2,CardModel _vira);

    bool fim_turno();

    std::size_t jogador_ganhou_turno();

    int pontuacao(std::size_t _jogador);

    bool verifica_truco(std::size_t _jogador_trucou);

    int checa_mao_de_11();

    bool ia_aceita_mao_11();


protected:
    unsigned int jogador_vencedor();

    void joga_jogador_posicao0_11();

    void rodada_as_cegas();

    void joga_jogador_comeca();

    void joga_carta_cima(unsigned int _carta);

    void jogador_ganhou_rodada(std::size_t _jogador);

    std::vector<CardModel> mostra_mao_jogador_pos(std::size_t _jogador);

    void comeca_novo_turno();

    void incrementa_jog_atual();

    void jogador_soma_pontos(std::size_t _jogador, int pontos);

    bool mao_de_11();

    void fim_rodada(std::size_t _jogador_ganhou);

    //O jogador j1 pede truco
    void pede_truco(std::size_t j1);

    void joga_jogador_posicao_0();
    void ia_joga();

    bool _turno;
    bool _cond_rodada;
    bool _truco;									//turno vale truco ou nao
    int _valor_truco;								//quantidade de pontos que o truco vale
    std::vector<std::size_t> _jogadores_ganharam;
    std::size_t carta_ganhando;
    std::size_t jogador_ganhando;

private:
    std::unique_ptr<GameView> gameScreen;
};

#endif // PLAYTRUCOCONTROLLER_H

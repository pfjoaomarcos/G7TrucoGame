#ifndef RULESCONTROLLER_H
#define RULESCONTROLLER_H

#include <deque>
#include <random>
#include <algorithm>
#include <stdexcept>
#include "../Model/gamerulesmodel.h"
#include "../Model/cardmodel.h"
#include "../Model/playermodel.h"

class RulesController final: public GameRulesModel{
public:
    enum class Compara{Maior, Menor, Igual};
    RulesController(std::size_t numero_de_jogadores,
                int cartas_jogadores,
                int rodadas,
                int pontuacao_max,
                int menor_pontuacao,
                int cartas_inicial);

    virtual ~RulesController();

    bool checa_fim_rodada(std::size_t pos) override;

    void jogador_ganhou_rodada(std::size_t jogador,std::size_t rodada) override;

    std::size_t jogador_ganhou_turno() override;

    void recomeca_turno() override;

    bool fim_turno(std::size_t rodada, std::size_t ganhou) override;

    int valor_pontuacao(bool cond,int valor) override;

    int compara(CardModel c1, CardModel c2, CardModel _vira) override;

    std::size_t jogador_comeca() override;

    void jogador_comeca(std::size_t n_pos) override;

    std::size_t jogador_termina() override;

    void jogador_termina(std::size_t n_pos) override;

    std::size_t jogador_comeca_turno() override;

    void jogador_comeca_turno(std::size_t n_pos) override;


private:
    //Compara a forca das manilhas de acordo com o truco
    bool compara_naipe(CardModel c1,CardModel c2);
    //Compara manilha se o _vira = 12
    int compara_vira_12(CardModel c1,CardModel c2);
    //Compara o valor numerico das cartas
    int compara_valor(CardModel c1 , CardModel c2);

    std::size_t _jogador_comeca;
    std::size_t _jogador_termina;
    std::size_t _jogador_comeca_turno;
    std::vector<std::size_t> _jogadores_ganharam;
};

#endif // RULESCONTROLLER_H

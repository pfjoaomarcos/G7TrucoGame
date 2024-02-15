#include "gamerulesmodel.h"

GameRulesModel::GameRulesModel(std::size_t numero_de_jogadores,
             int cartas_jogadores,
             int rodadas /* = -1 */,
             int pontuacao_max /* = -1 */,
             int menor_pontuacao /* = -1 */,
             int cartas_inicial /* = 52 */,
             modo_fim fim /* = modo_fim::pontuacao */,
             condicao_vitoria vit /* = condicao_vitoria::maior_pontuacao */,
             condicao_derrota der /* = condicao_derrota::nenhuma */,
             int auto_pontos_carta_mao /* = 0 */) :
    _fim(fim), _vit(vit), _der(der), _pont_cartas_mao(auto_pontos_carta_mao) {

    _numero_de_jogadores = numero_de_jogadores;
    _cartas_inicial = cartas_inicial;
    _cartas_jogadores = cartas_jogadores;
    _rodadas = rodadas;
    _pontuacao_max = pontuacao_max;
    _menor_pontuacao = menor_pontuacao;
}

GameRulesModel::~GameRulesModel() {

}

std::size_t GameRulesModel::numero_de_jogadores() const {
    return _numero_de_jogadores;
}
int GameRulesModel::cartas_inicial() const {//retorna numero de cartas do monte
    return _cartas_inicial;
}
int GameRulesModel::cartas_jogadores() const { //retorna cartas iniciais por jogadores
    return  _cartas_jogadores;
}
int GameRulesModel::max_rodadas() const {//retorna numero maximo de rodadas
    return _rodadas;
}
int GameRulesModel::pontuacao_max() const {//retorna numero de pontos para termino
    return _pontuacao_max;
}

GameRulesModel::modo_fim GameRulesModel::fim() const {

    return _fim;
}

GameRulesModel::condicao_vitoria GameRulesModel::cond_vit() const {

    return _vit;
}

GameRulesModel::condicao_derrota GameRulesModel::cond_der() const {

    return _der;
}

int GameRulesModel::pontuacao_carta_mao() const {

    return _pont_cartas_mao;
}

//TODO implementada:
int GameRulesModel::compara(CardModel c1, CardModel c2, CardModel c3){

    (void) c1;
    (void) c2;
    (void) c3;
    return 0;
}

bool GameRulesModel::checa_fim_rodada(std::size_t pont){

    (void) pont;
    return false;
}

void GameRulesModel::jogador_ganhou_rodada(std::size_t jogador,std::size_t rodada){

    (void) jogador;
    (void) rodada;
    return;
}

std::size_t GameRulesModel::jogador_ganhou_turno(){return 0;}

void GameRulesModel::recomeca_turno(){return;}

bool GameRulesModel::fim_turno(std::size_t rodada, std::size_t ganhou){

    (void) rodada;
    (void) ganhou;
    return false;
}

int GameRulesModel::valor_pontuacao(bool cond,int valor){

    (void) cond;
    (void) valor;
    return 0;
}

std::size_t GameRulesModel::jogador_comeca(){
    return 0;
}

void GameRulesModel::jogador_comeca(std::size_t n_pos){

    (void) n_pos;
    return;
}

std::size_t GameRulesModel::jogador_termina(){return 0;}

void GameRulesModel::jogador_termina(std::size_t n_pos){

    (void) n_pos;
    return;
}

std::size_t GameRulesModel::jogador_comeca_turno(){return 0;}

void GameRulesModel::jogador_comeca_turno(std::size_t n_pos){

    (void) n_pos;
    return;
}

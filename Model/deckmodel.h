#ifndef DECKMODEL_H
#define DECKMODEL_H

#include <iostream>
#include <deque>
#include <random>
#include <algorithm>

#include "cardmodel.h"

template<class CardModel>
class DeckModel
{
public:
    //Construtor
    //recebe o numero de cartas total do baralho
    //se o numero de cartas nao for divisivel pelo numero de naipes, retorna um baralho com o valor truncado da divisao
    //de numerocartas por numero de naipes do baralho;
    DeckModel(std::size_t numerocartas = 0);

    //Destrutor
    virtual ~DeckModel();

    //Emabaralha o baralho
    //utiliza um algoritimo que faz trocas de posicoes aleatorias no vetor de cartas
    void embaralhar();

    //Pega uma carta do topo
    //retorna a primeira carta do vetor de cartas e remove ela do vetor
    CardModel pega_topo(void);

    //Pega uma carta de baixo
    //retorna a ultima carta do vetor de cartas e remove ela do vetor
    CardModel pega_baixo(void);

    //retorna a primeira carta do vetor de cartas e nao remove ela do vetor
    CardModel* retorna_topo(void);

    //Coloca uma carta no topo do baralho
    //a carta passada como argumento é colocada no inicio do vetor de cartas
    void coloca_topo(CardModel c);

    //Coloca uma carta em baixa do baralho
    //a carta passada como argumento é colocada no final do vetor de cartas
    void coloca_baixo(CardModel c);

    //Retorna o numero de cartas do baralho
    std::size_t size() const;

    //Restaura as cartas do baralho as iniciais
    //limpa o vetor de cartas e recoloca todas elas no vetor de cartas novamente como se fosse o baralho inicial
    void restaurar();

    // vira a carta do topo do baralho
    //
    // nao retorna nada
    //
    // ex: baralho.vira_topo();
    //
    void vira_topo();

    // vira a carta de baixo do baralho
    //
    // nao retorna nada
    //
    // ex: baralho.vira_baixo();
    //
    void vira_baixo();

    // vira uma carta de um jogador
    //
    // retorna um vetor contendo cartas e um booleano, caso a carta na respectiva posicao esteja virada para baixo,
    // o booleano sera false e a carta tera um valor padrao indicando estar virada para baixo, caso a carta esteja
    // virada para cima o booleano sera true e a carta correspondera ao valor da carta do baralho na posicao
    //
    // ex: baralho.mostra_baralho()[0].second; // acesso a carta no topo
    //     baralho.mostra_baralho()[baralho.size() - 1].first; // verifica se a carta em baixo do baralho esta virada para cima
    //
    std::vector<std::pair<bool, CardModel> > mostra_baralho() const;

    //esvazia monte
    //exclui todas as cartas do vetor de cartas e deixa o monte com tamanho 0
    void esvazia_monte();

protected:

    //guarda o numero de cartas inicial passado ao baralho
    std::size_t _numerocartas;

    //vetor de cartas que representa o baralho
    std::deque<CardModel> _monte;
};

template<class CardModel> DeckModel<CardModel>::DeckModel(std::size_t numerocartas/* = 0 */) : _numerocartas{numerocartas} {

    if(numerocartas % CardModel::n_naipes) std::cerr << "Baralho::Baralho -- numero de cartas nao divisivel pelo numero de naipes\n";

    restaurar();
}

template<class CardModel> DeckModel<CardModel>::~DeckModel() {
}

template<class CardModel> void DeckModel<CardModel>::embaralhar(){

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_monte.begin(), _monte.end(), g);
}

template<class CardModel> CardModel DeckModel<CardModel>::pega_topo(void){
    CardModel c = _monte.front();
    _monte.pop_front();
    return c;
}

template<class CardModel> CardModel DeckModel<CardModel>::pega_baixo(void){
    CardModel c = _monte.back();
    _monte.pop_back();
    return c;
}

template<class CardModel> CardModel* DeckModel<CardModel>::retorna_topo(void){
    CardModel *c = &(_monte.front());
    return c;
}

template<class CardModel> void DeckModel<CardModel>::coloca_topo(CardModel c){

    _monte.push_front(c);
}

template<class CardModel> void DeckModel<CardModel>::coloca_baixo(CardModel c){

    _monte.push_back(c);
}

template<class CardModel> std::size_t DeckModel<CardModel>::size() const {

    return _monte.size();
}

template<class CardModel> void DeckModel<CardModel>::restaurar(){

    std::size_t cartas_por_naipe = _numerocartas / CardModel::n_naipes;

    _monte.clear();

    for(int naipe = 0; naipe < CardModel::n_naipes; naipe++){

        for(std::size_t numero = 0; numero < cartas_por_naipe; numero++){

            _monte.emplace_back((numero%CardModel::n_numeros) + 1, (typename CardModel::Suit) naipe);
        }
    }
}

template<class CardModel> void DeckModel<CardModel>::vira_topo(){

    _monte.front().vira();
}

template<class CardModel> void DeckModel<CardModel>::vira_baixo(){

    _monte.back().vira();
}

template<class CardModel> std::vector<std::pair<bool, CardModel> > DeckModel<CardModel>::mostra_baralho() const {

    std::vector<std::pair<bool, CardModel> > vec;

    vec.reserve(this->size());

    for(auto carta : _monte) vec.emplace_back(carta.mostra(), carta.mostra() ? carta : CardModel(0, static_cast<typename CardModel::Suit>(0)));

    return vec;
}

template<class CardModel> void DeckModel<CardModel>::esvazia_monte(){
    _monte.clear();
}

using Baralho = DeckModel<CardModel>;

#endif // DECKMODEL_H

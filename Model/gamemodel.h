#ifndef MODEL_GAMEMODEL_H
#define GAMEMODEL_H

#include <memory>
#include <limits>
#include "tablemodel.h"
#include "gamerulesmodel.h"

template<class CARTA, class MESA = TableModel<CARTA, PlayerModel<CARTA>, DeckModel<CARTA>>>
class GameModel {
public:

    //Construtor
    //recebe um ponteiro da classe regra e um vetor de nomes de jogadores
    //inicializa os atributos rodada com 1, jogador atual como 0 e jogando como true
    //cria a mesa e distribui o numero de cartas inicial para a mao dos jogadores
    GameModel(GameRulesModel *regra, std::vector<std::string> nomes);

    virtual ~GameModel();

    std::size_t numero_de_jogadores() const; //retorna numero de jogares
    int cartas_inicial() const; //retorna numero de cartas iniciais monte
    int cartas_jogadores() const; //retorna cartas iniciais por jogadores
    int max_rodadas() const; //retorna numero maximo de rodadas
    int pontuacao_max() const; //retorna numero de pontos para termino

    //reinicia o jogo como se o objeto GameModel fosse recem criado
    void reiniciar();

    //Termina a jogada do jogador atual, caso ele seja o ultimo jogador, muda a rodada
    virtual bool fim_jogada();

    //Retorna se o jogo esta em andamento
    bool jogando() const;

    //Retorna numero da rodada atual
    std::size_t rodada() const;

    //Retorna o nome do jogador atual
    std::string nome_jogador_atual() const;

    //Retorna a posicao na mesa do jogador atual
    std::size_t posicao_jogador_atual() const;

    //Retorna um vetor contendo as cartas do jogador atual
    std::vector<CARTA> mostra_mao_jogador_atual() const;

    //Retorna um vetor contendo as cartas viradas para cim do jogador na posi pos
    //se a carta estiver virada para baixo ele retorna uma carta de valor "zero"
    std::vector<CARTA> mostra_mao_jogador(std::size_t pos) const;

    //Retorna um vetor de cartas com a mao do jogador sem considerar se estao viradas ou não
    std::vector<CARTA> mostra_mao_jogador_consulta(int pos);

    //Retorna a pontucao do jogador atual
    int pontuacao_jogador_atual() const;

    //Aumenta a pontucao do jogador que esta na posicao "pos" em "pontos" pontos
    void jogador_soma_pontos(int pontos, std::size_t pos = jogador_atual);

    //Diminui a pontucao do jogador que esta na posicao "pos" em "pontos" pontos
    void jogador_subtrai_pontos(int pontos, std::size_t pos = jogador_atual);

    // move carta do jogador atual para outro jogador
    bool move_carta_j(CARTA carta, std::size_t j);

    // move carta do monte principal para outro monte
    bool move_carta_m(std::size_t m, bool p_cima = true, bool m_cima = true);

    //altera a posicao do jogador atual
    //recebe como parametro a nova posicao do jogador atual sendo '0' a primeira e 'numero de jogadores -1' a ultima
    void muda_jogador_atual(int novapos);

    // move carta entre jogadores
    //
    // "carta" - Carta que será retirada de um jogador para ser passado a outro(usa o comparador padrao da carta)
    // "j1" - indice do jogador que entregara a carta ao outro
    // "j2" - indice do jogador que recebera a carta
    //
    // retorna um booleano indicando se "carta" foi encontrada na mao de "j1" podendo executar a troca
    //
    // ex: jogo.move_carta_jj(Carta(3, Carta::Naipe::copas), jogador_atual, 3);
    //
    bool move_carta_jj(CARTA carta, std::size_t j1, std::size_t j2 = jogador_atual);

    // move carta de um jogador para um monte
    //
    // "carta" - Carta que será retirada de um jogador para ser passado a um monte(usa o comparador padrao da carta)
    // "j" - indice do jogador que entregara a carta ao monte
    // "m" - indice do monte
    // "m_cima" - caso true a carta sera colocada na parte de cima do baralho, caso false em baixo
    //
    // retorna um booleano indicando se "carta" foi encontrada na mao de "j" podendo executar a troca
    //
    // ex: jogo.move_carta_jm(Carta(3, Carta::Naipe::copas), 2, 0, false);
    //
    bool move_carta_jm(CARTA carta, std::size_t j = jogador_atual, std::size_t m = 0, bool m_cima = true);

    // move carta de um monte para um jogador
    //
    // "m" - indice do jogador que entregara a carta ao outro
    // "j" - indice do jogador que recebera a carta
    // "m_cima" - caso true a carta sera tirada da parte de cima do baralho, caso falso de baixo
    //
    // retorna um booleano se "m" nao esta vazio, dessa forma, podendo fazer a troca
    //
    // ex: jogo.move_carta_mj(3, jogador_atual, true);
    //
    bool move_carta_mj(std::size_t m = 0, std::size_t j = jogador_atual, bool m_cima = true);

    // move carta entre montes
    //
    // "m1" - indice do monte que entregara a carta ao outro
    // "m2" - indice do monte que recebera a carta
    // "m1_cima" - caso true a carta sera tirada da parte de cima do baralho "m1", caso falso de baixo
    // "m2_cima" - caso true a carta sera colocada na parte de cima do baralho "m2', caso false em baixo
    //
    // retorna um booleano se "m1" nao esta vazio, dessa forma, podendo fazer a troca
    //
    // ex: jogo.move_carta_mm(0, 1, true, true);
    //
    bool move_carta_mm(std::size_t m1, std::size_t m2 = 0, bool m1_cima = true, bool m2_cima = true);


    //Cria um novo monte na mesa
    void novo_monte();

    //Deleta um monte da mesa especificada em "i"
    void deleta_monte(std::size_t i);

    //Mostra um monte dado que está na mesa (monte 0 é o monte principal da mesa)
    std::vector<std::pair<bool, CARTA> > mostra_monte(std::size_t pos_monte) const;

    // vira uma carta de um monte
    //
    // "m" - Indice do monte que tera uma de suas cartas virada
    // "m_cima" - Caso true a carta sera tira do topo do monte, caso contrario, de baixo
    //
    // nao retorna nada
    //
    // ex: jogo.vira_carta_monte(2, false);
    //
    void vira_carta_monte(std::size_t m = 0, bool m_cima = true);

    // vira uma carta de um jogador
    //
    // "pos_carta" - Posicao da carta a ser virada na mao do jogador
    // "j" - indice do jogador que tera uma de suas cartas virada
    //
    // nao retorna nada
    //
    // ex: jogo.vira_carta_jogador(2);
    //
    void vira_carta_jogador(std::size_t pos_carta, std::size_t j = jogador_atual);

    // Distribui as cartas para os jogadores. O metodo apenas chama o metodo ja feito na mesa.h.
    // o numero de cartas distribuidas vai ser o mesmo numero de cartas escolhidas na regra.
    //
    // nao retorna nada

    // ex: jogo.distribuir;
    void distribuir();

    //limpa outros montes menos o principal
    //chama o metodo de mesa.h
    void limpa_outros_montes();

    //jogadores aptos viram espectadores, e espectadores viram jogadores aptos
    //a posicao do jogador que tera sua aptidao mudada é especificada em pos
    //chama o metodo de mesa.h
    void muda_aptidao(int pos);

    //informa se jogador esta apto
    //para saber se o jogador esta apto passa-se sua posicao
    //chama o metodo de mesa.h
    bool esta_apto(int pos);

    //Retorna o numero de jogadores aptos
    //chama o metodo de mesa.h
    std::size_t numero_jogadores_aptos();		//retorna o numero de jogadores aptos restante no jogo

    //restaura as cartas do monte inicial às do inicio de jogo
    //certifique-se primeiro de nao haver cartas nas maos dos jogadores para nao criar cartas a mais
    //chama o metodo de mesa.h
    void restaurar_monte_inicial();


    //embaralha as cartas do monte principal
    //cuidado, este metodo nao restaura as cartas do monte
    //chama o metodo de mesa.h
    void embaralhar_monte_principal();

    //esvazia mao do jogador especificado em _jogador
    //chama o metodo esvazia_mao da mesa
    void esvazia_mao(std::size_t _jogador);

protected:

    static const std::size_t jogador_atual = std::numeric_limits<std::size_t>::max();

    virtual void verifica_fim_de_jogo();

    virtual void verifica_vitoria();					//checa se algum jogador ja ganhou

    virtual void verifica_jogadores_derrotados();		//checa se algum jogador perdeu

    virtual bool todos_jogadores_derrotados();			//retorna se todos os jogadores perderam

    virtual void verifica_fim_zero_cartas();			//ultizado na condicao de fim de todos com zero cartas

    virtual void verifica_jogador_pontuacao_maxima();	//utilizado para condicao de vitoria de maior pontuacao

    virtual void verifica_jogador_pontuacao_minima();	//utilizado para condicao de vitoria de menor pontuacao

    virtual void verifica_jogador_mais_cartas();		//ultizado para condicao de vitoria de mais cartas

    virtual void verifica_jogador_menos_cartas();		//ultizado para condicao de vitoria de menos cartas

    virtual void verifica_jogador_unico();				//utilizado na condicao de vitoria de ultimo jogador

    virtual void declara_fim_de_jogo();					//troca o estado da variavel que declara se o jogo esta rodando

    virtual void declara_vencedor(std::size_t j);		//declara o jogador j como vencedor e encerra o jogo

    void _coloca_monte(CARTA c, std::size_t m, bool topo);	//coloca a carta c no topo(se for true) do monte m

    virtual CARTA _pega_monte(std::size_t m, bool topo);	//pega uma carta do topo(se for true) do monte m

    std::unique_ptr<GameRulesModel> _regra;		//ponteiro para a regra do jogo
    MESA _mesa;			//objeto da classe mesa que representa a mesa do jogo
    std::size_t _jog_atual;				//guarda a posicao do jogador atual
    std::size_t _rodada;				//guarda a rodada do jogo
    bool _jogando;   					//se for true o jogo esta rodando

};



template<class CARTA, class MESA> GameModel<CARTA, MESA>::GameModel(GameRulesModel *regra, std::vector<std::string> nomes) : _regra{regra}, _mesa{ (unsigned int) regra->cartas_inicial() },
    _jog_atual{0}, _rodada{1}, _jogando{true} {

    if(nomes.size() != numero_de_jogadores()) std::cerr << "Jogo::Jogo -- Numero incorreto de nomes passado\n";

    auto it = nomes.begin();

    for(std::size_t i = 0; i < numero_de_jogadores(); i++){

        _mesa.add_jogador((it != nomes.end()) ? *it : "");

        it++;
    }

    _mesa.distribuir(cartas_jogadores());

    if(!cartas_jogadores()){

        int aux = _regra->pontuacao_carta_mao()*cartas_jogadores();

        for(std::size_t i = 0; i < numero_de_jogadores(); i++) _mesa.jogador_soma_pontos(aux, i);
    }
}

template<class CARTA, class MESA> GameModel<CARTA, MESA>::~GameModel() {}

template<class CARTA, class MESA> std::size_t GameModel<CARTA, MESA>::numero_de_jogadores() const {
    return _regra->numero_de_jogadores();
}

template<class CARTA, class MESA> int GameModel<CARTA, MESA>::cartas_inicial() const {
    return _regra->cartas_inicial();
}

template<class CARTA, class MESA> int GameModel<CARTA, MESA>::cartas_jogadores() const {
    return _regra->cartas_jogadores();
}

template<class CARTA, class MESA> int GameModel<CARTA, MESA>::max_rodadas() const {
    return _regra->max_rodadas();
}

template<class CARTA, class MESA> int GameModel<CARTA, MESA>::pontuacao_max() const {
    return _regra->pontuacao_max();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::reiniciar(){

    _rodada = 1;
    _jog_atual = 0;
    _jogando = true;

    //Reseta pontuacao, limpa a mao e muda aptidao se nao for apto
    for(std::size_t pos_jogador=0; pos_jogador < numero_de_jogadores(); pos_jogador++)
    {
        _mesa.ver_jogador(pos_jogador).pontuacao(0);
        _mesa.esvazia_mao(pos_jogador);
        if(!_mesa.ver_jogador(pos_jogador).esta_apto())
            _mesa.ver_jogador(pos_jogador).muda_aptidao();
    }

    //Restaura o monte da mesa e resdistribui as cartas para os jogadores
    _mesa.monte_mesa().restaurar();
    _mesa.limpa_outros_montes();
    _mesa.distribuir(cartas_jogadores());

    if(!cartas_jogadores()){

        int aux = _regra->pontuacao_carta_mao()*cartas_jogadores();

        for(std::size_t i = 0; i < numero_de_jogadores(); i++) _mesa.jogador_soma_pontos(aux, i);
    }
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::fim_jogada(){

    if(!_jogando) return false;

    if(max_rodadas() > 0)  if(_rodada >= (std::size_t) max_rodadas()) return false;

    while(1){

        if(++_jog_atual == numero_de_jogadores()){

            _jog_atual = 0;

            _rodada++;

            verifica_jogadores_derrotados();
            verifica_fim_de_jogo();
            verifica_vitoria();
        }

        if(_mesa.ver_jogador(_jog_atual).esta_apto()) break;

    }

    return true;
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::jogando() const {

    return _jogando;
}

template<class CARTA, class MESA> std::size_t GameModel<CARTA, MESA>::rodada() const {

    return _rodada;
}

template<class CARTA, class MESA> std::size_t GameModel<CARTA, MESA>::posicao_jogador_atual() const {

    return _jog_atual;
}

template<class CARTA, class MESA> std::string GameModel<CARTA, MESA>::nome_jogador_atual() const {

    return _mesa.ver_jogador(_jog_atual).nome();
}

template<class CARTA, class MESA> std::vector<CARTA> GameModel<CARTA, MESA>::mostra_mao_jogador_atual() const {

    return _mesa.ver_jogador(_jog_atual).mostra_mao();
}


template<class CARTA, class MESA> std::vector<CARTA> GameModel<CARTA, MESA>::mostra_mao_jogador(std::size_t pos) const{

    auto vet = _mesa.ver_jogador(pos).mostra_mao();

    //abaixo:
    //retorna apenas as cartas viradas para cima, as para baixo voltam como cartas de valor "zero";

    std::vector<CARTA> aux;

    aux.reserve(vet.size());

    for(auto carta : vet){

        if(carta.mostra()) aux.push_back(carta);
        else aux.emplace_back(0, (typename CARTA::Suit) 0);
    }

    return aux;
}




template<class CARTA, class MESA> int GameModel<CARTA, MESA>::pontuacao_jogador_atual() const {

    return _mesa.ver_jogador(_jog_atual).pontuacao();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::jogador_soma_pontos(int pontos, std::size_t pos /* = jogador_atual */){

    _mesa.jogador_soma_pontos(pontos, (pos == jogador_atual) ? _jog_atual : pos);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::jogador_subtrai_pontos(int pontos, std::size_t pos /* = jogador_atual */){

    jogador_soma_pontos(-pontos,(pos == jogador_atual) ? _jog_atual : pos);
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::move_carta_j(CARTA carta, std::size_t j){

    return move_carta_jj(carta, jogador_atual, j);
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::move_carta_m(std::size_t m, bool p_cima /* = true */, bool m_cima /* = true */){

    return move_carta_mm(0, m, p_cima, m_cima);
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::move_carta_jj(CARTA carta, std::size_t j1, std::size_t j2 /* = jogador_atual */){

    if(j1 == jogador_atual) j1 = _jog_atual;
    if(j2 == jogador_atual) j2 = _jog_atual;

    if(_mesa.jogador_tira_carta(carta, j1)){

        _mesa.jogador_recebe_carta(carta, j2);

        return true;
    }

    _mesa.jogador_soma_pontos(-_regra->pontuacao_carta_mao(), j1);
    _mesa.jogador_soma_pontos(_regra->pontuacao_carta_mao(), j2);

    return false;
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::move_carta_jm(CARTA carta, std::size_t j /* = jogador_atual */, std::size_t m /* = 0 */, bool m_cima /* = true */){

    if(j == jogador_atual) j = _jog_atual;

    if(!_mesa.jogador_tira_carta(carta, j)) return false;

    _coloca_monte(carta, m, m_cima);

    _mesa.jogador_soma_pontos(-_regra->pontuacao_carta_mao(), j);

    return true;
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::move_carta_mj(std::size_t m /* = 0 */, std::size_t j /* =  jogador_atual */, bool m_cima /* = true */){

    if(_mesa.tamanho_monte(m) == 0) return false;

    if(j == jogador_atual) j = _jog_atual;

    _mesa.jogador_recebe_carta(_pega_monte(m, m_cima), j);

    _mesa.jogador_soma_pontos(_regra->pontuacao_carta_mao(), j);

    return true;
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::move_carta_mm(std::size_t m1, std::size_t m2 /* = 0 */, bool m1_cima /* = true */, bool m2_cima /* = true */){

    if(_mesa.tamanho_monte(m1) == 0) return false;

    _coloca_monte(_pega_monte(m1, m1_cima), m2, m2_cima);

    return true;
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::novo_monte(){

    _mesa.novo_monte();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::deleta_monte(std::size_t i){

    _mesa.deleta_monte(i);
}

template<class CARTA, class MESA> std::vector<std::pair<bool, CARTA> > GameModel<CARTA, MESA>::mostra_monte(std::size_t pos_monte) const{

    return _mesa.mostra_monte(pos_monte);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_fim_de_jogo()
{
    switch(_regra->fim())
    {
    case (GameRulesModel::modo_fim::padrao) :		//caso de um jogador restante
        if(numero_jogadores_aptos() == 1) declara_fim_de_jogo();
        break;

    case (GameRulesModel::modo_fim::pontuacao) :	//caso de um jogador ter atingido pontuacao maxima
        for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
        {
            if(_mesa.ver_jogador(pos_jogador).esta_apto() && _mesa.ver_jogador(pos_jogador).pontuacao() >= _regra->pontuacao_max())
                declara_fim_de_jogo();
        }
        break;

    case (GameRulesModel::modo_fim::rodadas) : 	//caso atingido numero maximo de rodadas
        if((int)rodada() > _regra->max_rodadas())
            declara_fim_de_jogo();
        break;

    case (GameRulesModel::modo_fim::zero_cartas) :
    {
        bool condicao = true;	//condicao para checar se todos possuem zero cartas

        for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
        {
            if(_mesa.ver_jogador(pos_jogador).esta_apto() && _mesa.ver_jogador(pos_jogador).mostra_mao().size() != 0)	condicao = false;;
        }
        if(condicao) declara_fim_de_jogo();
        break;
    }

    case (GameRulesModel::modo_fim::zero_jogadores) :
        if(numero_jogadores_aptos() == 0)
            declara_fim_de_jogo();
        break;

    }

}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_vitoria() {

    if(!_jogando) return;

    if(todos_jogadores_derrotados()) return;

    switch(_regra->cond_vit())
    {
    case GameRulesModel::condicao_vitoria::padrao :
        if(numero_de_jogadores() > 1) verifica_jogador_unico();
        break;

    case GameRulesModel::condicao_vitoria::maior_pontuacao :
        verifica_jogador_pontuacao_maxima();
        break;

    case GameRulesModel::condicao_vitoria::menor_pontuacao :
        verifica_jogador_pontuacao_minima();
        break;

    case GameRulesModel::condicao_vitoria::mais_cartas :
        verifica_jogador_mais_cartas();
        break;

    case GameRulesModel::condicao_vitoria::menos_cartas :
        verifica_jogador_menos_cartas();
        break;

    }
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_jogadores_derrotados()
{
    if(!jogando()) return;

    if(!todos_jogadores_derrotados()) return;

    switch(_regra->cond_der())
    {
    case GameRulesModel::condicao_derrota::estoura_pontuacao :
        for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
        {
            if(_mesa.ver_jogador(pos_jogador).esta_apto() && _mesa.ver_jogador(pos_jogador).pontuacao() > _regra->pontuacao_max())
                _mesa.ver_jogador(pos_jogador).muda_aptidao();
        }
        break;

    case GameRulesModel::condicao_derrota::zero_cartas :
        for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
        {
            if(_mesa.ver_jogador(pos_jogador).esta_apto() && _mesa.ver_jogador(pos_jogador).mostra_mao().size() == 0)
                _mesa.ver_jogador(pos_jogador).muda_aptidao();
        }
        break;

    case GameRulesModel::condicao_derrota::zero_pontos :
        for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
        {
            if(_mesa.ver_jogador(pos_jogador).esta_apto() && _mesa.ver_jogador(pos_jogador).pontuacao() == 0)
                _mesa.ver_jogador(pos_jogador).muda_aptidao();
        }
        break;

    case GameRulesModel::condicao_derrota::nenhuma :
        break;
    }
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::todos_jogadores_derrotados() {

    if(numero_jogadores_aptos() == 0){
        declara_fim_de_jogo();
        return true;
    }
    return false;
}


template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_fim_zero_cartas(){

    for(std::size_t i = 0; i < numero_de_jogadores(); i++){

        if(_mesa.ver_jogador(i).mostra_mao().size() == 0){

            declara_fim_de_jogo();
        }
    }
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_jogador_unico(){

    if(todos_jogadores_derrotados()) return;

    std::size_t jog_aptos = 0;
    std::size_t last = _jog_atual;

    for(std::size_t i = 0; i < _mesa.numero_jogadores(); i++){

        if(_mesa.ver_jogador(i).esta_apto()){

            jog_aptos++;

            last = i;
        }
    }

    if(jog_aptos > 1) return;

    declara_vencedor(last);
}

template<class CARTA, class MESA> std::size_t GameModel<CARTA, MESA>::numero_jogadores_aptos(){

    return _mesa.numero_jogadores_aptos();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_jogador_pontuacao_maxima(){

    if(todos_jogadores_derrotados()) return;

    int maior_pontuacao = 0;
    int jogador_vencedor = 0;

    //checa todos os jogadores aptos e ve qual tem mais pontos
    for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
    {
        if(_mesa.ver_jogador().esta_apto() && _mesa.ver_jogador(pos_jogador).pontuacao() > maior_pontuacao)
        {
            maior_pontuacao = _mesa.ver_jogador(pos_jogador).pontuacao();
            jogador_vencedor = (int)pos_jogador;
        }
    }

    declara_vencedor(jogador_vencedor);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_jogador_pontuacao_minima(){

    if(todos_jogadores_derrotados()) return;

    int menor_pontuacao = 999999;
    int jogador_vencedor = 0;

    //checa todos os jogadores aptos e ve qual tem menos pontos
    for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
    {
        if(_mesa.ver_jogador().esta_apto() && _mesa.ver_jogador(pos_jogador).pontuacao() < menor_pontuacao)
        {
            menor_pontuacao = _mesa.ver_jogador(pos_jogador).pontuacao();
            jogador_vencedor = (int)pos_jogador;
        }
    }

    declara_vencedor(jogador_vencedor);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_jogador_mais_cartas(){

    if(todos_jogadores_derrotados()) return;

    std::size_t maior_numero_cartas = -999999;
    std::size_t jogador_vencedor = 0;

    //checa todos os jogadores aptos e ve qual tem mais cartas
    for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
    {
        if(_mesa.ver_jogador().esta_apto() && _mesa.ver_jogador(pos_jogador).mostra_mao().size() > maior_numero_cartas)
        {
            maior_numero_cartas = _mesa.ver_jogador(pos_jogador).mostra_mao().size();
            jogador_vencedor = pos_jogador;
        }
    }

    declara_vencedor(jogador_vencedor);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::verifica_jogador_menos_cartas(){

    if(todos_jogadores_derrotados()) return;

    std::size_t menor_numero_cartas = 999999;
    std::size_t jogador_vencedor = 0;

    //checa todos os jogadores aptos e ve qual tem menos cartas
    for(std::size_t pos_jogador = 0; pos_jogador < _mesa.numero_jogadores(); pos_jogador++)
    {
        if(_mesa.ver_jogador().esta_apto() && _mesa.ver_jogador(pos_jogador).mostra_mao().size() < menor_numero_cartas)
        {
            menor_numero_cartas = _mesa.ver_jogador(pos_jogador).mostra_mao().size();
            jogador_vencedor = pos_jogador;
        }
    }

    declara_vencedor(jogador_vencedor);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::declara_fim_de_jogo(){

    _jogando = false;
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::declara_vencedor(std::size_t j){

    _jog_atual = j;

    _jogando = false;
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::_coloca_monte(CARTA c, std::size_t m, bool topo){

    if(topo) _mesa.coloca_topo(c, m);
    else _mesa.coloca_baixo(c, m);
}

template<class CARTA, class MESA> CARTA GameModel<CARTA, MESA>::_pega_monte(std::size_t m, bool topo){

    if(topo) return _mesa.pega_topo(m);
    else return _mesa.pega_baixo(m);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::vira_carta_monte(std::size_t m /* = 0 */, bool m_cima /* = true */){

    _mesa.vira_carta_monte(m, m_cima);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::vira_carta_jogador(std::size_t pos_carta, std::size_t j /* = jogador_atual */){

    if(j == jogador_atual) j = _jog_atual;

    _mesa.vira_carta_jogador(pos_carta, j);
}


template<class CARTA, class MESA> void GameModel<CARTA, MESA>::distribuir(){

    _mesa.distribuir(cartas_jogadores());
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::muda_jogador_atual(int novapos){
    _jog_atual = novapos;
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::muda_aptidao(int pos){
    _mesa.muda_aptidao(pos);
}

template<class CARTA, class MESA> bool GameModel<CARTA, MESA>::esta_apto(int pos){
    return _mesa.esta_apto(pos);
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::restaurar_monte_inicial(){
    _mesa.restaurar_monte_inicial();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::limpa_outros_montes(){
    _mesa.limpa_outros_montes();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::embaralhar_monte_principal(){
    _mesa.embaralhar_monte_principal();
}

template<class CARTA, class MESA> void GameModel<CARTA, MESA>::esvazia_mao(std::size_t _jogador){
    _mesa.esvazia_mao(_jogador);
    return ;
}

template<class CARTA, class MESA> std::vector<CARTA> GameModel<CARTA, MESA>::mostra_mao_jogador_consulta(int pos){
    return _mesa.ver_jogador(pos).mostra_mao();
}

using Game = GameModel<CardModel, Mesa>;

#endif // GAMEMODEL_H

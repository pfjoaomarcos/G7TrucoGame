#include "playtrucocontroller.h"

PlayTrucoController::PlayTrucoController(GameRulesModel *regra, std::vector<std::string> nomes, GameView *_interface):Game(regra, nomes),
    gameScreen{_interface}{

    _truco = false;
    _valor_truco = 0;

    _jog_atual = _regra->jogador_comeca();
    carta_ganhando = 0;
    jogador_ganhando = 0;
    _cond_rodada = true;
    _turno = true;
    _rodada = 0;

    gameScreen->iniciaScene();

    gameScreen->mostraBaralho(mostra_monte(0));
    gameScreen->mostraMaoInicio(mostra_mao_jogador_pos(0));
    for(std::size_t i = 1; i < numero_de_jogadores(); i++){
        gameScreen->outrasMaos(i,mostra_mao_jogador(i));
    }

    gameScreen->showFullScreen();
    gameScreen->mostraMao();
}

PlayTrucoController::~PlayTrucoController() {
}

void PlayTrucoController::jogar(){
    bool resposta = false;
    bool mao_11 = false;
    novo_monte();
    //Cria o monte em que as cartas serão jogadas
    novo_monte();
    //move uma carta do monte principal para o monte 1 que sera o vira

    move_carta_mm(0,1,true,true);
    vira_carta_monte(1,true);

    while(jogando()){
        resposta = false;
        while(!fim_turno() && _turno == true){

            gameScreen->mostraVira(mostra_monte(1)[0].second);
            carta_ganhando = 0;
            jogador_ganhando = 0;

            if(checa_mao_de_11() == 2){
                if(mao_11 == false){
                    gameScreen->JogadoresAsCegas();
                    mao_11 = true;
                }
                rodada_as_cegas();
            }
            else if(checa_mao_de_11() == 0 && resposta == false){
                resposta = mao_de_11();

                if(resposta == false){
                    jogador_ganhando = checa_mao_de_11() + 1;
                    while(!fim_turno()){
                        do{
                            incrementa_jog_atual();
                        }while(checa_fim_rodada() == false);
                        jogador_ganhou_rodada(jogador_ganhando);
                        fim_rodada(jogador_ganhando);

                    }
                    break;
                }
            }
            else if(checa_mao_de_11() == 1 ){
                gameScreen->jogadoresMaode11();
                if(ia_aceita_mao_11() == false){
                    jogador_ganhando = checa_mao_de_11() + 1;
                    while(!fim_turno()){
                        do{
                            incrementa_jog_atual();
                        }while(checa_fim_rodada() == false);
                        jogador_ganhou_rodada(jogador_ganhando);
                        fim_rodada(jogador_ganhando);
                    }
                    break;
                }
            }

            do{
                gameScreen->mostraVira(mostra_monte(1)[0].second);
                if(posicao_jogador_atual() == 0){
                    if(checa_mao_de_11() == 2){
                        joga_jogador_posicao0_11();

                    }
                    else{
                        joga_jogador_posicao_0();
                    }
                }
                else{
                    ia_joga();
                }
            }while(checa_fim_rodada() == false && _cond_rodada == true);
            if(!mostra_monte(2).empty()){
                gameScreen->jogadorGanhouRodada(mostra_monte(2)[carta_ganhando].second,jogador_ganhando);
            }
            jogador_ganhou_rodada(jogador_ganhando);
            fim_rodada(jogador_ganhando);
            gameScreen->comeca_nova_rodada();
        }

        if(checa_mao_de_11() == -1 || (checa_mao_de_11() == 0 && resposta == false) ||
            (checa_mao_de_11() == 1 && !ia_aceita_mao_11()) || checa_mao_de_11() ==2){
            if(checa_mao_de_11() == 1 && !ia_aceita_mao_11()){
                gameScreen->JogadoresCorreram();
            }
            jogador_soma_pontos(jogador_ganhou_turno(),valor_pontuacao());
            gameScreen->setPontuacao(QString::number(pontuacao(jogador_ganhou_turno())),jogador_ganhou_turno());
        }

        else if(checa_mao_de_11() == 0 && (resposta == true)){
            jogador_soma_pontos(jogador_ganhou_turno(),3);
            gameScreen->setPontuacao(QString::number(pontuacao(jogador_ganhou_turno())),jogador_ganhou_turno());
        }
        else if(checa_mao_de_11() == 1 && ia_aceita_mao_11()){
            jogador_soma_pontos(jogador_ganhou_turno(),3);
            gameScreen->setPontuacao(QString::number(pontuacao(jogador_ganhou_turno())),jogador_ganhou_turno());
        }

        gameScreen->comeca_novo_turno();
        comeca_novo_turno();
        fim_jogo();
    }
    gameScreen->fimDeJogo(jogador_vencedor());
}

void PlayTrucoController::fim_jogo(){
    verifica_fim_de_jogo();
    return;
}
bool PlayTrucoController::checa_fim_rodada(){
    return _regra->checa_fim_rodada(_jog_atual);
}


bool PlayTrucoController::truco(){
    return _truco;
}

int PlayTrucoController::valor_truco(){
    return _valor_truco;
}

int PlayTrucoController::valor_pontuacao(){
    return _regra->valor_pontuacao(truco(), valor_truco());
}


std::size_t PlayTrucoController::jogador_comeca(){
    return _regra->jogador_comeca();
}

int PlayTrucoController::compara(CardModel c1, CardModel c2,CardModel _vira){
    return _regra->compara(c1,c2,_vira);
}


bool PlayTrucoController::fim_turno(){
    return _regra->fim_turno(_rodada,jogador_ganhou_turno());

}

std::size_t PlayTrucoController::jogador_ganhou_turno(){
    return _regra->jogador_ganhou_turno();
}


int PlayTrucoController::pontuacao(std::size_t _jogador){
    if(_jogador > numero_de_jogadores()){
        return 0;
    }
    else{
        return _mesa.ver_jogador(_jogador).pontuacao();
    }
}

bool PlayTrucoController::verifica_truco(std::size_t _jogador_trucou){
    std::size_t posicao = _jogador_trucou;
    int aceitou_truco = 0;
    int cartas_altas = 0;

    if (posicao == numero_de_jogadores() -1){
        posicao =0;
    }
    posicao++;
    while(posicao != _jogador_trucou){
        cartas_altas = 0;
        if(posicao != posicao_jogador_atual() + 2){
            for(int i = 0; i < (int)(mostra_mao_jogador_pos(posicao)).size(); i++){
                if((mostra_mao_jogador_pos(posicao))[i].numero() <= 3 ||
                    (mostra_mao_jogador_pos(posicao))[i].numero() == (mostra_monte(1))[0].second.numero() + 1){

                    cartas_altas++;
                }
            }
        }
        if(cartas_altas >= 1){
            aceitou_truco++;
        }
        if(posicao == numero_de_jogadores() - 1){
            posicao = 0;
        }
        else{
            posicao++;
        }
    }

    if(aceitou_truco == 2 && numero_de_jogadores() == 4){
        return true;
    }
    else if(aceitou_truco == 1 && numero_de_jogadores() == 2){
        return true;
    }
    else{
        return false;
    }
}

int PlayTrucoController::checa_mao_de_11(){
    int _mao1 = 0;
    int _mao2 = 0;
    std::size_t _jogador = 0;
    for(std::size_t pos = 0; pos < numero_de_jogadores(); pos++){
        if(pontuacao(pos) == 11){
            if(pos == 0 || pos == 2){
                _jogador = 0;
                _mao1 ++;
            }
            else if(pos == 1 || pos == 3){
                _jogador = 1;
                _mao2 ++;
            }
        }
    }
    if(_mao1 >= 1 && _mao2 >= 1){
        return 2;
    }
    else if(_mao1 >=1 || _mao2 >= 1){
        return _jogador;
    }
    return -1;
}

bool PlayTrucoController::ia_aceita_mao_11(){
    int cartas_altas = 0;
    for(std::size_t i = 0 ; i < mostra_mao_jogador_pos(1).size(); i++){
        if(mostra_mao_jogador_pos(1)[i].numero() <= 3 ||
            mostra_mao_jogador_pos(1)[i].numero() == (mostra_monte(1)[0].second).numero() +1){
            cartas_altas ++;
        }
    }
    if(numero_de_jogadores() == 4){
        for(std::size_t i = 0 ; i < mostra_mao_jogador_pos(3).size(); i++){
            if(mostra_mao_jogador_pos(3)[i].numero() <= 3 ||
                mostra_mao_jogador_pos(3)[i].numero() == (mostra_monte(1)[0].second).numero() +1){
                cartas_altas ++;
            }
        }
        if(cartas_altas == 2){
            return true;
        }
        return false;
    }
    else{
        if(cartas_altas  == 1){
            return true;
        }
        return false;
    }
}
//Funcoes privadas
unsigned int PlayTrucoController::jogador_vencedor(){
    unsigned int vencedor = 0;
    for(unsigned int i = 0; i < numero_de_jogadores(); i++){
        if(_mesa.ver_jogador(i).pontuacao() >= 12){
            vencedor = i;
        }
    }
    return vencedor;
}

void PlayTrucoController::joga_jogador_posicao0_11(){
    gameScreen->mostraValorTruco();
    gameScreen->mostraMao();
    gameScreen->mostraMaooff();
    int _carta = gameScreen->cartaSelecionada();
    joga_carta_cima(_carta);


}

void PlayTrucoController::rodada_as_cegas(){
    for(unsigned int i = 0; i < mostra_mao_jogador_pos(0).size(); i++){
        if(mostra_mao_jogador_pos(0)[i].mostra()){
            _mesa.vira_carta_jogador(i,0);
        }
    }
    gameScreen->rodadaAsCegas(mostra_mao_jogador_pos(0));
}

void PlayTrucoController::joga_jogador_comeca(){
    int _carta = gameScreen->cartaSelecionada();

    vira_carta_jogador(_carta, posicao_jogador_atual());
    if(mostra_monte(2).empty()){
        carta_ganhando = 0;
        jogador_ganhando = posicao_jogador_atual();
    }

    else{
        if(compara(mostra_mao_jogador_atual()[_carta],mostra_monte(2)[carta_ganhando].second,
                    mostra_monte(1)[0].second)==(int) PlayTrucoController::Compara::Maior){

            carta_ganhando = 0;
            jogador_ganhando = posicao_jogador_atual();
        }
        else if(compara(mostra_mao_jogador_atual()[_carta], mostra_monte(2)[carta_ganhando].second,
                         mostra_monte(1)[0].second) == (int)PlayTrucoController::Compara::Igual && (jogador_ganhando%2 != posicao_jogador_atual()%2)){

            carta_ganhando = 0;
            jogador_ganhando = numero_de_jogadores();
        }
        else{
            carta_ganhando++;
        }
    }
    gameScreen->jogaCarta(posicao_jogador_atual(),_carta,mostra_mao_jogador_atual()[_carta]);
    move_carta_jm((mostra_mao_jogador_atual())[_carta],posicao_jogador_atual(),2, true);
    incrementa_jog_atual();

}

void PlayTrucoController::joga_carta_cima(unsigned int _carta){

    vira_carta_jogador(_carta, posicao_jogador_atual());

    if(mostra_monte(2).empty()){
        carta_ganhando = 0;
        jogador_ganhando = posicao_jogador_atual();
    }

    else{
        if(compara(mostra_mao_jogador_atual()[_carta],mostra_monte(2)[carta_ganhando].second,
                    mostra_monte(1)[0].second)==(int) PlayTrucoController::Compara::Maior){

            carta_ganhando = 0;
            jogador_ganhando = posicao_jogador_atual();
        }
        else if(compara(mostra_mao_jogador_atual()[_carta], mostra_monte(2)[carta_ganhando].second,
                         mostra_monte(1)[0].second) == (int)PlayTrucoController::Compara::Igual &&(jogador_ganhando%2 != posicao_jogador_atual()%2)){

            carta_ganhando = 0;
            jogador_ganhando = numero_de_jogadores();
        }
        else{
            carta_ganhando++;
        }
    }
    gameScreen->jogaCarta(posicao_jogador_atual(),_carta,mostra_mao_jogador_atual()[_carta]);
    move_carta_jm((mostra_mao_jogador_atual())[_carta],posicao_jogador_atual(),2, true);
    incrementa_jog_atual();
}

std::vector<CardModel> PlayTrucoController::mostra_mao_jogador_pos(std::size_t _jogador){
    if(_jogador > numero_de_jogadores()){
        return _mesa.ver_jogador(0).mostra_mao();
    }
    else{
        return _mesa.ver_jogador(_jogador).mostra_mao();
    }
}

bool PlayTrucoController::mao_de_11(){
    bool resposta = false;
    if(numero_de_jogadores() == 4){
        if(_jog_atual == 0 || _jog_atual == 2){
            for(int i = 0; i < cartas_jogadores(); i++){
                if(!(mostra_mao_jogador_pos(0)[i].mostra())){
                    _mesa.vira_carta_jogador(i,0);
                }
            }
            for(int i = 0; i < cartas_jogadores(); i++){
                if(!(mostra_mao_jogador_pos(2)[i].mostra())){
                    _mesa.vira_carta_jogador(i,2);
                }
            }
            resposta =  gameScreen->maoDe11(mostra_mao_jogador_pos(0),mostra_mao_jogador_pos(2), mostra_monte(1)[0].second);

            for(int i = 0; i < cartas_jogadores(); i++){
                if((mostra_mao_jogador_pos(0)[i].mostra())){
                    _mesa.vira_carta_jogador(i,0);
                }
            }

            for(int i = 0; i < cartas_jogadores(); i++){
                if((mostra_mao_jogador_pos(2)[i].mostra())){
                    _mesa.vira_carta_jogador(i,2);
                }
            }
        }
        return resposta;
    }
    else{
        resposta = gameScreen->maoDe11_2();
        return resposta;
    }
}

void PlayTrucoController::comeca_novo_turno(){
    _turno = true;
    _cond_rodada = true;
    _truco = false;
    _valor_truco = 0;
    _rodada = 0;

    _regra->jogador_comeca_turno(_regra->jogador_comeca() +1);
    if(_regra->jogador_comeca_turno()== numero_de_jogadores()){
        _regra->jogador_comeca_turno(0);
    }

    _regra->jogador_comeca(_regra->jogador_comeca_turno());
    _jog_atual = _regra->jogador_comeca_turno();

    if(_regra->jogador_comeca() ==0){
        _regra->jogador_termina(numero_de_jogadores());
    }
    else{
        _regra->jogador_termina(_regra->jogador_comeca());
    }

    _regra->recomeca_turno();

    for(std::size_t pos_jogador=0; pos_jogador < numero_de_jogadores(); pos_jogador++)
    {
        esvazia_mao(pos_jogador);
    }

    move_carta_mm(1,0,true,true);
    std::size_t _tamanho_monte = mostra_monte(2).size();

    for(std::size_t i = 0; i < _tamanho_monte ; i++){
        move_carta_mm(2,0,true,true);
    }

    if(jogando()){

        restaurar_monte_inicial();
        embaralhar_monte_principal();
        _mesa.distribuir(cartas_jogadores());

        move_carta_mm(0,1,true,true);
        vira_carta_monte(1,true);
    }
    gameScreen->mostraBaralho(mostra_monte(0));
    gameScreen->mostraMaoInicio(mostra_mao_jogador_pos(0));
    for(std::size_t i = 1; i < numero_de_jogadores(); i++){
        gameScreen->outrasMaos(i,mostra_mao_jogador(i));
    }

}


void PlayTrucoController::incrementa_jog_atual(){
    if(_regra->jogador_comeca() == 0){
        if(_jog_atual == numero_de_jogadores()){
            _jog_atual = 0;
        }
        else{
            _jog_atual ++;
        }
    }
    else{
        if(_jog_atual == numero_de_jogadores() -1){
            _jog_atual = 0;
            return;
        }
        else{
            _jog_atual++;
        }
    }
}

void PlayTrucoController::jogador_soma_pontos(std::size_t _jogador,int pontos){
    if(numero_de_jogadores() == 4){
        if(_jogador  == 0){
            _mesa.jogador_soma_pontos(pontos, 0);
            _mesa.jogador_soma_pontos(pontos, 2);
        }
        else if(_jogador  == 1){
            _mesa.jogador_soma_pontos(pontos, 1);
            _mesa.jogador_soma_pontos(pontos, 3);
        }
    }
    else{
        _mesa.jogador_soma_pontos(pontos, _jogador);
    }
}

void PlayTrucoController::jogador_ganhou_rodada(std::size_t _jogador){
    _regra->jogador_ganhou_rodada(_jogador, _rodada);
}

void PlayTrucoController::pede_truco(std::size_t j1){
    if(pontuacao(j1) == 11){
        _truco = false;
    }
    else if(_truco == false){
        _valor_truco = 3;
        _truco = true;
    }
    else if(_truco == true){
        if(_valor_truco == 12){
            _valor_truco = 12;
        }
        else{
            _valor_truco += 3;
        }
    }
}


void PlayTrucoController::fim_rodada(std::size_t _jogador_ganhou){
    if(_jogador_ganhou == numero_de_jogadores()){
        _regra->jogador_comeca(_regra->jogador_comeca_turno());
        _jog_atual = _regra->jogador_comeca();
    }
    else{
        _regra->jogador_comeca(_jogador_ganhou);
        _jog_atual = _regra->jogador_comeca();
    }

    if(_regra->jogador_comeca() == 0){
        _regra->jogador_termina(numero_de_jogadores());
    }
    else{
        _regra->jogador_termina(_regra->jogador_comeca());
    }

    if(!mostra_monte(2).empty()){
        std::size_t _tamanho_monte = mostra_monte(2).size();

        for(std::size_t i = 0; i < _tamanho_monte ; i++){
            move_carta_mm(2,0,true,true);
        }
    }

    _rodada++;
}


void PlayTrucoController::joga_jogador_posicao_0(){
    gameScreen->mostraValorTruco();
    if(posicao_jogador_atual() == jogador_comeca() || rodada() == 0){
        gameScreen->mostraMaooff();
    }
    else{
        gameScreen->mostraMao();
    }

    gameScreen->acao(pontuacao_jogador_atual());

    if((gameScreen->statusTruco() && verifica_truco(posicao_jogador_atual()) == true)){
        gameScreen->setTrucoFalse();
        gameScreen->mostraValorTruco(valor_truco());

        pede_truco(posicao_jogador_atual());
        if(posicao_jogador_atual() == jogador_comeca()){
            joga_jogador_comeca();
        }
        else{
            int _carta = gameScreen->cartaSelecionada();
            if(gameScreen->getClick(_carta)){
                joga_carta_cima(_carta);
            }
            else{
                gameScreen->jogaCarta(posicao_jogador_atual(),_carta,mostra_mao_jogador_atual()[_carta]);
                move_carta_jm((mostra_mao_jogador_atual())[_carta],posicao_jogador_atual(),0, true);
                incrementa_jog_atual();
            }
        }
    }
    else if((gameScreen->statusTruco() && verifica_truco(posicao_jogador_atual()) == false)){
        gameScreen->setTrucoFalse();

        jogador_ganhando = posicao_jogador_atual();
        while(!fim_turno()){
            jogador_ganhou_rodada(jogador_ganhando);
            fim_rodada(jogador_ganhando);
            gameScreen->comeca_nova_rodada();

        }
        gameScreen->JogadoresCorreram();
        _rodada = false;
        _cond_rodada = false;
    }
    else{
        if(posicao_jogador_atual() == jogador_comeca()){
            joga_jogador_comeca();
        }
        else{
            int _carta = gameScreen->cartaSelecionada();

            if(gameScreen->getClick(_carta)){
                joga_carta_cima(_carta);
            }
            else{
                gameScreen->jogaCarta(posicao_jogador_atual(),_carta,mostra_mao_jogador_atual()[_carta]);
                move_carta_jm((mostra_mao_jogador_atual())[_carta],posicao_jogador_atual(),0, true);
                incrementa_jog_atual();
            }
        }
    }
}

void PlayTrucoController::ia_joga(){
    vira_carta_jogador(0,posicao_jogador_atual());

    if(mostra_monte(2).empty()){
        carta_ganhando = 0;
        jogador_ganhando = posicao_jogador_atual();
    }
    else{
        if(compara(mostra_mao_jogador_atual()[0],
                    mostra_monte(2)[carta_ganhando].second,
                    mostra_monte(1)[0].second) == (int)PlayTrucoController::Compara::Maior){

            carta_ganhando = 0;
            jogador_ganhando = posicao_jogador_atual();

        }
        else if(compara(mostra_mao_jogador_atual()[0],
                         mostra_monte(2)[carta_ganhando].second,
                         mostra_monte(1)[0].second) == (int)PlayTrucoController::Compara::Igual &&(jogador_ganhando%2 != posicao_jogador_atual()%2)){

            carta_ganhando = 0;
            jogador_ganhando = numero_de_jogadores();
        }
        else{
            carta_ganhando++;
        }
    }
    gameScreen->jogaCarta(posicao_jogador_atual(),0,mostra_mao_jogador_atual()[0]);
    move_carta_jm((mostra_mao_jogador_atual())[0],posicao_jogador_atual(),2,true);
    incrementa_jog_atual();
}

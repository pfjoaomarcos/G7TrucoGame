#ifndef CARDMODEL_H
#define CARDMODEL_H

class CardModel
{
public:

    //representa os naipes existentes para criar uma carta
    enum class Suit{Espadas,Copas,Paus,Ouros};

    // numero de naipes
    static const int n_numeros = 13;
    static const int n_naipes = 4;

    //Cria uma carta
    //recebe o valor do numero, naipe e um booleano indicando se a carta esta virada para cima
    CardModel(int num, Suit np, bool f = false);

    //Destrutor
    virtual ~CardModel();

    //Retorna o valor da carta
    int numero() const;

    //Retorna o naipe da carta
    Suit naipe() const;

    //Vira a carta
    void vira();

    //Indica se a face da carta esta virada para cima
    bool mostra() const;

    //Retorna true se a carta for igual a "c"
    bool operator==(const CardModel& c) const;

    //Retorna true se a carta for diferente de "c"
    bool operator!=(const CardModel& c) const;

    //retorna true se a carta for menor que "c"
    bool operator<(const CardModel& c) const;

    //retorna true se a carta for maior que "c"
    bool operator>(const CardModel& c) const;

    //retorna true se a carta for menor ou igual a "c"
    bool operator<=(const CardModel& c) const;

    //retorna true se a carta for maior ou igual a "c"
    bool operator>=(const CardModel& c) const;

protected:

    //guarda o numero da carta nao necessariamente representando seu valor
    int _numero;

    //guarda o naipe da carta
    Suit _naipe;

    //guarda se a carta esta virada para cima(true)
    bool _frente;
};

#endif // CARDMODEL_H

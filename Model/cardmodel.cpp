#include "cardmodel.h"

CardModel::CardModel(int num, Suit np, bool f /* =false */):	//por padrao carta virada para baixo
    _numero{num},_naipe{np},_frente{f}{
}

CardModel::~CardModel() {
}

int CardModel::numero() const {
    return _numero;
}

CardModel::Suit CardModel::naipe() const {
    return _naipe;
}

void CardModel::vira(){
    _frente=!_frente;
}

bool CardModel::mostra() const {
    return _frente;
}

bool CardModel::operator==(const CardModel& c) const {

    if(this->_numero != c._numero) return false;
    if(this->_naipe != c._naipe) return false;
    return true;
}

bool CardModel::operator!=(const CardModel& c) const {

    return !(*this == c);
}

bool CardModel::operator<(const CardModel& c) const {

    if(this->_numero < c._numero) return true;
    return false;
}

bool CardModel::operator>(const CardModel& c) const{

    return !(*this <= c);
}

bool CardModel::operator<=(const CardModel& c) const{

    return (*this == c || *this < c);
}

bool CardModel::operator>=(const CardModel& c) const{

    return !(*this < c);
}

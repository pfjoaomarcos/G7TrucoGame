#include "cardview.h"
#include "ui_cardview.h"

CardView::CardView(CardModel c1)
{
    clicked = c1.mostra();
    verso.load(":/mainview/Resources/back.jpg");

    if(c1.numero() == 0){
        frente.load(":/mainview/Resources/truco.jpg");
    }
    if(c1.numero() == 1){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/A_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/A_Copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/A_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/A_ouros.jpg");
        }
    }
    if(c1.numero() == 2){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/2_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/2_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/2_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/2_ouros.jpg");
        }
    }
    if(c1.numero() == 3){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/3_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/3_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/3_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/3_ouros.jpg");
        }
    }
    if(c1.numero() == 4){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/4_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/4_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/4_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/4_ouros.jpg");
        }
    }
    if(c1.numero()== 5){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/5_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/5_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/5_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/5_ouros.jpg");
        }
    }
    if(c1.numero() == 6){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/6_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/6_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/6_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/6_ouros.jpg");
        }
    }
    if(c1.numero() == 7){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/7_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/7_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/7_paus.jpg");
        }
        else if((int)c1.naipe()== 3){
            frente.load(":/mainview/Resources/7_ouros.jpg");
        }
    }
    if(c1.numero() == 8){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/Q_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/Q_copas.jpg");
        }
        else if((int)c1.naipe()== 2){
            frente.load(":/mainview/Resources/Q_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/Q_ouros.jpg");
        }
    }
    if(c1.numero() == 9){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/J_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/J_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/J_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/J_ouros.jpg");
        }
    }
    if(c1.numero() == 10){
        if((int)c1.naipe() == 0){
            frente.load(":/mainview/Resources/K_espadas.jpg");
        }
        else if((int)c1.naipe() == 1){
            frente.load(":/mainview/Resources/K_copas.jpg");
        }
        else if((int)c1.naipe() == 2){
            frente.load(":/mainview/Resources/K_paus.jpg");
        }
        else if((int)c1.naipe() == 3){
            frente.load(":/mainview/Resources/K_ouros.jpg");
        }
    }

    clickable = false;
    selected = false;
    selectable = false;
    verso = verso.scaled(90,120);
    frente = frente.scaled(90,120);
    setFlag( QGraphicsItem::ItemIsFocusable );
    setAcceptedMouseButtons(Qt::AllButtons);
    setPos(0,0);
}


QRectF CardView::boundingRect() const{
    return QRectF(x(),y(),90,120);
}

void CardView::setClickable(){
    clickable = !clickable;
}

bool CardView::getClickable(){
    return clickable;
}

void CardView::setSelected(bool status){
    selected = status;
}

bool CardView::getSelected(){
    return selected;
}

bool CardView::getClicked(){
    return clicked;
}

void CardView::setSelectable(){
    selectable = !selectable;
}

bool CardView::getSelectable(){
    return selectable;
}

void CardView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!clicked){
        painter->drawPixmap(x(),y(),verso);
    }else{
        painter->drawPixmap(x(),y(),frente);
    }
}


void CardView::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::RightButton && clickable == true){
        clicked = !clicked;
    }
    else if(event->button() == Qt::LeftButton && selectable == true){
        if(getSelected()){
            this->setSelected(false);
            this->setPos(this->x(), this->y() + 30);
        }
        else{
            this->setPos(this->x(), this->y() - 30);
            this->setSelected(true);
        }
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}


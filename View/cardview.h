#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include "../Model/cardmodel.h"

namespace Ui {
class CardView;
}

class CardView : public QGraphicsItem
{
public:
    CardView(CardModel c1);

    QRectF boundingRect() const;

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    void setClickable();
    bool getClickable();
    void setSelectable();
    bool getSelectable();
    void setSelected(bool status);
    bool getSelected();
    bool getClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool clicked;
    bool selected;
    bool clickable;
    bool selectable;
    QPixmap verso;
    QPixmap frente;
};

#endif // CARDVIEW_H

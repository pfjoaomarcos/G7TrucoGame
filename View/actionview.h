#ifndef ACTIONVIEW_H
#define ACTIONVIEW_H

#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <vector>
#include <QApplication>
#include <QGraphicsItem>
#include <QEventLoop>
#include "../Model/cardmodel.h"
#include "cardview.h"

namespace Ui {
class ActionView;
}

class ActionView : public QDialog
{
    Q_OBJECT

public:
    explicit ActionView(QWidget *parent = 0);
    ~ActionView();
    bool getAcao();
    void addMao(std::vector<CardModel> mao1, std::vector<CardModel> mao2, CardModel _vira);

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ActionView *ui;
    QGraphicsScene *scene;
    std::vector<CardView *> _mao1;
    std::vector<CardView *> _mao2;
    QGraphicsTextItem * text2;
    QGraphicsTextItem * text;
    bool aceitar;
};

#endif // ACTIONVIEW_H

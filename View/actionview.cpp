#include "actionview.h"
#include "ui_actionview.h"

ActionView::ActionView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionView)
{
    ui->setupUi(this);
    aceitar = false;
    scene = new QGraphicsScene(this);

    QGraphicsTextItem * text2 = new QGraphicsTextItem();
    QGraphicsTextItem * text = new QGraphicsTextItem();
    QGraphicsTextItem * text3 = new QGraphicsTextItem();
    QFont helvetica("Times",18);
    text->setFont(helvetica);
    text->setPlainText("Sua Mao");
    text->setPos(0,0);

    text2->setFont(helvetica);
    text2->setPlainText("Mao do Parceiro");
    text2->setPos(260,0);

    text3->setFont(helvetica);
    text3->setPlainText("Vira");
    text3->setPos(240,300);

    scene->addItem(text);
    scene->addItem(text2);
    scene->addItem(text3);

    ui->graphicsView->setScene(scene);


}

ActionView::~ActionView()
{
    delete ui;
}

bool ActionView::getAcao(){
    QEventLoop loop;
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),&loop,SLOT(quit()));
    loop.exec();

    return aceitar;
}

void ActionView::addMao(std::vector<CardModel> mao1, std::vector<CardModel> mao2, CardModel _vira){
    if(!_mao1.empty()){
        _mao1.clear();
    }
    if(!_mao2.empty()){
        _mao2.clear();
    }

    for(unsigned int i = 0; i < mao1.size(); i++){
        _mao1.emplace_back(new CardView(mao1[i]));
        _mao1[i]->setPos(0 + i*40, 60);
        scene->addItem(_mao1[i]);
    }
    for(unsigned int i = 0; i < mao2.size();i++){
        _mao2.emplace_back(new CardView(mao2[i]));
        _mao2[i]->setPos(160+ i*40,60);
        scene->addItem(_mao2[i]);
    }

    CardView *virou = new CardView(_vira);
    virou->setPos(120,180);
    scene->addItem(virou);
}

void ActionView::on_pushButton_3_clicked()
{
    aceitar = true;
    hide();
}

void ActionView::on_pushButton_4_clicked()
{
    aceitar = false;
    hide();
}

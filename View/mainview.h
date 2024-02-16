#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsScene>
#include "nicknameview.h"
#include "serverview.h"
#include "gameview.h"
#include "helpview.h"
#include "../Controller/playtrucocontroller.h"
#include "../Controller/rulescontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainView;
}
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    std::vector<std::string> jogadores();
    int numero_jogadores();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    std::vector<std::string> _jogadores;
    int _numero_jogadores;
    Ui::MainView *ui;
    GameView *_jogo;
    QGraphicsScene *scene;
    QGraphicsTextItem *text;
    QGraphicsRectItem *rect;
    QGraphicsPixmapItem *imagem;
    RulesController *rule;
};
#endif // MAINVIEW_H

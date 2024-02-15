#ifndef NICKNAMEVIEW_H
#define NICKNAMEVIEW_H

#include <QDialog>
#include <QString>

namespace Ui {
class NicknameView;
}

class NicknameView : public QDialog
{
    Q_OBJECT

public:
    explicit NicknameView(QWidget *parent = 0);
    ~NicknameView();
    QString nome();
    int numero_jogadores();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NicknameView *ui;
    QString _nome;
    int _jogadores;
};

#endif // NICKNAMEVIEW_H

#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <QDialog>

namespace Ui {
class ServerView;
}

class ServerView : public QDialog
{
    Q_OBJECT

public:
    explicit ServerView(QWidget *parent = 0);
    ~ServerView();
    QString server();
    QString porta();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ServerView *ui;
    QString _server;
    QString _porta;
};

#endif // SERVERVIEW_H

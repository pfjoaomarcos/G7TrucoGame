#ifndef SAVEVIEW_H
#define SAVEVIEW_H

#include <QDialog>
#include "../Controller/savecontroller.h"

namespace Ui {
class SaveView;
}

class SaveView : public QDialog
{
    Q_OBJECT

public:
    explicit SaveView(QWidget *parent = nullptr);
    ~SaveView();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::SaveView *ui;
    SaveController *save;
};

#endif // SAVEVIEW_H

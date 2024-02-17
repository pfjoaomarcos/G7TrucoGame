#include "saveview.h"
#include "ui_saveview.h"

SaveView::SaveView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SaveView)
{
    ui->setupUi(this);
}

SaveView::~SaveView()
{
    delete ui;
}

void SaveView::on_pushButton_clicked()
{
    QApplication::quit();
}

void SaveView::on_pushButton_2_clicked()
{
    save = new SaveController();
    save->SaveGame();
}

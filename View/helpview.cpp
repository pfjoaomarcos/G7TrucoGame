#include "helpview.h"
#include "ui_helpview.h"

HelpView::HelpView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HelpView)
{
    ui->setupUi(this);
}

HelpView::~HelpView()
{
    delete ui;
}

void HelpView::on_pushButton_clicked()
{
    close();
}

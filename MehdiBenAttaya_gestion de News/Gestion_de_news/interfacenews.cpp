#include "interfacenews.h"
#include "ui_interfacenews.h"

InterfaceNews::InterfaceNews(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceNews)
{
    ui->setupUi(this);
}

InterfaceNews::~InterfaceNews()
{
    delete ui;
}

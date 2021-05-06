#include "incluirdvd.h"
#include "ui_incluirdvd.h"
#include <QString>
#include "loja.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString n(ui->nome->text());
    QString p(ui->preco->text());
    QString d(ui->duracao->text());
    emit signIncluirDVD(n,p,d);
}

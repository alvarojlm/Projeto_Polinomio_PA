#include "incluircd.h"
#include "ui_incluircd.h"
#include <QString>
#include "loja.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::on_buttonBox_accepted()
{
    QString n(ui->nome->text());
    QString p(ui->preco->text());
    QString f(ui->faixas->text());
    emit signIncluirCD(n,p,f);
}

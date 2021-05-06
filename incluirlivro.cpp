#include "incluirlivro.h"
#include "ui_incluirlivro.h"
#include <QString>
#include "loja.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::on_buttonBox_accepted()
{
    QString n(ui->nome->text());
    QString p(ui->preco->text());
    QString a(ui->autor->text());
    emit signIncluirLivro(n,p,a);
}

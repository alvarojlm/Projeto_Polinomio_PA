#include "mainloja.h"
#include "ui_mainloja.h"
#include "loja.h"
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"
#include "mainloja.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QtMath>
#include <QTableWidgetItem>
#include <QFile>
#include <QDialogButtonBox>

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    , X()
    , inclLivros(NULL)
    , inclCD(NULL)
    , inclDVD(NULL)
    , total_itens(NULL)
{
    ui->setupUi(this);
    ui->tableLivros->setTabKeyNavigation(false);
    ui->tableCDs->setTabKeyNavigation(false);
    ui->tableDVDs->setTabKeyNavigation(false);

    ui->tableLivros->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableCDs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableDVDs->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableLivros->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableCDs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableDVDs->setSelectionBehavior(QAbstractItemView::SelectRows);

    total_itens =new QLabel(this);

    statusBar()->insertWidget(0, new QLabel("Total de itens:"));
    statusBar()->insertWidget(1, total_itens);

   /* ui->label->setStyleSheet("background:linghtyellow");
    ui->label_2->setStyleSheet("background:linghtgray");
    ui->label_3->setStyleSheet("background:linghtgray");

    ui->tableLivros->setStyleSheet("QHeaderView::select{background-color:linghtgray");
    ui->tableCDs->setStyleSheet("QHeaderView::select{background-color:linghtgray");
    ui->tableDVDs->setStyleSheet("QHeaderView::select{background-color:linghtgray");

    ui->tableLivros->setHorizontalHeaderLabels(QStringList()<<"NOME"<<"PRECO"<<"AUTOR");
    ui->tableCDs->setHorizontalHeaderLabels(QStringList()<<"NOME"<<"PRECO"<<"Nº FAIXAS");
    ui->tableDVDs->setHorizontalHeaderLabels(QStringList()<<"NOME"<<"PRECO"<<"DURACAO");
*/
exibeListaCDs();
exibeListaDVDS();
exibeListaLivros();

 inclLivros=new IncluirLivro(this);
 inclCD=new IncluirCD(this);
 inclDVD=new IncluirDVD(this);


connect(inclLivros, SIGNAL(signIncluirLivro(QString,QString,QString)), this, SLOT(slotIncluirLivro(QString,QString,QString)));
connect(inclCD, SIGNAL(signIncluirCD(QString,Qstring,QString)), this, SLOT(slotIncluirCD(QString,QString,QString)));
connect(inclDVD, SIGNAL(signIncluirDVD(QString,Qstring,QString)), this, SLOT(slotIncluirDVD(QString,QString,QString)));
}

MainLoja::~MainLoja()
{
    delete ui;
}
void MainLoja::exibirTodos(){
    exibeListaCDs();
    exibeListaDVDS();
    exibeListaLivros();
}
void MainLoja::on_tableLivros_cellDoubleClicked(int row)
{
    if(row>0 && unsigned(row)<=X.getNumLivro()){
    X.excluirLivro(row);
    exibeListaLivros();
    }
}

void MainLoja::on_tableCDs_cellDoubleClicked(int row)
{
    if(row>0 && unsigned(row)<=X.getNumCD()){
    X.excluirCD(row);
    exibeListaCDs();
    }
}

void MainLoja::on_tableDVDs_cellDoubleClicked(int row)
{
    if(row>0 && unsigned(row)<=X.getNumDVD()){
    X.excluirDVD(row);
    exibeListaDVDS();
    }
}

void MainLoja::itens(){
    total_itens->setText(QString::number((X.getNumLivro()+X.getNumCD()+X.getNumDVD())));
}

void MainLoja::on_actionLer_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                     "Ler estoque",
                                                     QString(),
                                                     "Texte Files (*.txt);");
     X.ler(fileName.toStdString());
    if(!fileName.isEmpty()){
        QFile file (fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this, tr("Erro"),tr("Não foi possivel abrir o arquivo..."));
                    return;
        }
        X.ler(fileName.toStdString());
        exibirTodos();
        file.close();
    }


}

void MainLoja::on_actionSalvar_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                     "Salvar estoque",
                                                     QString(),
                                                     "Texte Files (*.txt);");
    X.salvar(fileName.toStdString());
    if(!fileName.isEmpty()){
        QFile file (fileName);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, tr("Erro"),tr("Não foi possivel salvar o arquivo..."));
                    return;
        }
        file.close();

}
}

void MainLoja::on_actionSair_triggered(){
QCoreApplication::quit();
}

void MainLoja::on_actionIncluir_Livro_triggered()
{
    inclLivros->show();
}

void MainLoja::on_actionIncluir_CD_triggered()
{
    inclCD->show();
}

void MainLoja::on_actionIncluir_DVD_triggered()
{
    inclDVD->show();
}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor){
    float preco_f=preco.toFloat();
    unsigned preco_u=round(100.0*preco_f);
    Livro L(nome.toStdString(),preco_u,autor.toStdString());
    if(L.getNome()!="" && L.getPreco()>0.0 && L.getAutor()!=""){
        X.incluirLivro(L);
        exibeListaLivros();
    }
    else{
        QMessageBox::critical(this,"Livro invalido",QString ("Nao foi possivel incluir o livro! \nNome: "+nome+"\nPreco: "+preco+"\nAutor: "+autor));
    }
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas){
    float preco_f=preco.toFloat();
    unsigned preco_u=round(100.0*preco_f);
    CD C(nome.toStdString(),preco_u,numfaixas.toUInt());
    if(C.getNome()!="" && C.getPreco()>0.0 && C.getNumFaixas()>0){
        X.incluirCD(C);
        exibeListaCDs();
    }
    else{
        QMessageBox::critical(this,"Livro invalido",QString ("Nao foi possivel incluir o CD! \nNome: "+nome+"\nPreco: "+preco+"\nFaixas: "+numfaixas));
    }
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao){
    float preco_f=preco.toFloat();
    unsigned preco_u=round(100.0*preco_f);
    DVD D(nome.toStdString(),preco_u,duracao.toFloat());
    if(D.getNome()!="" && D.getPreco()>0.0 && D.getDuracao()>0.0){
        X.incluirDVD(D);
        exibeListaDVDS();
    }
    else{
        QMessageBox::critical(this,"Livro invalido",QString ("Nao foi possivel incluir o DVD! \nNome: "+nome+"\nPreco: "+preco+"\nDuracao: "+duracao));
    }

}

void MainLoja::exibeListaLivros()
{
  ui->tableLivros->clearContents();
  ui->tableLivros->setRowCount(X.getNumLivro());
 Livro L;

 for(unsigned i=0;i<X.getNumLivro();i++) {
 L=X.getLivro(i);
     for(int j=0;j<3;j++){
         QTableWidgetItem *prov = new QTableWidgetItem;
         prov->setFlags(Qt::ItemIsEnabled);
     if(j==0){
       prov->setText(QString::fromStdString(L.getNome()));
 }else if(j==1){
       prov->setText(QString::number(L.getPreco()));
}else if(j==2){
       prov->setText(QString::fromStdString(L.getAutor()));
}
      prov->setFlags(Qt::ItemIsEnabled);
      prov->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter );
      ui->tableLivros->setItem(i,j,prov);
}
 }
}

void MainLoja::exibeListaCDs()
{  ui->tableCDs->clearContents();
    ui->tableCDs->setRowCount(X.getNumCD());
    CD C;
    for(unsigned i=0;i<X.getNumCD();i++) {
    C=X.getCD(i);
        for(int j=0;j<3;j++){
            QTableWidgetItem *prov = new QTableWidgetItem;
            prov->setFlags(Qt::ItemIsEnabled);
        if(j==0){
          prov->setText(QString::fromStdString(C.getNome()));
    }else if(j==1){
          prov->setText(QString::number(C.getPreco()));
   }else if(j==2){
          prov->setText(QString::number(C.getNumFaixas()));
   }
         prov->setFlags(Qt::ItemIsEnabled);
         prov->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter );
         ui->tableCDs->setItem(i,j,prov);
   }
    }

}

void MainLoja::exibeListaDVDS()
{  ui->tableDVDs->clearContents();
    ui->tableDVDs->setRowCount(X.getNumDVD());
    DVD D;
    for(unsigned i=0;i<X.getNumDVD();i++) {
    D=X.getDVD(i);
        for(int j=0;j<3;j++){
            QTableWidgetItem *prov = new QTableWidgetItem;
            prov->setFlags(Qt::ItemIsEnabled);
        if(j==0){
          prov->setText(QString::fromStdString(D.getNome()));
    }else if(j==1){
          prov->setText(QString::number(D.getPreco()));
   }else if(j==2){
          prov->setText(QString::number(D.getDuracao()));
   }
         prov->setFlags(Qt::ItemIsEnabled);
         prov->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter );
         ui->tableDVDs->setItem(i,j,prov);
   }
    }
}

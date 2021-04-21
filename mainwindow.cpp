#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clients.h"
#include "commande.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    ui->CIN->setValidator (new QIntValidator(0,99999999, this));
    ui->cinsupp->setValidator (new QIntValidator(0,99999999, this));
    ui->ref->setValidator (new QIntValidator(0,99999999, this));
    ui->refsupp->setValidator (new QIntValidator(0,99999999, this));

    ui->table_clients->setModel(C.afficher());
    ui->table_commande->setModel(C1.afficher());
    }




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    int CIN=ui->CIN->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString adresse=ui->adresse->text();
    QString email=ui->email->text();
    int num=ui->num->text().toInt();


    clients C(CIN, nom, prenom, adresse, email, num);
    bool test=C.ajouter();
    QMessageBox msgBox;
    if(test)
  {
    msgBox.setText("ajout avec succée");
    ui->table_clients->setModel(C.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


/*void MainWindow::on_pushButton_4_clicked()
{
    clients C; C.setCIN(ui->cinsupp->text().toInt());
    bool test=C.supprimer(C.getCIN());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succée");
    ui->table_clients->setModel(C.afficher());}
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}*/

void MainWindow::on_pushButton_clicked()
{
    int qte=ui->qte->text().toInt();
    int ref=ui->ref->text().toInt();
    int montant=ui->montant->text().toInt();
    int PrixUnit =ui->prixUnitaire->text().toInt();
    QString designation=ui->designation->text();


    commande C1(designation, qte, ref, montant, PrixUnit);
    bool test=C1.ajouter_commande();
    QMessageBox msgBox;
    if(test)
      {
      msgBox.setText("ajout avec succée");
      ui->table_commande->setModel(C1.afficher());
    }

    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();
}


void MainWindow::on_pushButton_5_clicked()
{
    commande C1; C1.set_ref(ui->refsupp->text().toInt());
    bool test=C1.supprimer_commande(C1.get_ref());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succée");
    ui->table_commande->setModel(C1.afficher());}
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    clients C; C.setCIN(ui->cinsupp->text().toInt());
    bool test=C.supprimer(C.getCIN());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succée");
    ui->table_clients->setModel(C.afficher());}
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}


void MainWindow::on_pushButton_11_clicked()
{
    clients C;
    QSqlQuery query;
    int cin=ui->cinmodif->text().toInt();
    QString cin_string=QString::number(cin);
   if(C.recherche_cin(cin))
   {
       query.prepare("SELECT * FROM CLIENTS WHERE cin like :cin");
       query.bindValue(0,cin_string);
       query.exec();
       while(query.next())
    {
       ui->nommodif->setText(query.value(1).toString());
       ui->prenommodif->setText(query.value(2).toString());
       ui->adressemodif->setText(query.value(3).toString());
       ui->emailmodif->setText(query.value(4).toString());
       ui->nummodif->setText(query.value(5).toString());

    }
   }
}

void MainWindow::on_pushButton_3_clicked()
{
    clients C;
    QMessageBox msg;
    C.setCIN(ui->cinmodif->text().toInt());
    C.setNom(ui->nommodif->text());
    C.setPrenom(ui->prenommodif->text());
    C.setAdresse(ui->adressemodif->text());
    C.setEmail(ui->emailmodif->text());
    C.setNum(ui->nummodif->text().toInt());

    bool test=C.modifier(C.getCIN());
    if(test)
    {
        msg.setText("modification avec succès");
        ui->table_clients->setModel(C.afficher());
    }
    else
        msg.setText("echec de modification");

    msg.exec();
}

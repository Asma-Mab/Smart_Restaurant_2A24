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

 void MainWindow::on_pushButton_3_clicked()
 {
     if((ui->nommodif->text() != "") &&(ui->prenommodif->text() != "") &&(ui->adressemodif->text() != "") &&(ui->emailmodif->text() != "") &&(ui->nummodif->text() != ""))
     {
         if(C.modifier(ui->comboBox->currentText().toInt(),ui->nummodif->text().toInt(),ui->nommodif->text(),ui->prenommodif->text(),ui->adressemodif->text(),ui->emailmodif->text()))
         {
             //refresh tableau
             ui->table_clients->setModel(C.afficher());}

             //message
             QMessageBox::information(this, QObject::tr("Modifier un client"),
                         QObject::tr("client Modifier.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else
         {
             QMessageBox::critical(this, QObject::tr("client une reservation"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }


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

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    {
        QSqlQuery query;

        QString CIN = ui->comboBox->currentText();

        query =C.request(CIN);
        if(query.exec())
        {
            while(query.next())
            {
                ui->nommodif->setText(query.value(2).toString());
                ui->prenommodif->setText(query.value(3).toString());
                ui->adressemodif->setText(query.value(4).toString());
                ui->emailmodif->setText(query.value(5).toString());
                ui->nummodif->setText(query.value(6).toString());


            }
        }

    }
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
    {
        {
            QSqlQuery query;

            QString ref = ui->comboBox_2->currentText();

            query =C1.request(ref);
            if(query.exec())
            {
                while(query.next())
                {
                    ui->designationmodif->setText(query.value(1).toString());
                    ui->PrixUnitmodif->setText(query.value(4).toString());
                    ui->montantmodif->setText(query.value(5).toString());


                }
            }

        }
    }


void MainWindow::on_pushButton_6_clicked()
{
    if((ui->designationmodif->text() != "") &&(ui->PrixUnitmodif->text() != "") &&(ui->montantmodif->text() != ""))
    {
        if(C1.modifier(ui->PrixUnitmodif->text().toInt(),ui->montantmodif->text().toInt(),ui->quantitemodif->text().toInt(),ui->comboBox_2->currentText().toInt(),ui->designationmodif->text()))
        {
            //refresh tableau
            ui->table_commande->setModel(C1.afficher());}

            //message
            QMessageBox::information(this, QObject::tr("Modifier une commande"),
                        QObject::tr("commande Modifier.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier une commande"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }


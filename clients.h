#ifndef CLIENTS_H
#define CLIENTS_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class clients;
}
class clients
{
    QString nom, prenom, adresse, email;
    int cin, num;

     public:
            clients();
            clients(int,int,QString,QString,QString,QString);
            int getcin();
            int getnum();
            QString getnom();
            QString getprenom();
            QString getadresse();
            QString getemail();



            void setcin(int cin);
            void setnum(int num);
            void setnom(QString nom);
            void setprenom(QString prenom);
            void setadresse(QString adresse);
            void setemail(QString email);



            bool ajouter();
            QSqlQueryModel* afficher();
            QSqlQueryModel* afficher_cin(int);
            QSqlQueryModel* afficher_nom(QString);
            QSqlQueryModel* afficher_num(int);
            bool modifier(int);
            bool recherche_nom(QString);
            bool recherche_num(int);
            bool recherche_cin(int);
            bool supprimer(int);
      };






/*{  QString nom, prenom, adresse, email;
    int CIN, num;
public:

    clients(){}
    clients(int, QString, QString, QString , QString, int );



    QString getAdresse(){return adresse;}
    QString getEmail(){return email;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getCIN(){return CIN;}
    int getNum(){return num;}

    void setAdresse(QString adresse){adresse=adresse;}
    void setNom(QString nom){nom=nom;}
    void setPrenom(QString prenom){prenom=prenom;}
    void setEmail(QString email){email=email;}
    void setCIN(int CIN){CIN=CIN;}
    void setNum(int num){num=num;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int);
    bool supprimer(int);

    bool recherche_nom(QString);
    bool recherche_num(int);
    bool recherche_cin(int);

    QSqlQueryModel * trie_az();
    QSqlQueryModel * trie_CIN();
    QSqlQueryModel * trie_num();
    QSqlQuery request(QString);

    QSqlQueryModel* afficher_cin(int);

};*/

#endif // CLIENTS_H

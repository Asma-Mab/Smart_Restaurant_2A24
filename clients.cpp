#include "clients.h"

clients::clients(int CIN, QString adresse, QString nom, QString prenom, QString email, int num)
{
     this->CIN=CIN;
     this->num=num;
     this->adresse=adresse;
     this->nom=nom;
     this->prenom=prenom;
     this->email;
}

bool clients::ajouter()
{
    QSqlQuery query;
       QString res=QString::number(CIN);

       query.prepare("INSERT INTO CLIENTS (CIN,nom,prenom,adresse,email,num) VALUES (:CIN,:nom,:prenom,:adresse,:email,:num)");
              query.bindValue(":CIN",res);
              query.bindValue(":nom",nom);
              query.bindValue(":prenom",prenom);
              query.bindValue(":adresse", adresse);
              query.bindValue(":email", email);
              query.bindValue(":num", num);

             return query.exec();

}


QSqlQueryModel * clients::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT * FROM CLIENTS");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("numero"));

     return  model;
}

bool clients::modifier (int CIN, int num, QString nom, QString prenom , QString adresse, QString email)
{

    QSqlQuery query;
    QString res= QString::number(CIN);
    QString res5= QString::number(num);

    query.prepare("UPDATE clients SET nom=:nom,prenom=:prenom,adresse=:adresse,num=:num WHERE CIN =:res");
    query.bindValue(":CIN",res);
    query.bindValue(":prenom",nom);
    query.bindValue(":nom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":email",email);
    query.bindValue(":num",res5);

    return query.exec();



}



bool clients::supprimer(int CIN)

    {
    QSqlQuery query;
    QString res = QString::number(CIN);
    query.prepare("Delete from CLIENTS where CIN= :CIN");
    query.bindValue(":CIN",res);
    return query.exec();
    }




QSqlQueryModel * clients::trie_az()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients order by nom asc");
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("num"));
return model;
}



QSqlQueryModel * clients::trie_CIN()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients order by CIN desc");
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("num"));
return model;
}



QSqlQueryModel * clients::trie_num()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients order by num desc");
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("num"));
return model;
}
QSqlQueryModel * clients::rechercher(QString res)
{

QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from clients where ref ='"+res+"'");
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("num"));
return model;
}

int clients::calcul_client(int min, int max)
{
    QSqlQuery query;
    query.prepare("select *from CLIENTS where CIN between :min and :max");
    query.bindValue(":min",min);
    query.bindValue(":max",max);
    query.exec();

    int total=0;
    while(query.next()){
        total++;
    }
    return total;
}

//******REMPLIR COMBO BOX

QSqlQueryModel * clients::remplircomboreser()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT CIN from CLIENTS");
    query.exec();
    mod->setQuery(query);
    return mod;
}
QSqlQuery clients::request(QString CIN)
{
    QSqlQuery query;

    query.prepare("select * from CLIENTS where CIN= '"+CIN+"'");
    query.addBindValue(CIN);
    query.exec();
    return query;
}


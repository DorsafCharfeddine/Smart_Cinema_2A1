#include "billet.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QDebug>
#include <QSqlQueryModel>
#include<QLineEdit>
#include<QString>
//#include "ui_mainwindow.h"

billet::billet()
{

}
billet::billet( QString reference,QString categorie,int prix)
{
    this->reference=reference;
    this->categorie=categorie;
    this->prix=prix;
}

bool billet:: ajouter()
{
    QString num_prix=QString::number(prix);

       QSqlQuery query;
             query.prepare("INSERT INTO billet (reference,categorie,prix) "
                           "VALUES (:id, :forename, :surname)");

             query.bindValue(":id",reference);
             query.bindValue(":forename",categorie);
             query.bindValue(":surname", num_prix);
              return query.exec();
}

QSqlQueryModel * billet:: afficher()
{


    QSqlQueryModel *model = new QSqlQueryModel;
              model->setQuery("SELECT * FROM billet");
        return model;

}

bool billet::modifier(QString reference ,QString categorie ,int prix)
{

    QSqlQuery query;

       QString prix_string= QString::number(prix);

       query.prepare("UPDATE billet SET  categorie = :categorie,prix= :prix  WHERE reference = :reference ");
       query.bindValue(":reference", reference);
       query.bindValue(":categorie", categorie);
       query.bindValue(":prix", prix_string);

       return  query.exec();


}
bool billet :: supprimer(QString reference)
{

    QSqlQuery query;
            query.prepare("delete from billet where reference= :reference");
            query.bindValue(":reference", reference);

             return query.exec();
}

QSqlQueryModel * billet::rechercher(QString reference)
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model-> setQuery("SELECT * FROM billet where reference = "+reference);


       return model;

}

QSqlQueryModel * billet::tridesc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from billet order by reference");

    return model;
}

QString billet:: apercu_pdf()
 {
     QString text="             ************ Les billets **********       \n \n " ;
     QSqlQuery query ;
     QString i,x,z;

      query.exec("select * from billet ");
      while (query.next())
      {
         i=query.value(0).toString();
          x=query.value(1).toString();
          z=query.value(2).toString();

        text += "\n reference: "+i+"\n\n - categorie : "+ x+"\n  - - prix : "+z+"\n-____________\n";
     }
return text ;
 }




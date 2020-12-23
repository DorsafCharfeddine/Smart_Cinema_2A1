#include "pointdevente.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QDebug>
#include <QSqlQueryModel>
#include<QLineEdit>
#include<QString>
#include "ui_mainwindow.h"
pointdevente::pointdevente()
{

}
pointdevente:: pointdevente(QString nom,QString adresse,int tel, QString referenceb)
{
    this->nom=nom;
    this->adresse=adresse;
    this->tel=tel;
    this->referenceb=referenceb;
}


bool pointdevente:: ajouter()
{
    QString string_tel=QString::number(tel);

       QSqlQuery query;
             query.prepare("INSERT INTO point (NOM,ADRESSE,TEL,REFERENCE) "
                           "VALUES (:nom,:adresse,:tel,:ref)");

             query.bindValue(":nom",nom);
             query.bindValue(":adresse",adresse);
             query.bindValue(":tel",string_tel);
             query.bindValue(":ref",referenceb);

              return query.exec();
}
  QSqlQueryModel * pointdevente::  afficher()
  {

      QSqlQueryModel *model = new QSqlQueryModel;
                model->setQuery("SELECT * FROM POINT");
          return model;

  }

  QSqlQueryModel *  pointdevente::recherche(QString referenceb)
  {

      QSqlQueryModel * model= new QSqlQueryModel();
         model-> setQuery("SELECT * FROM POINT where REFERENCE = "+referenceb);


         return model;

  }

  QSqlQueryModel * pointdevente::tridesc()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
  model->setQuery("select * from POINT order by REFERENCE");

      return model;
  }

  bool pointdevente:: modifier(QString nom ,QString adresse,int tel,QString referenceb)
  {
      QSqlQuery query;

         QString tel_string= QString::number(tel);

         query.prepare("UPDATE POINT SET  ADRESSE = :ADRESSE,TEL= :TEL,NOM= :NOM  WHERE REFERENCE = :REFERENCE ");

         query.bindValue(":ADRESSE",adresse);
         query.bindValue(":TEL",tel_string);
          query.bindValue(":NOM",nom);
         query.bindValue(":REFERENCE",referenceb);

         return  query.exec();

  }

  bool pointdevente:: supprimer(QString referenceb)
  {

      QSqlQuery query;
              query.prepare("delete from POINT where REFERENCE= :reference");
              query.bindValue(":reference", referenceb);

               return query.exec();

  }
  QString  pointdevente::apercu_pdf()
  {

      QString text="             ************ Les point de ventes **********       \n \n " ;
      QSqlQuery query ;
      QString i,x,z,y;

       query.exec("select * from POINT ");
       while (query.next())
       {
          i=query.value(0).toString();
           x=query.value(1).toString();
           z=query.value(2).toString();
           y=query.value(3).toString();


         text += "\n nom: "+i+"\n\n - adresse : "+ x+"\n  - - tel : "+z+"\n-__ reference :"+y+"\n__________\n";
      }
 return text ;



  }



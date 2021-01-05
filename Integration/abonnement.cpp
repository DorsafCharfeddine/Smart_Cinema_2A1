#include "abonnement.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QDebug>
#include <QSqlQueryModel>
#include<QLineEdit>
#include<QString>
#include<QComboBox>

abonnement::abonnement()
{
numero="";
libelle="";
nb_point="";
id="";
}
abonnement::abonnement(QString numero,QString libelle,QString nb_point ,QString id,QString datea)
{
    this->numero=numero;
    this->libelle=libelle;
    this->nb_point=nb_point;
   this->id=id;
    this->datea=datea;

}
bool abonnement::verifiernum(QString numero )
{

    QSqlQuery query;
       QString n;

               query.exec("SELECT numero from ABONNEMENT ");
               while (query.next())
               {
                   n=query.value("numero").toString();
                   if (n==numero)
                   {
                       return true;
                   }
               }
       return false;

}
 bool abonnement:: verifierid(QString id )
 {



     QSqlQuery query;
        QString n;

                query.exec("SELECT id from ABONNEMENT ");
                while (query.next())
                {
                    n=query.value("id").toString();
                    if (n==id)
                    {
                        return true;
                    }
                }
        return false;


 }
 bool abonnement:: ajouter()
 {

     QSqlQuery query;
           query.prepare("INSERT INTO ABONNEMENT (numero,libelle,nb_point,id,datea) "
                         "VALUES (:numero, :libelle, :nb_point, :id, :datea)");

           query.bindValue(":numero",numero);
           query.bindValue(":libelle",libelle);
           query.bindValue(":nb_point",nb_point);
           query.bindValue(":id",id);
            query.bindValue(":datea",datea);

            return query.exec();
 }
 QSqlQueryModel* abonnement:: afficher()
 {


     QSqlQueryModel *model = new QSqlQueryModel;
               model->setQuery("SELECT * FROM ABONNEMENT left join CLIENT on ABONNEMENT.id=CLIENT.id");
         return model;

 }
 QSqlQueryModel *abonnement:: rechercher(QString numero)
 {

     QSqlQueryModel * model= new QSqlQueryModel();
         model-> setQuery("SELECT * FROM ABONNEMENT where numero = "+numero );


         return model;

 }
 QSqlQueryModel *abonnement::  recherche(QString id)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
         model-> setQuery("SELECT * FROM ABONNEMENT where id = "+id );


         return model;



 }
 QSqlQueryModel *abonnement::  tridesc()
 {

     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from ABONNEMENT order by ID desc ");

         return model;

  }
  QSqlQueryModel *abonnement:: tridasc()
  {
 QSqlQueryModel * model= new QSqlQueryModel();
      model->setQuery("select * from ABONNEMENT order by ID ASC ");

          return model;
  }
   bool abonnement ::supprimer(QString numero)
   {
       QSqlQuery query;


                   query.prepare("delete from ABONNEMENT where numero= :numero");
                   query.bindValue(":numero",numero);

              return query.exec();

   }
   QString abonnement:: apercu_pdf()
   {
       QString text="            ******* Les abonnement  ********       \n \n " ;
       QSqlQuery query ;
       QString i,x,z,n,a;


        query.exec("select * from ABONNEMENT ");
        while (query.next())
        {
           i=query.value(0).toString();
            x=query.value(1).toString();
            z=query.value(2).toString();
            n=query.value(3).toString();
            a=query.value(4).toString();


          text += "\n Numero de l abonnement: "+i+"\n\n - Libelle de labonnement : "+ x+"\n  - - nombre des points de labonnement : "+z+"\n--  ID client:"+n+"\n____ Fate de labonnement :"+a+"\n__________\n";



       }

               return text ;


   }
   bool abonnement::modifier(QString numero,QString libelle,QString nb_point ,QString id,QString datea)
   {

       QSqlQuery query;


          query.prepare("UPDATE ABONNEMENT SET  id = :id, libelle= :libelle,nb_point= :nb_point,DATEA= :datea  WHERE numero= :numero ");
          query.bindValue(":numero",numero);
          query.bindValue(":libelle",libelle);
          query.bindValue(":nb_point",nb_point);
          query.bindValue(":id",id);
          query.bindValue(":datea",datea);

          return  query.exec();

   }


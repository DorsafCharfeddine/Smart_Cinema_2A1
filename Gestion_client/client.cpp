#include "client.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QDebug>
#include <QSqlQueryModel>
#include<QLineEdit>
#include<QString>
#include "ui_mainwindow.h"
#include<QComboBox>

client::client()
{
id="";
nom="";
prenom="";
email="";
}
client::client(QString id,QString nom,QString prenom ,QString email)
{
   this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
}
bool client::verifierId(QString id )
{

    QSqlQuery query;
       QString n;

               query.exec("SELECT id from client ");
               while (query.next())
               {
                   n=query.value("id_p").toString();
                   if (n==id)
                   {
                       return true;
                   }
               }
       return false;

}

bool client:: ajouter()
{


       QSqlQuery query;
             query.prepare("INSERT INTO client (id,nom,prenom,email) "
                           "VALUES (:id, :nom, :prenom, :email)");

             query.bindValue(":id",id);
             query.bindValue(":nom",nom);
             query.bindValue(":prenom",prenom);
             query.bindValue(":email",email);

              return query.exec();


}


QSqlQueryModel* client:: afficher()
{

    QSqlQueryModel *model = new QSqlQueryModel;
              model->setQuery("SELECT * FROM CLIENT");
        return model;

}

 bool client:: modifier(QString id,QString nom,QString prenom,QString email)
 {
     QSqlQuery query;


        query.prepare("UPDATE CLIENT SET  nom = :nom, prenom= :prenom,email= :email  WHERE id= :id ");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":email",email);

        return  query.exec();


 }
 bool client:: supprimer(QString id)
 {


         QSqlQuery query;
               query.prepare("delete from CLIENT where ID= :id");
               query.bindValue(":id",id);

                return query.exec();
 }

 QSqlQueryModel *client:: rechercher(QString id )
{
     QSqlQueryModel * model= new QSqlQueryModel();
         model-> setQuery("SELECT * FROM CLIENT where id = "+id );


         return model;



 }
  QSqlQueryModel * client ::recherche(QString prenom )
  {

      QSqlQueryModel * model= new QSqlQueryModel();
          model-> setQuery("SELECT * FROM CLIENT where PRENOM = "+prenom);


          return model;

  }
  QSqlQueryModel * client::tridesc()
  {

      QSqlQueryModel * model= new QSqlQueryModel();
      model->setQuery("select * from CLIENT order by ID desc ");

          return model;

  }

  QSqlQueryModel * client:: tridasc()
  {

      QSqlQueryModel * model= new QSqlQueryModel();
      model->setQuery("select * from CLIENT order by ID ASC ");

          return model;


  }

QString client::  apercu_pdf()
{

    QString text="            ******* Les CLIENT  ********       \n \n " ;
    QSqlQuery query ;
    QString i,x,z,n;


     query.exec("select * from CLIENT ");
     while (query.next())
     {
        i=query.value(0).toString();
         x=query.value(1).toString();
         z=query.value(2).toString();
         n=query.value(3).toString();

       text += "\n ID client: "+i+"\n\n - Nom client : "+ x+"\n  - - Prenom client : "+z+"\n--  Email client:"+n+"\n______________\n";



    }

            return text ;
}



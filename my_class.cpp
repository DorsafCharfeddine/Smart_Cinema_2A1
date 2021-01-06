#include "my_class.h"

my_class::my_class()
{

}



my_class::my_class(int nb,QString n ,QString nu,QString t ,QString d  ){
    nombre=nb;
    nom=n;
    num=nu;
    text=t;
    date=d;

}


bool my_class::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO RES (NBR_TICKET, NOM_RESERVATION,NUM_RESERVATION,TEXT,DATE_RESERVATION) "
                        "VALUES (:nb,:s1,:s2,:s3,:s4)");
    query.bindValue(":nb", nombre);
    query.bindValue(":s1",nom); //remplir la valeur d'une maniere securisée
    query.bindValue(":s2", num);
    query.bindValue(":s3", text);
    query.bindValue(":s4", date);


    return    query.exec();

}

bool my_class::modifier(int selected){

    QSqlQuery query;


    query.prepare(" UPDATE RES SET NOM_RESERVATION= :s1 ,NUM_RESERVATION= :s2,TEXT= :s3 ,DATE_RESERVATION= :s4 "
                  " where NBR_TICKET= :nb");
    query.bindValue(":nb", selected);
    query.bindValue(":s1",nom); //remplir la valeur d'une maniere securisée
    query.bindValue(":s2", num);
    query.bindValue(":s3", text);
    query.bindValue(":s4", date);

    return    query.exec();

}

 QSqlQueryModel * my_class::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM RES");

     return modal;

 }
  bool my_class::supprimer(int selected)
  {

      QSqlQuery query;
      query.prepare("Delete from RES where NBR_TICKET = :sel ");
      query.bindValue(":sel", selected);
      return    query.exec();


  }

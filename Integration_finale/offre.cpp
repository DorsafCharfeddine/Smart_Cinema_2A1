#include "offre.h"

offre::offre()
{

}




offre::offre(QString s1 ,QString s2,QString s3 ,QString s4  ){
    combo=s1;
    line=s2;
    text=s3;
    date=s4;

}
bool offre::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO TABLE1 (NOM_OFFRE, TYPE,DELAI,COMMENT_) "
                        "VALUES ( :line,:combo,:date,:text)");
    //remplir la valeur d'une maniere securisée
    query.bindValue(":combo", combo);
    query.bindValue(":line", line);
    query.bindValue(":text", text);
    query.bindValue(":date", date);

    return    query.exec();

}

bool offre::modifier(QString selected){

    QSqlQuery query;


    query.prepare(" UPDATE TABLE1  SET  ,TYPE= :combo,COMMENT_= :text ,DELAI= :date "
                  " where NOM_OFFRE= :line");
   query.bindValue(":line", selected);
    //remplir la valeur d'une maniere securisée
    query.bindValue(":combo", combo);
    //query.bindValue(":line", line);
    query.bindValue(":text", text);
    query.bindValue(":date", date);


    return    query.exec();

}

 QSqlQueryModel * offre::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM TABLE1");

     return modal;

 }
  bool offre::supprimer(QString selected){

      QSqlQuery query;
      query.prepare("Delete from TABLE1 where NOM_OFFRE = :sel ");
      query.bindValue(":sel", selected);
      return    query.exec();


  }

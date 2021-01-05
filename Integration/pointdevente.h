#ifndef POINTDEVENTE_H
#define POINTDEVENTE_H
#include<QSqlQueryModel>
#include<QString>

class pointdevente
{
public:
    pointdevente();
    pointdevente(QString,QString,int,QString);
    bool  ajouter();
      QSqlQueryModel *  afficher();
      QSqlQueryModel * recherche(QString);
      QSqlQueryModel *tridesc();
      bool modifier(QString ,QString ,int,QString);
      bool  supprimer(QString);
      QString apercu_pdf();
private:
    QString nom;
    QString adresse;
    int tel;
     QString referenceb;
};

#endif // POINTDEVENTE_H

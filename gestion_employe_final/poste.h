#ifndef POSTE_H
#define POSTE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>


class poste
{
    QString NOM;
    int ID;
    int NBRH;
    int SALAIRE;
public:
    //constructeur
    poste();
    poste(QString n,int i,int nbrh, int s):NOM(n),ID(i),NBRH(nbrh),SALAIRE(s){}

    //getters
    QString get_NOM(){return NOM;}
    int get_ID(){return ID;}
    int get_NBRH(){return NBRH;}
    int get_SALAIRE(){return SALAIRE;}

    //setters
    void set_NOM(QString n){NOM=n;}
    void set_ID(int i)     {ID=i;}
    void set_NBRH(int nbrh){NBRH=nbrh;}
    void set_SALAIRE(int s){SALAIRE=s;}

    //fonctions realtifs
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString NOM);
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel *tri();
};

#endif // POSTE_H

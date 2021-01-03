#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>


class Employe
{
    QString NOM;
    QString PRENOM ;

    int CIN;
    int POSTE;
     QString MAIL;
public:
    //constructeur
    Employe();
    Employe(QString n,QString p,int c,int po,QString m):NOM(n),PRENOM(p),CIN(c),POSTE(po),MAIL(m){}

    //getters
    QString get_NOM(){return NOM;}
    QString get_PRENOM(){return PRENOM;}
    int get_CIN(){return CIN;}
    int get_POSTE(){return POSTE;}
    QString get_MAIL(){return MAIL;}


    //setters
    void set_NOM(QString n){NOM=n;}
    void set_PRENOM(QString p){PRENOM=p;}
    void set_CIN(int c){CIN=c;}
    void set_POSTE(int po){POSTE=po;}
    void set_MAIL(QString m){MAIL=m;}


    //fonctions realtifs
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString NOM);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel *tri();
};

#endif // EMPLOYE_H

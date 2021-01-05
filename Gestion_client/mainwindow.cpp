#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QDate>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableView>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include<QString>
//#include<QMediaPlayer>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QComboBox>
#include "abonnement.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabclient->setModel(c_temp.afficher());
     ui->tababo->setModel(a_temp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajoutcl_clicked()
{
    QString id=ui->id_aj->text();
     QString nom=ui->nom_aj->text();
     QString prenom=ui->prenom_aj->text();
     QString email=ui->email_aj->text();


     QString numbers = "123456789";
 bool verifHedhi = false;
   bool verif_id=true;
   bool verifHedhi1= false;
   bool verifHedhi2= false;


    for(int i = 0; i < id.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(id[i] == numbers[j]){
                                          verifHedhi = true;      // test sur id_p numero
                                      }
                }
                if(verifHedhi == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("id il faut que un numero <>0 .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  if (id ==""){
                       verif_id = false;
                       QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("il faut que le numero de dossier different de vide.\n"//test num
                                               "Click Cancel to exit."), QMessageBox::Cancel);
               }
  QString caractere = "azertyuiopqsdfghjklmwxcvbn";

  for(int i = 0; i < nom.length(); i++){
              for(int j = 0; j < caractere.length(); j++){

                  if(nom[i] == caractere[j]){
                                        verifHedhi1 = true;      // test sur id_p numero
                                    }
              }
              if(verifHedhi1 == false ){

                                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("il faut que le nom est alphabetique .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

                                break;
                            }
                        }
  for(int i = 0; i < prenom.length(); i++){
              for(int j = 0; j < caractere.length(); j++){

                  if(prenom[i] == caractere[j]){
                                        verifHedhi2 = true;      // test sur id_p numero
                                    }
              }
              if(verifHedhi2 == false ){

                                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("il faut que le prenom est alphabetique .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

                                break;
                            }
                        }




     if((verif_id==true)&&(verifHedhi==true)&&(verifHedhi1==true)&&(verifHedhi2==true)){

 client c(id,nom,prenom,email);
     QMessageBox msg;
     bool testt=c.verifierId(id);
             if(testt)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                              QObject::tr(" id client déjà existant !.\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

                }
             else

     {
                 bool test=c.ajouter();
                 if(test){


         ui->tabclient->setModel(c_temp.afficher());
          msg.setText("Ajout avec succes");
     }

         else {
         msg.setText("Echec au niveau de lajout d un client");
     }
     msg.exec();
     }
 }
}

void MainWindow::on_quittercl_clicked()
{
    ui->id_aj->clear();
      ui->nom_aj->clear();//annuler ajout
      ui->prenom_aj->clear();
      ui->email_aj->clear();
}

void MainWindow::on_modifcl_clicked()
{
    QString id=ui->id_aj->text();
     QString nom=ui->nom_aj->text();
     QString prenom=ui->prenom_aj->text();
     QString email=ui->email_aj->text();


     QString numbers = "123456789";
 bool verifHedhi = false;
   bool verif_id=true;
   bool verifHedhi1= false;
   bool verifHedhi2= false;


    for(int i = 0; i < id.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(id[i] == numbers[j]){
                                          verifHedhi = true;      // test sur id_p numero
                                      }
                }
                if(verifHedhi == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("id il faut que un numero <>0 .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  if (id ==""){
                       verif_id = false;
                       QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("il faut que le numero de dossier different de vide.\n"//test num
                                               "Click Cancel to exit."), QMessageBox::Cancel);
               }
  QString caractere = "azertyuiopqsdfghjklmwxcvbn";

  for(int i = 0; i < nom.length(); i++){
              for(int j = 0; j < caractere.length(); j++){

                  if(nom[i] == caractere[j]){
                                        verifHedhi1 = true;      // test sur id_p numero
                                    }
              }
              if(verifHedhi1 == false ){

                                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("il faut que le nom est alphabetique .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

                                break;
                            }
                        }
  for(int i = 0; i < prenom.length(); i++){
              for(int j = 0; j < caractere.length(); j++){

                  if(prenom[i] == caractere[j]){
                                        verifHedhi2 = true;      // test sur id_p numero
                                    }
              }
              if(verifHedhi2 == false ){

                                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("il faut que le prenom est alphabetique .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

                                break;
                            }
                        }




     if((verif_id==true)&&(verifHedhi==true)&&(verifHedhi1==true)&&(verifHedhi2==true)){

 client c(id,nom,prenom,email);
     QMessageBox msg;
     bool testt=c.verifierId(id);
             if(testt)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                              QObject::tr(" id client déjà existant !.\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

                }
             else

     {
                 bool test=c.modifier(id,nom,prenom,email);
                 if(test){


         ui->tabclient->setModel(c_temp.afficher());
          msg.setText("modification avec succes");
     }

         else {
         msg.setText("Echec au niveau de modification d un client");
     }
     msg.exec();
     }
 }

}

void MainWindow::on_suppcl_clicked()
{
    client c;

         QString id= ui->combosup_cl->currentText();

         bool test=c_temp.supprimer(id);
         QMessageBox msg;
         if(test)
         {

             msg.setText("suppression avec succes");
    ui->tabclient->setModel(c_temp.afficher());

         }

             else {
             msg.setText("Echec au niveau de la suppression d un client");
         }
         msg.exec();

    }
//}

void MainWindow::on_pushButton_clicked()
{
    QString id = ui->id_rech->text();

        ui->tabclient->setModel(c_temp.rechercher(id));

}

void MainWindow::on_pushButton_2_clicked()
{
    QString prenom=ui->nom_rech->text();

        ui->tabclient->setModel(c_temp.recherche(prenom));

}

void MainWindow::on_trie_desc_clicked()
{
    ui->tabclient->setModel(c_temp.tridesc());
}

void MainWindow::on_trie_asc_clicked()
{
     ui->tabclient->setModel(c_temp.tridasc());
}

void MainWindow::on_imprimercl_clicked()
{
    client c;
           QString text=c.apercu_pdf();
           ui->impcc->setText(text);

           QPrinter printer ;
           printer.setPrinterName("imprim");
           QPrintDialog dialog (&printer,this);
           if(dialog.exec()==QDialog::Rejected) return ;
           ui->impcc->print(&printer);
}



void MainWindow::on_quitter_af_clicked()
{
     ui->id_rech->clear();
      ui->nom_rech->clear();
}

void MainWindow::on_refrech_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("select ID from CLIENT");
        qry->exec();
        model->setQuery(*qry);
        ui->combosup_cl->setModel(model);
}

void MainWindow::on_ajouterabo_clicked()
{
    QString numero=ui->numab->text();
     QString libelle=ui->libab->text();
     QString nb_point=ui->nbrab->text();
       QString id= ui->comboBoxab->currentText();
       QString datea=ui->datea->date().toString();



     QString numbers = "123456789";
 bool verifHedhi = false;
   bool verif_numero=true;
   bool verifHedhi1= false;
 bool verif_nb_point=true;


    for(int i = 0; i < numero.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(numero[i] == numbers[j]){
                                          verifHedhi = true;      // test sur id_p numero
                                      }
                }
                if(verifHedhi == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("id il faut que le numero de labo est un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  if ((numero =="0")||(numero =="")){
                       verif_numero = false;
                       QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("il faut que le numero de labo different de vide et dif de 0.\n"//test num
                                               "Click Cancel to exit."), QMessageBox::Cancel);
               }



  for(int i = 0; i < nb_point.length(); i++){
              for(int j = 0; j < numbers.length(); j++){

                  if(nb_point[i] == numbers[j]){
                                        verifHedhi1 = true;      // test sur id_p numero
                                    }
              }
              if(verifHedhi1 == false ){

                                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("id il faut que le nombre des points  de labo est un numero .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

                                break;
                            }
                        }
if ((nb_point =="0")||(nb_point =="")){
                     verif_nb_point= false;
                     QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("il faut que le nombre des points different de vide et dif de 0.\n"//test num
                                             "Click Cancel to exit."), QMessageBox::Cancel);
             }






     if((verif_numero==true)&&(verifHedhi==true)&&( verif_nb_point==true)&&(verifHedhi1==true)){

 abonnement a(numero,libelle,nb_point,id,datea);
     QMessageBox msg;
     bool testt=a.verifiernum(numero);
             if(testt)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                              QObject::tr(" numero abo déjà existant !.\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

                }
             else

     {
                 bool test=a.ajouter();
                 if(test){


        ui->tababo->setModel(a_temp.afficher());
          msg.setText("Ajout avec succes");
     }

         else {
         msg.setText("Echec au niveau de lajout d un abonnement");
     }
     msg.exec();
     }
 }

}

void MainWindow::on_refrechabo_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("select ID from CLIENT");
        qry->exec();
        model->setQuery(*qry);
        ui->comboBoxab->setModel(model);
}

void MainWindow::on_rech_num_clicked()
{
    QString numero = ui->num_rech->text();

        ui->tababo->setModel(a_temp.rechercher(numero));
}

void MainWindow::on_rech_id_clicked()
{
    QString id = ui->id_rechab->text();

        ui->tababo->setModel(a_temp.recherche(id));

}

void MainWindow::on_quitterab_clicked()
{
    ui->num_rech->clear();
     ui->id_rechab->clear();
}

void MainWindow::on_quitterabo_clicked()
{
    ui->numab->clear();
     ui->libab->clear();
     ui->nbrab->clear();

}

void MainWindow::on_trie_asc_ab_clicked()
{
     ui->tababo->setModel(a_temp.tridasc());
}

void MainWindow::on_trie_desc_abo_clicked()
{
     ui->tababo->setModel(a_temp.tridesc());
}

void MainWindow::on_sup_abo_clicked()
{
    abonnement a;

         QString numero=ui->comboBoxsupprimer->currentText();

         bool test=a_temp.supprimer(numero);
         QMessageBox msg;
         if(test)
         {

             msg.setText("suppression avec succes");
    ui->tababo->setModel(a_temp.afficher());

         }

             else {
             msg.setText("Echec au niveau de la suppression d un abonnement");
         }
         msg.exec();

}




void MainWindow::on_pushButton_sup_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("select numero from ABONNEMENT");
        qry->exec();
        model->setQuery(*qry);
        ui->comboBoxsupprimer->setModel(model);

}

void MainWindow::on_imprimercl_2_clicked()
{
    abonnement a;
           QString text=a.apercu_pdf();
           ui->impcc_2->setText(text);

           QPrinter printer ;
           printer.setPrinterName("imprim");
           QPrintDialog dialog (&printer,this);
           if(dialog.exec()==QDialog::Rejected) return ;
           ui->impcc_2->print(&printer);

}

void MainWindow::on_modifierabo_clicked()
{
    QString numero=ui->numab->text();
     QString libelle=ui->libab->text();
     QString nb_point=ui->nbrab->text();
       QString id= ui->comboBoxab->currentText();

 QString datea=ui->datea->date().toString();

     QString numbers = "123456789";
 bool verifHedhi = false;
   bool verif_numero=true;
   bool verifHedhi1= false;
 bool verif_nb_point=true;


    for(int i = 0; i < numero.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(numero[i] == numbers[j]){
                                          verifHedhi = true;      // test sur id_p numero
                                      }
                }
                if(verifHedhi == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("id il faut que le numero de labo est un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  if ((numero =="0")||(numero =="")){
                       verif_numero = false;
                       QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                   QObject::tr("il faut que le numero de labo different de vide et dif de 0.\n"//test num
                                               "Click Cancel to exit."), QMessageBox::Cancel);
               }



  for(int i = 0; i < nb_point.length(); i++){
              for(int j = 0; j < numbers.length(); j++){

                  if(nb_point[i] == numbers[j]){
                                        verifHedhi1 = true;      // test sur id_p numero
                                    }
              }
              if(verifHedhi1 == false ){

                                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("id il faut que le nombre des points  de labo est un numero .\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

                                break;
                            }
                        }
if ((nb_point =="0")||(nb_point =="")){
                     verif_nb_point= false;
                     QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                 QObject::tr("il faut que le nombre des points different de vide et dif de 0.\n"//test num
                                             "Click Cancel to exit."), QMessageBox::Cancel);
             }






     if((verif_numero==true)&&(verifHedhi==true)&&( verif_nb_point==true)&&(verifHedhi1==true)){

 abonnement a(numero,libelle,nb_point,id,datea);
     QMessageBox msg;
     /*bool testt=a.verifierid(id);
             if(testt)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                              QObject::tr(" numero abo déjà existant !.\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

                }*/



                 bool test=a.modifier(numero,libelle,nb_point,id,datea);
                 if(test){


        ui->tababo->setModel(a_temp.afficher());
          msg.setText("Modification avec succes");
     }

         else {
         msg.setText("Echec au niveau de Modification d un abonnement");
     }
     msg.exec();
     }
 }




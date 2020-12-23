#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "billet.h"
#include <QDate>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableView>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include<QString>
#include"pointdevente.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabbillet->setModel(b_temp.afficher());
        ui->tabpoint->setModel(p_temp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_billet_clicked()
{
        QString reference=ui->ref_aj->text();
        QString categorie=ui->cat_aj->text();
        int prix=ui->prix_aj->text().toInt();

        billet b(reference,categorie,prix);
            QMessageBox msg;

            bool test=b.ajouter();
                            if(test){


                    ui->tabbillet->setModel(b_temp.afficher());
                     msg.setText("Ajout avec succes");
                }

                    else {
                    msg.setText("Echec au niveau de lajout d un billets");
                }
                msg.exec();
}




void MainWindow::on_modifier_billet_clicked()
{
    QString reference=ui->ref_aj->text();
    QString categorie=ui->cat_aj->text();
    int prix=ui->prix_aj->text().toInt();

    billet b(reference,categorie,prix);
      QMessageBox msg;
      bool test=b.modifier(reference,categorie,prix);
       if(test)
          {
              ui->ref_aj->clear();
              ui->cat_aj->clear();
              ui->prix_aj->clear();
              ui->tabbillet->setModel(b_temp.afficher());

              msg.setText("modification avec succes");


          }

              else {
              msg.setText("Echec au niveau de la modification d un billet");
          }
          msg.exec();

      }




void MainWindow::on_supprimer_billet_clicked()
{
billet b;
 QString reference=ui->ref_supp->text();
 bool test=b_temp.supprimer(reference);
      QMessageBox msg;
      if(test)
      {

          msg.setText("suppression avec succes");
          ui->tabbillet->setModel(b_temp.afficher());

      }

          else {
          msg.setText("Echec au niveau de la suppression d une billet");
      }
      msg.exec();

 }


void MainWindow::on_rech_billet_clicked()
{
    QString reference = ui->ref_cher->text();

       ui->tabbillet->setModel(b_temp.rechercher(reference));
}

void MainWindow::on_triee_billet_clicked()
{
    ui->tabbillet->setModel(b_temp.tridesc());
}



void MainWindow::on_imprimer_billet_clicked()
{
    billet b;
             QString text=b.apercu_pdf();
             ui->imprimmmmmer->setText(text);

             QPrinter printer ;
             printer.setPrinterName("imprim");
             QPrintDialog dialog (&printer,this);
             if(dialog.exec()==QDialog::Rejected) return ;
             ui->imprimmmmmer->print(&printer);
}



void MainWindow::on_ajouter_pointdevente_clicked()
{
    QString nom=ui->nommm_p->text();
    QString adresse=ui->adrrr_p->text();
    int tel=ui->telll_p->text().toInt();
     QString referenceb=ui->refff_p->text();

     pointdevente p(nom,adresse,tel,referenceb);
        QMessageBox msg;

        bool test=p.ajouter();
                        if(test){


               ui->tabpoint->setModel(p_temp.afficher());
                 msg.setText("Ajout avec succes");
            }

                else {
                msg.setText("Echec au niveau de lajout d un point de vente");
            }
            msg.exec();
}

void MainWindow::on_rech_p_clicked()
{
    QString referenceb = ui->ref_cher_p->text();

       ui->tabpoint->setModel(p_temp.recherche(referenceb));
}

void MainWindow::on_trie_p_clicked()
{
     ui->tabpoint->setModel(p_temp.tridesc());
}

void MainWindow::on_modif_point_clicked()
{
    QString reference=ui->refff_p->text();
     QString adresse=ui->adrrr_p->text();
     int tel=ui->telll_p->text().toInt();
    QString nom=ui->nommm_p->text();




    pointdevente p(reference,adresse,tel,nom);
      QMessageBox msg;
      bool test=p.modifier(reference,adresse,tel,nom);
       if(test)
          {
              ui->refff_p->clear();
              ui->nommm_p->clear();
              ui->adrrr_p->clear();
              ui->telll_p->clear();

              ui->tabpoint->setModel(p_temp.afficher());

              msg.setText("modification avec succes");


          }

              else {
              msg.setText("Echec au niveau de la modification d un point de vente");
          }
          msg.exec();


}

void MainWindow::on_pushButton_clicked()
{
pointdevente p;
QString reference=ui->ref_suprimerrr->text();
     bool test=p_temp.supprimer(reference);
          QMessageBox msg;
          if(test)
          {

              msg.setText("suppression avec succes");

                 ui->tabpoint->setModel(p_temp.afficher());

          }

              else {
              msg.setText("Echec au niveau de la suppression d un point de vente");
          }
          msg.exec();
}

void MainWindow::on_imprimer_p_clicked()
{
    pointdevente p;
             QString text=p.apercu_pdf();
             ui->imppppr->setText(text);

             QPrinter printer ;
             printer.setPrinterName("imprim");
             QPrintDialog dialog (&printer,this);
             if(dialog.exec()==QDialog::Rejected) return ;
             ui->imppppr->print(&printer);

}

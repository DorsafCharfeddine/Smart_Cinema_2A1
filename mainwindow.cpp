#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "film.h"
#include "projection.h"
#include <QMessageBox>
#include <QDate>
#include <QString>
#include <QDateEdit>
#include <QModelIndex>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QPropertyAnimation>
#include <QPrintDialog>
#include <QTextStream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_id->setMaxLength(8);
    ui->lineEdit_duree->setMaxLength(3);
    ui->dateEdit_ds->setMinimumDate(QDate::currentDate().addDays(-45000));
    ui->dateEdit_ds->setMaximumDate(QDate::currentDate().addDays(2));
    ui->dateEdit_ds->setDisplayFormat("dd.MM.yyyy");
    ui->lineEdit_duree->setMaxLength(4);


    ui->dateTimeEdit_datep->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit_datep->setMaximumDate(QDate::currentDate().addDays(730));
    ui->lineEdit_capacite->setMaxLength(3);
    ui->spinBox_salle->setMaximum(40);
    ui->dateTimeEdit_datep->setDisplayFormat("dd.MM.yyyy hh:mm");


    ui->tableView_films->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_films->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView_projections->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_projections->setSelectionMode(QAbstractItemView::SingleSelection);

   /* QPropertyAnimation *animation = new QPropertyAnimation(ui->ajouter, "geometry");
    animation->setDuration(200);
    animation->setStartValue(ui->ajouter->geometry());
    animation->setEndValue(QRect(200, 200, 100, 50));
    animation->start();*/


    ui->tableView_films->setModel(tmpFilm.afficher());
    ui->tableView_projections->setModel(tmpProjection.afficher_p());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString genre = ui->comboBox_genre->currentText();
    QString description = ui->textEdit_description->toPlainText();
    QString duree = ui->lineEdit_duree->text();
    QDate date_sortie = ui->dateEdit_ds->date();
    film f(id, nom, genre, description, duree, date_sortie);
    if (id>0 && nom!="" && description!= "" && duree!="")
    {
        bool test = f.ajouter();
        if(test)
        {
            ui->tableView_films->setModel(tmpFilm.afficher());
            QMessageBox::information(nullptr, QObject::tr("Ajout film") ,
                     QObject::tr("Film ajouté avec succès.\n" "Click cancel to exit"), QMessageBox::Cancel);
        }
    }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ajout film") ,
                     QObject::tr("Ajout échoué.\n" "Click cancel to exit"), QMessageBox::Cancel);
        }
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>())
    {
    widget->clear();
    }
}


void MainWindow::on_tableView_films_activated(const QModelIndex &index)
{
    /*QString id = ui->tableView_films->model()->data(index).toString();
    QSqlQuery query;
    query.prepare(" select * from film where id = '"+id+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_id->setText(query.value(0).toString());
            ui->lineEdit_nom->setText(query.value(1).toString());
            ui->comboBox_genre->setText(query.value(2).toString());
            ui->textEdit_description->setText(query.value(3).toString());
            ui->lineEdit_duree->setText(query.value(4).toString());
            ui->dateEdit_ds->setDate(query.value(5));
        }
    }
    ui->tableView_films->setStyleSheet("QTableView { selection-color: black; selection-background-color: black; }");
*/
}



void MainWindow::on_pushButton_update_clicked()
{
    ui->pushButton_update->setDisabled(true);
    ui->pushButton_update->setText("Modifiable");
    QSqlTableModel *tableModel= new QSqlTableModel();
    tableModel->setTable("FILM");
    tableModel->select();
    ui->tableView_films->setModel(tableModel);
}


void MainWindow::on_pushButton_suppFilm_clicked()
{
    QItemSelectionModel *select = ui->tableView_films->selectionModel();

      int id =select->selectedRows(0).value(0).data().toInt();

      if(tmpFilm.supprimer(id))
      {
        ui->tableView_films->setModel(tmpFilm.afficher());
        QMessageBox::information(nullptr, QObject::tr("Suppression film") ,
                     QObject::tr("Film supprimé avec succès.\n" "Click cancel to exit"), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Suppresion film") ,
                     QObject::tr("Suppression échoué.\n" "Click cancel to exit"), QMessageBox::Cancel);
    }
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
}


void MainWindow::on_pushButton_clicked()
{
            int id=ui->lineEdit_rechid->text().toInt();
            QString nom=ui->lineEdit_rechnom->text();
            QDate date_sortie=ui->dateEdit_rech->date();

            QSqlQueryModel *rech=tmpFilm.rechercher_multi(id,nom,date_sortie);
            if(rech)
            {
                ui->tableView_films->setModel(rech);
            }
            else
            {
                ui->tableView_films->setModel(tmpFilm.afficher());

            }

}

void MainWindow::on_pushButton_tri_clicked()
{
    if (ui->checkBox_idTri->isChecked())
    {
        ui->tableView_films->setModel(tmpFilm.trier("id"));
    }
    else if (ui->checkBox_nomTri->isChecked())
    {
        ui->tableView_films->setModel(tmpFilm.trier("nom"));
    }
    else if (ui->checkBox_dateTri->isChecked())
    {
        ui->tableView_films->setModel(tmpFilm.trier("date_sortie"));

    }
}



void MainWindow::on_pushButton_pdfFilms_clicked()
{
      QString strStream;
      QTextStream out(&strStream);
      const int rowCount = ui->tableView_films->model()->rowCount();
      const int columnCount = ui->tableView_films->model()->columnCount();

      out << "<h2 align=left>CINE + </h2>";
      out << "<h2 align=right>HEXASCRIPT </h2>";
      out << "<h1 align=center>LISTE DES FILMS </h1>";

      for(int column = 0;column < columnCount; column++)
        if(!ui->tableView_films->isColumnHidden(column))
               out <<QString("<td>%1</td>").arg(ui->tableView_films->model()->headerData(column, Qt::Horizontal).toString());
         for(int row = 0;row < rowCount; row++)
         {
             out <<"<tr>";
             for(int column = 0 ;column < columnCount ; column++)
             {
                  if(!ui->tableView_films->isColumnHidden(column))
                  {
                        QString data =ui->tableView_films->model()->data(ui->tableView_films->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                  }
              }
          }

       QTextDocument *document = new QTextDocument();
       document->setHtml(strStream);
       QPrinter printer(QPrinter::PrinterResolution);
       QPrintDialog *daddy = new QPrintDialog(&printer , NULL);
       if(daddy->exec() == QDialog::Accepted){
            document->print(&printer);
       }
       delete document;
}


void MainWindow::on_pushButton_2_clicked()
{
    tmpFilm.exporter_excel(ui->tableView_films);
}



// --------------PROJECTION------------//



void MainWindow::on_pushButton_ajouter_proj_clicked()
{
    int num_projection = ui->lineEdit_nump->text().toInt();
    int id = ui->lineEdit_idfilmp->text().toInt();
    QDateTime date_projection = ui->dateTimeEdit_datep->dateTime();
    int num_salle = ui->spinBox_salle->text().toInt();
    int capacite_salle = ui->lineEdit_capacite->text().toInt();
    projection p(num_projection, id, date_projection, num_salle, capacite_salle);
    if(num_projection>0 && num_salle !=0 && capacite_salle<500)
    {
    bool test = p.ajouter_p();
    if(test)
    {
         ui->tableView_projections->setModel(tmpProjection.afficher_p());
            QMessageBox::information(nullptr, QObject::tr("Ajout Projection") ,
                     QObject::tr("Projection ajoutée avec succès.\n" "Click cancel to exit"), QMessageBox::Cancel);
    }
    }
    else
    {
         QMessageBox::critical(nullptr, QObject::tr("Ajout Projection") ,
                     QObject::tr("Ajout échoué.\n" "Click cancel to exit"), QMessageBox::Cancel);
    }
}



void MainWindow::on_tableView_projections_activated(const QModelIndex &index)
{

}

void MainWindow::on_pushButton_update_proj_clicked()
{
    ui->pushButton_update_proj->setDisabled(true);
    ui->pushButton_update_proj->setText("Modifiable");
    ui->statusbar->showMessage("Veuillez séléctionner les champs à changer.");
    QSqlTableModel *tableModel= new QSqlTableModel();
    tableModel->setTable("PROJECTION");
    tableModel->select();
    ui->tableView_projections->setModel(tableModel);
    ui->pushButton_update_proj->setEnabled(true);
    ui->pushButton_update_proj->setText("Modifier");

}


void MainWindow::on_pushButton_supp_proj_clicked()
{
    QItemSelectionModel *select = ui->tableView_projections->selectionModel();

      int num_projection =select->selectedRows(0).value(0).data().toInt();

      if(tmpProjection.supprimer_p(num_projection))
      {
          ui->tableView_projections->setModel(tmpProjection.afficher_p());
          QMessageBox::information(nullptr, QObject::tr("Suppression projection") ,
                       QObject::tr("Projection supprimée avec succès.\n" "Click cancel to exit"), QMessageBox::Cancel);

      }
}

void MainWindow::on_rech_proj_clicked()
{
    int num_projection=ui->lineEdit_rech_nump->text().toInt();
    QDateTime date_projection=ui->dateTimeEdit_rechP->dateTime();
    int num_salle=ui->spinBox_rechsalle->text().toInt();

    QSqlQueryModel *rech=tmpProjection.rechercher_p(num_projection,date_projection,num_salle);
    if(rech)
    {
        ui->tableView_projections->setModel(rech);
    }
    else
    {
        ui->tableView_projections->setModel(tmpProjection.afficher_p());
    }
}

void MainWindow::on_tri_proj_clicked()
{
    if (ui->checkBox_numpTri->isChecked())
    {
        ui->tableView_projections->setModel(tmpProjection.trier_p("num_projection"));
    }
    else if(ui->checkBox_datePTri->isChecked())
    {
        ui->tableView_projections->setModel(tmpProjection.trier_p("date_projection"));
    }
    else if(ui->checkBox_salleTri->isChecked())
    {
        ui->tableView_projections->setModel(tmpProjection.trier_p("num_salle"));
    }

}


void MainWindow::on_exporterPdf_proj_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tableView_projections->model()->rowCount();
    const int columnCount = ui->tableView_projections->model()->columnCount();

    out << "</div>"
    "<h2 align=left>"
          "CINE+ <h2>";
    out << "<h2 align=right>HEXASCRIPT </h2>";
    out << "<h1 align=center>LISTE DES PROJECTIONS </h1>";

    for(int column = 0;column < columnCount; column++)
      if(!ui->tableView_projections->isColumnHidden(column))
             out <<QString("<td>%1</td>").arg(ui->tableView_projections->model()->headerData(column, Qt::Horizontal).toString());
       for(int row = 0;row < rowCount; row++)
       {
           out <<"<tr>";
           for(int column = 0 ;column < columnCount ; column++)
           {
                if(!ui->tableView_films->isColumnHidden(column))
                {
                      QString data =ui->tableView_projections->model()->data(ui->tableView_projections->model()->index(row, column)).toString().simplified();
                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
        }

     QTextDocument *document = new QTextDocument();
     document->setHtml(strStream);
     QPrinter printer(QPrinter::PrinterResolution);
     QPrintDialog *daddy = new QPrintDialog(&printer , NULL);
     if(daddy->exec() == QDialog::Accepted){
          document->print(&printer);
     }
     delete document;
}

void MainWindow::on_exporterExcel_proj_clicked()
{
    tmpProjection.exporterExcel_p(ui->tableView_projections);
}

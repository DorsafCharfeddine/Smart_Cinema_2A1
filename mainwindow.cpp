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
#include <QRegExp>
#include <QMediaPlayer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    duree_reg=QRegExp("[0-4]+h[0-5]+[0-9]$");
    int const n=0;

    ui->setupUi(this);


    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("C:/Users/Asus/Documents/cine/Beautiful-cinematic-piano-background-music.mp3"));
    player->setVolume(n);
    player->play();
    ui->spinBox->setRange(0,100);
    ui->spinBox->setValue(n);
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(n);
    QObject::connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)));
    QObject::connect(ui->spinBox,SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)));
    QObject::connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
    QObject::connect(ui->spinBox,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));

    ui->lineEdit_id->setPlaceholderText("ID...");
    ui->lineEdit_nom->setPlaceholderText("Nom...");
    ui->textEdit_description->setPlaceholderText("Desc...");
    ui->lineEdit_duree->setPlaceholderText(".h..");
    ui->lineEdit_nump->setPlaceholderText("Num...");
    ui->lineEdit_idfilmp->setPlaceholderText("ID...");
    ui->lineEdit_capacite->setPlaceholderText("Capacite...");
    ui->lineEdit_rechid->setPlaceholderText("ID film...");
    ui->lineEdit_rechnom->setPlaceholderText("Nom film...");
    ui->lineEdit_rech_nump->setPlaceholderText("Num projec...");

    //this->setStyleSheet("background-color: rgb(96, 168, 209);");

    ui->lineEdit_id->setMaxLength(8);
    ui->lineEdit_duree->setMaxLength(4);
    ui->dateEdit_ds->setMinimumDate(QDate::currentDate().addDays(-45000));
    ui->dateEdit_ds->setMaximumDate(QDate::currentDate().addDays(1));
    ui->dateEdit_ds->setDisplayFormat("dd.MM.yyyy");
    ui->lineEdit_rechid->setMaxLength(8);
    ui->dateEdit_rech->setMinimumDate(QDate::currentDate().addDays(-45000));
    ui->dateEdit_rech->setMaximumDate(QDate::currentDate().addDays(1));


    ui->lineEdit_nump->setMaxLength(8);
    ui->lineEdit_idfilmp->setMaxLength(8);
    ui->lineEdit_capacite->setMaxLength(3);
    ui->spinBox_salle->setMaximum(40);
    ui->dateTimeEdit_datep->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_datep->setMaximumDateTime(QDateTime::currentDateTime().addDays(730));
    ui->dateTimeEdit_datep->setDisplayFormat("dd.MM.yyyy hh:mm");
    ui->lineEdit_rech_nump->setMaxLength(8);
    ui->spinBox_rechsalle->setMaximum(40);
    ui->dateTimeEdit_rechP->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_rechP->setMaximumDateTime(QDateTime::currentDateTime().addDays(730));


    ui->tableView_films->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_films->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView_projections->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_projections->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_films->setModel(tmpFilm.afficher());
    ui->tableView_projections->setModel(tmpProjection.afficher_p());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    bool duree_verif = duree_reg.exactMatch(ui->lineEdit_duree->text());
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString genre = ui->comboBox_genre->currentText();
    QString description = ui->textEdit_description->toPlainText();
    QString duree = ui->lineEdit_duree->text();
    QDate date_sortie = ui->dateEdit_ds->date();
    film f(id, nom, genre, description, duree, date_sortie);
    if (id>0 && nom!="" && description!= "" && duree!="")
    {
        if (!duree_verif)
        {
             QMessageBox::warning(this,"Erreur","duree invalide");
        }
        else
        {
             bool test = f.ajouter();
             if(test)
             {
                    ui->tableView_films->setModel(tmpFilm.afficher());
                    QMessageBox::information(nullptr, QObject::tr("Ajout film") ,
                     QObject::tr("Film ajouté avec succès.\n" "Click cancel to exit"), QMessageBox::Cancel);
                    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>())
                        {
                        widget->clear();
                        }
             }
         }
    }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ajout film") ,
                     QObject::tr("Ajout échoué.\n" "Click cancel to exit"), QMessageBox::Cancel);
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
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click2.mp3"));
       sound->play();
    if (ui->pushButton_update->isEnabled())
    {
        ui->pushButton_update->setDisabled(true);
        QApplication::processEvents();
        ui->pushButton_update->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("FILM");
        tableModel->select();
        ui->tableView_films->setModel(tableModel);
    }
    ui->pushButton_update->setEnabled(true);
    ui->pushButton_update->setText("Modifier");
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
}


void MainWindow::on_pushButton_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
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
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
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
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
            QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tableView_films->model()->rowCount();
                    const int columnCount =ui->tableView_films->model()->columnCount();

                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("film")
                            <<  "</head>\n"
                            "<body bgcolor=#C5D4F6 link=#5000A0>\n"
                                "<img src='C:/Users/Asus/Documents/cine/hexa_script.png' width='100' height='100'>\n"
                                "<h1>Liste des films</h1>"
                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView_films->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView_films->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tableView_films->isColumnHidden(column)) {
                                       QString data = ui->tableView_films->model()->data(ui->tableView_films->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";

                           QTextDocument *document = new QTextDocument();
                           document->setHtml(strStream);
                           QPrinter printer;
                           QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                           if (dialog->exec() == QDialog::Accepted) {
                               document->print(&printer);
                            }

}


void MainWindow::on_pushButton_2_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
    tmpFilm.exporter_excel(ui->tableView_films);
}



// ----------------PROJECTION-----------------//



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
                foreach(QLineEdit *widget, this->findChildren<QLineEdit*>())
                {
                 widget->clear();
                }
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
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click2.mp3"));
       sound->play();
    if (ui->pushButton_update->isEnabled())
    {
        ui->pushButton_update_proj->setDisabled(true);
        QApplication::processEvents();
        ui->pushButton_update_proj->setText("Modifiable");
        ui->statusbar->showMessage("Veuillez selectionner les champs a changer.");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("PROJECTION");
        tableModel->select();
        ui->tableView_projections->setModel(tableModel);
    }
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
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Suppresion Projection") ,
                       QObject::tr("Suppression échoué.\n" "Click cancel to exit"), QMessageBox::Cancel);
      }
}

void MainWindow::on_rech_proj_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
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
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
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
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
    QString strStream;
            QTextStream out(&strStream);
            const int rowCount = ui->tableView_projections->model()->rowCount();
            const int columnCount =ui->tableView_projections->model()->columnCount();

            out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    <<  QString("<title>%1</title>\n").arg("projection")
                    <<  "</head>\n"
                    "<body bgcolor=#C5D4F6 link=#5000A0>\n"
                        "<img src='C:/Users/Asus/Documents/cine/hexa_script.png' width='100' height='100'>\n"
                        "<h1>Liste des projections</h1>"
                        "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers
                out << "<thead><tr bgcolor=#f0f0f0>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tableView_projections->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tableView_projections->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";
                // data table
                   for (int row = 0; row < rowCount; row++) {
                       out << "<tr>";
                       for (int column = 0; column < columnCount; column++) {
                           if (!ui->tableView_projections->isColumnHidden(column)) {
                               QString data = ui->tableView_projections->model()->data(ui->tableView_projections->model()->index(row, column)).toString().simplified();
                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                           }
                       }
                       out << "</tr>\n";
                   }
                   out <<  "</table>\n"
                       "</body>\n"
                       "</html>\n";

                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);
                   QPrinter printer;
                   QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                   if (dialog->exec() == QDialog::Accepted) {
                       document->print(&printer);
                   }
}

void MainWindow::on_exporterExcel_proj_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
    tmpProjection.exporterExcel_p(ui->tableView_projections);
}


void MainWindow::on_pushButton_afficherF_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
    ui->tableView_films->setModel(tmpFilm.afficher());
}

void MainWindow::on_pushButton_afficherP_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
    ui->tableView_projections->setModel(tmpProjection.afficher_p());
}

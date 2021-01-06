#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "film.h"
#include "projection.h"
#include "stats.h"
#include "arduino.h"
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
#include "client.h"
#include "abonnement.h"
#include "pointdevente.h"
#include "billet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    duree_reg=QRegExp("[0-4]+h[0-5]+[0-9]+m$");
    int const n=0;

    ui->setupUi(this);

    //this->setStyleSheet("background-color: rgb(129, 173, 186); color: rgb(0, 0, 0);");

    //MUSIC
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
    ui->lineEdit_duree->setPlaceholderText(".h..m");
    ui->lineEdit_nump->setPlaceholderText("Num proj...");
    ui->lineEdit_capacite->setPlaceholderText("Capacite...");
    ui->lineEdit_rechnom->setPlaceholderText("Nom film...");
    ui->lineEdit_rech_numP->setPlaceholderText("Num proj...");
    ui->lineEdit_username->setPlaceholderText("USERNAME..");
    ui->lineEdit_password->setPlaceholderText("PASSWORD..");

    //Background
    QPixmap bkgnd("C:\\Users\\Asus\\Desktop\\backgroundd.jpg");
       bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
       QPalette palette;
       palette.setBrush(QPalette::Background, bkgnd);
       this->setPalette(palette);

    //Controle de saisie max
    ui->lineEdit_id->setMaxLength(8);
    ui->lineEdit_duree->setMaxLength(5);
    ui->dateEdit_ds->setMinimumDate(QDate::currentDate().addYears(-100));
    ui->dateEdit_ds->setMaximumDate(QDate::currentDate().addDays(1));
    ui->dateEdit_ds->setDisplayFormat("dd.MM.yyyy");
    ui->dateEdit_rech->setMinimumDate(QDate::currentDate().addYears(-100));
    ui->dateEdit_rech->setMaximumDate(QDate::currentDate().addDays(1));

    ui->lineEdit_nump->setMaxLength(8);
    ui->lineEdit_capacite->setMaxLength(3);
    ui->spinBox_salle->setMaximum(40);
    ui->dateTimeEdit_datep->setMinimumDateTime(QDateTime::currentDateTime().addYears(-1));
    ui->dateTimeEdit_datep->setMaximumDateTime(QDateTime::currentDateTime().addYears(3));
    ui->dateTimeEdit_datep->setDisplayFormat("dd.MM.yyyy hh:mm");
    ui->lineEdit_rech_numP->setMaxLength(8);
    ui->spinBox_rechsalle->setMaximum(40);
    ui->dateTimeEdit_rechP->setMinimumDateTime(QDateTime::currentDateTime().addYears(-2));
    ui->dateTimeEdit_rechP->setMaximumDateTime(QDateTime::currentDateTime().addYears(3));

    //Selection des tables
    ui->tableView_films->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_films->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_projections->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_projections->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_poste_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_employe_3->setSelectionMode(QAbstractItemView::SingleSelection);

    //Affichage des tables
    ui->tableView_films->setModel(tmpFilm.afficher());
    ui->tableView_projections->setModel(tmpProjection.afficher_p());
    ui->tableView_employe_3->setModel(tmp_employe.afficher());
    ui->tableView_poste_3->setModel(tmp_poste.afficher());
    ui->tabpoint->setModel(p_temp.afficher());
    ui->tabbillet->setModel(b_temp.afficher());
    ui->tababo->setModel(a_temp.afficher());
    ui->tabclient->setModel(c_temp.afficher());

    int ret=A.connect_arduino();
           switch (ret)
           {
           case 0:
               qDebug() << "arduino is available and connected to:" << A.getarduino_port_name();
               break;
           case 1:
               qDebug() << "arduino is available but not connected to:" << A.getarduino_port_name();
               break;
           case -1:
               qDebug() << "arduino is not available";
               break;
           }

           QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

    int nb = ui->tableView_films->model()->rowCount();
    for (int i=0; i<nb; i++)
      {
          QString id = ui->tableView_films->model()->index(i, 0).data().toString();
          ui->comboBox_idF_proj->addItem(id);
      }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    if(ui->lineEdit_username->text()=="admin" && ui->lineEdit_password->text()== "admin")
    {
        ui->stackedWidget->setCurrentIndex(1);
        reset();
    }
    else if(ui->lineEdit_username->text()=="agent" && ui->lineEdit_password->text()== "agent")
    {
        ui->stackedWidget->setCurrentIndex(2);
        reset();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Username ou mot de passe incorrect") ,
                     QObject::tr("Connexion failed.\n" "Click cancel to exit"), QMessageBox::Cancel);
        reset();
    }
}
void MainWindow::reset()
{
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>())
        {
        widget->clear();
        }
}
void MainWindow::on_menuPROG1_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_menuPROG2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_menuNOTIF1_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_menuNOTIF2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_eye_pwd_clicked()
{
    ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
}

void MainWindow::on_menuCLIENT1_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_menuEmploye_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_menuBILLET_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


// -------------------DORSAF------------//

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
    bool existe = tmpFilm.id_existe(id);
    if(existe)
    {
        ui->lineEdit_id->setStyleSheet("color: red");
        ui->statusbar->showMessage("ID EXISTE!");
    }
    if (id>0 && nom!="" && description!= "" && duree!="" && duree_verif && !existe)
    {
             bool test = f.ajouter();
             if(test)
             {
                    ui->tableView_films->setModel(tmpFilm.afficher());
                    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                    notifyIcon->show();
                    notifyIcon->setIcon(QIcon("icone.png"));
                    notifyIcon->showMessage("GESTION FILMS ","Film Ajouté avec succès",QSystemTrayIcon::Information,15000);
                    ui->lineEdit_duree->setStyleSheet("color: black");
                    ui->lineEdit_id->setStyleSheet("color: black");
                    ui->lineEdit_nom->setStyleSheet("color: black");
                    ui->textEdit_description->setStyleSheet("color: black");
                    reset();
             }
     }
     else
     {
        if (!duree_verif)
        {
            ui->lineEdit_duree->setStyleSheet("color: red");
        }
        if(id<=0)
        {
            ui->lineEdit_id->setStyleSheet("color: red");
        }
        if(nom=="")
        {
            ui->lineEdit_nom->setStyleSheet("color: red");
        }
        if(description == "")
        {
            ui->textEdit_description->setStyleSheet("color: red");
        }
        if (!duree_verif && id <=0 && nom=="" && description=="")
        {
            ui->statusbar->showMessage("Tout les champs sont invalides.");
        }
      }
}


void MainWindow::on_tableView_films_activated(const QModelIndex &index)
{
/*
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
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->setIcon(QIcon("icone.png"));
        notifyIcon->showMessage("GESTION FILMS ","Film supprimé avec succès",QSystemTrayIcon::Information,15000);    }
    else
    {
          ui->statusbar->showMessage("Erreur de supression. Film existe dans une projection.");
    }
}


void MainWindow::on_pushButton_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
    sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
    sound->play();
    QString genre = ui->comboBox_rechF->currentText();
    QString nom=ui->lineEdit_rechnom->text();
    QDate date_sortie=ui->dateEdit_rech->date();
    QSqlQueryModel *rech=tmpFilm.rechercher_multi(genre,nom,date_sortie);
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

void MainWindow::on_statsFilms_clicked()
{
    stats *w = new stats();
               w->make();
               w->show();
}


// ----------------PROJECTION-----------------//



void MainWindow::on_pushButton_ajouter_proj_clicked()
{
    int num_projection = ui->lineEdit_nump->text().toInt();
    int id = ui->comboBox_idF_proj->currentText().toInt();
    QDateTime date_projection = ui->dateTimeEdit_datep->dateTime();
    int num_salle = ui->spinBox_salle->text().toInt();
    int capacite_salle = ui->lineEdit_capacite->text().toInt();
    projection p(num_projection, id, date_projection, num_salle, capacite_salle);
    bool existe = tmpProjection.num_existe(num_projection);
    if(existe)
    {
        ui->lineEdit_nump->setStyleSheet("color: red");
        ui->statusbar->showMessage("NUM PROJECTION EXISTE!");
    }
    if(num_projection>0 && num_salle !=0 && capacite_salle<500 && capacite_salle !=0 && !existe)
    {
        bool test = p.ajouter_p();
        if(test)
        {
            ui->tableView_projections->setModel(tmpProjection.afficher_p());
            ui->lineEdit_nump->setStyleSheet("color: black");
            ui->lineEdit_capacite->setStyleSheet("color: black");
            QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->setIcon(QIcon("icone.png"));
            notifyIcon->showMessage("GESTION PROJECTIONS ","Projection Ajoutée avec succès",QSystemTrayIcon::Information,15000);
            reset();
        }
    }
    else
    {
        if(num_projection <= 0)
        {
            ui->lineEdit_nump->setStyleSheet("color: red");
            ui->statusbar->showMessage("Numero projection invalide.");
        }
        if(capacite_salle <= 0)
        {
            ui->lineEdit_capacite->setStyleSheet("color: red");
            ui->statusbar->showMessage("Capacité salle invalide.");
        }
        if(num_salle == 0)
        {
            ui->spinBox_salle->setStyleSheet("color: red");
            ui->statusbar->showMessage("Numero salle vide.");
        }
        if(capacite_salle <=0 && num_projection<=0 && num_salle == 0)
        {
            ui->statusbar->showMessage("Les champs sont invalides.");
        }
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
          QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
          notifyIcon->show();
          notifyIcon->setIcon(QIcon("icone.png"));
          notifyIcon->showMessage("GESTION PROJECTIONS ","Projection supprimée avec succès",QSystemTrayIcon::Information,15000);
      }
      else
      {
          ui->statusbar->showMessage("Erreur de suppression.");
      }
}

void MainWindow::on_rech_proj_clicked()
{
    QMediaPlayer * sound = new QMediaPlayer();
       sound->setMedia(QUrl("C:/Users/Asus/Documents/cine/click3.mp3"));
       sound->play();
    int num_projection = ui->lineEdit_rech_numP->text().toInt();
    int num_salle = ui->spinBox_rechsalle->text().toInt();
    QDateTime date_projection = ui->dateTimeEdit_rechP->dateTime();
    QSqlQueryModel *rech=tmpProjection.rechercher_p(num_projection ,num_salle, date_projection);
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

void MainWindow::on_nightmode_clicked()
{
    ui->groupBox_ajoutP->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 gray, stop: 0.3 gray, stop: 1 gray);}");
    ui->groupBox_listeP->setStyleSheet("background-color: gray}");
    ui->groupBox_ajoutF->setStyleSheet("background-color: gray}");
    ui->groupBox_listeF->setStyleSheet("background-color: gray}");
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));
    notifyIcon->showMessage("GESTION FILMS ET PROJECTIONS","Mode nuit activé.",QSystemTrayIcon::Information,15000);
}

void MainWindow::on_daymode_clicked()
{
    ui->groupBox_ajoutF->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x1: 0, y2: 1, stop: 0.5 #88D1C7, stop: 1 #FFFFFF);}");
    ui->groupBox_listeF->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x1: 0, y2: 1, stop: 0 #88D1C7, stop: 1 #FFFFFF);}");
    ui->groupBox_ajoutP->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x1: 0, y2: 1, stop: 0 #88D1C7, stop: 1 #FFFFFF);}");
    ui->groupBox_listeP->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x1: 0, y2: 1, stop: 0 #88D1C7, stop: 1 #FFFFFF);}");
}

void MainWindow::on_returnPROG_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::update_label()
{
    data=A.read_from_arduino();
    tmp+=data;
    qDebug() << data;
    if (tmp.endsWith("\r\n"))
    {
        tmp = tmp.left(5);
        ui->lcdNumber_temp->display(tmp.toFloat());
        if(tmp.toFloat() > 25)
        {
            QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->setIcon(QIcon("icone.png"));
            notifyIcon->showMessage("GESTION NOTIF ","ATTENTION TEMPERATURE ELEVEE DETECTEE",QSystemTrayIcon::Information,15000);
         }
        tmp="";
     }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_checkBox_ENGLISH_clicked()
{
    if(ui->checkBox_ENGLISH->isChecked())
    {
    translator->load("C:/Users/Asus/Desktop/smart_cinema/Integration_Smart_Cinema/english.qm");
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    }
    ui->checkBox_FRENCH->setChecked(false);
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("icone.png"));
    notifyIcon->showMessage("MANAGE PROGRAM","Lanquage has been changed.",QSystemTrayIcon::Information,15000);
}

void MainWindow::on_checkBox_FRENCH_clicked()
{
    if(ui->checkBox_FRENCH->isChecked())
    {
    translator->load("C:/Users/Asus/Desktop/smart_cinema/Integration_Smart_Cinema/french.ts");
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    }
    ui->checkBox_ENGLISH->setChecked(false);
}


//-------------------RAED------------------//

void MainWindow::on_ae_pushButton_3_clicked()
{
    QString NOM = ui->lineEdit_NE_3->text();
    QString PRENOM = ui->lineEdit_PE_3->text();
    int CIN = ui->lineEdit_CinE_3->text().toInt();
    int POSTE = ui->lineEdit_PosteE_3->text().toInt();
    QString MAIL = ui->lineEdit_mailE_3->text();
    Employe Employe(NOM, PRENOM, CIN, POSTE, MAIL);

    bool test = Employe.ajouter();
    if (test)
    {
        ui->tableView_employe_3->setModel(tmp_employe.afficher());

    }
    else {
        QMessageBox::warning(this, "Erreur lors de l ajout du employé", "Veuillez remplir tous les champs à nouveau");
    }
}



void MainWindow::on_se_pushButton_3_clicked()
{
    QItemSelectionModel *select = ui->tableView_employe_3->selectionModel();

    QString NOM = select->selectedRows(0).value(0).data().toString();

    if (tmp_employe.supprimer(NOM))
    {
        ui->tableView_employe_3->setModel(tmp_employe.afficher());
        ui->statusbar->showMessage("employé supprimé");
    }
}

void MainWindow::on_pushButton_modifierE_3_clicked()
{
    if (ui->pushButton_modifierE_3->isChecked())
    {
        // ui->pushButton_modifier->setDisabled(true);
        ui->pushButton_modifierE_3->setText("Modifiable");
        QSqlTableModel* tableModel = new QSqlTableModel();
        tableModel->setTable("EMPLOYE");
        tableModel->select();
        ui->tableView_employe_3->setModel(tableModel);
    }
    else
    {
        ui->pushButton_modifierE_3->setText("Modifier");
        ui->tableView_employe_3->setModel(tmp_employe.afficher());

    }
}



void MainWindow::on_tri_5_clicked()
{
    Employe *r = new Employe();
    ui->tableView_employe_3->setModel(r->tri());
}

void MainWindow::on_PDF_3_clicked()
{
    QString strStream;
              QTextStream out(&strStream);
              const int rowCount = ui->tableView_employe_3->model()->rowCount();
              const int columnCount =ui->tableView_employe_3->model()->columnCount();

              out <<  "<html>\n"
                      "<head>\n"
                      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      <<  QString("<title>%1</title>\n").arg("employé")
                      <<  "</head>\n"
                      "<body bgcolor=#006BFF link=#5000A0>\n"
                          "<img src='D:/qt/hexa_script.png' width='100' height='100'>\n"
                          "<h1>Liste des Employes</h1>"
                          "<table border=1 cellspacing=0 cellpadding=2>\n";


              // headers
                  out << "<thead><tr bgcolor=#f0f0f0>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tableView_employe_3->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView_employe_3->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";
                  // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView_employe_3->isColumnHidden(column)) {
                                 QString data = ui->tableView_employe_3->model()->data(ui->tableView_employe_3->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_re_3_clicked()
{
    QString rech =ui->lineEdit_Recherche_Cin_3->text();
    ui->tableView_employe_3->setModel(tmp_employe.rechercher(rech));
}

void MainWindow::on_ap_pushButton_3_clicked()
{
    QString NOM = ui->lineEdit_Np_3->text();
        int ID = ui->lineEdit_id_P_3->text().toInt();
        int NBRH = ui->lineEdit_nbr_H_3->text().toInt();
        int SALAIRE = ui->lineEdit_salaire_3->text().toInt();
        poste poste(NOM, ID, NBRH, SALAIRE);

        bool test = poste.ajouter();
        if (test)
        {
            ui->tableView_poste_3->setModel(tmp_poste.afficher());

        }
        else {
            QMessageBox::warning(this, "Erreur lors de l ajout du poste", "Veuillez remplir tous les champs à nouveau");
        }
}

void MainWindow::on_mp_pushButton_3_clicked()
{
    if (ui->mp_pushButton_3->isChecked())
    {
        // ui->pushButton_modifier->setDisabled(true);
        ui->mp_pushButton_3->setText("Modifiable");
        QSqlTableModel* tableModel = new QSqlTableModel();
        tableModel->setTable("POSTE");
        tableModel->select();
        ui->tableView_poste_3->setModel(tableModel);
    }
    else
    {
        ui->mp_pushButton_3->setText("Modifier");
        ui->tableView_poste_3->setModel(tmp_poste.afficher());

    }
}

void MainWindow::on_sp_pushButton_3_clicked()
{
    QItemSelectionModel *select = ui->tableView_poste_3->selectionModel();

    QString NOM = select->selectedRows(0).value(0).data().toString();

    if (tmp_poste.supprimer(NOM))
    {
        ui->tableView_poste_3->setModel(tmp_poste.afficher());
        ui->statusbar->showMessage("poste supprimé");
    }
}



void MainWindow::on_tri_6_clicked()
{
    poste *r = new poste();
    ui->tableView_poste_3->setModel(r->tri());
}

void MainWindow::on_stat_3_clicked()
{
        statistique stat;
        double dag = stat.statestique_partie1();
        double dir = stat.statestique_partie2();


          // set dark background gradient:
          QLinearGradient gradient(0, 0, 0, 400);
          gradient.setColorAt(0, QColor(90, 90, 90));
          gradient.setColorAt(0.38, QColor(105, 105, 105));
          gradient.setColorAt(1, QColor(70, 70, 70));
          ui->gplot_3->setBackground(QBrush(gradient));
          // create empty bar chart objects:

          QCPBars *fossil = new QCPBars(ui->gplot_3->xAxis, ui->gplot_3->yAxis);
          fossil->setAntialiased(false);


          fossil->setStackingGap(1);


          // prepare x axis with country labels:
          QVector<double> ticks;
          QVector<QString> labels;
          ticks << 1 << 2 ;
          labels << "prix entre 400 et 800" << "prix entre 801 et 1200 " ;
          QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
          textTicker->addTicks(ticks, labels);
          ui->gplot_3->xAxis->setTicker(textTicker);
          ui->gplot_3->xAxis->setTickLabelRotation(60);
          ui->gplot_3->xAxis->setSubTicks(false);
          ui->gplot_3->xAxis->setTickLength(0, 4);
          ui->gplot_3->xAxis->setRange(0, 13);
          ui->gplot_3->xAxis->setBasePen(QPen(Qt::white));
          ui->gplot_3->xAxis->setTickPen(QPen(Qt::white));
          ui->gplot_3->xAxis->grid()->setVisible(true);
          ui->gplot_3->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
          ui->gplot_3->xAxis->setTickLabelColor(Qt::white);
          ui->gplot_3->xAxis->setLabelColor(Qt::white);

          // prepare y axis:
          ui->gplot_3->yAxis->setRange(0, 10);
          ui->gplot_3->yAxis->setPadding(5); // a bit more space to the left border
          ui->gplot_3->yAxis->setLabel("les salaires");
          ui->gplot_3->yAxis->setBasePen(QPen(Qt::white));
          ui->gplot_3->yAxis->setTickPen(QPen(Qt::white));
          ui->gplot_3->yAxis->setSubTickPen(QPen(Qt::white));
          ui->gplot_3->yAxis->grid()->setSubGridVisible(true);
          ui->gplot_3->yAxis->setTickLabelColor(Qt::white);
          ui->gplot_3->yAxis->setLabelColor(Qt::white);
          ui->gplot_3->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
          ui->gplot_3->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

          // Add data:
          QVector<double> fossilData;

          fossilData  << dag << dir ;
          fossil->setData(ticks, fossilData);

          ui->gplot_3->legend->setVisible(true);
          ui->gplot_3->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
          ui->gplot_3->legend->setBrush(QColor(255, 255, 255, 100));
          ui->gplot_3->legend->setBorderPen(Qt::NoPen);
          QFont legendFont = font();
          legendFont.setPointSize(10);
          ui->gplot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
          ui->gplot_3->legend->setFont(legendFont);
}

void MainWindow::on_Recherche_3_clicked()
{
    QString rech =ui->lineEdit_Rech_idP_3->text();
    ui->tableView_poste_3->setModel(tmp_poste.rechercher(rech));
}


// ------------------ IHEB -------------//

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



void MainWindow::on_quitterabo_clicked()
{
    ui->numab->clear();
     ui->libab->clear();
     ui->nbrab->clear();

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
     /*bool testt=c.verifierId(id);
             if(testt)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                              QObject::tr(" id client déjà existant !.\n"
                                          "Click Ok to exit."), QMessageBox::Ok);

                }
             else

     {*/
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

void MainWindow::on_quittercl_clicked()
{
    ui->id_aj->clear();
      ui->nom_aj->clear();//annuler ajout
      ui->prenom_aj->clear();
      ui->email_aj->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString id = ui->id_rech->text();

        ui->tabclient->setModel(c_temp.rechercher(id));

}

void MainWindow::on_pushButton_6_clicked()
{
    QString prenom=ui->nom_rech->text();

        ui->tabclient->setModel(c_temp.recherche(prenom));

}

void MainWindow::on_quitter_af_clicked()
{
     ui->id_rech->clear();
      ui->nom_rech->clear();
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

void MainWindow::on_refrech_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("select ID from CLIENT");
        qry->exec();
        model->setQuery(*qry);
        ui->combosup_cl->setModel(model);
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

void MainWindow::on_trie_asc_clicked()
{
     ui->tabclient->setModel(c_temp.tridasc());
}

void MainWindow::on_trie_desc_clicked()
{
    ui->tabclient->setModel(c_temp.tridesc());
}

void MainWindow::on_trie_asc_ab_clicked()
{
     ui->tababo->setModel(a_temp.tridasc());
}

void MainWindow::on_trie_desc_abo_clicked()
{
     ui->tababo->setModel(a_temp.tridesc());
}

void MainWindow::on_menuCLIENT2_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


// -------------- ALA ------------//

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

void MainWindow::on_rech_p_clicked()
{
    QString referenceb = ui->ref_cher_p->text();

       ui->tabpoint->setModel(p_temp.recherche(referenceb));
}

void MainWindow::on_trie_p_clicked()
{
    ui->tabpoint->setModel(p_temp.tridesc());
}

void MainWindow::on_pushButton_7_clicked()
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

void MainWindow::on_pushButton_8_clicked()
{

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

void MainWindow::on_rech_billet_clicked()
{
    QString reference = ui->ref_cher->text();

       ui->tabbillet->setModel(b_temp.rechercher(reference));
}

void MainWindow::on_triee_billet_clicked()
{
      ui->tabbillet->setModel(b_temp.tridesc());
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

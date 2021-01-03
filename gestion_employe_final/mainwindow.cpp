#include "mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_employe->setModel(tmp_employe.afficher());
    ui->tableView_employe->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_employe->setSelectionMode(QAbstractItemView::SingleSelection);
    son=new QSound("son.wav");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*----------------------------------EMPLOYE------------------------------------------------*/

void MainWindow::on_ae_pushButton_clicked() //ajouter employé
{
    QString NOM = ui->lineEdit_NE->text();
    QString PRENOM = ui->lineEdit_PE->text();
    int CIN = ui->lineEdit_CinE->text().toInt();
    int POSTE = ui->lineEdit_PosteE->text().toInt();
    QString MAIL = ui->lineEdit_mailE->text();
    Employe Employe(NOM, PRENOM, CIN, POSTE, MAIL);

    bool test = Employe.ajouter();
    if (test)
    {
        ui->tableView_employe->setModel(tmp_employe.afficher());

    }
    else {
        QMessageBox::warning(this, "Erreur lors de l ajout du employé", "Veuillez remplir tous les champs à nouveau");
    }
}

void MainWindow::on_pushButton_modifierE_clicked()  //modifier employé
{
    if (ui->pushButton_modifierE->isChecked())
    {
        // ui->pushButton_modifier->setDisabled(true);
        ui->pushButton_modifierE->setText("Modifiable");
        QSqlTableModel* tableModel = new QSqlTableModel();
        tableModel->setTable("EMPLOYE");
        tableModel->select();
        ui->tableView_employe->setModel(tableModel);
    }
    else
    {
        ui->pushButton_modifierE->setText("Modifier");
        ui->tableView_employe->setModel(tmp_employe.afficher());

    }
}

void MainWindow::on_re_clicked()    //recherche employé
{
    QString rech =ui->lineEdit_Recherche_Cin->text();
    ui->tableView_employe->setModel(tmp_employe.rechercher(rech));
}

void MainWindow::on_tri_clicked()   //tri employé
{
    Employe *r = new Employe();
    ui->tableView_employe->setModel(r->tri());
}

void MainWindow::on_se_pushButton_clicked() //supprimer employé
{
    QItemSelectionModel* select = ui->tableView_employe->selectionModel();

    QString NOM = select->selectedRows(0).value(0).data().toString();

    if (tmp_employe.supprimer(NOM))
    {
        ui->tableView_employe->setModel(tmp_employe.afficher());
        ui->statusbar->showMessage("employé supprimé");
    }
}

/*----------------------------------POSTE------------------------------------------------*/

void MainWindow::on_sp_pushButton_clicked() //supprimer poste
{
    QItemSelectionModel* select = ui->tableView_poste->selectionModel();

    QString NOM = select->selectedRows(0).value(0).data().toString();

    if (tmp_poste.supprimer(NOM))
    {
        ui->tableView_poste->setModel(tmp_poste.afficher());
        ui->statusbar->showMessage("poste supprimé");
    }
}

void MainWindow::on_ap_pushButton_clicked() //ajouter poste
{
    QString NOM = ui->lineEdit_Np->text();
    int ID = ui->lineEdit_id_P->text().toInt();
    int NBRH = ui->lineEdit_nbr_H->text().toInt();
    int SALAIRE = ui->lineEdit_salaire->text().toInt();
    poste poste(NOM, ID, NBRH, SALAIRE);

    bool test = poste.ajouter();
    if (test)
    {
        ui->tableView_poste->setModel(tmp_poste.afficher());

    }
    else {
        QMessageBox::warning(this, "Erreur lors de l ajout du poste", "Veuillez remplir tous les champs à nouveau");
    }
}


void MainWindow::on_mp_pushButton_clicked() //modifier poste
{
    if (ui->mp_pushButton->isChecked())
    {
        // ui->pushButton_modifier->setDisabled(true);
        ui->mp_pushButton->setText("Modifiable");
        QSqlTableModel* tableModel = new QSqlTableModel();
        tableModel->setTable("POSTE");
        tableModel->select();
        ui->tableView_poste->setModel(tableModel);
    }
    else
    {
        ui->mp_pushButton->setText("Modifier");
        ui->tableView_poste->setModel(tmp_poste.afficher());

    }
}

void MainWindow::on_tri_2_clicked() //tri poste
{
    poste *r = new poste();
    ui->tableView_poste->setModel(r->tri());
}

void MainWindow::on_Recherche_clicked() //tri poste
{
    QString rech =ui->lineEdit_Rech_idP->text();
    ui->tableView_poste->setModel(tmp_poste.rechercher(rech));
}




void MainWindow::on_mail_pushButton_clicked()
{

}

void MainWindow::on_stat_pushButton_clicked()
{

}



void MainWindow::on_PDF_clicked()
{
    QString strStream;
              QTextStream out(&strStream);
              const int rowCount = ui->tableView_employe->model()->rowCount();
              const int columnCount =ui->tableView_employe->model()->columnCount();

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
                      if (!ui->tableView_employe->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView_employe->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";
                  // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView_employe->isColumnHidden(column)) {
                                 QString data = ui->tableView_employe->model()->data(ui->tableView_employe->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_stat_clicked()
{
    statistique stat;
        double dag = stat.statestique_partie1();
        double dir = stat.statestique_partie2();


          // set dark background gradient:
          QLinearGradient gradient(0, 0, 0, 400);
          gradient.setColorAt(0, QColor(90, 90, 90));
          gradient.setColorAt(0.38, QColor(105, 105, 105));
          gradient.setColorAt(1, QColor(70, 70, 70));
          ui->gplot->setBackground(QBrush(gradient));
          // create empty bar chart objects:

          QCPBars *fossil = new QCPBars(ui->gplot->xAxis, ui->gplot->yAxis);
          fossil->setAntialiased(false);


          fossil->setStackingGap(1);


          // prepare x axis with country labels:
          QVector<double> ticks;
          QVector<QString> labels;
          ticks << 1 << 2 ;
          labels << "prix entre 400 et 800" << "prix entre 801 et 1200 " ;
          QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
          textTicker->addTicks(ticks, labels);
          ui->gplot->xAxis->setTicker(textTicker);
          ui->gplot->xAxis->setTickLabelRotation(60);
          ui->gplot->xAxis->setSubTicks(false);
          ui->gplot->xAxis->setTickLength(0, 4);
          ui->gplot->xAxis->setRange(0, 13);
          ui->gplot->xAxis->setBasePen(QPen(Qt::white));
          ui->gplot->xAxis->setTickPen(QPen(Qt::white));
          ui->gplot->xAxis->grid()->setVisible(true);
          ui->gplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
          ui->gplot->xAxis->setTickLabelColor(Qt::white);
          ui->gplot->xAxis->setLabelColor(Qt::white);

          // prepare y axis:
          ui->gplot->yAxis->setRange(0, 10);
          ui->gplot->yAxis->setPadding(5); // a bit more space to the left border
          ui->gplot->yAxis->setLabel("les salaires");
          ui->gplot->yAxis->setBasePen(QPen(Qt::white));
          ui->gplot->yAxis->setTickPen(QPen(Qt::white));
          ui->gplot->yAxis->setSubTickPen(QPen(Qt::white));
          ui->gplot->yAxis->grid()->setSubGridVisible(true);
          ui->gplot->yAxis->setTickLabelColor(Qt::white);
          ui->gplot->yAxis->setLabelColor(Qt::white);
          ui->gplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
          ui->gplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

          // Add data:
          QVector<double> fossilData;

          fossilData  << dag << dir ;
          fossil->setData(ticks, fossilData);

          ui->gplot->legend->setVisible(true);
          ui->gplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
          ui->gplot->legend->setBrush(QColor(255, 255, 255, 100));
          ui->gplot->legend->setBorderPen(Qt::NoPen);
          QFont legendFont = font();
          legendFont.setPointSize(10);
          ui->gplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
          ui->gplot->legend->setFont(legendFont);
}

void MainWindow::on_paly_clicked()
{
    son->play();
    son->setLoops(QSound::Infinite);
}

void MainWindow::on_mute_clicked()
{
    son->stop();
}

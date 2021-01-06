#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connexion.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
    Connexion c;
     c.createconnect();
    //affichage contenu base
    show_tables();

    //for email tab
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    //for arduino
    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }





}

MainWindow::~MainWindow()
{


    if(arduino->isOpen()){
        arduino->close();
    }

    delete ui;



     //affichage contenu de la base
     show_tables();

}

//RES

//ajout
void MainWindow::on_actionadd_triggered()
{

    //creation instance
        add_class ac(this);

        //ouvrir dialog
        int res=ac.exec();
        if (res == QDialog::Rejected )
            return;

      //recuperation des donnees
        int i=ac.nbr();
        QString s1=ac.nom();
        QString s2=ac.num();
        QString s3=ac.texte();
        QString s4=ac.get_date();


        //ajout
        my_class mc(i,s1,s2,s3,s4);
        mc.ajouter();

    //refresh du tableau (affichage)
     show_tables();

}

//affichage + metier tri
void MainWindow::show_tables(){
//creation model (masque du tableau) : permet recherche et tri
    proxyo = new QSortFilterProxyModel();

    proxyr = new QSortFilterProxyModel();


 //definir la source (tableau original)
    proxyr->setSourceModel(tmp.afficher());
proxyo->setSourceModel(tp.afficher());

 //pour la recherche
    proxyr->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
    proxyr->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
    proxyo->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
    proxyo->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
   //remplissage tableau avec le masque
    ui->tableau_res->setModel(proxyr);
    ui->tableau_off->setModel(proxyo);

}

//recuperer l'entier (integer) on l'appelle selected
void MainWindow::on_tableau_5_clicked(const QModelIndex &index)
{
     selectedr=ui->tableau_res->model()->data(index).toInt();

}

//supression
void MainWindow::on_actiondelete_triggered()
{
    my_class mc;
  mc.supprimer(selectedr);

 //refresh du tableau (affichage)
   show_tables();
}

//modification
void MainWindow::on_tableau_5_doubleClicked()
{

    add_class ac(this);

  ac.fill_form(selectedr);
  int res=ac.exec();
  if (res == QDialog::Rejected )
    return;


  //recuperation des donnees
  QString s1=ac.nom();
  QString s2=ac.num();
  QString s3=ac.texte();
  QString s4=ac.get_date();



    //mofication
    my_class mc(selectedr,s1,s2,s3,s4);
    mc.modifier(selectedr);



  //refresh du tableau (affichage)
   show_tables();

}

//METIER

//recherche dynamique
void MainWindow::on_recherche_4_textChanged(const QString &arg1)
{
proxyr->setFilterFixedString(arg1);
}

//TABLE1


void MainWindow:: on_actionajouter_triggered()
{

    //creation instance
       add_offre ac(this);

        //ouvrir dialog
        int res=ac.exec();
        if (res == QDialog::Rejected )
            return;

      //recuperation des donnee

        QString s2=ac.line();
        QString s1=ac.combobox();
        QString s3=ac.text();
        QString s4=ac.get_date();


        //ajout
    offre mc(s1,s2,s3,s4);
        mc.ajouter();

    //refresh du tableau (affichage)
     show_tables();
}
void MainWindow::on_actionSupprimer_Offre_triggered()
{
    offre mc;
     mc.supprimer(selectedo);
      if( mc.supprimer(selectedo))
      {

        ui->statusbar->showMessage("Film supprimé avec succès.");
    }
    else
    {
          ui->statusbar->showMessage("Erreur de supression. Film existe dans une projection.");
    }
   show_tables();
}
void MainWindow::on_recherche_3_textChanged(const QString &arg1)
{
    proxyo->setFilterFixedString(arg1);
}
void MainWindow::on_tableau_4_clicked(const QModelIndex &index)
{
     selectedo=ui->tableau_off->model()->data(index).toString();
}


void MainWindow::on_tableau_4_doubleClicked(const QModelIndex &index)
{
    add_offre ac(this);

      ac.fill_form(selectedo);
  int res=ac.exec();
  if (res == QDialog::Rejected )
    return;


  //recuperation des donnees
    QString s2=ac.line();
    QString s1=ac.combobox();
    QString s3=ac.text();
    QString s4=ac.get_date();


    //mofication
    offre mc(selectedo,s2,s3,s4);
    mc.modifier(selectedo);



  //refresh du tableau (affichage)
   show_tables();

}

//export excel
void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableau_res);

    //colums to export
    obj.addField(0, "ticket", "char(20)");
    obj.addField(1, "nom", "char(20)");
    obj.addField(2, "num", "char(20)");
    obj.addField(3, "comment", "char(20)");
    obj.addField(4, "temps", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

//mailing
void  MainWindow::browse()
{
    files.clear();


    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("abir.seddiki@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("abir.seddiki@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("abir.seddiki@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void MainWindow::on_red_slider_rangeChanged(int value)
{
    ui->red_value_label->setText(QString("<span style=\" font-size:18pt; font-weight:600;\">%1</span>").arg(value));
    MainWindow::updateRGB(QString("r%1").arg(value));
    qDebug() << value;

}

void MainWindow::on_green_slider_rangeChanged(int value)
{
    ui->green_value_label->setText(QString("<span style=\" font-size:18pt; font-weight:600;\">%1</span>").arg(value));
    MainWindow::updateRGB(QString("g%1").arg(value));
    qDebug() << value;
}
void MainWindow::updateRGB(QString command)
{

    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}

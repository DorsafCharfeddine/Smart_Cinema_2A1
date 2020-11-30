#include "film.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QStringListModel>
#include <QSqlRecord>
#include <QFile>
#include <QFileDialog>
#include <QTableView>
#include <QTextStream>
#include <QCoreApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTableWidget>
#include <QtPrintSupport/QPrintDialog>

film::film()
{

}

film::film(int id, QString nom, QString genre, QString description, QString duree, QDate date_sortie)
{
    this->id = id;
    this->nom = nom;
    this->genre = genre;
    this->description = description;
    this->duree = duree;
    this->date_sortie = date_sortie;
}

bool film::ajouter()
{
    QSqlQuery query;
    query.prepare("Insert into film (id, nom, genre,description, duree, date_sortie)"
                  "Values(:id, :nom, :genre, :description, :duree, :date_sortie)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":genre", genre);
    query.bindValue(":description", description);
    query.bindValue(":duree", duree);
    query.bindValue(":date_sortie", date_sortie);
    return query.exec();

}

QSqlQueryModel * film::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from film");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date de sortie"));

    return model;
}

bool film::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE from film where id = :id");
    query.bindValue(":id", res);
    return query.exec();
}

QSqlQueryModel * film::rechercher_multi(int id,QString nom,QDate date_sortie)
{
    QSqlQuery *query=new QSqlQuery();
    query->prepare("select * from film where id=:id or nom=:nom or date_sortie=:date_sortie");
    query->bindValue(":id",id);
    query->bindValue(":nom",nom);
    query->bindValue(":date_sortie",date_sortie);
    query->exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*query);
    return model;
}

QSqlQueryModel * film::trier(QString crit)
{
    QSqlQuery *qry=new QSqlQuery();
       QSqlQueryModel *model=new QSqlQueryModel();
       qry->prepare("select * from film order by "+crit+" ");
       qry->exec();
       model->setQuery(*qry);
       return model;
}

/*void film::exporter(QTableView *table)
{
    QString filters("PDF files (.pdf);;All files (*.*)");
    QString defaultFilter("PDF files (*.pdf)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                                        filters, &defaultFilter);
    QFile file(fileName);
    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++)
        {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
         }
         data << strList.join(";") << "\n";
         for (int i = 0; i < model->rowCount(); i++)
         {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++)
            {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
             }
                data << strList.join(";") + "\n";
            }
            file.close();
        }
}*/
/*void film::ex(QTableView *table)
{
   const int columns = tbl->columnCount();
                const int rows = tbl->rowCount();
                QTextDocument doc;
                QTextCursor cursor(&doc);
                QTextTableFormat tableFormat;
                tableFormat.setHeaderRowCount(1);
                tableFormat.setAlignment(Qt::AlignHCenter);
                tableFormat.setCellPadding(0);
                tableFormat.setCellSpacing(0);
                tableFormat.setBorder(1);
                tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
                tableFormat.clearColumnWidthConstraints();
                QTextTable *textTable = cursor.insertTable(rows + 1, columns, tableFormat);
                QTextCharFormat tableHeaderFormat;
                tableHeaderFormat.setBackground(QColor("#DADADA"));
                for (int i = 0; i < columns; i++) {
                    QTextTableCell cell = textTable->cellAt(0, i);
                    cell.setFormat(tableHeaderFormat);
                    QTextCursor cellCursor = cell.firstCursorPosition();
                    cellCursor.insertText(tbl->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString());
                }
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        QTableWidgetItem *item = tbl->item(i, j);
                        if (!item || item->text().isEmpty()) {
                            tbl->setItem(i, j, new QTableWidgetItem("0"));
                        }

                        QTextTableCell cell = textTable->cellAt(i, j);
                        QTextCursor cellCursor = cell.firstCursorPosition();
                        cellCursor.insertText(tbl->item(i, j)->text());
                    }
                }
                cursor.movePosition(QTextCursor::End);
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOrientation(QPrinter::Landscape);
                printer.setOutputFileName(strFile);
                doc.setDocumentMargin(0);
                doc.setTextWidth(5);
                doc.print(&printer);

    void film::PrintTable( QPrinter* printer, QSqlQuery&  Query ) {
      QString strStream;
      QTextStream out(&strStream);

      const int rowCount = Query.size();
      const int columnCount = Query.record().count();

      out <<  "<html>\n"
          "<head>\n"
          "<meta Content=\"Text/html; charset=Windows-1251\">\n"
          <<  QString("<title>%1</title>\n").arg("TITLE OF TABLE")
          <<  "</head>\n"
          "<body bgcolor=#ffffff link=#5000A0>\n"
          "<table border=1 cellspacing=0 cellpadding=2>\n";

      // headers
      out << "<thead><tr bgcolor=#f0f0f0>";
      for (int column = 0; column < columnCount; column++)
        out << QString("<th>%1</th>").arg(Query.record().fieldName(column));
      out << "</tr></thead>\n";

      while (Query.next()) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
          QString data = Query.value(column).toString();
          out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
        }
        out << "</tr>\n";
      }

      out <<  "</table>\n"
          "</body>\n"
          "</html>\n";

      QTextDocument document;
      document.setHtml(strStream);
      document.print(printer);

    }*/
      void film::print() {
    QString html;
    QString id;
    QString nom;
       QString genre;
       QString description;
       QString date_sortie;
    html="<h1>id: "+id+"</h1>"
         "<h1>nom: "+nom+"</h1>"
         "<h1>genre: "+genre+"</h1>"
         "<h1>description: "+description+"</h1>"
         "<h1>date_sortie: "+date_sortie+"</h1>";
       QTextDocument document;
       document.setHtml(html);
       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName("test.pdf");
       document.print(&printer);
}

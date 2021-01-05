#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "film.h"
#include "projection.h"
#include "arduino.h"
#include <QMainWindow>
#include <QTranslator>
#include "employe.h"
#include "poste.h"
#include "statistique.h"
#include "qcustomplot.h"
#include "client.h"
#include "abonnement.h"
#include "pointdevente.h"
#include "billet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVariant Data(const QModelIndex &index, int role) const;



;

private slots:
    void update_label();

    void on_ajouter_clicked();

    void on_tableView_films_activated(const QModelIndex &index);

    void on_pushButton_suppFilm_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_clicked();

    void on_pushButton_pdfFilms_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_ajouter_proj_clicked();

    void on_tableView_projections_activated(const QModelIndex &index);

    void on_pushButton_update_proj_clicked();

    void on_pushButton_supp_proj_clicked();

    void on_pushButton_2_clicked();

    void on_rech_proj_clicked();

    void on_tri_proj_clicked();

    void on_exporterPdf_proj_clicked();

    void on_exporterExcel_proj_clicked();

    void on_pushButton_afficherF_clicked();

    void on_pushButton_afficherP_clicked();

    void on_night_mode_clicked();

    void on_daymode_clicked();

    void on_statsFilms_clicked();

    void on_login_clicked();

    void on_menuPROG2_clicked();

    void on_returnPROG_clicked();

    void on_logout_clicked();

    void on_nightmode_clicked();

    void on_pushButton_3_clicked();

    void on_menuNOTIF1_clicked();

    void on_menuNOTIF2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_logout_clicked();

    void on_menuPROG1_clicked();

    void reset();
    void on_checkBox_ENGLISH_clicked();

    void on_checkBox_FRENCH_clicked();

    void on_eye_pwd_clicked();

    void on_eye_pwd_clicked(bool checked);

    void on_ae_pushButton_3_clicked();

    void on_se_pushButton_3_clicked();

    void on_pushButton_modifierE_3_clicked();

    void on_tri_5_clicked();

    void on_PDF_3_clicked();

    void on_re_3_clicked();

    void on_ap_pushButton_3_clicked();

    void on_mp_pushButton_3_clicked();

    void on_sp_pushButton_3_clicked();

    void on_tri_6_clicked();

    void on_stat_3_clicked();

    void on_Recherche_3_clicked();

    void on_ajouterabo_clicked();

    void on_modifierabo_clicked();

    void on_sup_abo_clicked();
    void on_quitterab_clicked();
    void on_rech_id_clicked();
    void on_rech_num_clicked();
    void on_refrechabo_clicked();
    void on_quitterabo_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_sup_clicked();
    
    void on_imprimercl_2_clicked();
    
    void on_ajoutcl_clicked();
    void on_quittercl_clicked();
    void on_modifcl_clicked();
    
    void on_pushButton_6_clicked();
    
    void on_quitter_af_clicked();
    
    void on_suppcl_clicked();
    
    void on_refrech_clicked();
    
    void on_imprimercl_clicked();
    
    void on_trie_asc_clicked();
    
    void on_trie_desc_clicked();
    void on_trie_asc_ab_clicked();
    void on_trie_desc_abo_clicked();
    
    void on_menuCLIENT2_clicked();

    void on_ajouter_pointdevente_clicked();

    void on_modif_point_clicked();

    void on_rech_p_clicked();

    void on_trie_p_clicked();

    void on_pushButton_7_clicked();

    void on_imprimer_p_clicked();

    void on_ajouter_billet_clicked();

    void on_pushButton_8_clicked();

    void on_modifier_billet_clicked();

    void on_rech_billet_clicked();

    void on_triee_billet_clicked();

    void on_supprimer_billet_clicked();

    void on_imprimer_billet_clicked();

    void on_menuCLIENT1_clicked();

    void on_menuEmploye_clicked();

    void on_menuBILLET_clicked();

private:
    Ui::MainWindow *ui;
    film tmpFilm;
    Employe tmp_employe;
    poste tmp_poste;
    projection tmpProjection;
    //arduino A;
    QByteArray data;
    QRegExp duree_reg;
    QString tmp="";
    arduino A;
    QTranslator *translator=new QTranslator;
    client c_temp;
    abonnement a_temp;
     billet b_temp;
     pointdevente p_temp;

    //QSound *son;

};
#endif // MAINWINDOW_H

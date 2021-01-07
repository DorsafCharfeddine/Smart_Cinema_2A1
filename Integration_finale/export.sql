--------------------------------------------------------
--  Fichier cr�� - mercredi-janvier-06-2021   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table ABONNEMENT
--------------------------------------------------------

  CREATE TABLE "DORSAF"."ABONNEMENT" 
   (	"NUMERO" VARCHAR2(20 BYTE), 
	"LIBELLE" VARCHAR2(20 BYTE), 
	"NB_POINT" VARCHAR2(20 BYTE), 
	"ID" VARCHAR2(20 BYTE), 
	"DATEA" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table BILLET
--------------------------------------------------------

  CREATE TABLE "DORSAF"."BILLET" 
   (	"REFERENCE" VARCHAR2(20 BYTE), 
	"CATEGORIE" VARCHAR2(20 BYTE), 
	"PRIX" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table CLIENT
--------------------------------------------------------

  CREATE TABLE "DORSAF"."CLIENT" 
   (	"ID" VARCHAR2(20 BYTE), 
	"NOM" VARCHAR2(20 BYTE), 
	"PRENOM" VARCHAR2(20 BYTE), 
	"EMAIL" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table EMPLOYE
--------------------------------------------------------

  CREATE TABLE "DORSAF"."EMPLOYE" 
   (	"NOM" VARCHAR2(20 BYTE), 
	"PRENOM" VARCHAR2(20 BYTE), 
	"CIN" NUMBER, 
	"POSTE" NUMBER, 
	"MAIL" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table FILM
--------------------------------------------------------

  CREATE TABLE "DORSAF"."FILM" 
   (	"ID" NUMBER(*,0), 
	"NOM" VARCHAR2(20 BYTE), 
	"GENRE" VARCHAR2(20 BYTE), 
	"DESCRIPTION" VARCHAR2(100 CHAR), 
	"DUREE" VARCHAR2(20 BYTE), 
	"DATE_SORTIE" DATE
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table POINT
--------------------------------------------------------

  CREATE TABLE "DORSAF"."POINT" 
   (	"NOM" VARCHAR2(20 BYTE), 
	"ADRESSE" VARCHAR2(20 BYTE), 
	"TEL" NUMBER, 
	"REFERENCE" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table POSTE
--------------------------------------------------------

  CREATE TABLE "DORSAF"."POSTE" 
   (	"NOM" VARCHAR2(20 BYTE), 
	"ID" NUMBER, 
	"NBRH" NUMBER, 
	"SALAIRE" NUMBER
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table PROJECTION
--------------------------------------------------------

  CREATE TABLE "DORSAF"."PROJECTION" 
   (	"NUM_PROJECTION" NUMBER(*,0), 
	"ID" NUMBER(*,0), 
	"DATE_PROJECTION" DATE, 
	"NUM_SALLE" NUMBER(*,0), 
	"CAPACITE_SALLE" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table RES
--------------------------------------------------------

  CREATE TABLE "DORSAF"."RES" 
   (	"NBR_TICKET" NUMBER, 
	"NOM_RESERVATION" VARCHAR2(20 BYTE), 
	"NUM_RESERVATION" VARCHAR2(20 BYTE), 
	"TEXT" VARCHAR2(20 BYTE), 
	"DATE_RESERVATION" VARCHAR2(20 BYTE), 
	"NOM_OFFRE" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Table TABLE1
--------------------------------------------------------

  CREATE TABLE "DORSAF"."TABLE1" 
   (	"NOM_OFFRE" VARCHAR2(20 BYTE), 
	"TYPE" VARCHAR2(20 BYTE), 
	"DELAI" VARCHAR2(20 BYTE), 
	"COMMENT_" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into DORSAF.ABONNEMENT
SET DEFINE OFF;
REM INSERTING into DORSAF.BILLET
SET DEFINE OFF;
REM INSERTING into DORSAF.CLIENT
SET DEFINE OFF;
REM INSERTING into DORSAF.EMPLOYE
SET DEFINE OFF;
REM INSERTING into DORSAF.FILM
SET DEFINE OFF;
Insert into DORSAF.FILM (ID,NOM,GENRE,DESCRIPTION,DUREE,DATE_SORTIE) values ('12','df','Horreur','df','2h20m',to_date('01/01/00','DD/MM/RR'));
Insert into DORSAF.FILM (ID,NOM,GENRE,DESCRIPTION,DUREE,DATE_SORTIE) values ('98','batman','Action','okey','2h20',to_date('02/12/14','DD/MM/RR'));
Insert into DORSAF.FILM (ID,NOM,GENRE,DESCRIPTION,DUREE,DATE_SORTIE) values ('3','dorsaf','Comedie','d','2h50',to_date('01/01/12','DD/MM/RR'));
REM INSERTING into DORSAF.POINT
SET DEFINE OFF;
Insert into DORSAF.POINT (NOM,ADRESSE,TEL,REFERENCE) values ('d','d','123','123');
REM INSERTING into DORSAF.POSTE
SET DEFINE OFF;
Insert into DORSAF.POSTE (NOM,ID,NBRH,SALAIRE) values ('admin','123','2','22');
REM INSERTING into DORSAF.PROJECTION
SET DEFINE OFF;
Insert into DORSAF.PROJECTION (NUM_PROJECTION,ID,DATE_PROJECTION,NUM_SALLE,CAPACITE_SALLE) values ('150','3',to_date('28/12/20','DD/MM/RR'),'6','50');
Insert into DORSAF.PROJECTION (NUM_PROJECTION,ID,DATE_PROJECTION,NUM_SALLE,CAPACITE_SALLE) values ('12','12',to_date('22/12/20','DD/MM/RR'),'1','20');
Insert into DORSAF.PROJECTION (NUM_PROJECTION,ID,DATE_PROJECTION,NUM_SALLE,CAPACITE_SALLE) values ('85','98',to_date('03/01/21','DD/MM/RR'),'3','80');
Insert into DORSAF.PROJECTION (NUM_PROJECTION,ID,DATE_PROJECTION,NUM_SALLE,CAPACITE_SALLE) values ('11','12',to_date('06/01/20','DD/MM/RR'),'1','1');
REM INSERTING into DORSAF.RES
SET DEFINE OFF;
REM INSERTING into DORSAF.TABLE1
SET DEFINE OFF;
--------------------------------------------------------
--  DDL for Index PROJECTION_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."PROJECTION_PK" ON "DORSAF"."PROJECTION" ("NUM_PROJECTION") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index CLIENT_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."CLIENT_PK" ON "DORSAF"."CLIENT" ("ID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index RESERVATION_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."RESERVATION_PK" ON "DORSAF"."RES" ("NBR_TICKET") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index TABLE1_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."TABLE1_PK" ON "DORSAF"."TABLE1" ("NOM_OFFRE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index POSTE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."POSTE_PK" ON "DORSAF"."POSTE" ("ID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index POINT_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."POINT_PK" ON "DORSAF"."POINT" ("REFERENCE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index TICKET_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."TICKET_PK" ON "DORSAF"."BILLET" ("REFERENCE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index FILM_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."FILM_PK" ON "DORSAF"."FILM" ("ID") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index ABONNEMENT_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."ABONNEMENT_PK" ON "DORSAF"."ABONNEMENT" ("NUMERO") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Index EMPLOYE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "DORSAF"."EMPLOYE_PK" ON "DORSAF"."EMPLOYE" ("CIN") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  Constraints for Table PROJECTION
--------------------------------------------------------

  ALTER TABLE "DORSAF"."PROJECTION" ADD CONSTRAINT "PROJECTION_PK" PRIMARY KEY ("NUM_PROJECTION")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
  ALTER TABLE "DORSAF"."PROJECTION" MODIFY ("NUM_PROJECTION" NOT NULL ENABLE);
--------------------------------------------------------
--  Constraints for Table ABONNEMENT
--------------------------------------------------------

  ALTER TABLE "DORSAF"."ABONNEMENT" MODIFY ("ID" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."ABONNEMENT" MODIFY ("NUMERO" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."ABONNEMENT" ADD CONSTRAINT "ABONNEMENT_PK" PRIMARY KEY ("NUMERO")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
--------------------------------------------------------
--  Constraints for Table POSTE
--------------------------------------------------------

  ALTER TABLE "DORSAF"."POSTE" MODIFY ("SALAIRE" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."POSTE" MODIFY ("NBRH" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."POSTE" MODIFY ("NOM" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."POSTE" ADD CONSTRAINT "POSTE_PK" PRIMARY KEY ("ID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
--------------------------------------------------------
--  Constraints for Table RES
--------------------------------------------------------

  ALTER TABLE "DORSAF"."RES" MODIFY ("NBR_TICKET" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."RES" ADD CONSTRAINT "RESERVATION_PK" PRIMARY KEY ("NBR_TICKET")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
--------------------------------------------------------
--  Constraints for Table CLIENT
--------------------------------------------------------

  ALTER TABLE "DORSAF"."CLIENT" MODIFY ("ID" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."CLIENT" ADD CONSTRAINT "CLIENT_PK" PRIMARY KEY ("ID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
--------------------------------------------------------
--  Constraints for Table BILLET
--------------------------------------------------------

  ALTER TABLE "DORSAF"."BILLET" MODIFY ("PRIX" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."BILLET" MODIFY ("CATEGORIE" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."BILLET" ADD CONSTRAINT "TICKET_PK" PRIMARY KEY ("REFERENCE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
  ALTER TABLE "DORSAF"."BILLET" MODIFY ("REFERENCE" NOT NULL ENABLE);
--------------------------------------------------------
--  Constraints for Table TABLE1
--------------------------------------------------------

  ALTER TABLE "DORSAF"."TABLE1" MODIFY ("NOM_OFFRE" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."TABLE1" ADD CONSTRAINT "TABLE1_PK" PRIMARY KEY ("NOM_OFFRE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
--------------------------------------------------------
--  Constraints for Table EMPLOYE
--------------------------------------------------------

  ALTER TABLE "DORSAF"."EMPLOYE" ADD CONSTRAINT "EMPLOYE_PK" PRIMARY KEY ("CIN")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
  ALTER TABLE "DORSAF"."EMPLOYE" MODIFY ("POSTE" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."EMPLOYE" MODIFY ("CIN" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."EMPLOYE" MODIFY ("MAIL" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."EMPLOYE" MODIFY ("PRENOM" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."EMPLOYE" MODIFY ("NOM" NOT NULL ENABLE);
--------------------------------------------------------
--  Constraints for Table FILM
--------------------------------------------------------

  ALTER TABLE "DORSAF"."FILM" ADD CONSTRAINT "FILM_PK" PRIMARY KEY ("ID")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
--------------------------------------------------------
--  Constraints for Table POINT
--------------------------------------------------------

  ALTER TABLE "DORSAF"."POINT" MODIFY ("ADRESSE" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."POINT" MODIFY ("REFERENCE" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."POINT" MODIFY ("TEL" NOT NULL ENABLE);
  ALTER TABLE "DORSAF"."POINT" ADD CONSTRAINT "POINT_PK" PRIMARY KEY ("REFERENCE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
  ALTER TABLE "DORSAF"."POINT" MODIFY ("NOM" NOT NULL ENABLE);
--------------------------------------------------------
--  Ref Constraints for Table ABONNEMENT
--------------------------------------------------------

  ALTER TABLE "DORSAF"."ABONNEMENT" ADD CONSTRAINT "ABONNEMENT_FK1" FOREIGN KEY ("ID")
	  REFERENCES "DORSAF"."CLIENT" ("ID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table EMPLOYE
--------------------------------------------------------

  ALTER TABLE "DORSAF"."EMPLOYE" ADD CONSTRAINT "EMPLOYE_FK1" FOREIGN KEY ("POSTE")
	  REFERENCES "DORSAF"."POSTE" ("ID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table PROJECTION
--------------------------------------------------------

  ALTER TABLE "DORSAF"."PROJECTION" ADD CONSTRAINT "PROJECTION_FK1" FOREIGN KEY ("ID")
	  REFERENCES "DORSAF"."FILM" ("ID") ENABLE;
--------------------------------------------------------
--  Ref Constraints for Table RES
--------------------------------------------------------

  ALTER TABLE "DORSAF"."RES" ADD CONSTRAINT "RESERVATION_FK1" FOREIGN KEY ("NOM_OFFRE")
	  REFERENCES "DORSAF"."TABLE1" ("NOM_OFFRE") ENABLE;
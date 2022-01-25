#define TAILLE_MAX 100
#define TAILLE_MIN 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct enterprise
{
  char name[TAILLE_MIN];
  char mail[TAILLE_MIN];
};

struct teacher
{
  char name[TAILLE_MIN];
  char surname[TAILLE_MIN];
  char date[TAILLE_MIN];
};

struct intern
{
  char name[TAILLE_MIN];
  char surname[TAILLE_MIN];
  long salaire;
  long level; // niveau d'étude universitaire
  long time; // duree du stage
  struct teacher prof;
  struct enterprise entreprise;
};

typedef struct teacher teacher; // structure professeur
typedef struct enterprise enterprise; // structure entreprise
typedef struct intern intern; // structure stagiaire

void del(char *word); // supprimer le caractère de retour à la ligne de fgets
void menu(int *bool);
void working_file(intern var);
void save_intern(); // enregistrer des stagiaires
void modify_intern(); // modifier les infos d'un stagiaire
void delete_intern(); // supprimer un stagiaire
// int delete_line(char *file_name,int line); // supprimer une ligne dans un fichier
int nbr_lines(char *file_name); // donner le nombre de ligne d'un fichier
void show_intern(intern var); // afficher un stagiaire
void show_interns(); // afficher tout les stagiaires
void intern_teacher(); // afficher les stagiaires dont un professeur est responsable
void intern_enterprise(); // afficher les stagiaires appartenant à la meme entreprise
void teacher_date(); // afficher les dates de visite d'un professeur
void intern_intern(); // fonction pour l'affichage d'un stagiare

int main()
{
  int bool=1;

  while(bool)
    menu(&bool);
  
  return 0;
}

void del(char *word)
{
  char *caract=strchr(word,'\n');
  if(caract)
    *caract='\0';
}

void save_intern()
{
  FILE *file=NULL;
  int choix,i;
  intern var;
  
  file=fopen("stagiaires.dat","a");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("1-1 *---> Enregistrer un stagiaire:\n");
  printf("Combien de stagiares voulez-vous enregistrer:");
  scanf("%d",&choix);
  getchar();
  for(i=0;i<choix;i++)
    {
      printf("\n\tNom:");
      fgets(var.name,TAILLE_MIN,stdin);
      del(var.name);
      printf("\n\tPrenom:");
      fgets(var.surname,TAILLE_MIN,stdin);
      del(var.surname);
      printf("\n\tSalaire:");
      scanf("%ld",&var.salaire);
      getchar();
      printf("\n\tNiveau d'étude(en année):");
      scanf("%ld",&var.level);
      getchar();
      printf("\n\tDuree de stage:");
      scanf("%ld",&var.time);
      getchar();
      printf("\n\tProfesseur:");
      printf("\n\t\tNom:");
      fgets(var.prof.name,TAILLE_MIN,stdin);
      del(var.prof.name);
      printf("\n\t\tPrenom:");
      fgets(var.prof.surname,TAILLE_MIN,stdin);
      del(var.prof.surname);
      printf("\n\t\tDate de visite:");
      fgets(var.prof.date,TAILLE_MIN,stdin);
      del(var.prof.date);
      printf("\n\tEntreprise:");
      printf("\n\t\tNom:");
      fgets(var.entreprise.name,TAILLE_MIN,stdin);
      del(var.entreprise.name);
      printf("\n\t\tMail:");
      fgets(var.entreprise.mail,TAILLE_MIN,stdin);
      del(var.entreprise.mail);

      fprintf(file,"%s,%s,%ld,%ld,%ld,%s,%s,%s,%s,%s\n",var.name,var.surname,var.salaire,var.level,var.time,var.prof.name,var.prof.surname,var.prof.date,var.entreprise.name,var.entreprise.mail);
    }
  
  printf("Stagiaires enregistrer avec succès\n");
  fclose(file);
}

void show_intern(intern var)
{
  printf("Stagiaire \"%s %s\":\n",var.name,var.surname);
  printf("\tNom: %s\n",var.name);
  printf("\tPrenom: %s\n",var.surname);
  printf("\tSalaire: %ld\n",var.salaire);
  printf("\tNiveau d'etude(en année): %ld\n",var.level);
  printf("\tDurée de stage(en mois): %ld\n",var.time);
  printf("\tProfesseur de suivie:\n");
  printf("\t\tNom: %s\n",var.prof.name);
  printf("\t\tPrenom: %s\n",var.prof.surname);
  printf("\t\tDate de visite(jj/mm/aa): %s\n",var.prof.date);
  printf("\tEntreprise de stage:\n");
  printf("\t\tNom: %s\n",var.entreprise.name);
  printf("\t\tMail: %s\n",var.entreprise.mail);
}

void menu(int *bool)
{
  static int choix_menu=0;
  int choix=0;

  printf("##############################\n");
  printf("#      Bienvenue sur le      #\n");
  printf("#   gestionnaire de stage    #\n");
  printf("##############################\n");
  printf("\n");
  printf("1.Gérer les stagiaires\n2.Visualiser les stagiaires\n3.Quitter\n\n");
  //choix=0;
  while(choix_menu<1||choix_menu>4)
    {
      printf("Quel est votre choix:");
      scanf("%d",&choix_menu);
      getchar();
    }
  switch(choix_menu)
    {
    case 1:
      choix=0;
      printf("1 *---> Gérer les stagiaires:\n\t1.Enregistrer des stagiaires\n\t2.Modifier les infos d'un stagiaires\n\t3.Supprimer un stagiaire\n\t4.Retour\n");
      while(choix<1||choix>5)
	{
	  printf("Quel est votre choix:");
	  scanf("%d",&choix);
	  getchar();
	  printf("\n");
	}
      switch(choix)
	{
	case 1:
	  save_intern();
	  break;
	case 2:
	  modify_intern();
	  break;
	case 3:
	  delete_intern();
	  break;
	case 4:
	  choix_menu=0;
	  break;
	}
      break;
    case 2:
      choix=0;
      printf("2 *---> Visualiser les stagiares:\n\t1.Liste des stagiaires\n\t2.Liste des stagiaires par enseignant\n\t3.Liste des stagiaires par entreprise");
      printf("\n\t4.Lister les informations d'un stagiaire\n\t5.Lister les dates de visite d'un enseignant\n\t6.Retour\n");
      while(choix<1||choix>7)
	{
	  printf("Quel est votre choix:");
	  scanf("%d",&choix);
	  getchar();
	  printf("\n");
	}
      switch(choix)
	{
	case 1:
	  show_interns();
	  break;
	case 2:
	  intern_teacher();
	  break;
	case 3:
	  intern_enterprise();
	  break;
	case 4:
	  intern_intern();
	  break;
	case 5:
	  teacher_date();
	  break;
	case 6:
	  choix_menu=0;
	  break;
	}
      break;
    case 3:
      printf("3 *---> Quitter:\n\tMerci d'avoir utiliser notre programme.\n\n");
      printf("  --------> A bientot <--------  \n");
      *bool=0;
      break;
    }
}


void modify_intern()
{
  int i,caract=0,bool=1,choix;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="",name[TAILLE_MIN]="",surname[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("Entrez le nom du stagiaire:");
  fgets(name,TAILLE_MIN,stdin);
  del(name);
  printf("Entrez le prenom du stagiaire:");
  fgets(surname,TAILLE_MIN,stdin);
  del(surname);
  printf("\n");
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(!strcmp(name,var.name)&&!strcmp(surname,var.surname))
	{
	  choix=0;
	  bool=0;
	  printf("Quel informations voulez vous modifier:");
	  printf("\n\t1.Nom\n\t2.Prenom\n\t3.salaire\n\t4.niveau d'etude\n\t5.Duree du stage\n\t6.Nom du professeur\n\t");
	  printf("7.Prenom du professeur\n\t8.Date de visite du professeur\n\t9.Nom de l'entreprise\n\t10.Mail de l'entreprise\n");
	  while(choix<1||choix>10)
	    {
	      printf("Quel est votre choix:");
	      scanf("%d",&choix);
	      getchar();
	      printf("\n");
	    }
	  switch(choix)
	    {
	    case 1:
	      printf("Nouveau nom:");
	      fgets(var.name,TAILLE_MIN,stdin);
	      del(var.name);
	      break;
	    case 2:
	      printf("Nouveau prenom:");
	      fgets(var.surname,TAILLE_MIN,stdin);
	      del(var.surname);
	      break;
	    case 3:
	      printf("Nouveau salaire:");
	      scanf("%ld",&var.salaire);
	      getchar();
	      break;
	    case 4:
	      printf("Nouveau niveau:");
	      scanf("%ld",&var.level);
	      getchar();
	      break;
	    case 5:
	      printf("Nouvelle duree:");
	      scanf("%ld",&var.time);
	      getchar();
	      break;
	    case 6:
	      printf("Nouveau nom:");
	      fgets(var.prof.name,TAILLE_MIN,stdin);
	      del(var.prof.name);
	      break;
	    case 7:
	      printf("Nouveau prenom:");
	      fgets(var.prof.surname,TAILLE_MIN,stdin);
	      del(var.prof.surname);
	      break;
	    case 8:
	      printf("Nouvelle date:");
	      fgets(var.prof.date,TAILLE_MIN,stdin);
	      del(var.prof.date);
	      break;
	    case 9:
	      printf("Nouveau nom:");
	      fgets(var.entreprise.name,TAILLE_MIN,stdin);
	      del(var.entreprise.name);
	      break;
	    case 10:
	      printf("Nouveau mail:");
	      fgets(var.entreprise.mail,TAILLE_MIN,stdin);
	      del(var.entreprise.mail);
	      break;
	    }
	  working_file(var);
	}
      else
	{
	  working_file(var);
	}
      caract=fgetc(file);
    }
  if(bool)
    {
      printf("Aucun stagiaire du nom de \"%s %s\"\n",name,surname);
      remove("tmp_file.dat");
    }
  else
    {
      FILE *tmp_file=NULL;
      
      fclose(file);
      file=fopen("stagiaires.dat","w+");
      if(!file)
	{
	  fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
	  exit(EXIT_FAILURE);
	}
      tmp_file=fopen("tmp_file.dat","r");
      if(!tmp_file)
	{
	  fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
	  exit(EXIT_FAILURE);
	}
      caract=fgetc(tmp_file);
      while(caract!=EOF)
	{
	  fputc(caract,file);
	  caract=fgetc(tmp_file);
	}
      fclose(tmp_file);
      remove("tmp_file.dat");

      printf("Informations modifier avec succès\n\n");
    }
  fclose(file);
}

void delete_intern()
{
  int i,caract=0,bool=1;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="",name[TAILLE_MIN]="",surname[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("Entrez le nom du stagiaire:");
  fgets(name,TAILLE_MIN,stdin);
  del(name);
  printf("Entrez le prenom du stagiaire:");
  fgets(surname,TAILLE_MIN,stdin);
  del(surname);
  printf("\n");
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(!strcmp(name,var.name)&&!strcmp(surname,var.surname))
	bool=0;
      else
	{
	  working_file(var);
	}
      caract=fgetc(file);
    }
  if(bool)
    {
      printf("Aucun stagiaire du nom de \"%s %s\"\n",name,surname);
      remove("tmp_file.dat");
    }
  else
    {
      bool=1;
      FILE *tmp_file=NULL;
      
      fclose(file);
      file=fopen("stagiaires.dat","w+");
      if(!file)
	{
	  fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
	  exit(EXIT_FAILURE);
	}
      tmp_file=fopen("tmp_file.dat","r");
      if(!tmp_file)
	{
	  printf("Le stagiaire \"%s %s\" à bien été supprimer\n\n",name,surname);
	  bool=0;
	}
      if(bool)
	{
	  caract=fgetc(tmp_file);
	  while(caract!=EOF)
	    {
	      fputc(caract,file);
	      caract=fgetc(tmp_file);
	    }
	  fclose(tmp_file);
	  remove("tmp_file.dat");
	  printf("Le stagiaire \"%s %s\" à bien été supprimer\n\n",name,surname);
	}
    }
  fclose(file);
}

void intern_teacher()
{
  int i,caract=0,bool=1;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="",name[TAILLE_MIN]="",surname[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("Entrez le nom de l'enseignant:");
  fgets(name,TAILLE_MIN,stdin);
  del(name);
  printf("Entrez le prenom de l'enseignant:");
  fgets(surname,TAILLE_MIN,stdin);
  del(surname);
  printf("\n");
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(!strcmp(name,var.prof.name)&&!strcmp(surname,var.prof.surname))
	{
	  bool=0;
	  show_intern(var);
	}
      caract=fgetc(file);
    }
  if(bool)
    printf("Aucun stagiaire n'est sous la charge du professeur \"%s %s\"\n\n",name,surname);
  
  fclose(file);
}

void intern_enterprise()
{
  int i,caract=0,bool=1;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="",name[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("Entrez le nom de l'entreprise:");
  fgets(name,TAILLE_MIN,stdin);
  del(name);
  printf("\n");
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(!strcmp(name,var.entreprise.name))
	{
	  bool=0;
	  show_intern(var);
	}
      caract=fgetc(file);
    }
  if(bool)
    printf("Aucun stagiaire n'est dans l'entreprise \"%s\"\n\n",name);
  
  fclose(file);
}

void teacher_date()
{
  int i,caract=0,bool=1;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="",name[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("Entrez la date de visite recherché(jj/mm/aa):");
  fgets(name,TAILLE_MIN,stdin);
  del(name);
  printf("\n");
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(!strcmp(name,var.prof.date))
	{
	  bool=0;
	  show_intern(var);
	}
      caract=fgetc(file);
    }
  if(bool)
    printf("Aucune date de visite ne correspond à la date \"%s\"\n\n",name);
  
  fclose(file);
}

void intern_intern()
{
  int i,caract=0,bool=1;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="",name[TAILLE_MIN]="",surname[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  printf("Entrez le nom du stagiaire:");
  fgets(name,TAILLE_MIN,stdin);
  del(name);
  printf("Entrez le prenom du stagiaire:");
  fgets(surname,TAILLE_MIN,stdin);
  del(surname);
  printf("\n");
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(!strcmp(name,var.name)&&!strcmp(surname,var.surname))
	{
	  bool=0;
	  show_intern(var);
	}
      caract=fgetc(file);
    }
  if(bool)
    printf("Aucun stagiaire sous le nom de \"%s %s\"\n\n",name,surname);
  
  fclose(file);
}
/*
int delete_line(char *file_name,int line)
{
  FILE *tmp_file=NULL,*file=NULL;
  int caract=0,nbr=0;

  tmp_file=fopen("tmp_file.del","w");
  nbr=nbr_lines(file_name);
  file=fopen(file_name,"r");
  if(!(tmp_file&&file))
    return 0;
  if(line<=nbr)
    {
      caract=fgetc(file);
      for(nbr=1;nbr<line;caract=fgetc(file))
	{
	  fputc(caract,tmp_file);
	  if(caract=='\n')
	    nbr++;
	}
      fseek(file,-1,SEEK_CUR);
      while(fgetc(file)!='\n');
      caract=fgetc(file);
      while(caract!=EOF)
	{
	  fputc(caract,tmp_file);
	  caract=fgetc(file);
	}
      fclose(file);
      fclose(tmp_file);
      tmp_file=fopen("tmp_file.del","r");
      file=fopen(file_name,"w+");
      if(!(tmp_file&&file))
	return 0;
      caract=fgetc(tmp_file);
      while(caract!=EOF)
	{
	  fputc(caract,file);
	  caract=fgetc(tmp_file);
	}
      fclose(file);
      fclose(tmp_file);
      remove("tmp_file.del");
      return 1;
    }
  else
    {
      fclose(tmp_file);
      fclose(file);
      remove("tmp_file.del");
      return 0;
    }

}
*/
int nbr_lines(char *file_name)
{
  int lines=0,caract=0;
  FILE *file=NULL;

  file=fopen(file_name,"r");
  if(!file)
    return 0;
  caract=fgetc(file);
  while(caract!=EOF)
    {
      if(caract=='\n')
	lines++;
      caract=fgetc(file);
    }
  fclose(file);

  return lines;
}

void show_interns()
{
  int i,caract=0;
  FILE *file=NULL;
  intern var;
  char tmp_chaine[TAILLE_MIN]="";
  
  file=fopen("stagiaires.dat","r");
  if(!file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  caract=fgetc(file);
  while(caract!=EOF)
    {
      for(i=0;caract!=',';i++)
	{
	  var.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.salaire=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.level=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  tmp_chaine[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    tmp_chaine[i+1]='\0';
	}
      var.time=strtol(tmp_chaine,NULL,10);
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.surname[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.surname[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.prof.date[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.prof.date[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!=',';i++)
	{
	  var.entreprise.name[i]=caract;
	  caract=fgetc(file);
	  if(caract==',')
	    var.entreprise.name[i+1]='\0';
	}
      caract=fgetc(file);
      for(i=0;caract!='\n';i++)
	{
	  var.entreprise.mail[i]=caract;
	  caract=fgetc(file);
	  if(caract=='\n')
	    var.entreprise.mail[i+1]='\0';
	}
      if(caract!=EOF)
	show_intern(var);
      caract=fgetc(file);
    }
  fclose(file);
}
void working_file(intern var)
{
  FILE *tmp_file=NULL;

  tmp_file=fopen("tmp_file.dat","a");
  if(!tmp_file)
    {
      fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
      exit(EXIT_FAILURE);
    }
  fprintf(tmp_file,"%s,%s,%ld,%ld,%ld,%s,%s,%s,%s,%s\n",var.name,var.surname,var.salaire,var.level,var.time,var.prof.name,var.prof.surname,var.prof.date,var.entreprise.name,var.entreprise.mail);

  fclose(tmp_file);
}

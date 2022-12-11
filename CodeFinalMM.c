#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define N 20

int verif_lettre(char a){
    /*fonction qui vérifie si la lettre est bien en majuscule */
    int b;
    b = a;

    if(b>=65 && b<=90){
        return 0;
    }
    else{
        return 1;
    } 
}

void sauvegarde(int taille, char grille[][taille],int compteur,char stockage_mot[][taille+1]){
    /*fonction qui sauvegarde la taille de la grille, le nombre de mot a trouver, les mots a trouvé , et la grille du jeu dans un fichier.txt */
    FILE* fichier;
    
    fichier=fopen("sauvegarde.txt", "w");
    if (fichier != NULL){
                        
        int i, j;
        fprintf(fichier, "La taille de la grille est : %d\n", taille);
        fprintf(fichier,"Le nombre de mots cachés est : %d\n",compteur);
        for(i = 0; i < compteur; i++){
            
                fprintf(fichier,"%s ", stockage_mot[i]); 

            } 
	fprintf(fichier,"\n");
        


        for (i = 0; i < taille; i++) {
            for (j = 0; j < taille; j++) {
                fprintf(fichier, "%c ",grille[i][j]);
            }
            fprintf(fichier, "\n");
        }
        printf("Partie sauvegardée !\n");
    }

    fclose(fichier);

}

int scan_lettres(int taille,char mot[taille]){
    /*fonction qui prend un mot en paramètre et qui vérifie si chaque lettre est en majuscule*/
    int i;

    for (i = 0;mot[i]!='\0';i++){


        if (verif_lettre(mot[i]) == 1){

            return 1;
        }

    }
    if (mot[i] == '\0'){

        return 0;
    }
}


int Ini_taille(void){
    /* fonction qui initialise la taille de la grille et la renvoie */
    int taille;
    printf("saisir taille de la grille");
    scanf("%d",&taille);
    while(taille>20 || taille<1){
    printf("Erreur , veuillez saisir une taille valide de la grille");
    scanf("%d",&taille);
    }
    return taille; 
}

int y_final(int taille,char grille[][taille] , int direction, int x,int y, char mot[]){
    /*fonction qui renvoie le y (ordonné) de la derniere lettre du mot placer dans la grille */
    int i;
    int cmpt=0;
    int x_fin;
    int y_fin;

    for(i=0,cmpt=0;mot[i]!='\0';i++,cmpt++){
        switch(direction){
            case(0):x_fin= x-i;
                    y_fin= y-i;
                    break;

            case(1):x_fin= x-i;
                    y_fin= y;
                    break;

            case(2):x_fin= x-i;
                    y_fin= y+i;
                    break;

            case(4):x_fin= x;
                    y_fin= y+i;
                    break;

            case(7):x_fin= x+i;
                    y_fin= y+i;
                    break;

            case(6):x_fin= x+i;
                    y_fin= y;
                    break;

            case(5):x_fin= x+i;
                    y_fin= y-i;
                    break;

            case(3):x_fin= x;
                    y_fin= y-i;
                    break;

        }
    }

    return y_fin;

}

int x_final(int taille,char grille[][taille] , int direction, int x,int y, char mot[]){
    /*fonction qui renvoie le x (abscisse) de la derniere lettre du mot placer dans la grille */

    int i;
    int cmpt=0;
    int x_fin;
    int y_fin;

    for(i=0,cmpt=0;mot[i]!='\0';i++,cmpt++){
        switch(direction){
            case(0):x_fin= x-i;
                    y_fin= y-i;
                    break;

            case(1):x_fin= x-i;
                    y_fin= y;
                    break;

            case(2):x_fin= x-i;
                    y_fin= y+i;
                    break;

            case(4):x_fin= x;
                    y_fin= y+i;
                    break;

            case(7):x_fin= x+i;
                    y_fin= y+i;
                    break;

            case(6):x_fin= x+i;
                    y_fin= y;
                    break;

            case(5):x_fin= x+i;
                    y_fin= y-i;
                    break;

            case(3):x_fin= x;
                    y_fin= y-i;
                    break;

        }
    }

    return x_fin;

}

void remplir(int taille,char grille[][taille] , int direction, int x,int y, char mot[]){
    /*fonction qui remplie la grille avec le mot entré en fonction des coordonnées et d'une direction */
    int i;
    int cmpt=0;

    for(i=0,cmpt=0;mot[i]!='\0';i++,cmpt++){
        switch(direction){
            case(0):grille[x-i][y-i]=mot[cmpt];break;
            case(1):grille[x-i][y]=mot[cmpt];break;
            case(2):grille[x-i][y+i]=mot[cmpt];break;
            case(4):grille[x][y+i]=mot[cmpt];break;
            case(7):grille[x+i][y+i]=mot[cmpt];break;
            case(6):grille[x+i][y]=mot[cmpt];break;
            case(5):grille[x+i][y-i]=mot[cmpt];break;
            case(3):grille[x][y-i]=mot[cmpt];break;

        }
    }

}


void entrer_mot(char mot[]){
    /*fonction qui permet la saisie d'un mot*/
    printf("saisir un mot en MAJUSCULE: ");
    scanf("%s",mot);

}



void affiche(int taille, char grille[][taille]){
    /*fonction qui affiche la grille du jeu */
	int i, j;
	for(i = 0; i<taille ; i++){
		for(j = 0; j<taille; j++){
			printf("%c|", grille[i][j]);
		}
		printf("\n");
		for(j = 0; j<taille; j++){
			printf("--");
		}
		printf("\n");
	}
	printf("\n");
}

void remplir_lettre_vide(int taille, char tab[][taille]){
    /*fonction qui remplie la grille avec des lettre au hasard en minuscule quand la case est vide */
    int i,j;
    srand(time(NULL));
    char lettre;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            if(tab[i][j]=='.'){
                lettre= rand()%26+97;   //génère une lettre aléatoire
                tab[i][j]=lettre;
            }
}
}
}


int directi(void){
    /*fonction qui permet la saisie d'une direction */
    int d;
    printf("la position initiale etant la croix, saisir une direction par rapport au chiffre\n");
    printf("0 1 2\n");
    printf("3 + 4\n");
    printf("5 6 7\n");
    printf("\n");
    printf("la direction est:");
    scanf("%d",&d);
    return d;
}

int abscisse(void){
    /*fonction qui permet la saisie d'une abscisse*/
    int x;
    printf("entrez l'abscisse");
    scanf("%d",&x);

    return x;

}

int ordonnee(void){
    /*fonction qui permet la saisie d'une ordonnée*/
    int y;
    printf("entrez l'ordonnee");
    scanf("%d",&y);

    return y;
}



void init_grille(int taille, char grille[][taille]){
    /*fonction qui initialise la grille avec des '.' dans chaque case*/
    int i,j;
    for(i=0;i<taille;i++){
        for(j=0;j<taille;j++){
            grille[i][j]='.';
        }

    }

}

int verif(int taille,char grille[][taille] , int direction, int x,int y, char mot[]){
    /*fonction qui vérifie si le mot saisie est en majuscule et possède une taille correct , 
    si ce mot a des coordonnées et une direction valide , et si ce mot n'est pas en conflit avec un autre */
    int post_x;
    int post_y;

    if(strlen(mot)>taille){
        return 1;
    }




    int cmpt;
    int i;
    for(i=0,cmpt=0;mot[i]!='\0';i++,cmpt++){
        switch(direction){
            case(0):if(grille[x-i][y-i]!='.'){return 1;}
                    post_x= x-i;
                    post_y= x-i;
                    break;

            case(1):if(grille[x-i][y]!='.'){return 1;}
                    post_x= x-i;
                    post_y= y;
                    break;

            case(2):if(grille[x-i][y+i]!='.'){return 1;}
                    post_x= x-i;
                    post_y= y+i;
                    break;

            case(4):if(grille[x][y+i]!='.'){return 1;}
                    post_x= x;
                    post_y= y+1;
                    break;

            case(7):if(grille[x+i][y+i]!='.'){return 1;}
                    post_x= x+i;
                    post_y= y+i;
                    break;

            case(6):if(grille[x+i][y]!='.'){return 1;}
                    post_x= x+i;
                    post_y= y;
                    break;

            case(5):if(grille[x+i][y-i]!='.'){return 1;}
                    post_x= x+i;
                    post_y= y-i;
                    break;
            case(3):if(grille[x][y-i]!='.'){return 1;}
                    post_x= x;
                    post_y= y-i;
                    break;


        }

    }

    if(taille<post_x || taille<post_y || post_y<0 || post_x<0){
        return 1;
    }

    else{
        return 0;
    }
}






int main(void){
    int taille=Ini_taille();
    char grille[taille][taille];
    init_grille(taille,grille);                    //initialisation de la grille
    char mot[taille];

    char stockage_mot[taille + 1][taille + 1];
    int stockage_x_depart[taille];
    int stockage_y_depart[taille];
    int stockage_x_arrive[taille];
    int stockage_y_arrive[taille];

    int max_mots;
    int v;
    int s;
    int compteur=0;
    for(max_mots=0;max_mots<taille;max_mots++){
        entrer_mot(mot);
        int y=abscisse();
        int x=ordonnee();
        int direction=directi();
        s=scan_lettres(taille,mot);
        v=verif(taille,grille,direction,x,y,mot);  // vérification si le mot est valide , renvoi 0 si il est valide ou 1 si il le ne est pas.
        if(v==0 && s==0){
            remplir(taille,grille,direction,x,y,mot);  // remplie la grille avec le mot
            strcpy(stockage_mot[compteur],mot);
            
            stockage_x_depart[compteur]=x;
            stockage_y_depart[compteur]=y;
            stockage_x_arrive[compteur]=x_final(taille,grille,direction,x,y,mot);
            stockage_y_arrive[compteur]=y_final(taille,grille,direction,x,y,mot);
            compteur=compteur+1;


        }
        affiche(taille,grille); // affiche la grille

    }


    remplir_lettre_vide(taille,grille); //remplie les cases vide de la grille avec une lettre aléatoire
    
    affiche(taille,grille); // affiche la grille

    int numero[compteur];            // tableau 'compteur' qui permet la vérification de victoire a la fin du jeu 
    for(int i=0;i<compteur;i++){
        numero[i]=i;
    }
    

    for(int i=0;i<compteur;i++){
        printf("%d->%s \n",numero[i],stockage_mot[i]);
    }

    int numj;
    int xdj;
    int ydj;
    int xaj;
    int yaj;
    int i;
    

    while(numj>0 || numj<compteur){  //cette boucle permet de jouer au jeu 
		
	    int sortie=0;

        printf("selectionnez le numero du mot trouvé (ou entrez un numero négatif pour abandonner)\n");
        scanf("%d",&numj);
        if(numj<0){
		    break;
		    }
     
        printf("selectionnez le x de depart\n");
        scanf("%d",&xdj);
        printf("selectionnez le y de depart\n");
        scanf("%d",&ydj);
        printf("selectionnez le x de d'arrivé\n");
        scanf("%d",&yaj);
        printf("selectionnez le y de d'arrivé\n");
        scanf("%d",&xaj);
		printf("\n");
    

        if(ydj==stockage_x_depart[numj] && xdj==stockage_y_depart[numj] && xaj==stockage_x_arrive[numj] && yaj==stockage_y_arrive[numj]){
            numero[numj]= -1;
            for (i = 0; stockage_mot[numj][i] != '\0'; i++) {
                if(stockage_mot[numj][i] >= 'A' && stockage_mot[numj][i] <= 'Z') {
                  stockage_mot[numj][i] = stockage_mot[numj][i] + 32;
                }
            }
                printf("MOT TROUVÉ\n");
        }
        else{
            printf("MOT INCORRECT\n");
        }
        
        printf("\n");
        
        affiche(taille,grille);
    
        for(i=0;i<compteur;i++){                       //affiche la liste de mots a trouvé
          if (numero[i] == -1)
            printf("->%s \n",stockage_mot[i]);
          else
            printf("%d->%s \n",numero[i],stockage_mot[i]);
        }
    
        for(i=0;i<compteur;i++){
		    if(numero[i]!=-1){
                sortie=1;
             }

        }
        if(sortie==0){ 
		    break;
	    }
	    
	    
    }
	
	
	printf("\n");
	int verif_victoire=0;
    for(i=0;i<compteur;i++){
        if(numero[i]!=-1){
            verif_victoire=1;

        }
      }
     
     if(verif_victoire==1){
		 printf("PERDU\n");
	 }
	else
	{
		printf("GAGNÉ\n");
	}
    

	sauvegarde(taille,grille,compteur,stockage_mot);


    return 0;
}

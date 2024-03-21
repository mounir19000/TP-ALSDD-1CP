#ifndef SECR
#define SECR

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define LETTER_ALPHABETIC 26

//*--------------------------------------------------- LISTE DES STRUCTURES ---------------------------------------------------*//

struct syllables {  // Un enregistrement qui contient la syllable
    char *syllable; // pointeur vers la syllable
    struct syllables* suivant;  // pointeur vers le maillon suivant de syllable
};

typedef struct syllables* ptrsyllables; // Un type de pointeur vers maillon de syllable

struct words {  // Un enregistrement qui contient le mot
    char mot[25];  // Le mot
    int nb_caractere ;  // Le nombre de caractere du mot
    int nb_consonne ;   // Le nombre de consonne du mot
    int nb_voyelle ;    // Le nombre de voyelle du mot
    int nb_syllable ;   // Le nombre de syllable du mot
    char mot_ordonne[25] ; // Le mot ordonner en ordre alphabetique
    bool ordred ;   // Un boolean qui indique si le mot est ordonne ou non
    struct words* suivant_words; // suivant_words
    struct words* precedent_words; // precedent_words
    struct words* suiv_sous_chaine; // Suivant de question 1
    char indice_sous_chaine; // indice qui aura trois valeurs : 0 --> non lié , 1 --> lié , 2 --> c'est une téte de liste 
    struct words* champ_ed; // Le participe passe de question 2
    struct words* champ_ing; // La forme ing de question 2
    struct words* suiv_anagrm; // Suivant de question 3
    struct words* suiv_prochelex; // Suivant de question 4
    bool fin_prochelex;     //indique si le mot est le maillon de fin de la liste prochelex a laquelle il appartient (si elle existe)
    struct words* suiv_sequence_mots; // Suivant de question 5
    struct words* prec_sequence_mots; // Precedent de question 5
    ptrsyllables tete_syllables;   //tete liste de syllable
};

typedef struct words* ptrwords; // Un type de pointeur vers maillon de mot

struct Lettre { // Un enregistrement qui contient la tete et queue de laa liste de mot qui commance par le meme caractere
    ptrwords tete_mots ; // tete bidirectionnel
    ptrwords queue_mots ; // queue bidirectionnel
    int nb_word ; // le nombre de mots qui commence par cette lettre
};

// extern veut dire une variable externe 
// cette variable est utiliser comme variable globale dans tout le programme

extern struct Lettre T[LETTER_ALPHABETIC]; // Le tableau d'enregistrement 

struct Anagramme // Un enregistrement qui contient la tete de la sous liste d'anagramme
{
    ptrwords tete_liste; // La tete de la sous liste trouver
    int nb_mots; // Le nombre de mots qui sont dans la sous liste liste
};

typedef struct Anagramme* ptrAnagramme; // Un type de pointeur qui point l'entregistrement precedent

extern ptrAnagramme Tab_anagrm; //Tableau qui contient les anagrammes

struct Prochelex // Un enregistrement qui contient la tete de la sous liste de mots proche lexicalement
{
    ptrwords tete_liste; // La tete de la sous liste trouver
    int nb_mots; // Le nombre de mots qui sont dans la sous liste liste
};

typedef struct Prochelex* ptrProchelex; // Un type de pointeur qui point l'entregistrement precedent

extern ptrProchelex Tab_prochelex; //Tableau qui contient les listes des mots proches lexicalement

struct sequence_mots // Un enregistrement qui contient la tete de la sous liste de mots de question 3
{
    ptrwords tete_liste; // La tete de la sous liste trouver
    ptrwords queue_liste; // La queue de la sous liste trouver
    int nb_mots; // Le nombre de mots qui sont dans la sous liste liste
};

typedef struct sequence_mots* ptrSeqmots; // Un type de pointeur qui point l'entregistrement precedent

extern ptrSeqmots Tab_sequences_mots; //Tableau qui contient les listes des sequences de mots formées par l'ajout graduel d'une lettre


struct sous_chaine // Un enregistrement qui contient la tete de la sous liste de mots de question 1
{
    ptrwords tete_liste; // La tete de la sous liste trouver
    int nb_mots; // Le nombre de mots qui sont dans la sous liste liste
};

typedef struct sous_chaine* ptrSousChaine; // Un type de pointeur qui point l'entregistrement precedent

extern ptrSousChaine Tab_sous_chaine; //Tableau qui contient les listes de sous chaine ajouter

extern int size1 , size2 , size3 , size4 , size5 ; // La taile des sous liste cree dans les 5 questions

//*--------------------------------------------------- FONCTIONS PAGE ACCEUIL ------------------------------------------------------*//

// Fonction pour afficher la page d'acceuil
void page_acceuil();

// Fonction pour afficher une barre d'attente
void page_chargement();

//*--------------------------------------------------- FONCTIONS BASE DE DONNEES ------------------------------------------------------*//

//intialisation de la base de donnees
void init_base_donnees(void);

//Fonction qui va reintialiser toutes les structures utiliser dans le programme et les pointeurs de tous les mots également
void reinit_base_donnees(void);

//Lecture de tous les mots du fichier "words.txt" et remplissage de la base de donnees
int Remplir_base_donnees(void);

//ajouter le mot (maillon) dans la liste bidirect correspendante
void ajout_mot(char *ch_mot);

//Fonction qui va créer la liste de syllables pour un mot
void Cree_liste_syl(ptrwords mot , char * ch_syl);

//Fonction qui supprime le mot de la liste a partir d'un pointeur donner
void Supp_mot(ptrwords ptr);

//Recherche un mot introduit par l'utilisateur et renvoie un ptr vers le maillon qui le contient; NIL si il n'existe pas
ptrwords Rech_mot(char ch_mot[25]);

// Supprime tous les caractères non alphabetique d'une chaîne de caractères
void supp_no_alpha(char *chaine);

// Retourne le nombre de caractères alphabétiques dans une chaîne de caractères
int nb_car(char S[25]);

// Retourne le nombre de consonnes dans une chaîne de caractères
int nb_cons(char S[25]);

// Retourne le nombre de voyelles dans une chaîne de caractères
int nb_voy(char S[25]);

// Retourne le nombre de syllabes dans une chaîne de caractères
int nb_syl(char S[25]);

// Vérifie si les caractères d'une chaîne sont ordonnés alphabétiquement
bool isordered(char S[25]);

// Retourne la chaîne de caractères triée par ordre alphabétique (passage par variable)
void ordonne_mot(char S[25]);

//Fonction qui compare deux chaines selon la taille , et selon l'ordre alphabetique si ils ont la meme taille
int str_comp_ordr(char *ch1 , char* ch2); 

//*--------------------------------------------------- MACHINE ABSTRAITE STRUCT WORDS -------------------------------------------------*//
//Alloue un maillon 
void Allouer_mot(ptrwords *p);

//Libere le maillon de mot
void Liberer_mot(ptrwords ptr);

// Affecte un pointeur vers mot dans le champ de suivant du pointeur mot donner
void Aff_Adr_suivant_word(ptrwords ptr, ptrwords suivantptr);

// Affecte un pointeur vers mot dans le champ de precedent du pointeur mot donner
void Aff_Adr_precedent_word(ptrwords ptr, ptrwords precedentptr);

// Affecte un mot dans le champ de mot du pointeur words donner
void Aff_Val_word(ptrwords ptr, char mot[25]);

// Affecte le nombre de caractere dans le champ de nombre de caractere du pointeur words donner
void Aff_Val_nb_car(ptrwords ptr, int val);

// Affecte le nombre de consonne dans le champ de nombre de consonne du pointeur words donner
void Aff_Val_nb_cons(ptrwords ptr, int val);

// Affecte le nombre de voyelle dans le champ de nombre de voyelle du pointeur words donner
void Aff_Val_nb_voy(ptrwords ptr, int val);

// Affecte le nombre de syllable dans le champ de nombre de syllable du pointeur words donner
void Aff_Val_nb_syl(ptrwords ptr, int val);

// Affecte un mot ordonner dans le champ de mot ordoner du pointeur words donner
void Aff_Val_word_ordrer(ptrwords ptr, char mot_ordoner[25]);

// Affecte un bool d'indice dans le champ de l'indice d'ordre du pointeur words donner
void Aff_Val_ordred(ptrwords ptr, bool ordred);

// Fonction qui affect une address au champ tete_syllables du mot de "p"
void Aff_adr_tete_syllables(ptrwords p ,ptrsyllables adr);

// Retourne le mot
char* Valeur_mot(ptrwords ptr);

// Retourne le nombre de caractere
int Valeur_nb_car(ptrwords ptr);

// Retourne le nombre de consonne
int Valeur_nb_cons(ptrwords ptr);

// Retourne le nombre de voyelle
int Valeur_nb_voy(ptrwords ptr);

// Retourne le nombre de syllable
int Valeur_nb_syl(ptrwords ptr);

// Retourne un boolean qui indique si le mot est ordonne
bool Valeur_ordred(ptrwords ptr);

// Retourne le mot ordonne
char* Valeur_mot_ordonne(ptrwords ptr);

// Retourne un pointeur vers le mot suivant
ptrwords Suivant_mot(ptrwords ptr);

// Retourne un pointeur vers le mot precedent
ptrwords Precedent_mot(ptrwords ptr);

// Fonction qui affect une address au champ sous chaine d'un mot
void Aff_adr_sous_chaine(ptrwords ptr1, ptrwords ptr2);

// Fonction qui va affecter au champ d'indice de sous chaine une valeur donner
void Aff_val_indice_sous_chaine(ptrwords p , char c);

// Fonction qui retourne la valeure du champs suivant sous chaine
ptrwords Valeur_sous_chaine(ptrwords p);

// Fonction qui retourne la valeur de l'indice de sous chaine
char Valeur_indice_sous_chaine(ptrwords p);

//Fonction qui donne le suivant dans le champ ed
ptrwords Suivant_ED(ptrwords ptr);

//Fonction qui affecte au champ ED un pointeur
void Aff_adr_ED(ptrwords adr1, ptrwords adr2);

//Fonction qui donne le suivant dans le champ ING
ptrwords Suivant_ING(ptrwords ptr);

//Fonction qui affecte au champ ING un pointeur
void Aff_adr_ING(ptrwords adr1, ptrwords adr2);

//Fonction qui affecte au champ suiv_sequence_mots de "p" un pointeur
void Aff_adr_suiv_sequence_mots(ptrwords p , ptrwords adr);

//Fonction qui affecte au champ prec_sequence_mots de "p" un pointeur
void Aff_adr_prec_sequence_mots(ptrwords p , ptrwords adr);

//Fonction qui donne le champ suiv_sequence_mots du pointeur "p"
ptrwords Suivant_seq(ptrwords p);

//Fonction qui donne le champ prec_sequence_mots du pointeur "p"
ptrwords Precedent_seq(ptrwords p);

//Fonction qui affecte au champ prochelex de "p" un pointeur
void Aff_adr_prochelex(ptrwords p , ptrwords adr);

// Fonction qui retourne la valeur du champ suiv_prochelex de "p"
ptrwords Valeur_suiv_prochelex(ptrwords p);

//Fonction qui affecte au champ fin_prochelex de "p" un booleen
void Aff_val_fin_prochelex(ptrwords p , bool val);

// Fonction qui retourne la valeur du champ fin_prochelex de "p"
bool Valeur_fin_prochelex(ptrwords p);

//Fonction qui affecte au champ anagrm de "p" un pointeur
void Aff_adr_angrm(ptrwords p , ptrwords adr);

//Fonction qui retourne la valeur du champ suiv_anagrm de "p"
ptrwords Valeur_suiv_anagramme(ptrwords p);

//*--------------------------------------------------- MACHINE ABSTRAITE STRUCT SYLLABLES  --------------------------------------------*//

//Fonction qui fait le malloc d'une structure syl pour le pointeur
void Allouer_syl(ptrsyllables *p);

//Fonction qui libere le maillon de syllable
void Liberer_syl(ptrsyllables ptr);

//Fonction qui retourne un pointeur vers la liste de syllables du mot
ptrsyllables Tete_syl(ptrwords ptr);

//Fonction qui retourne un pointeur vers la syllable suivante
ptrsyllables Suivant_syl(ptrsyllables ptr); 

//Fonction qui retourne la chaine syllable
char* Valeur_syl(ptrsyllables ptr);

//Fonction qui affecte un pointeur vers syllable dans le champ de suivant du pointeur syllable donner
void Aff_Adr_syl(ptrsyllables ptr, ptrsyllables suivantptr);

//Fonction qui affecte une syllable dans le champ de syllable du pointeur syllable donner
void Aff_Val_syl(ptrsyllables ptr, char syl[9]);

//*--------------------------------------------------- MACHINE ABSTRAITE QUESTION 1 ---------------------------------------------------*//

// Fonction qui vérifie si str2 est construite en ajoutant un prefix ou sufix ou sous chaine à str1
bool issouschainemadeoff(char str1[25], char str2[25]);

//Fonction qui affiche les listes de sous chaine
void Affiche_sous_chaine(int ty);

// Fonction qui retourne le nombre de mot dans une chaine
int Valeur_nb_mot_sous_chaine(ptrSousChaine p);

// Fonction qui affecte un nombre donné au champ nbmotsouschaine du tableau
void Aff_val_nb_mot_sous_chaine(ptrSousChaine p , int nb);

// Fonction qui va parcourir les mots et cree le tableau des tete de liste
int Cree_tab_sous_chaine();

// Fonction qui va remplire les champs sous chaine
void Remplire_sous_chaine(int* taille);

//*--------------------------------------------------- MACHINE ABSTRAITE QUESTION 2 ---------------------------------------------------*//

// Fonction qui cherche le participe passés d'un mot
ptrwords RechED(ptrwords ptr);

// Fonction qui cherche la forme ING d'un mot
ptrwords RechING(ptrwords ptr);

// Fonction qui va créer les liens de ED et ING
void Remplire_ED_ING(int *Nb_liste_ED_ING);

// Fonction qui va afficher les mot + participe passé + forme ING
void Affiche_mot_ed_ing(int size);

//*--------------------------------------------------- MACHINE ABSTRAITE QUESTION 3 ---------------------------------------------------*//

//Fonction qui retourne vrai si str2 est formée par l'ajout d'une lettre a str1 ; retourne faux sinon
bool isonecharadded(char str1[25], char str2[25]);

//Fonction pour créer toutes les sequences de mots formées par l'ajout graduel d'une lettre et les stocker dans le tableau "Tab_sequences_mots" elle retourne la taille du tableau
void Remplir_sequences_mots(int* size);

//Fonction pour parcourir toute une liste bidirect de sequence de mots formé par l'ajout graduel d'une lettre a partir d'une tete donnée et retourne la taille de la liste dans "taille" ainsi qu'un pointeur vers le maillon ptrwords qui contient la queue en sortie
ptrwords Parcourir_liste_bidirect_seq(ptrwords tete , int* taille);

// Fonction pour afficher les listes de sous sequence
void Affiche_sous_seq(int ty);

//*--------------------------------------------------- MACHINE ABSTRAITE QUESTION 4 ---------------------------------------------------*//

//Fonction pour remplir tout le tableau "Tab_prochelex" et cree toutes les liste des mots proche lexicalement; retourne la taille du tableau (donc le nombre de listes crees) dans size
void Remplir_prochelex(int* size);

//Fonction pour comparer deux mots si ils sont proches lexicalement (si 1 seul caractere est different); retourne la position du caractere qui differe sinon retourne -1
int IsProchelex(char* ch1 , char* ch2);

// Fonction qui affiche les listes des mots proches lexicalement
void Affiche_proche_lex(int ty); 

//*--------------------------------------------------- MACHINE ABSTRAITE QUESTION 5 ---------------------------------------------------*//

//Fonction pour remplir tout le tableau "Tab_anagrm" et cree toutes les liste d'anagrammes possible retourne la taille du tableau (donc le nombre de listes crees) dans size
void Remplir_anagrammes(int* size);

// Fonction qui affiche les listes des anagrammes
void Affiche_anagrammes(int ty);

//*--------------------------------------------------- FONCTIONS D'AFFICHAGE ----------------------------------------------------------*//

//Fonction qui affiche la liste de syllabes du mot
void Affiche_liste_syl(ptrwords mot);

// Fonction qui affiche un mot a partir d'un pointeur
void Affiche_mot(ptrwords p);

//Fonction qui affiche les mots avec details qui commence par la lettre de l'ordre n
void Affiche_liste_mots_n_details(int n);

//Fonction qui affiche les mots avec details qui commence par la lettre de l'ordre n mais en ordre inversé
void Affiche_liste_mots_n_inv_details(int n);

//Fonction qui affiche les mots en ordre decroissant sans detail qui commence par la lettre de l'ordre n
void Affiche_liste_mots_inv_n(int n);

//Fonction qui affiche les mots qui commence par la lettre de l'ordre n
void Affiche_liste_mots_n(int n);

//Fonction qui affiche tous les mots en compresser
void Affiche_mots_simple(void);

//*------------------------------------------------------------------------------------------------------------------------------------*//




//*--------------------------------------------------- LES CORPS DES FONCTIONS --------------------------------------------------------*//

void page_acceuil() {
    system("Cls"); // Effacer l'ecran
    int k ;
    for (k = 0 ; k<10 ; k++ ) {  // Afficher 10 fois le logo de ESI
        if (k % 2 == 0) // Les iterations paires s'afficherent en vert
        system("color 0A");
        if (k % 2 == 1) // Les iterations impaires s'afficherent en ciane
        system("color 0B");

        printf("\n\n\n\n\n\n"); // imprimer le logo de ESI
        printf(
            "\t\t\t\t                                              iiii\n"
            "\t\t\t\t                                             i::::i\n"
            "\t\t\t\t                                              iiii\n\n"
            "\t\t\t\t        eeeeeeeeeeee          ssssssssss    iiiiiii\n"
            "\t\t\t\t      ee::::::::::::ee      ss::::::::::s   i:::::i\n"
            "\t\t\t\t     e::::::eeeee:::::ee  ss:::::::::::::s   i::::i\n"
            "\t\t\t\t    e::::::e     e:::::e  s::::::ssss:::::s  i::::i\n"
            "\t\t\t\t    e:::::::eeeee::::::e   s:::::s  ssssss   i::::i\n"
            "\t\t\t\t    e:::::::::::::::::e      s::::::s        i::::i\n"
            "\t\t\t\t    e::::::eeeeeeeeeee          s::::::s     i::::i\n"
            "\t\t\t\t    e:::::::e             ssssss   s:::::s   i::::i\n"
            "\t\t\t\t    e::::::::e            s:::::ssss::::::s i::::::i\n"
            "\t\t\t\t     e::::::::eeeeeeee    s::::::::::::::s  i::::::i\n"
            "\t\t\t\t      ee:::::::::::::e     s:::::::::::ss   i::::::i\n"
            "\t\t\t\t        eeeeeeeeeeeeee      sssssssssss     iiiiiiii\n"
        );

        Sleep(200);     // Attendre 200 ms (0,2 s) a chaque iteration
        system("cls");
    }

    system("cls");  // effacer l'ecran
    printf("\t\t\t\033[96m           R%cpublique Alg%crienne D%cmocratique et Populaire           \033[0m\n", 130, 130, 130);
    printf("\t\t\t\033[96m  Minist%cre de l'Enseignement Sup%crieur et de la Recherche Scientifique\033[0m\n", 130, 130);
    printf("\t\t\t      \033[96m _______________________________________________________\n");
    printf("\t\t\t      \033[96m|        \033[92m_______\033[0m    \033[91m _______\033[0m    \033[97m _\033[0m                      \033[96m|\n");
    printf("\t\t\t      \033[96m|       \033[92m|  _____|\033[0m   \033[91m|  _____|\033[0m   \033[97m| |\033[0m  \033[92m%ccole nationale\033[0m    \033[96m|\n", 130);
    printf("\t\t\t      \033[96m|       \033[92m| |_____\033[0m    \033[91m| |_____\033[0m    \033[97m| |\033[0m                     \033[96m|\n");
    printf("\t\t\t      \033[96m|       \033[92m|  _____|\033[0m   \033[91m|_____  |\033[0m   \033[97m| |\033[0m  \033[91msup%crieure\033[0m         \033[96m|\n", 130);
    printf("\t\t\t      \033[96m|       \033[92m| |_____\033[0m    \033[91m _____| |\033[0m   \033[97m| |\033[0m                     \033[96m|\n");
    printf("\t\t\t      \033[96m|       \033[92m|_______|\033[0m   \033[91m|_______|\033[0m   \033[97m|_|\033[0m  \033[97md'informatique\033[0m     \033[96m|\n");
    printf("\t\t\t      \033[96m|_______________________________________________________|\033[0m\n\n");

    printf("\t\t\t\t\033[96m  CPI - 1%cre Ann%ce - Ann%ce Universitaire 2022/2023 \n", 138, 130, 130);
    printf("\t\t\t\033[96m ___________________________________________________________________\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|     REALISE PAR :  \033[97mMOSTEFAI MOUNIR SOFIANE\033[96m                        |\n");
    printf("\t\t\t\033[96m|                              &                                    |\n");
    printf("\t\t\t\033[96m|                           \033[97mKHALEF BADIS\033[96m                            |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|               SECTION :  \033[97mB\033[96m          GROUPE: \033[97m04\033[96m                    |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|             TP1 :  \033[97mLes listes lin%caires chain%ces\033[96m                  |\n", 130, 130);
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|                         <  \033[97mdictionnaire\033[96m >                         |\n");
    printf("\t\t\t\033[96m|___________________________________________________________________|\n\n\n");


    printf("\t\t\t                            \033[91mS'il vous plait                                 \n");
    printf("\t\t\t          Appuyez sur n'importe quelle touche pour continuer...\033[0m               ");
    getch();

    system("cls");
}

//-----------------------------------------------//-----------------------------------------------//

void page_chargement() {

    /*
    Le principe est simple on va juste afficher la barre avec le pourcentage
    et puis effacer l'ecran et reafficher la barre suivante
    */

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

    printf("\t\t\t\t|||                                                 5%%  ");
    Sleep(300);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t|||||                                               20%%  ");
    Sleep(300);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t||||||||||||||||                                    30%%  ");
    Sleep(300);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t|||||||||||||||||||||||||                           45%%  ");
    Sleep(300);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t|||||||||||||||||||||||||||||||                     60%%  ");
    Sleep(300);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t||||||||||||||||||||||||||||||||||||||||            80%%  ");
    Sleep(300);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t||||||||||||||||||||||||||||||||||||||||||||||||||  100%% ");
    system("cls");
}

//-----------------------------------------------//-----------------------------------------------//

int Remplir_base_donnees(void)             //Cette fonction permet de lire le fichier "words.txt" et recuperer tous les mots
{
    FILE *fichier = fopen("words.txt","r");
    char ch[25];
    if (fichier == NULL)
    {   
        printf("Error opening file !\n");
        return 1;
    }
    while (!feof(fichier)) {
        fgets(ch,25,fichier); // prendre 25 caractere chaque fois et puisque fgets va lire jusqu'a \n alors on aura un mot a chaque iteration
        if (ch[strlen(ch)-1] == '\n') 
        {
            ch[strlen(ch)-1] = '\0';   // chaque line se termine par \n alors en le modifie par \0
        } 
        if (ch[0] != '\0') 
        {
            ajout_mot(ch);
        } 
    }

    fclose(fichier);
    
    return 0;
}

//-----------------------------------------------//-----------------------------------------------//

int nb_car(char S[25])              //Cette fonction renvoit le nombre total de caractères dans la chaîne "S"
{
    int Cpt = 0; // Initialiser le compteur des caractères
    for (int i = 0; i < strlen(S); i++) {
        char c = tolower(S[i]); // Convertir le caractère en minuscule
        if (c >= 'a' && c <= 'z') { // Vérifier que c'est un caractère alphabétique
            Cpt++; // Incrémenter le compteur car c'est un caractère
        }
    }
    return Cpt; 
}

//-----------------------------------------------//-----------------------------------------------//

int nb_cons(char S[25])             //Cette fonction renvoit le nombre total de consonnes dans la chaîne "S"
{
    int Cpt = 0; // Initialiser le compteur des consonnes
    for (int i = 0; i < strlen(S); i++) {
        char c = tolower(S[i]); // Convertir le caractère en minuscule
        if (c >= 'a' && c <= 'z') { // Vérifier que c'est un caractère alphabétique
            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'y') {
                Cpt++; // Incrémenter le compteur car c'est une consonne
            }
        }
    }
    return Cpt;
}

//-----------------------------------------------//-----------------------------------------------//

int nb_voy(char S[25])              //Cette fonction renvoit le nombre total de voyelles dans la chaîne "S"
{
    int Cpt = 0; // Initialiser le compteur des voyelles
    for (int i = 0; i < strlen(S); i++) {
        char c = tolower(S[i]); // Convertir le caractère en minuscule
        if (c >= 'a' && c <= 'z') { // Vérifier que c'est un caractère alphabétique
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
                Cpt++; // Incrémenter le compteur car c'est une voyelle
            }
        }
    }
    return Cpt; 
}

//-----------------------------------------------//-----------------------------------------------//

int nb_syl(char S[25])             //Cette fonction renvoit le nombre total de syllabes dans la chaîne "S"
{
    int Cpt = 1; // Initialiser le compteur des syllabes à 1 car il y a toujours au moins une syllabe dans un mot
    for (int i = 0; i < strlen(S); i++) {
        char c = S[i]; // Prendre le caractère à tester
        if (c == '/') {
            Cpt++; // Incrémenter le compteur car c'est une syllabe
        }
    }
    return Cpt; 
}

//-----------------------------------------------//-----------------------------------------------//

bool isordered(char S[25])         //Cette fonction renvoit un boleen qui indique si la chaîne "S" est ordonnée
{
    for (int i = 0; i < strlen(S) - 1; i++) { // Parcourt la chaîne de caractères S jusqu'à l'avant-dernier caractère
        if (S[i] > S[i + 1]) { // Vérifie si le caractère actuel est supérieur au caractère suivant
            return 0; // Si c'est le cas, la chaîne n'est pas ordonnée et on retourne false
        }
    }
    return 1; // Si la boucle s'est terminée sans retourner false, alors la chaîne est ordonnée et on retourne true
}

//-----------------------------------------------//-----------------------------------------------//

void supp_no_alpha(char *chaine)        //Cette fonction supprime tous les caractères non alphabetique dans la chaîne "S"
{
    int i, j;
    for (i = 0, j = 0; i < strlen(chaine); i++)     //on parcourt la chaine
    {
        if ( isalpha(chaine[i]) )                   //si le caractere actuellement traiter est une lettre alphabetique on le garde
        {
            chaine[j++] = tolower(chaine[i]);
        }
    }
    chaine[j] = '\0';                               //a la fin de la chaine on met le "\0"
}

//-----------------------------------------------//-----------------------------------------------//

void ordonne_mot(char S[25])            //Cette fonction ordennera la chaîne "S" (ex : S = "acb" (apres appel)---> S = "abc" )
{
    if (!isordered(S)) { // Tester si la chaine n'est pas ordonner pour l'ordonner
        for (int i = 0; i < strlen(S) - 1; i++) { // Parcourt la chaîne de caractères S jusqu'à l'avant-dernier caractère
            for (int j = i + 1; j < strlen(S); j++) { // Parcourt la chaîne de caractères S à partir de l'indice i + 1
                if (tolower(S[i]) > tolower(S[j])) { // Compare le caractère actuel avec le caractère suivant en les mettant en minuscule
                    char temp = S[i]; // Échange les deux caractères
                    S[i] = S[j];
                    S[j] = temp;
                }
            }
        }
    }
}

//-----------------------------------------------//-----------------------------------------------//

void Allouer_mot(ptrwords *p)
{
    *p = malloc(sizeof(struct words));
};

//-----------------------------------------------//-----------------------------------------------//

void Liberer_mot(ptrwords ptr) {
    free(ptr);
};

//-----------------------------------------------//-----------------------------------------------//

void Allouer_syl(ptrsyllables *p)
{
    *p = malloc(sizeof(struct syllables));
}


//-----------------------------------------------//-----------------------------------------------//

void Liberer_syl(ptrsyllables ptr) {
    free(ptr->syllable);
    free(ptr);
};

//-----------------------------------------------//-----------------------------------------------//

ptrsyllables Suivant_syl(ptrsyllables ptr) {
    return ptr->suivant;
};

//-----------------------------------------------//-----------------------------------------------//

char* Valeur_syl(ptrsyllables ptr) {
    return ptr->syllable;
};

//-----------------------------------------------//-----------------------------------------------//

char* Valeur_mot(ptrwords ptr) {
    return ptr->mot;
};

//-----------------------------------------------//-----------------------------------------------//

int Valeur_nb_car(ptrwords ptr) {
    return ptr->nb_caractere;
};

//-----------------------------------------------//-----------------------------------------------//

int Valeur_nb_cons(ptrwords ptr) {
    return ptr->nb_consonne;
};

//-----------------------------------------------//-----------------------------------------------//

int Valeur_nb_voy(ptrwords ptr) {
    return ptr->nb_voyelle;
};

//-----------------------------------------------//-----------------------------------------------//

int Valeur_nb_syl(ptrwords ptr) {
    return ptr->nb_syllable;
};

//-----------------------------------------------//-----------------------------------------------//

bool Valeur_ordred(ptrwords ptr) {
    return ptr->ordred;
};

//-----------------------------------------------//-----------------------------------------------//

char* Valeur_mot_ordonne(ptrwords ptr) {
    return ptr->mot_ordonne;
};

//-----------------------------------------------//-----------------------------------------------//

ptrwords Suivant_mot(ptrwords ptr) {
    return ptr->suivant_words;
};

//-----------------------------------------------//-----------------------------------------------//

ptrwords Precedent_mot(ptrwords ptr) {
    return ptr->precedent_words;
};

//-----------------------------------------------//-----------------------------------------------//

ptrsyllables Tete_syl(ptrwords ptr) {
    return ptr->tete_syllables;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_adr_tete_syllables(ptrwords p ,ptrsyllables adr)
{
    p->tete_syllables = adr;
}

//-----------------------------------------------//-----------------------------------------------//

void Aff_Adr_syl(ptrsyllables ptr ,ptrsyllables suivantptr) {  
    ptr->suivant = suivantptr;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_syl(ptrsyllables ptr, char syl[9]) {
    strcpy(ptr->syllable , syl);
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_word(ptrwords ptr, char mot[25]) {
    strcpy(ptr->mot , mot);
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_nb_car(ptrwords ptr, int val) {
    ptr->nb_caractere = val;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_nb_cons(ptrwords ptr, int val) {
    ptr->nb_consonne = val;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_nb_voy(ptrwords ptr, int val) {
    ptr->nb_voyelle = val;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_nb_syl(ptrwords ptr, int val) {
    ptr->nb_syllable = val;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_word_ordrer(ptrwords ptr, char mot_ordoner[25]) {
    strcpy(ptr->mot_ordonne , mot_ordoner);
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Val_ordred(ptrwords ptr, bool ordred) {
    ptr->ordred = ordred;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Adr_suivant_word(ptrwords ptr, ptrwords suivantptr) {
    ptr->suivant_words = suivantptr;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_Adr_precedent_word(ptrwords ptr, ptrwords precedentptr) {
    ptr->precedent_words = precedentptr;
};

//-----------------------------------------------//-----------------------------------------------//

void ajout_mot(char *ch_mot)           //ch_mot : le mot copié tel qu'il est depuis le fichier avec le separateur "/"
{   
    char ch_mot_syl[25];                       //sauvegarde pour le mot avec le separateur "/"
    char ch_mot_ord[25];                       //la chaine qui servira pour le mot ordonné
    strcpy(ch_mot_syl , ch_mot);               //copie le mot avec le separateur pour utilisation avec les syllabes
    supp_no_alpha(ch_mot);                     //fonction supp_no_alpha pour enlever tout caractere non alphabetique
    strcpy(ch_mot_ord , ch_mot);               //affectation pour la chaine qu'on utilsera pour le mot ordonné
    int i_tab = tolower(ch_mot[0])-97;         //l'indice correspendant dans le tableau tsma la t3 la lettre ; echfa lzm init t3 compteur nb word 0 pour savoir si liste vide ou pas
    bool est_ce_que_cree_liste_syl = true;     //pour savoir si on cree la liste de syl ou pas (le cas ou le mot se repete)

    ptrwords maillon_mot ;              //creation du maillon et intialisation des champs :
    
    Allouer_mot(&maillon_mot);
    Aff_Val_word(maillon_mot , ch_mot);     
    Aff_Val_nb_car(maillon_mot , nb_car(ch_mot));                                  
    Aff_Val_nb_cons(maillon_mot , nb_cons(ch_mot));
    Aff_Val_nb_voy(maillon_mot , nb_voy(ch_mot));
    Aff_Val_nb_syl(maillon_mot , nb_syl(ch_mot_syl));
    Aff_Val_ordred(maillon_mot , isordered(ch_mot)); 
    ordonne_mot(ch_mot_ord);
    Aff_Val_word_ordrer(maillon_mot , ch_mot_ord);
    Aff_adr_tete_syllables(maillon_mot , NULL);                     
    Aff_Adr_suivant_word(maillon_mot , NULL);
    Aff_Adr_precedent_word(maillon_mot , NULL);
    Aff_adr_ED(maillon_mot , NULL);
    Aff_adr_ING(maillon_mot , NULL);
    Aff_adr_angrm(maillon_mot, NULL);
    Aff_adr_prochelex(maillon_mot, NULL);
    Aff_val_fin_prochelex(maillon_mot , false);
    Aff_adr_suiv_sequence_mots(maillon_mot, NULL);
    Aff_adr_prec_sequence_mots(maillon_mot, NULL);
    Aff_adr_sous_chaine(maillon_mot , NULL);
    Aff_val_indice_sous_chaine(maillon_mot,0);


    //pour la creation de la liste de syl on le fera apres avoir placer le mot dans la liste bidirect car pour le cas ou le mot se repete on va creer la liste pour rien et on va devoir la supprimer apres en plus; on saura si il faut la creer ou pas grace au boolen "est_ce_que_cree_liste_syl"

    //recherche de l'emplacement et insertion du maillon dans la liste bidirect

    if ( T[i_tab].nb_word == 0)             //cas ou la liste est vide donc remplissage de liste bidirect correspandante a la lettre pour la premiere fois
    {
        T[i_tab].tete_mots = T[i_tab].queue_mots = maillon_mot;
        T[i_tab].nb_word++;
    }   
    else                                    //cas la liste contient au moin un element
    {
        if ( (T[i_tab].tete_mots != NULL) && (T[i_tab].queue_mots != NULL) )    //cas liste non vide donc verification des deux pointeurs
        {   
            ptrwords parcr = T[i_tab].tete_mots ;        //parcr = parcourir , pour parcourir la liste bidirect et trouver l'emplacement du maillon selon l'ordre de taille ou alphabetique si la meme taille en utilisant la fonction str_comp_ordr
            
            while ( (Suivant_mot(parcr) != NULL) && (str_comp_ordr(parcr->mot , ch_mot) < 0) )   
            {
                parcr = Suivant_mot(parcr);
            }
                

            if (str_comp_ordr(parcr->mot , ch_mot) < 0)   //donc affectation a droite de prcr + si suivant = nil donc a la fin de la liste --> changement de queue
            {
                Aff_Adr_suivant_word(maillon_mot , Suivant_mot(parcr));          //meme si suivant parcr == null ca match                
                Aff_Adr_precedent_word(maillon_mot , parcr);    
                Aff_Adr_suivant_word(parcr , maillon_mot);
                if (Suivant_mot(maillon_mot) == NULL)                     //on est a la fin vu que ca pointe null a droite donc changement de queue
                    T[i_tab].queue_mots = maillon_mot;    
                else
                    Aff_Adr_precedent_word( Suivant_mot(maillon_mot) , maillon_mot );   //on n'est pas a la fin donc au milieu ; alors il faut faire le chainage du suivant qui pointe le maillon   
                
                T[i_tab].nb_word++;                                 //vu qu'on vient d'ajouter un maillon on incremente le nombre de mots
            }
            else                                   //donc affectation a gauche de prcr + si precedant prcr = nil donc au debut de la liste --> changement de tete
            {   
                if (str_comp_ordr(parcr->mot , ch_mot) > 0)         // sans cette condition ca fera la negation du if precedant c.a.d : str_cmp_ordr >= 0 or on veut eliminer le cas == (égalité) pour éviter la repetition des mots
                {
                    Aff_Adr_precedent_word(maillon_mot , Precedent_mot(parcr));    //meme si precedant parcr == null ca match (le cas tete)
                    Aff_Adr_suivant_word(maillon_mot , parcr);                          
                    Aff_Adr_precedent_word(parcr , maillon_mot);
                    if (Precedent_mot(maillon_mot) == NULL)                     //on est au debut vu que ca pointe null a gauche donc changement de tete
                        T[i_tab].tete_mots = maillon_mot; 
                    else                                                       //on n'est pas au debut donc au milieu ; alors il faut faire le chainage precedant pointe maillon
                        Aff_Adr_suivant_word( Precedent_mot(maillon_mot) , maillon_mot );  
                    
                    T[i_tab].nb_word++;                             //vu qu'on vient d'ajouter un maillon on incremente le nombre de mots
                }
                else   
                    est_ce_que_cree_liste_syl = false;                       //le cas ou le mot se repete on libere le maillon et on cree pas la liste de syl
            }

        }
        
    }

    if (est_ce_que_cree_liste_syl)
    {
        Cree_liste_syl(maillon_mot , ch_mot_syl);
    }
    else
        Liberer_mot(maillon_mot);


}

//-----------------------------------------------//-----------------------------------------------//

void init_base_donnees(void)            //cette fonction initialisera pour la premiere fois le tableau qui contiendra les listes (bidirectionnelles) des mots 
{
    for (int i = 0 ; i < LETTER_ALPHABETIC ; i++)
    {
        T[i] = (struct Lettre) { NULL , NULL , 0 };
    }
}

//-----------------------------------------------//-----------------------------------------------//

void Supp_mot(ptrwords ptr)           //Fonction qui supprime le mot de la liste a partir d'un pointeur donner
{
    // on commance par supprimer la liste de syllable
    if (Tete_syl(ptr) != NULL) {
        ptrsyllables p;
        while (Tete_syl(ptr) != NULL) {
            p = Tete_syl(ptr);
            Aff_adr_tete_syllables( ptr ,  Suivant_syl(Tete_syl(ptr)) );
            Liberer_syl(p); // elle va liberer le maillon et la chaine de caractere
        }
    }

    //Ensuite on libere le mot de la liste et on refait les liens entre les maillons
    if (Precedent_mot(ptr) == NULL)             //cas debut + cas un seul element aussi
    {
        T[tolower(ptr->mot[0])-97].tete_mots = Suivant_mot(ptr);
        if ( Suivant_mot(ptr) == NULL)          // donc 1 seul element --> changement de queue aussi 
            T[tolower(ptr->mot[0])-97].queue_mots = NULL;
        else
            Aff_Adr_precedent_word(Suivant_mot(ptr) , NULL);
    }
    else
    {
        Aff_Adr_suivant_word(Precedent_mot(ptr) , Suivant_mot(ptr));
        if (Suivant_mot(ptr) == NULL)
            T[tolower(ptr->mot[0])-97].queue_mots = Precedent_mot(ptr);
        else
            Aff_Adr_precedent_word(Suivant_mot(ptr) , Precedent_mot(ptr));

    }
    
    T[tolower(ptr->mot[0])-97].nb_word--;      //decrementer le nombre de mot
    Liberer_mot(ptr); 
}

//-----------------------------------------------//-----------------------------------------------//

void Affiche_mot(ptrwords p)         //Fonction qui affiche un mot a partir d'un pointeur
{
    if (p != NULL) {
        printf("#############################################################################################################\n");
        printf("#%35c#  Mot : %-27s#%35c#\n",32,Valeur_mot(p),32);
        printf("#%35c#  Mot ordonn%c: %-20s#%35c#\n",32,130,Valeur_mot_ordonne(p),32);
        printf("#%35c#  Nombre de caract%cre : %-11d#%35c#\n",32,130,Valeur_nb_car(p),32);
        printf("#%35c#  Nombre de consonne : %-12d#%35c#\n",32,Valeur_nb_cons(p),32);
        printf("#%35c#  Nombre de voyelle : %-13d#%35c#\n",32,Valeur_nb_voy(p),32);
        printf("#%35c#  Nombre de syllable : %-12d#%35c#\n",32,Valeur_nb_syl(p),32);
        printf("#%35c#  Le bool%cen : %-20d#%35c#\n",32,130,Valeur_ordred(p),32);
        printf("#############################################################################################################\n");
    }
}

//-----------------------------------------------//-----------------------------------------------//

void Affiche_liste_mots_n_details(int n)        //Fonction qui affiche les mots avec details qui commence par la lettre de l'ordre n
{
    if (0 <= n && n < 26) {
        ptrwords p = T[n].tete_mots;
        
        printf("#############################################################################################################\n");
        printf("#%53c%c%53c#\n",32, n+97,32);
        printf("#############################################################################################################\n");

        if (p == NULL) {
        printf("#%33cPas de mots qui commence par la lettre %c%34c#\n",32, n+97,32);
        printf("#############################################################################################################\n");
        }

        while (p != NULL) {
            if (p != NULL && Suivant_mot(p) != NULL && Suivant_mot(Suivant_mot(p)) != NULL) {
                printf("#  Mot : %-27s#  Mot : %-27s#  Mot : %-27s#\n",Valeur_mot(p),Valeur_mot(Suivant_mot(p)),Valeur_mot(Suivant_mot(Suivant_mot(p))));
                printf("#  Mot ordonn%c: %-20s#  Mot ordonn%c: %-20s#  Mot ordonn%c: %-20s#\n",130,Valeur_mot_ordonne(p),130,Valeur_mot_ordonne(Suivant_mot(p)),130,Valeur_mot_ordonne(Suivant_mot(Suivant_mot(p))));
                printf("#  Nombre de caract%cre : %-11d#  Nombre de caract%cre : %-11d#  Nombre de caract%cre : %-11d#\n",130,Valeur_nb_car(p),130,Valeur_nb_car(Suivant_mot(p)),130,Valeur_nb_car(Suivant_mot(Suivant_mot(p))));
                printf("#  Nombre de consonne : %-12d#  Nombre de consonne : %-12d#  Nombre de consonne : %-12d#\n",Valeur_nb_cons(p),Valeur_nb_cons(Suivant_mot(p)),Valeur_nb_cons(Suivant_mot(Suivant_mot(p))));
                printf("#  Nombre de voyelle : %-13d#  Nombre de voyelle : %-13d#  Nombre de voyelle : %-13d#\n",Valeur_nb_voy(p),Valeur_nb_voy(Suivant_mot(p)),Valeur_nb_voy(Suivant_mot(Suivant_mot(p))));
                printf("#  Nombre de syllable : %-12d#  Nombre de syllable : %-12d#  Nombre de syllable : %-12d#\n",Valeur_nb_syl(p),Valeur_nb_syl(Suivant_mot(p)),Valeur_nb_syl(Suivant_mot(Suivant_mot(p))));
                printf("#  Le bool%cen : %-20d#  Le bool%cen : %-20d#  Le bool%cen : %-20d#\n",130,Valeur_ordred(p),130,Valeur_ordred(Suivant_mot(p)),130,Valeur_ordred(Suivant_mot(Suivant_mot(p))));
                printf("#############################################################################################################\n");
                p = Suivant_mot(Suivant_mot(Suivant_mot(p)));
            } else if (p != NULL && Suivant_mot(p) != NULL && Suivant_mot(Suivant_mot(p)) == NULL) {
                printf("#  Mot : %-44s###  Mot : %-44s#\n",Valeur_mot(p),Valeur_mot(Suivant_mot(p)));
                printf("#  Mot ordonn%c: %-37s###  Mot ordonn%c: %-37s#\n",130,Valeur_mot_ordonne(p),130,Valeur_mot_ordonne(Suivant_mot(p)));
                printf("#  Nombre de caract%cre : %-28d###  Nombre de caract%cre : %-28d#\n",130,Valeur_nb_car(p),130,Valeur_nb_car(Suivant_mot(p)));
                printf("#  Nombre de consonne : %-29d###  Nombre de consonne : %-29d#\n",Valeur_nb_cons(p),Valeur_nb_cons(Suivant_mot(p)));
                printf("#  Nombre de voyelle : %-30d###  Nombre de voyelle : %-30d#\n",Valeur_nb_voy(p),Valeur_nb_voy(Suivant_mot(p)));
                printf("#  Nombre de syllable : %-29d###  Nombre de syllable : %-29d#\n",Valeur_nb_syl(p),Valeur_nb_syl(Suivant_mot(p)));
                printf("#  Le bool%cen : %-37d###  Le bool%cen : %-37d#\n",130,Valeur_ordred(p),130,Valeur_ordred(Suivant_mot(p)));
                printf("#############################################################################################################\n");
                p = Suivant_mot(Suivant_mot(p));
            } else if (p != NULL && Suivant_mot(p) == NULL) {
                printf("#%35c#  Mot : %-27s#%35c#\n",32,Valeur_mot(p),32);
                printf("#%35c#  Mot ordonn%c: %-20s#%35c#\n",32,130,Valeur_mot_ordonne(p),32);
                printf("#%35c#  Nombre de caract%cre : %-11d#%35c#\n",32,130,Valeur_nb_car(p),32);
                printf("#%35c#  Nombre de consonne : %-12d#%35c#\n",32,Valeur_nb_cons(p),32);
                printf("#%35c#  Nombre de voyelle : %-13d#%35c#\n",32,Valeur_nb_voy(p),32);
                printf("#%35c#  Nombre de syllable : %-12d#%35c#\n",32,Valeur_nb_syl(p),32);
                printf("#%35c#  Le bool%cen : %-20d#%35c#\n",32,130,Valeur_ordred(p),32);
                printf("#############################################################################################################\n");
                p = Suivant_mot(p);
            }
        }
        printf("\n");
    }
};

//-----------------------------------------------//-----------------------------------------------//

void Affiche_liste_mots_n_inv_details(int n)          //Fonction qui affiche les mots avec details qui commence par la lettre de l'ordre n mais en ordre inversé
{
    if (0 <= n && n < 26) {    
        ptrwords p = T[n].queue_mots;
        
        printf("#############################################################################################################\n");
        printf("#%53c%c%53c#\n",32, n+97,32);
        printf("#############################################################################################################\n");

        if (p == NULL) {
        printf("#%33cPas de mots qui commence par la lettre %c%34c#\n",32, n+97,32);
        printf("#############################################################################################################\n");
        }

        while (p != NULL) {
            if (p != NULL && Precedent_mot(p) != NULL && Precedent_mot(Precedent_mot(p)) != NULL) {
                printf("#  Mot : %-27s#  Mot : %-27s#  Mot : %-27s#\n",Valeur_mot(p),Valeur_mot(Precedent_mot(p)),Valeur_mot(Precedent_mot(Precedent_mot(p))));
                printf("#  Mot ordonn%c: %-20s#  Mot ordonn%c: %-20s#  Mot ordonn%c: %-20s#\n",130,Valeur_mot_ordonne(p),130,Valeur_mot_ordonne(Precedent_mot(p)),130,Valeur_mot_ordonne(Precedent_mot(Precedent_mot(p))));
                printf("#  Nombre de caract%cre : %-11d#  Nombre de caract%cre : %-11d#  Nombre de caract%cre : %-11d#\n",130,Valeur_nb_car(p),130,Valeur_nb_car(Precedent_mot(p)),130,Valeur_nb_car(Precedent_mot(Precedent_mot(p))));
                printf("#  Nombre de consonne : %-12d#  Nombre de consonne : %-12d#  Nombre de consonne : %-12d#\n",Valeur_nb_cons(p),Valeur_nb_cons(Precedent_mot(p)),Valeur_nb_cons(Precedent_mot(Precedent_mot(p))));
                printf("#  Nombre de voyelle : %-13d#  Nombre de voyelle : %-13d#  Nombre de voyelle : %-13d#\n",Valeur_nb_voy(p),Valeur_nb_voy(Precedent_mot(p)),Valeur_nb_voy(Precedent_mot(Precedent_mot(p))));
                printf("#  Nombre de syllable : %-12d#  Nombre de syllable : %-12d#  Nombre de syllable : %-12d#\n",Valeur_nb_syl(p),Valeur_nb_syl(Precedent_mot(p)),Valeur_nb_syl(Precedent_mot(Precedent_mot(p))));
                printf("#  Le bool%cen : %-20d#  Le bool%cen : %-20d#  Le bool%cen : %-20d#\n",130,Valeur_ordred(p),130,Valeur_ordred(Precedent_mot(p)),130,Valeur_ordred(Precedent_mot(Precedent_mot(p))));
                printf("#############################################################################################################\n");
                p = Precedent_mot(Precedent_mot(Precedent_mot(p)));
            } else if (p != NULL && Precedent_mot(p) != NULL && Precedent_mot(Precedent_mot(p)) == NULL) {
                printf("#  Mot : %-44s###  Mot : %-44s#\n",Valeur_mot(p),Valeur_mot(Precedent_mot(p)));
                printf("#  Mot ordonn%c: %-37s###  Mot ordonn%c: %-37s#\n",130,Valeur_mot_ordonne(p),130,Valeur_mot_ordonne(Precedent_mot(p)));
                printf("#  Nombre de caract%cre : %-28d###  Nombre de caract%cre : %-28d#\n",130,Valeur_nb_car(p),130,Valeur_nb_car(Precedent_mot(p)));
                printf("#  Nombre de consonne : %-29d###  Nombre de consonne : %-29d#\n",Valeur_nb_cons(p),Valeur_nb_cons(Precedent_mot(p)));
                printf("#  Nombre de voyelle : %-30d###  Nombre de voyelle : %-30d#\n",Valeur_nb_voy(p),Valeur_nb_voy(Precedent_mot(p)));
                printf("#  Nombre de syllable : %-29d###  Nombre de syllable : %-29d#\n",Valeur_nb_syl(p),Valeur_nb_syl(Precedent_mot(p)));
                printf("#  Le bool%cen : %-37d###  Le bool%cen : %-37d#\n",130,Valeur_ordred(p),130,Valeur_ordred(Precedent_mot(p)));
                printf("#############################################################################################################\n");
                p = Precedent_mot(Precedent_mot(p));
            } else if (p != NULL && Precedent_mot(p) == NULL) {
                printf("#%35c#  Mot : %-27s#%35c#\n",32,Valeur_mot(p),32);
                printf("#%35c#  Mot ordonn%c: %-20s#%35c#\n",32,130,Valeur_mot_ordonne(p),32);
                printf("#%35c#  Nombre de caract%cre : %-11d#%35c#\n",32,130,Valeur_nb_car(p),32);
                printf("#%35c#  Nombre de consonne : %-12d#%35c#\n",32,Valeur_nb_cons(p),32);
                printf("#%35c#  Nombre de voyelle : %-13d#%35c#\n",32,Valeur_nb_voy(p),32);
                printf("#%35c#  Nombre de syllable : %-12d#%35c#\n",32,Valeur_nb_syl(p),32);
                printf("#%35c#  Le bool%cen : %-20d#%35c#\n",32,130,Valeur_ordred(p),32);
                printf("#############################################################################################################\n");
                p = Precedent_mot(p);
            }
        }
        printf("\n");
    }
};

//-----------------------------------------------//-----------------------------------------------//

void Affiche_liste_mots_n(int n)         //Fonction qui affiche les mots qui commence par la lettre de l'ordre n
{
    if (0 <= n && n < 26) {
        ptrwords p = T[n].tete_mots;
        
        printf("#############################################################################################################\n");
        printf("#%53c%c%53c#\n",32, n+97,32);
        printf("#############################################################################################################\n");

        if (p == NULL) {
        printf("#%33cPas de mots qui commence par la lettre %c%34c#\n",32, n+97,32);
        printf("#############################################################################################################\n");
        }

        while (p != NULL) {
            if (p != NULL && Suivant_mot(p) != NULL && Suivant_mot(Suivant_mot(p)) != NULL) {
                printf("#        %-27s#        %-27s#        %-27s#\n",Valeur_mot(p),Valeur_mot(Suivant_mot(p)),Valeur_mot(Suivant_mot(Suivant_mot(p))));
                printf("#############################################################################################################\n");
                p = Suivant_mot(Suivant_mot(Suivant_mot(p)));
            } else if (p != NULL && Suivant_mot(p) != NULL && Suivant_mot(Suivant_mot(p)) == NULL) {
                printf("#        %-44s###        %-44s#\n",Valeur_mot(p),Valeur_mot(Suivant_mot(p)));
                printf("#############################################################################################################\n");
                p = Suivant_mot(Suivant_mot(p));
            } else if (p != NULL && Suivant_mot(p) == NULL) {
                printf("#%35c#        %-27s#%35c#\n",32,Valeur_mot(p),32);
                printf("#############################################################################################################\n");
                p = Suivant_mot(p);
            }
        }
        printf("\n");
    }
}

//-----------------------------------------------//-----------------------------------------------//

void Affiche_liste_mots_inv_n(int n)           //Fonction qui affiche les mots en ordre decroissant sans detail qui commence par la lettre de l'ordre n
{
    if (0 <= n && n < 26) {
        ptrwords p = T[n].queue_mots;
        
        printf("#############################################################################################################\n");
        printf("#%53c%c%53c#\n",32, n+97,32);
        printf("#############################################################################################################\n");

        if (p == NULL) {
        printf("#%33cPas de mots qui commence par la lettre %c%34c#\n",32, n+97,32);
        printf("#############################################################################################################\n");
        }

        while (p != NULL) {
            if (p != NULL && Precedent_mot(p) != NULL && Precedent_mot(Precedent_mot(p)) != NULL) {
                printf("#        %-27s#        %-27s#        %-27s#\n",Valeur_mot(p),Valeur_mot(Precedent_mot(p)),Valeur_mot(Precedent_mot(Precedent_mot(p))));
                printf("#############################################################################################################\n");
                p = Precedent_mot(Precedent_mot(Precedent_mot(p)));
            } else if (p != NULL && Precedent_mot(p) != NULL && Precedent_mot(Precedent_mot(p)) == NULL) {
                printf("#        %-44s###        %-44s#\n",Valeur_mot(p),Valeur_mot(Precedent_mot(p)));
                printf("#############################################################################################################\n");
                p = Precedent_mot(Precedent_mot(p));
            } else if (p != NULL && Precedent_mot(p) == NULL) {
                printf("#%35c#        %-27s#%35c#\n",32,Valeur_mot(p),32);
                printf("#############################################################################################################\n");
                p = Precedent_mot(p);
            }
        }
        printf("\n");
    }
}

//-----------------------------------------------//-----------------------------------------------//

ptrwords Suivant_ED(ptrwords ptr) {
    return ptr->champ_ed;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_adr_ED(ptrwords adr1, ptrwords adr2) {
    adr1->champ_ed = adr2;
};

//-----------------------------------------------//-----------------------------------------------//

ptrwords Suivant_ING(ptrwords ptr) {
    return ptr->champ_ing;
};

//-----------------------------------------------//-----------------------------------------------//

void Aff_adr_ING(ptrwords adr1, ptrwords adr2) {
    adr1->champ_ing = adr2;
};

//-----------------------------------------------//-----------------------------------------------//

ptrwords RechED(ptrwords ptr)        //Fonction qui cherche le participe passés d'un mot   
{
    ptrwords test = Suivant_mot(ptr);

    // Creation du participe passé pour le compare avec les mots
    int len1 = strlen(Valeur_mot(ptr));
    bool lastcase = false;
    char mot[25];
    char mot2[25];
    strcpy(mot,Valeur_mot(ptr));
    strcpy(mot2,Valeur_mot(ptr)); // Pour traiter le cas de derniere syllabe stresser donc en double la derniere consonne
    if (2 <= len1) {  
        mot2[len1] = mot2[len1 - 1];
        mot2[len1 + 1] = 'e';
        mot2[len1 + 2] = 'd';
        mot2[len1 + 3] = '\0';
    }


    if (mot[len1 - 1] == 'e') { // Premier cas (close --> closed)
        mot[len1] = 'd';
        mot[len1 + 1] = '\0';
    } else if (2 <= len1 && mot[len1 - 1] == 'y' && mot[len1 - 2] != 'a' && mot[len1 - 2] != 'e' && mot[len1 - 2] != 'y' && mot[len1 - 2] != 'u' && mot[len1 - 2] != 'i' && mot[len1 - 2] != 'o' )
    { // Dexieme cas (try --> tried)
        mot[len1 - 1] = 'i';
        mot[len1] = 'e';
        mot[len1 + 1] = 'd';
        mot[len1 + 2] = '\0';
    } else if (2 <= len1 && mot[len1 - 1] == 'y' && (mot[len1 - 2] == 'a' || mot[len1 - 2] == 'e' || mot[len1 - 2] == 'y' || mot[len1 - 2] == 'u' || mot[len1 - 2] == 'i' || mot[len1 - 2] == 'o') )
    { // Troixieme cas (play --> played)
        mot[len1] = 'e';
        mot[len1 + 1] = 'd';
        mot[len1 + 2] = '\0';
    } else if (2 <= len1 && mot[len1 - 1] == 'c' && mot[len1 - 2] == 'i')
    { // Quatrieme cas (panic --> panicked)
        mot[len1] = 'k';
        mot[len1 + 1] = 'e';
        mot[len1 + 2] = 'd';
        mot[len1 + 3] = '\0';
    } else { // le dernier cas
        lastcase = true; // pour verifier les deux cas (sans doubler la derniere consone ou avec doubler)
        mot[len1] = 'e';
        mot[len1 + 1] = 'd';
        mot[len1 + 2] = '\0';
    }  
    while (test != NULL) {
        if (!lastcase && strcmp(mot , Valeur_mot(test)) == 0 ) return test;
        if (lastcase && ( strcmp(mot , Valeur_mot(test)) == 0 || strcmp(mot2 , Valeur_mot(test)) == 0 ) ) return test;                     
        test = Suivant_mot(test);    
    }
    return NULL;
}

//-----------------------------------------------//-----------------------------------------------//

ptrwords RechING(ptrwords ptr)            //Fonction qui cherche la forme ING d'un mot
{
    ptrwords test = Suivant_mot(ptr);
    int len1 = strlen(Valeur_mot(ptr));
    bool lastcase = false;
    char mot[25];
    char mot2[25];
    strcpy(mot,Valeur_mot(ptr));
    strcpy(mot2,Valeur_mot(ptr)); // Pour traiter le cas de derniere syllabe stresser donc en double la derniere consonne
    if (2 <= len1) {  
        mot2[len1] = mot2[len1 - 1];
        mot2[len1 + 1] = 'i';
        mot2[len1 + 2] = 'n';
        mot2[len1 + 3] = 'g';
        mot2[len1 + 4] = '\0';
    }
    
    if (2 <= len1 && mot[len1 - 1] == 'e' && mot[len1 - 2] == 'i')
    {   // premier cas (tie --> tying)
        mot[len1 - 2] = 'y';
        mot[len1 - 1] = 'i';
        mot[len1] = 'n';
        mot[len1 + 1] = 'g';
        mot[len1 + 2] = '\0';     
    } else if (2 <= len1 && mot[len1 - 1] == 'e' && mot[len1 - 2] != 'e')
    { // (take --> taking)
        mot[len1 - 1] = 'i';
        mot[len1] = 'n';
        mot[len1 + 1] = 'g';
        mot[len1 + 2] = '\0';
    } else if (2 <= len1 && mot[len1 - 1] == 'c' && mot[len1 - 2] == 'i')
    { // (panic --> panicking)
        mot[len1] = 'k';
        mot[len1 + 1] = 'i';
        mot[len1 + 2] = 'n';
        mot[len1 + 3] = 'g';
        mot[len1 + 4] = '\0';
    } else if (2 <= len1 && mot[len1 - 1] == 'e' && mot[len1 - 2] == 'e')
    { // (see --> seeing)
        mot[len1] = 'i';
        mot[len1 + 1] = 'n';
        mot[len1 + 2] = 'g';
        mot[len1 + 3] = '\0';
    } else { // cas generale
        lastcase = true; // pour verifier les deux cas (sans doubler la derniere consone ou avec doubler)
        mot[len1] = 'i';
        mot[len1 + 1] = 'n';
        mot[len1 + 2] = 'g';
        mot[len1 + 3] = '\0';
    }
    while (test != NULL) {
        if (!lastcase && strcmp(mot , Valeur_mot(test)) == 0 ) return test;
        if (lastcase && ( strcmp(mot , Valeur_mot(test)) == 0 || strcmp(mot2 , Valeur_mot(test)) == 0 ) ) return test;          
        test = Suivant_mot(test);    
    }
    return NULL;
}

//-----------------------------------------------//-----------------------------------------------//

void Remplire_ED_ING(int *Nb_liste_ED_ING)          //Fonction qui va créer les liens de ED et ING
{
    *Nb_liste_ED_ING = 0;
    ptrwords p , ptred , ptring;

    for (int i = 0 ; i < LETTER_ALPHABETIC ; i++) {
        p = T[i].tete_mots;
        while (p != NULL) {
            ptred = RechED(p);
            ptring = RechING(p);
            if (ptred != NULL) Aff_adr_ED(p , ptred);
            if (ptring != NULL) Aff_adr_ING(p , ptring);
            if (Suivant_ED(p) != NULL || Suivant_ING(p) != NULL)
            {
                *Nb_liste_ED_ING = *Nb_liste_ED_ING + 1;
            } 
            p = Suivant_mot(p);
            ptred = NULL;
            ptring = NULL;
        }
    }
};

//-----------------------------------------------//-----------------------------------------------//

void Affiche_mot_ed_ing(int size)           //Fonction qui va afficher les mot + participe passé + forme ING
{
    if (size == 0) {
        printf("Dommage, il n'y a pas de mots avec leur participe pass%cs ou forme ing\n",130);
    } else {
        ptrwords p;
        int i = 0 ;
        printf("#############################################################################################################\n");
        printf("#%14cLe mot%15c#%8cLe participe pass%ce%8c#%11cLa forme ing%12c#\n",32,32,32,130,32,32,32);
        printf("#############################################################################################################\n");
        for (i ; i < LETTER_ALPHABETIC ; i++) {
            p = T[i].tete_mots;
            while (p != NULL)
            {
                if (Suivant_ED(p) != NULL && Suivant_ING(p) != NULL) {
                    printf("#     %-30s#     %-30s#     %-30s#\n",Valeur_mot(p) , Valeur_mot(Suivant_ED(p)) , Valeur_mot(Suivant_ING(p)));
                    printf("#############################################################################################################\n");
                } else if (Suivant_ED(p) != NULL && Suivant_ING(p) == NULL)
                {
                    printf("#     %-30s#     %-30s#%35c#\n",Valeur_mot(p) , Valeur_mot(Suivant_ED(p)) , 32);
                    printf("#############################################################################################################\n");
                } else if (Suivant_ED(p) == NULL && Suivant_ING(p) != NULL)
                {
                    printf("#     %-30s#%35c#     %-30s#\n",Valeur_mot(p) , 32 , Valeur_mot(Suivant_ING(p)) );
                    printf("#############################################################################################################\n");
                }
                p = Suivant_mot(p);
            }
        }
    }
}

//-----------------------------------------------//-----------------------------------------------//

int str_comp_ordr(char *ch1 , char* ch2)        //Fonction qui compare deux chaines selon la taille , et selon l'ordre alphabetique si ils ont la meme taille
{   //retourne : 1 si ch1 > ch2 ; 0 si ch1 = ch2 ; -1 si ch1 < ch2

    int ty1 = strlen(ch1);
    int ty2 = strlen(ch2);
    
    if (ty1 != ty2)                 //cas comparaison selon taille
    {
        if (ty1 > ty2)
            return 1;
        else
            return -1;
    }
    else // ty1 == ty2              //comparaison selon l'ordre alphabetique
    {   
        if (strcmp(ch1, ch2) < 0)
            return -1;
        else
        {
            if (strcmp(ch1, ch2) > 0)
                return 1;
            else // comp = 0
                return 0;
        }
    }
}

//-----------------------------------------------//-----------------------------------------------//

void Cree_liste_syl(ptrwords ptrmot , char * ch_syl)           //Fonction qui va créer la liste de syllables pour un mot
//ptrmot : pointeur vers le maillon qui contient le mot dans la liste bidirect ; ch_syl : la chaine du mot avec la separateur "/"
{
    char *syl = strtok(ch_syl , "/");               //on prend une syllabe de la chaine avec la fonction strtok et grace au delimiteur "/"
    ptrsyllables p = NULL;
    ptrsyllables prec = NULL;
    
    while ( syl != NULL )                           //syllabe non vide (condition de sortie)
    {
        Allouer_syl(&p);
        p->syllable = malloc(strlen(syl)+1);        //on alloue la taille de la syllabe +1 pour le "/0"
        strcpy(p->syllable , syl);
        Aff_Adr_syl(p , NULL);
        //placement du maillon "p" de la syllabe dans la liste du mot
        if ( Tete_syl(ptrmot) == NULL )
        {
            Aff_adr_tete_syllables(ptrmot, p);
            prec = p;
        }
        else
        {
            Aff_Adr_syl(prec , p);
            prec = p;
        }

        syl = strtok(NULL , "/");               //on continue de recuperer la prochaine syllabe
    }
}

//-----------------------------------------------//-----------------------------------------------//

void Affiche_liste_syl(ptrwords mot)            //Fonction qui va Afficher la liste de syllabes du mot
{   
    ptrsyllables p = Tete_syl(mot);
    
        printf("\n%38cLa liste de syllabes du mot \"%s\":\n",32,mot->mot);
    for (int i = 1 ; p != NULL ; i++)
    {   
        printf("%42c---------------------\n",32);
        printf("%42c|   syllable N*%d    |\n",32,i);
        printf("%42c|        %-11s|\n",32, p->syllable);
        printf("%42c---------------------\n",32);
        printf("%53c|\n",32);
        printf("%53c|\n",32);
        printf("%53c|\n",32);
        printf("%53c|\n",32);
        p = Suivant_syl(p);
    }
        printf("%52cNULL\n",32);
}

//-----------------------------------------------//-----------------------------------------------//

ptrwords Rech_mot(char ch_mot[25])         //recherche un mot introduit par l'utilisateur et renvoie un ptr vers le maillon qui le contient; NIL si il n'existe pas
{
    bool trouve = false; // boolean qui indique la trouvail du mot
    ptrwords p = NULL;   // pointeur de parcours
    char mot[25];        //le mot qu'on va utiliser
    strcpy(mot , ch_mot);
    supp_no_alpha(mot);  // pour etre sur d'avoir un mot de caractere
    int len = strlen(mot);  //la longueur du mot

    //recherche du mot dans la liste
    p = T[tolower(mot[0]) - 97].tete_mots;
    while ( (p != NULL) && (Valeur_nb_car(p) <= len) && (trouve == false) )
    {   // parcourir jusqu'a trouver le mot ou pas ou depacer la longeur du mot
        if (Valeur_nb_car(p) == len)        // pour eliminer le cas de longuere inferieure
        { 
            if (strcmp(Valeur_mot(p) , mot) == 0)       // tester ci le mot est trouver
            {
                trouve = true;
            } else {
                p = Suivant_mot(p);
            }
        } 
        else 
        {
            p = Suivant_mot(p);
        }  
    }
    if (!trouve)    // si on n'a pas trouver le mot
    { 
        p = NULL;
    }

    return p;       // on retourne le pointeur
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_adr_angrm(ptrwords p , ptrwords adr)
{
    p->suiv_anagrm = adr;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

ptrwords Valeur_suiv_anagramme(ptrwords p)
{
    return p->suiv_anagrm ;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Remplir_anagrammes(int* size)      //Fonction pour remplir tout le tableau "Tab_anagrm" et crée toutes les liste d'anagrammes possible retourne la taille du tableau (donc le nombre de listes crees) dans size
{
    int taille = 0 ; 
    ptrwords p , prec = NULL , q = NULL ;

    for (int i = 0 ; i < LETTER_ALPHABETIC ; i++)       //boucle pour parcourir toutes les listes bidirect avec le ptr "p"
    {
        p = T[i].tete_mots;
        
        while (p != NULL)                               //boucle pour parcourir tous les mots de la liste bidirect
        {
            if (Valeur_suiv_anagramme(p) == NULL)
            {   
                prec = p;
                taille++;
                Tab_anagrm = realloc(Tab_anagrm , taille*sizeof(struct Anagramme));
                Tab_anagrm[taille-1].tete_liste = p;
                Tab_anagrm[taille-1].nb_mots = 1;                     //l'indice taille-1 represente tjr le dernier elem du tableau

                for (int j = i ; j < LETTER_ALPHABETIC ; j++)       //la meme boucle pour parcourir toutes les listes bidirect avec le ptr "q" pour trouver les potentiels anagrammes pour le mot courant de "p"
                {
                    if (j == i) {
                        q = Suivant_mot(prec);
                    } else {
                        q = T[j].tete_mots;
                    }
                    
                    while ( (q != NULL) && (Valeur_nb_car(q) <= Valeur_nb_car(p)) )         //tant qu'on n'a pas atteint la fin de la liste bidirct courante et la taille du mot courant est toujrs <= car si > on va surement pas trouver notre mot dans les mots qui suivent vu que la taille sera toujours superieur
                    {
                        if ( (Valeur_nb_car(q) == Valeur_nb_car(p)) && (Valeur_suiv_anagramme(q) == NULL) && (strcmp( Valeur_mot_ordonne(q) , Valeur_mot_ordonne(p) ) == 0) )    //Valeur_suiv_anagramme(q) = nil car si <>nil le mot q est deja chainée dans une autre liste et donc pas la peine de continuer le test
                        {
                            Aff_adr_angrm(prec , q);
                            prec = q;
                            Tab_anagrm[taille-1].nb_mots++;
                        }
                        q = Suivant_mot(q);
                    }

                }
                if (Tab_anagrm[taille-1].nb_mots == 1)       //cas ou on a pas trouvé d'anagrm on doit reintialiser l'elemnt pour le supprim l'idee c'est de le reutiliser en ecrasant l'ancien contenu
                {
                    taille--;           //on reintialise la taille precedante avant de traiter le "p" actuel; en quelques sorte pour reutiliser l'elem du tableau dans le prochain mot
                }
            }
            p = Suivant_mot(p);
        }
    }
    if (Tab_anagrm[taille].nb_mots == 1)                   //cas ou le dernier element existe toujours alors que ce n'est pas une liste d'anagrammes; (on a decrementer l'indice mais pas liberer l'elem) 
        Tab_anagrm = realloc(Tab_anagrm , taille*sizeof(struct Anagramme));

    *size = taille;                                         //on retourne la taille du tableau
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Affiche_anagrammes(int ty)             //Fonction qui affiche les listes des anagrammes
{   
    if (ty != 0) {
        ptrwords p;
        for (int i = 0 ; i < ty ; i++)
        {   
            printf("\n");
            if (i == 0)
                printf("La premi%cre liste d'anagrammes :\n",138);
            else
                printf("La %d %cme liste d'anagrammes :\n",i+1,138);
            p = Tab_anagrm[i].tete_liste;
            while (1)
            {   
                printf("%s",Valeur_mot(p));
                p = Valeur_suiv_anagramme(p);
                if (p != NULL)
                    printf(" --- ");
                else
                    break;
            }
            printf("\nLe nombre de mots est : %d\n",Tab_anagrm[i].nb_mots);
            printf("\n");
        }
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_adr_prochelex(ptrwords p , ptrwords adr)
{
    p->suiv_prochelex = adr;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

ptrwords Valeur_suiv_prochelex(ptrwords p)
{
    return p->suiv_prochelex;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_val_fin_prochelex(ptrwords p , bool val)
{
    p->fin_prochelex = val;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

bool Valeur_fin_prochelex(ptrwords p)
{
    return p->fin_prochelex;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Remplir_prochelex(int* size)               //Fonction pour remplir tout le tableau "Tab_prochelex" et cree toutes les liste des mots proche lexicalement; retourne la taille du tableau (donc le nombre de listes crees) dans size
{
    int taille = 0 , j , pos , potpos;  //pos : la position du caractere different entre les mots proches lexicalement | potpos : la potentiel position du caractere different
    ptrwords p , prec = NULL , q = NULL ;

    for (int i = 0 ; i < LETTER_ALPHABETIC ; i++)       //boucle pour parcourir toutes les listes bidirect avec le ptr "p"
    {
        p = T[i].tete_mots;
        
        while (p != NULL)                               //boucle pour parcourir tous les mots de la liste bidirect
        {
            if ((Valeur_suiv_prochelex(p) == NULL) && (!Valeur_fin_prochelex(p)))
            {
                prec = p;
                taille++;
                Tab_prochelex = realloc(Tab_prochelex , taille*sizeof(struct Prochelex));
                Tab_prochelex[taille-1].tete_liste = p;
                Tab_prochelex[taille-1].nb_mots = 1;                     //l'indice taille-1 represente tjr le dernier elem du tableau

                for ( j = i ; j < LETTER_ALPHABETIC ; j++)       //la meme boucle pour parcourir toutes les listes bidirect avec le ptr "q" pour trouver les potentiels mots proches lexicalement pour le mot courant de "p"
                {
                    if (j == i) {
                        q = Suivant_mot(prec);
                    } else {
                        q = T[j].tete_mots;
                    }
                    
                    while ( (q != NULL) && (Valeur_nb_car(q) <= Valeur_nb_car(p)) )         //tant qu'on n'a pas atteint la fin de la liste bidirct courante et la taille du mot courant est toujrs <= car si > on va surement pas trouver des potentiels mots proches lexicalement dans les mots qui suivent vu que la taille sera toujours superieur
                    {
                        if ( (Valeur_nb_car(q) == Valeur_nb_car(p)) && (Valeur_suiv_prochelex(q) == NULL) && (!Valeur_fin_prochelex(q)) && ( ( potpos = IsProchelex(Valeur_mot(p) , Valeur_mot(q)) ) > -1 ) && ( (pos == potpos) || (prec == p) ))    //q->suiv_prochelex = nil car si <>nil le mot q est deja chainée dans une autre liste | !q->fin_prochelex (le booleen est faux) c.a.d le mot n'est pas une fin d'une autre liste | la fonction IsProchelex renvoit un entier qui indique la position du caractere different si ils sont proche lexicalement, sinon elle retourne -1 | (pos == potpos) cas ou la liste existe deja; on verifie si la position du caractere different du mot trouver est la meme
                        {
                            if ( prec == p )            //cas du premier proche lexicalement trouver on initialise la position du caractere qui differe
                                pos = potpos;

                            Aff_adr_prochelex(prec , q);
                            prec = q;
                            Tab_prochelex[taille-1].nb_mots++;
                        }
                        q = Suivant_mot(q);
                    }

                }
                if (Tab_prochelex[taille-1].nb_mots == 1)       //cas ou on a pas trouvé de mots proches lexicalement on doit reintialiser l'elemnt pour le supprimer; l'idee c'est de le reutiliser en ecrasant l'ancien contenu
                {
                    taille--;           //on reintialise la taille precedante avant de traiter le "p" actuel; en quelques sorte pour reutiliser l'elem du tableau pour le prochain mot
                }
                else                                           //cas ou on a trouver des mots proches lexicalement donc on garde l'elemt; on affecte "vrai" au champ bool du dernier element de la liste pour indiquer qu'il est le maillon de fin de la liste; ca sert a eviter de le retraiter par la suite et causer des erreurs (l'err sera de creer une autre liste tq la tete c'est la queue de cette liste c'est une concatenation en qlq sortes de deux listes !)
                {
                    Aff_val_fin_prochelex(prec , true);
                }
            }
            p = Suivant_mot(p);
        }
    }
    if (Tab_prochelex[taille].nb_mots == 1)                   //cas ou le dernier element existe toujours alors que ce n'est pas une liste valide; (on a decrementer l'indice mais pas liberer l'elem) 
        Tab_prochelex = realloc(Tab_prochelex , taille*sizeof(struct Prochelex));

    *size = taille;                                         //on retourne la taille du tableau
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

int IsProchelex(char* ch1 , char* ch2)         //Fonction pour comparer deux mots si ils sont proches lexicalement (si 1 seul caractere est different); retourne la position du caractere qui differe sinon retourne -1
{
    int len;

    if ( (len = strlen(ch1)) == strlen(ch2) )
    { 
        int cpt = 0 , pos;

        for (int i = 0 ; (i < len) && (cpt <= 1) ; i++)
        {
            if (ch1[i] != ch2[i])
            {    
                cpt++ ;
                pos = i;
            }
        }
        if (cpt == 1)
            return pos;
        else
            return -1;
    }

    return -1;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Affiche_proche_lex(int ty) 
{
    if (ty != 0) {
        ptrwords p;
        for (int i = 0 ; i < ty ; i++)
        {   
            printf("\n");
            if (i == 0)
                printf("La premi%cre liste de proche lexicalement :\n",138);
            else
                printf("La %d %cme liste de proche lexicalement :\n",i+1,138);
            p = Tab_prochelex[i].tete_liste;
            while (1)
            {   
                printf("%s",Valeur_mot(p));
                p = Valeur_suiv_prochelex(p);
                if (p != NULL)
                    printf(" --- ");
                else
                    break;
            }
            printf("\nLe nombre de mots est : %d\n",Tab_prochelex[i].nb_mots);
            printf("\n");
        }
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_adr_suiv_sequence_mots(ptrwords p , ptrwords adr)
{
    p->suiv_sequence_mots = adr;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_adr_prec_sequence_mots(ptrwords p , ptrwords adr)
{
    p->prec_sequence_mots = adr;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

ptrwords Suivant_seq(ptrwords p) {
    return p->suiv_sequence_mots;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

ptrwords Precedent_seq(ptrwords p) {
    return p->prec_sequence_mots;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Remplir_sequences_mots(int* size)          //Fonction pour creer toutes les sequences de mots formées par l'ajout graduel d'une lettre et les stocker dans le tableau "Tab_sequences_mots" elle retourne la taille du tableau
{
    // 1 : On parcourt les tous les mots pour cree tous les liens bidirectionnels entre les mots formés par l'ajout d'une lettre
    ptrwords p = NULL , q = NULL ;
    bool stop = false;     //condition d'arret pour le traitement d'un mot p si on trouve un mot q formé par l'ajout d'une lettre pour formé DES LISTE; (un mot est pris une seule fois sinon on doit utiliser des arbres)

    for (int i = 0 ; i < LETTER_ALPHABETIC ; i++)       //boucle pour parcourir toutes les listes bidirect avec le ptr "p"
    {
        p = T[i].tete_mots;
        while (p != NULL)                               //boucle pour parcourir tous les mots de la liste bidirect
        {
            if (Suivant_seq(p) == NULL) 
            {
                stop = false;
                for (int j = 0 ; j < LETTER_ALPHABETIC ; j++)       //la meme boucle pour parcourir toutes les listes bidirect avec le ptr "q" pour trouver un potentiel mot proche lexicalement pour le mot courant de "p"
                {   
                    q = T[j].tete_mots;
                    while (q != NULL && Valeur_nb_car(q) < Valeur_nb_car(p) + 1 )          //on saute les mots qui ne peuvent etre formés par l'ajout d'une lettre; car si la longueur de q est inferieur a la longueur de p + 1 : q ne peut etre mot formé par l'ajout d'une lettre a p;
                        q = Suivant_mot(q);
                    while ( (q != NULL) && !stop)         
                    {
                        if ( Precedent_seq(q) == NULL && isonecharadded(Valeur_mot(p) , Valeur_mot(q)) )
                        {
                            Aff_adr_prec_sequence_mots(q,p);                                            //chainage entre les deux maillons
                            Aff_adr_suiv_sequence_mots(p,q);
                            stop = true;
                        }
                        q = Suivant_mot(q);
                    }
                    if (stop)
                        break;
                }
            }
            p = Suivant_mot(p);
        }
    }

    // 2 : On reparcourt pour trouver toutes les listes de sequences de mots crees et les stocker dans le tableau Tab_sequences_mots
    int taille_tab = 0 , taille_liste = 0;
    p = NULL , q = NULL;

    for (int i = 0 ; i < LETTER_ALPHABETIC ; i++)       //boucle pour parcourir toutes les listes bidirect avec le ptr "p" pour trouver les listes bidirect des sequences de mots
    {   
        p = T[i].tete_mots;
        while (p != NULL)        
        {
            if ( Precedent_seq(p) == NULL && Suivant_seq(p) != NULL )           //donc p est une tete de liste (d'une sequence de mots)
            {
                taille_tab++;
                q = Parcourir_liste_bidirect_seq(p, &taille_liste);                         //la fonction "Parcourir_liste_bidirect_seq" va nous permettre de retrouver la queue d'une sequence et sa taille dans "taille_liste"
                Tab_sequences_mots = realloc(Tab_sequences_mots , taille_tab*sizeof(struct sequence_mots));
                Tab_sequences_mots[taille_tab-1].tete_liste = p;
                Tab_sequences_mots[taille_tab-1].queue_liste = q;
                Tab_sequences_mots[taille_tab-1].nb_mots = taille_liste;
            }
            p = Suivant_mot(p);
        }
    }

    *size = taille_tab;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

ptrwords Parcourir_liste_bidirect_seq(ptrwords tete , int* taille)      //Fonction pour parcourir toute une liste bidirect de sequence de mots formé par l'ajout graduel d'une lettre a partir d'une tete donnée et retourne la taille de la liste dans "taille" ainsi qu'un pointeur vers le maillon ptrwords qui contient la queue en sortie
{
    ptrwords p = tete;
    int cpt = 1;

    while (Suivant_seq(p) != NULL)
    {
        cpt++;
        p = Suivant_seq(p);
    }

    *taille = cpt;
    return p;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

bool isonecharadded(char str1[25], char str2[25])           //Fonction qui retourne vrai si str2 est formée par l'ajout d'une lettre a str1 ; retourne faux sinon
{   

    // Si la longueur de str2 n'est pas exactement égale à la longueur de str1 + 1, alors str2 ne peut pas être construite en ajoutant un seul caractère à str1
    int len = strlen(str1);
    if (strlen(str2) != len + 1)
        return false;

    // Variables pour parcourir les deux chaînes
    int i = 0, j = 0;
    // Compteur pour le nombre de caractères différents entre les deux chaînes
    int cpt = 0;

    // Parcours des deux chaînes jusqu'à ce qu'on atteigne la fin de l'une des deux chaînes
    while (i < len && j < len + 1) { // Ici en peut mettre && ou || car les deux fonctionne
        // Si les caractères à la position i et j sont différents, on incrémente le compteur cpt
        if (str1[i] != str2[j]) {
            cpt++;
        } else {
            // Sinon, on passe au caractère suivant dans str1
            i++;
        }
        // On passe au caractère suivant dans str2
        j++;

        // Si cpt est supérieur à 1, cela signifie que plus d'un caractère est différent entre les deux chaînes, donc on renvoie false
        if (cpt > 1)
            return false;
    }
    // Si on arrive ici, cela signifie que str2 peut être construite en ajoutant exactement un caractère à str1, donc on renvoie true
    return true;
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Affiche_sous_seq(int ty)           //Fonction pour afficher les listes de sous sequence
{
    if (ty != 0) {
        ptrwords p;
        for (int i = 0 ; i < ty ; i++)
        {   
            printf("\n");
            if (i == 0)
                printf("La premi%cre liste de sous sequence :\n",138);
            else
                printf("La %d %cme liste de sous sequence :\n",i+1,138);
            p = Tab_sequences_mots[i].tete_liste;
            while (1)
            {   
                printf("%s",Valeur_mot(p));
                p = Suivant_seq(p);
                if (p != NULL)
                    printf(" --- ");
                else
                    break;
            }
            printf("\nLe nombre de mots est : %d\n",Tab_sequences_mots[i].nb_mots);
            printf("\n");
        }
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

bool issouschainemadeoff(char str1[25], char str2[25])         //Fonction qui vérifie si str2 est construite en ajoutant un prefix ou sufix ou sous chaine à str1
{
    int len1 = strlen(str1); // longueur de la première chaîne
    int len2 = strlen(str2); // longueur de la deuxième chaîne

    if (len2 <= len1) return false; // Si len2 est inférieur ou égal à len1, alors str2 ne peut pas être créée en ajoutant un préfixe ou un suffixe ou sous chaine à str1.

    int i = 0, j = 0; // Index pour parcourir les deux chaînes
    bool diffFound = false; // Booléen pour indiquer si une différence a été trouvée entre les deux chaînes

    while (i < len1 && j < len2) { // Parcours simultané des deux chaînes
        if (str1[i] == str2[j]) { // Si les caractères des deux chaînes sont les mêmes
            i++; // On incrémente l'index de la première chaîne
            j++; // On incrémente l'index de la deuxième chaîne
        } else if (str1[i] != str2[j] && !diffFound) { // Si on trouve une différence pour la première fois
            j = j + len2 - len1; // On saute la partie de la deuxième chaîne qui ne peut pas être de str1
            diffFound = true; // On indique qu'une différence a été trouvée
        } else { // Si on trouve une deuxième différence ou plus
            return false; // On retourne faux, car str2 ne peut pas être créée en ajoutant un préfixe ou un suffixe ou sous chaine à str1.
        }
    }
    return true; // Si on a parcouru toute la deuxième chaîne avec succès, c'est que str2 est créée en ajoutant un préfixe ou un suffixe ou sous chaine à str1.
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

ptrwords Valeur_sous_chaine(ptrwords p) {
    return p->suiv_sous_chaine;
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

char Valeur_indice_sous_chaine(ptrwords p) {
    return p->indice_sous_chaine;
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_adr_sous_chaine(ptrwords ptr1, ptrwords ptr2) {
    ptr1->suiv_sous_chaine = ptr2;
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_val_indice_sous_chaine(ptrwords p , char c) {
    p->indice_sous_chaine = c;
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

int Valeur_nb_mot_sous_chaine(ptrSousChaine p) {
    return p->nb_mots;
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Aff_val_nb_mot_sous_chaine(ptrSousChaine p , int nb) {
    p->nb_mots = nb;
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/

int Cree_tab_sous_chaine()          //Fonction qui va parcourir les mots et crée le tableau des tete de liste
{
    ptrwords p , q;
    int cpt;
    int i = 0 , size = 0;
    for ( i ; i < LETTER_ALPHABETIC ; i++ ) {
        p = T[i].tete_mots;
        while (p != NULL) {
            if (Valeur_indice_sous_chaine(p) == 2) {
                size++;
                Tab_sous_chaine = realloc(Tab_sous_chaine , size*sizeof(struct sous_chaine));
                Tab_sous_chaine[size - 1].tete_liste = p;
                q = p;
                cpt = 0;
                while (q != NULL)
                {
                    cpt++;
                    q = Valeur_sous_chaine(q);
                }
                Aff_val_nb_mot_sous_chaine(&Tab_sous_chaine[size - 1] , cpt);  
            }
            p = Suivant_mot(p);
        }
    }
    return size;
};


/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Remplire_sous_chaine(int* taille) {
    ptrwords p , q;
    int i , j;
    bool Trouver;
    for(i = 0 ; i < LETTER_ALPHABETIC ; i++ ) {
        p = T[i].tete_mots;
        while ( p != NULL)
        {
            Trouver = false;
            for ( j = 0 ; j < LETTER_ALPHABETIC ; j++ ) {
                q = T[i].tete_mots;
                while ( !Trouver && q != NULL)
                {
                    if ( Valeur_indice_sous_chaine(q) != 1 ) {
                        if ( issouschainemadeoff( Valeur_mot(p) , Valeur_mot(q) ) ) {
                            Aff_adr_sous_chaine(p , q);
                            Aff_val_indice_sous_chaine(q , 1);
                            if ( Valeur_indice_sous_chaine(p) == 0 ) {
                                Aff_val_indice_sous_chaine(p , 2);
                            }
                            Trouver = true;
                        }
                    }
                    q = Suivant_mot(q);
                }
                if (Trouver) break;
            } 
            p = Suivant_mot(p);
        }  
    }
    *taille = Cree_tab_sous_chaine();
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Affiche_sous_chaine(int ty) {
    ptrwords p;
    for (int i = 0 ; i < ty ; i++)
    {   
        printf("\n");
        if (i == 0)
            printf("La premi%cre liste de sous chaine :\n",138);
        else
            printf("La %d %cme liste de sous chaine :\n",i+1,138);
        p = Tab_sous_chaine[i].tete_liste;
        while (1)
        {   
            printf("%s",Valeur_mot(p));
            p = Valeur_sous_chaine(p);
            if (p != NULL)
                printf(" --- ");
            else
                break;
        }
        printf("\nLe nombre de mots est : %d\n",Tab_sous_chaine[i].nb_mots);
        printf("\n");
    }
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void Affiche_mots_simple(void)          //Fonction qui affiche tous les mots en compresser
{
    int i = 0 , cpt = 0;
    ptrwords p;
    for (i = 0 ; i < LETTER_ALPHABETIC ; i++)
    {
        p = T[i].tete_mots;
        while (p != NULL)
        {
            cpt++;
            if (cpt == 1)
                printf("%-25s",Valeur_mot(p));
            else
                printf("--- %-25s",Valeur_mot(p));
            p = Suivant_mot(p);
            if (cpt == 4)
            {
                printf("\n");
                cpt = 0;
            }
        }
    }
    printf("\n");
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/

void reinit_base_donnees(void)          //Fonction qui va reintialiser toutes les structures utiliser dans le programme et les pointeurs de tous les mots également
{
    int i = 0;
    ptrwords p = 0;

    size1 = size2 = size3 = size4 = size5 = 0;
    Tab_anagrm = realloc(Tab_anagrm,0);
    Tab_prochelex = realloc(Tab_prochelex,0);
    Tab_sequences_mots = realloc(Tab_sequences_mots,0);
    Tab_sous_chaine = realloc(Tab_sous_chaine,0);
    
    for (i = 0 ; i < LETTER_ALPHABETIC ; i++)
    {
        p = T[i].tete_mots;
        while (p != NULL)
        {   
            Aff_adr_ED(p , NULL);
            Aff_adr_ING(p , NULL);
            Aff_adr_angrm(p, NULL);
            Aff_adr_prochelex(p, NULL);
            Aff_val_fin_prochelex(p , false);
            Aff_adr_suiv_sequence_mots(p, NULL);
            Aff_adr_prec_sequence_mots(p, NULL);
            Aff_adr_sous_chaine(p , NULL);
            Aff_val_indice_sous_chaine(p,0);
            p = Suivant_mot(p);        
        }
    }
}


#endif
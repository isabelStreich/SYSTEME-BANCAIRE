#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include "RockUtiles.h"

using namespace std;

const unsigned short TAILLE_NOM = 31;
const unsigned short TAILLE_PRENOM = 31;

struct compte {
	unsigned int noCompte;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	double solde;
	bool actif;
};

enum TypeTransaction {
	DEPOT,
	RETRAIT
};

enum TypeDeTri {
	NO_COMPTE,
	NOM,
	PRENOM,
	SOLDE
};

enum OrdreDeTri {
	ASCENDANT,
	DESCENDANT
};



void afficherMenu(compte comptes[], unsigned int nbComptes);

void ajouterCompte(compte comptes[], unsigned int& nbComptesActuels);
void desactiverCompte(compte comptes[], unsigned int indice);

double calculerSommeSoldes(compte comptes[], unsigned int nbComptes);

unsigned int recupererNombreCompteActif(compte comptes[], unsigned int nbComptes);

void afficherSoldeMoyen(compte comptes[], unsigned int nbComptes);
void afficherSommeSoldes(compte comptes[], unsigned int nbComptes);
int rechercherClient(compte comptes[], unsigned int nbComptes);
void afficherComptes(compte comptes[], unsigned int nbComptes);
void afficherCompte(compte compte);

void effectuerTransaction(TypeTransaction typeTransaction, compte &compte, double montant);
void effectuerDepot(compte &compte, double montant);
void effectuerRetrait(compte &compte, double montant);

void echanger(compte &compte1, compte &compte2);
void trierComptes(TypeDeTri typeDeTri, OrdreDeTri ordreDeTri, compte comptes[], unsigned int nbComptes);
int saisirNoCompte(int nbDeComptes);
double saisirMontant();
void saisirChaine(char chaine[], const unsigned short TAILLE);

void cadre(int cd, int ld, int cf, int lf, int);




int main() {
	char enter;
	compte comptes[999];

	unsigned int nbDeComptes = 0;
	int indice;
	double montant;
	resetPalette();
	gotoXY(10, 10);
	whereX();
	whereY();

	do {

		system("cls");

		afficherMenu(comptes, nbDeComptes);
		cadre(10, 0, 110, 23, 12);
		enter = _getch();

		system("cls");
		switch (enter) {
		case '1':
			gotoXY(25, 4); ajouterCompte(comptes, nbDeComptes);
			gotoXY(25, 6); nbDeComptes++;
			break;
		case '2':
			gotoXY(25, 7); indice = saisirNoCompte(nbDeComptes);
			gotoXY(25, 8); desactiverCompte(comptes, indice);
			break;
		case '3':
			gotoXY(25, 7); indice = saisirNoCompte(nbDeComptes);
			gotoXY(25, 8); afficherCompte(comptes[indice]);
			break;
		case '4':
			gotoXY(25, 7); indice = saisirNoCompte(nbDeComptes);
			gotoXY(25, 9); cout << "Entrer depot: ";
			gotoXY(25, 10); montant = saisirMontant();
			gotoXY(25, 12); effectuerTransaction(TypeTransaction::DEPOT, comptes[indice], montant);
			break;
		case '5':
			gotoXY(25, 7); indice = saisirNoCompte(nbDeComptes);
			gotoXY(25, 10); cout << "Entrer retrait: ";
			gotoXY(25, 11); montant = saisirMontant();
			gotoXY(25, 12); effectuerTransaction(TypeTransaction::RETRAIT, comptes[indice], montant);
			break;
		case '6':
			gotoXY(25, 5); trierComptes(TypeDeTri::NOM, OrdreDeTri::ASCENDANT, comptes, nbDeComptes);
			break;
		case '7':
			gotoXY(25, 14); afficherSommeSoldes(comptes, nbDeComptes);
			break;
		case '8':
			gotoXY(25, 15); afficherSoldeMoyen(comptes, nbDeComptes);
			break;
		}
	} while (enter != '9');





	gotoXY(25, 10); system("exit");
	return 0;
}

/*
	Tâche : afficher le menu principal
	paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes dans l'application en ce moment
*/
void afficherMenu(compte comptes[], unsigned int nbComptes) {
	cadre(10, 0, 110, 23, 12);
	cout << " " << endl;
	color(11);
	gotoXY(25, 5);
	cout << "*******************" << "BANK " << "*******************" << endl;
	gotoXY(25, 6);
	cout << "1 Ajouter un compte de la banque" << endl;
	gotoXY(25, 7);
	cout << "2 Retirer un compte de la banque" << endl;
	gotoXY(25, 8);
	cout << "3 Afficher l'information d'un compte client en particulier (par no de compte)" << endl;
	gotoXY(25, 9);
	cout << "4 Effectuer un depot dans un compte en particulier (par no de compte)" << endl;
	gotoXY(25, 10);
	cout << "5 Effectuer un retrait dans un compte en particulier (par no de compte)" << endl;
	gotoXY(25, 11);
	cout << "6 Trier et afficher la liste des clients" << endl;
	gotoXY(25, 12);
	cout << "7 Afficher la somme totale de tout les comptes" << endl;
	gotoXY(25, 13);
	cout << "8 Afficher le solde moyen des comptes" << endl;
	gotoXY(25, 14);
	cout << "9 Quitter  l'application" << endl;
	gotoXY(25, 15);
	gotoXY(25, 16); cout << "Veuillez saisir une option(1 a 9)" << endl;

}


/*
	Tâche : ajouter un compte
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes dans l'application en ce moment

*/
void ajouterCompte(compte comptes[], unsigned int& nbComptesActuels) {
	gotoXY(25, 2); char chaine[TAILLE_PRENOM];
	cadre(10, 0, 110, 23, 12);
	gotoXY(25, 3); cout << "" << endl;
	gotoXY(25, 4); cout << "AJOUTER UN COMPTE" << "**********" << endl;
	gotoXY(25, 6); cout << "Entrer le prenom du client: ";
	gotoXY(25, 7); saisirChaine(comptes[nbComptesActuels].prenom, TAILLE_PRENOM);
	gotoXY(25, 8); cout << "Entrer le nom: ";
	gotoXY(25, 9); saisirChaine(comptes[nbComptesActuels].nom, TAILLE_NOM);
	gotoXY(25, 10); cout << "Entrer solde de depart: ";
	gotoXY(25, 11); comptes[nbComptesActuels].solde = saisirMontant();
	gotoXY(25, 12); comptes[nbComptesActuels].actif = true;
	gotoXY(25, 13); comptes[nbComptesActuels].noCompte = nbComptesActuels;


	gotoXY(25, 14); cout << "Compte cree avec succes" << endl;

	gotoXY(25, 15); system("pause");



}

/*
	Tâche : désactiver un compte si son solde est 0, sinon afficher un message
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes dans l'application en ce moment
*/
void desactiverCompte(compte comptes[], unsigned int indice) {
	cadre(10, 0, 110, 23, 12);
	gotoXY(25, 5); cout << "DESACTIVER UN COMPTE" << endl; gotoXY(25, 6); cout << "*******************" << endl;

	if (comptes[indice].actif == false) {
		gotoXY(25, 7); cout << "Le compte est deja desactive" << endl;
	}
	else if (comptes[indice].actif && comptes[indice].solde == 0) {
		comptes[indice].actif = false;
		gotoXY(25, 8); cout << "Compte no " << comptes[indice].noCompte << " desactive" << endl;
	}

	else { gotoXY(25, 11); cout << "Impossible de desactiver le compte, le solde n'est pas a 0" << endl; }
	gotoXY(25, 10); system("pause");

}

/*
	Tâche : calculer la somme de toutes les comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
*/
double calculerSommeSoldes(compte comptes[], unsigned int nbComptes) {
	double sommeSolde = 0;
	for (int i = 0; i < nbComptes; i++) {
		if (comptes[i].actif) {
			sommeSolde += comptes[i].solde;
		}
	}
	return sommeSolde;
}

/*
	Tâche : afficher la somme de toutes les comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
*/
void afficherSommeSoldes(compte comptes[], unsigned int nbComptes) {
	cadre(10, 0, 110, 23, 12);
	gotoXY(25, 4); cout << "La somme de tous les soldes est " << calculerSommeSoldes(comptes, nbComptes) << endl;
	gotoXY(25, 9); system("pause");
}
/*
	Tâche : récupérer le nombre total de comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
*/
unsigned int recupererNombreCompteActif(compte comptes[], unsigned int nbComptes) {
	// à compléter
	gotoXY(25, 9); return 0;
}

/*
	Tâche : affcher la moyenne des soldes de toutes les comptes actifs
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
*/
void afficherSoldeMoyen(compte comptes[], unsigned int nbComptes) {
	cadre(10, 0, 110, 23, 12);
	gotoXY(25, 4); double sommeSolde = 0;
	gotoXY(25, 5); int compteur = 0;
	for (int i = 0; i < nbComptes; i++) {
		if (comptes[i].actif) {
			sommeSolde += comptes[i].solde;
			compteur++;

		}


	}
	gotoXY(25, 6); cout << "Le solde moyen de tous les comptes est " << sommeSolde / compteur << endl;
	gotoXY(25, 8); system("pause");
}




/*
	Tâche : demander un numéro de compte et rechercher un compte actif en fonction du numéro de client saisie. Affiche "Compte inexistant" et retourne -1 si le compte
	est inexistant, sinon retourne l'indice dans le tableau ou se trouve le compte.
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
*/
int rechercherClient(compte comptes[], unsigned int nbComptes) {
	cadre(10, 0, 110, 23, 12);
	// à compléter
	gotoXY(25, 8); return 0;
}

/*
	Tâche : affiche les informations de toutes les comptes actifs.
	Paramètres : comptes : représente la liste complète des comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment
*/
void afficherComptes(compte comptes[], unsigned int nbComptes) {
	cadre(10, 0, 110, 23, 12);
	// à compléter

}

/*
	Tâche : affiche les informations d'un seul compte.
	Paramètres : compte : représente le compte d'un seul client
*/
void afficherCompte(compte compte) {
	cadre(10, 0, 110, 23, 12);
	gotoXY(25, 3); cout << "Numero de compte: " << compte.noCompte << endl;
	gotoXY(25, 4); cout << "Prenom: " << compte.prenom << endl;
	gotoXY(25, 5); cout << "Nom: " << compte.nom << endl;
	gotoXY(25, 6); cout << "Solde: " << compte.solde << endl;
	gotoXY(25, 8); system("pause");

}


/*
	Tâche : affectuer une transaction bancaire sur un compte en fonction d'un type de transaction et d'un montant
	Paramètres : typeTransaction : le type de transaction effectué
				 compte : représente le compte d'un client
				 montant : le montant de la transaction

*/
void effectuerTransaction(TypeTransaction typeTransaction, compte &compte, double montant) {
	cadre(10, 0, 110, 23, 12);
	if (typeTransaction == DEPOT) {
		gotoXY(25, 10); effectuerDepot(compte, montant);
	}
	 else { gotoXY(25, 10); effectuerRetrait(compte, montant); }

}

/*
	Tâche : affectuer un dépot dans le compte d'un client.
	Paramètres : compte : représente le compte d'un client
				 montant : le montant de la transaction
*/
void effectuerDepot(compte &compte, double montant) {
	cadre(10, 0, 110, 23, 12);
	compte.solde += montant;
	gotoXY(25, 5); cout << "Nouveau solde: " << compte.solde << endl;
	gotoXY(25, 13); system("pause");
}

/*
	Tâche : affectuer un retrait dans le compte d'un client.
	Paramètres : compte : représente le compte d'un client
				 montant : le montant de la transaction
*/
void effectuerRetrait(compte &compte, double montant) {
	cadre(10, 0, 110, 23, 12);
	compte.solde -= montant;
	gotoXY(25, 5); cout << "Nouveau solde: " << compte.solde << endl;
	gotoXY(25, 13); system("pause");

}

/*
	Tâche : trier les comptes en fonction du mode de tri et de l'ordre de tri passés en paramètre.
	Paramètres : typeDeTri : le type de tri désiré
				 ordreDeTri : l'ordre de tri désiré
				 comptes : le tableau de toutes les comptes dans l'application
				 nbComptes : représente le nombre de comptes saisies dans l'application en ce moment

*/
void trierComptes(TypeDeTri typeDeTri, OrdreDeTri ordreDeTri, compte comptes[], unsigned int nbComptes) {
	gotoXY(25, 3); cadre(10, 0, 110, 23, 12);
	// à compléter


}

/*
	Tâche : échanger en mémoire le contenu de deux comptes
	Paramètres : compte1 et compte2 : représente les comptes à échanger
*/
void echanger(compte &compte1, compte &compte2) {
	// à compléter
	cadre(10, 0, 110, 23, 12);
}
//Fonction pour valider la saisie d'un compte
int saisirNoCompte(int nbDeComptes) {
	
	int indice;
	 
	gotoXY(25, 3); cadre(10, 0, 110, 23, 12);
	gotoXY(25, 4); cout << "Saisir le no de compte : ";
	gotoXY(25, 5); cin >> indice;
	while (cin.fail() || cin.peek() != '\n' || indice >= nbDeComptes || indice < 0) {
		cin.clear();
		cin.ignore(512, '\n');
		gotoXY(25, 7); cout << "Saisir un no de compte valide : ";
		gotoXY(25, 8); cin >> indice;
	}
	cin.ignore(512, '\n');
	gotoXY(25, 9); return indice;
}
//Fonctions pour valider des saisies
double saisirMontant() {
	double montant;
	gotoXY(25, 3); cadre(10, 0, 110, 23, 12);
	gotoXY(25, 11); cin >> montant;
	while (cin.fail() || cin.peek() != '\n' || montant <= 0) {
		cin.clear();
		cin.ignore(512, '\n');
		gotoXY(25, 12); cout << "Saisir une valeur numerique(>0) : ";
		gotoXY(25, 13); cin >> montant;
	}
	 cin.ignore(512, '\n');
	 gotoXY(25, 13); return montant;
}

void saisirChaine(char chaine[], const unsigned short TAILLE) {
	
	cin.getline(chaine, TAILLE);
	while (cin.fail()) {
		cin.clear();
		cin.ignore(512, '\n');
		gotoXY(25, 7); cout << "Attention, 30 caracteres maximum: " << endl;
		cin.getline(chaine, TAILLE);
	}

}




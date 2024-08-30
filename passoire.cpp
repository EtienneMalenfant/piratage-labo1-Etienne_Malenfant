#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	//Si on ne donne pas asser d'argument ou si on ne lui donne pas les bons types, le programme ne compile pas / plante au d�marrage
	//Ce n'est pas grave, le seule cons�quence est qu'on ne peut pas ex�cuter le programme
	//Une solution serait de v�rifier le nombre d'argument avant d'ex�cuter le programme. Ensuite pour chaque commande, on v�rifie si
	//elle correspond aux crit�res (type, grosseur, longueur).
	if (argc != 6) {
		cout << "Nombre d'argument invalide. 5 arguments sont requis.";
		return -1;
	}

	int pansDeCloture { stoi(argv[1])};
	float montantAPayer { stof(argv[2])};
	float coutParPan {montantAPayer / pansDeCloture};

	// Poteaux n�cessaires pour faire une cl�ture en ligne droite
	int poteaux {pansDeCloture};
	montantAPayer += poteaux * 5;

	//Si l'argument du nom de fichier d�passe les 10 caract�res, �a l�ve une exeption qui fait planter l'application
	//On pourrait exploiter la faille pour faire un buffer overflow pour ins�rer du code malicieux dans la m�moire.
	//Une solution serait de v�rifier la longueur de l'argument avant de le copier, ou d'utliser strncpy() pour pas copier
	//si la string re�ue est trop grosse
	char nomFichier[10];
	strncpy(nomFichier, argv[3], sizeof(nomFichier));
	strcat(nomFichier, ".exe");
	ofstream fichier {nomFichier};
	fichier << argv[4];

	//On peut imprimer des caract�re sp�ciaux commen�ant par %.
	//On peut par exemple faire crash l'application, ou obtenir des adresses m�moire avec %p. En obtenant les adresses m�moire utilis�
	//par l'application, on pourrait peut �tre injecter des donn�es malicieuces dans la m�moire utilis� par l'application.
	//Une solution
	const char * msg {argv[4]};
	printf(msg, pansDeCloture, coutParPan);

	/*-En �x�cutant une commande de l'utilisateur sans la filtrer, il pourrait ex�cuter n'importe quelle commande.
	-On pourrait ex�cuter des commandes localement comme "shutdown /s" ce qui ferme l'ordi, on pourrait aussi acc�der aux
	donn�es de l'ordinateur, les supprim�, les r�cup�r�s etc, ou pourrait aussi �x�cuter un script.
	Bref, toutes sortes de choses malicieuses peuvent �tre faites en �x�cutant une commande. On pourrait totalement briser le syst�me
	d'exploitation ou voler/briser des donn�es.
	-La meilleur solution pour r�gler le probl�me serait de ne pas ex�cuter de commande. Mais si on y tient, on pourrait v�rifier si la commande
	est permise en la comparant � une liste de commandes permises. Si elle ne l'est pas, on �x�cute pas.
	*/
	const char* commande {argv[5]};
	system(commande);
}
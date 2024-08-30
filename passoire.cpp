#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	//Si on ne donne pas asser d'argument ou si on ne lui donne pas les bons types, le programme ne compile pas / plante au démarrage
	//Ce n'est pas grave, le seule conséquence est qu'on ne peut pas exécuter le programme
	//Une solution serait de vérifier le nombre d'argument avant d'exécuter le programme. Ensuite pour chaque commande, on vérifie si
	//elle correspond aux critères (type, grosseur, longueur).
	if (argc != 6) {
		cout << "Nombre d'argument invalide. 5 arguments sont requis.";
		return -1;
	}

	int pansDeCloture { stoi(argv[1])};
	float montantAPayer { stof(argv[2])};
	float coutParPan {montantAPayer / pansDeCloture};

	// Poteaux nécessaires pour faire une clôture en ligne droite
	int poteaux {pansDeCloture};
	montantAPayer += poteaux * 5;

	//Si l'argument du nom de fichier dépasse les 10 caractères, ça lève une exeption qui fait planter l'application
	//On pourrait exploiter la faille pour faire un buffer overflow pour insérer du code malicieux dans la mémoire.
	//Une solution serait de vérifier la longueur de l'argument avant de le copier, ou d'utliser strncpy() pour pas copier
	//si la string reçue est trop grosse
	char nomFichier[10];
	strncpy(nomFichier, argv[3], sizeof(nomFichier));
	strcat(nomFichier, ".exe");
	ofstream fichier {nomFichier};
	fichier << argv[4];

	//On peut imprimer des caractère spéciaux commençant par %.
	//On peut par exemple faire crash l'application, ou obtenir des adresses mémoire avec %p. En obtenant les adresses mémoire utilisé
	//par l'application, on pourrait peut être injecter des données malicieuces dans la mémoire utilisé par l'application.
	//Une solution
	const char * msg {argv[4]};
	printf(msg, pansDeCloture, coutParPan);

	/*-En éxécutant une commande de l'utilisateur sans la filtrer, il pourrait exécuter n'importe quelle commande.
	-On pourrait exécuter des commandes localement comme "shutdown /s" ce qui ferme l'ordi, on pourrait aussi accéder aux
	données de l'ordinateur, les supprimé, les récupérés etc, ou pourrait aussi éxécuter un script.
	Bref, toutes sortes de choses malicieuses peuvent être faites en éxécutant une commande. On pourrait totalement briser le système
	d'exploitation ou voler/briser des données.
	-La meilleur solution pour régler le problème serait de ne pas exécuter de commande. Mais si on y tient, on pourrait vérifier si la commande
	est permise en la comparant à une liste de commandes permises. Si elle ne l'est pas, on éxécute pas.
	*/
	const char* commande {argv[5]};
	system(commande);
}
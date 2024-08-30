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

	//Si un des 2 premiers arguments ne peuvent être converti en leur valeurs respective (int et float), le programme ne peut compiler.
	//L'inconvénient est qu'on ne peut utiliser l'application si on ne spécifie pas les bon arguments. Il vaut mieux quitter l'exécution
	//et expliquer pourquoi au lieu de planter.
	//On peut régler le problème en englobant la conversion dans un try catch.
	int pansDeCloture{ 0 };
	float montantAPayer{ 0.f };
	try {
		pansDeCloture = stoi(argv[1]);
		montantAPayer = stof(argv[2]);
	}
	catch (const exception& e) {
		cout << "Erreur:, un des argument n'a pu etre converti en valeur numerique. Le premier doit être de type int et le deuxième de type float." << endl << e.what();
		return -2;
	}
	float coutParPan{ montantAPayer / pansDeCloture };

	// Poteaux nécessaires pour faire une clôture en ligne droite
	int poteaux{ pansDeCloture };
	montantAPayer += poteaux * 5;

	//Si l'argument du nom de fichier dépasse les 10 caractères, ça lève une exeption qui fait planter l'application
	//On pourrait exploiter la faille pour faire un buffer overflow pour insérer du code malicieux dans la mémoire. Aussi, si
	// on dépasse le tableau cela pourrait corrompre les données dans les cases mémoires d'après.
	//Une solution serait de vérifier la longueur de l'argument avant de le copier, ou d'utliser strncpy() pour pas copier
	//si la string reçue est trop grosse.  Je fait de-même pour strcat() en strncat();
	char nomFichier[10];
	strncpy(nomFichier, argv[3], sizeof(nomFichier));
	strncat(nomFichier, ".exe", sizeof(nomFichier));
	ofstream fichier{ nomFichier };
	//Si le fichier n'a pu être créer, l'application plante
	//On pourrait faire exprès que le fichier ne peut être créer pour faire planter intentionnelement l'application.
	//La solution est de vérifier si le fichier est vlaide avant de procédé
	if (!fichier) {
		cout << "Erreur, le fichier n'a pu être créer";
		return -3;
	}
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
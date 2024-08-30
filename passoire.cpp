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

	//Si un des 2 premiers arguments ne peuvent �tre converti en leur valeurs respective (int et float), le programme ne peut compiler.
	//L'inconv�nient est qu'on ne peut utiliser l'application si on ne sp�cifie pas les bon arguments. Il vaut mieux quitter l'ex�cution
	//et expliquer pourquoi au lieu de planter.
	//On peut r�gler le probl�me en englobant la conversion dans un try catch.
	int pansDeCloture{ 0 };
	float montantAPayer{ 0.f };
	try {
		pansDeCloture = stoi(argv[1]);
		montantAPayer = stof(argv[2]);
	}
	catch (const exception& e) {
		cout << "Erreur:, un des argument n'a pu etre converti en valeur numerique. Le premier doit �tre de type int et le deuxi�me de type float." << endl << e.what();
		return -2;
	}
	float coutParPan{ montantAPayer / pansDeCloture };

	// Poteaux n�cessaires pour faire une cl�ture en ligne droite
	int poteaux{ pansDeCloture };
	montantAPayer += poteaux * 5;

	//Si l'argument du nom de fichier d�passe les 10 caract�res, �a l�ve une exeption qui fait planter l'application
	//On pourrait exploiter la faille pour faire un buffer overflow pour ins�rer du code malicieux dans la m�moire. Aussi, si
	// on d�passe le tableau cela pourrait corrompre les donn�es dans les cases m�moires d'apr�s.
	//Une solution serait de v�rifier la longueur de l'argument avant de le copier, ou d'utliser strncpy() pour pas copier
	//si la string re�ue est trop grosse.  Je fait de-m�me pour strcat() en strncat();
	char nomFichier[10];
	strncpy(nomFichier, argv[3], sizeof(nomFichier));
	strncat(nomFichier, ".exe", sizeof(nomFichier));
	ofstream fichier{ nomFichier };
	//Si le fichier n'a pu �tre cr�er, l'application plante
	//On pourrait faire expr�s que le fichier ne peut �tre cr�er pour faire planter intentionnelement l'application.
	//La solution est de v�rifier si le fichier est vlaide avant de proc�d�
	if (!fichier) {
		cout << "Erreur, le fichier n'a pu �tre cr�er";
		return -3;
	}
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
////////********************************* Tema 1 - EGC ***********************************////////
////////********************** Ciuciu Ioan-Dionisie   333 CA *****************************////////


__ ______________________
 1| Utilizare Aplicatie:
__| ---------------------

	Aplicatia creata, "Geometry Wars", are urmatoarele functionalitati:
		
		- W : miscare in sus
		- A : miscare la stanga
		- S : miscare in jos
		- D : miscare in dreapta
		- right-click : player-ul va lansa un proiectil, pe directia curenta a mouseului.
		
	Inamicii sunt spawnati random, inauntrul ferestrei, iar dupa ce player-ul elimina 25 de inamici, 
apare un inamic "boss" care daca este eliminat, jocul se termina.

__ ________________________
 2| Detalli de implementare:
__| -----------------------

	Pentru implementarea aplicatiei, am folosit o clasa generica GameObject, mostenita de clasele
Enemy, Player, si Bullet. Aceste obiecte au fost instantiate in clasa Laborator3, mentionand
ca pentru rezolvarea temei am folosit framework-ul de laborator. 
	Pentru inamici, si proiectile, folosesc vectori, in care le introduc dupa ce le initializez
proprietatile ( cum ar fi viteza, coordonate x si y, unghi de rotatie), pe masura ce am nevoie
de un astfel de element.
	Pentru desenarea obiectelor am folosit 2 functii, createRectangle si createTriangle, astfel
incat un player este compus din doua forme de triunghi unite, la fel un inamic, iar proiectilul
reprezinta un simplu dreptunghi. 
	Terminarea jocului este contorizata de niste variabile locale, numite wonGame si gameState.
Atunci cand player-ul ramane fara vieti, state-ul game-ului este "gameOver", iar atunci cand
player-ul ajunge la finalul jocului, variabila wonGame este setata pe 1. Aceste variabile sunt
folosite pentru a sti cand trebuie spawnate obiecte si cand nu, dar si pentru animatia de final
a jocului.

__ __________________
 4| Probleme aparute:
__| -----------------

	Cea mai grea parte a temei, din punctul meu de vedere, a fost tratarea coliziunilor, si
toate elementele matematice pe care rezolvarea acestei teme le-a inclus. Pentru tratarea coli-
ziunilor, am avut 2 tipuri de coliziuni, una intre inamic si player, si alta intre inamic si 
proiectil. Acestea au fost tratate similar, folosind distanta dintre centrele celor doua, com-
parata cu suma razelor cercurilor care incadreaza cele doua obiecte care intra in coliziune.
	O alta parte grea, a fost sa fac inamicii sa se spawneze o data la un timp stabilit, 
fapt pe care l-am rezolvat folosind Engine::GetElapsedTime(), pentru a afla timpul de cand
a pornit jocul.

__ ______________________________________________________
 5| Descriere bonus + Status implementare functionalitati
__| -----------------------------------------------------

	Specific ca toate functionalitatile obligatorii ale temei au fost implementate, si in
plus, am rezolvat partea din bonus care presupunea spawnarea unui inamic mai mare, "boss",
care se spawneaza dupa ce player-ul elimina 25 de inamici, si se misca doar pe coordonata
y, tragand in tot acest timp cu proiectile care se deplaseaza doar pe axa x. Acestea nu se 
indreapta inspre player, dar daca player-ul este atins de un singur proiectil, jocul se 
sfarseste. Pentru a-l distruge, player-ul trebuie sa il faca pe "boss" sa isi piarda toate
cele 10 vieti.

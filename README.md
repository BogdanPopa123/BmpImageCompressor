## Tema 2 - SDA
Popa Bogdan-Florin

Timp de lucru - aproximativ 8 ore

Punctaj checker local - 100/100

Punctaj vmchecker - 100/100


Mai intai am inceput prin a declara strcturile necesare pentru
implementarea structurilor de date ce vor fi necesare in realizarea
acestei teme:

* Structul Tree reprezinta un nod al arborelui cuaternar ce va fi
folosit la compresia fisierului PPM

* Structul pixel este folosit pentru a stoca valorile RGB ale unui
pixel din fisierul imagine in format PPM

* Structul QueueNode reprezinta nodul folosit pentru a implementa
coada ce va contine elemente de tip Tree. Aceste noduri contin pointer
catre urmatorul element din lista precum si Tree elementul curent.

* Structul Queue reprezinta coada de noduri Tree, aceasta continand doar
doua elemente, anume pointer catre primul si ultimul element din
coada.




Functiile folosite in acest program sunt:

* createQueue - folosita pentru initializarea cozii

* isEmptyQueue - verifica daca coada este goala sau nu

* enqueue - folosita pentru a adauga un element nou in coada

* dequeue - folosita pentru a scoate un element din coada

* front/rear - folosite pentru a returna primul/ultimul element din coada

* initTree - folosita pentru a initializa un nou nod al arborelui de compresie

* solve - folosita pentru a crea arborele de compresie pe baza matricei de
pixeli ce reprezinta imaginea din fisierul PPM

* fillPixelMap - folosita pentru a crea matricea de pixeli asociata imaginii
PPM, pornind de la arborele cuaternar

* getMean - folosita pentru a calcula scorul de similaritate descris in
enuntul problemei pentru un anumit bloc din imagine

* countNodes - folosita pentru a returna numarul de noduri dintr un
arbore cuaternar

* BFS - folosita pentru a returna elementele unui arbore cuaternar sub
forma unui array, elementele arborelui fiind parcurse in latime (BFS)


In functia main, programul se desfasoara in felul urmator: mai intai
verificam daca s a folosit flagul -c1 sau -c2, intrucat rezolvarea celor
doua cerinte presupune crearea arborelui si acestea au acelasi numar de
argumente in linie de comanda. Pentru aceste doua cerinte (indiferent care
din ele) citim datele din fisierul PPM, populam o matrice de tip pixel cu
datele imaginii din fisier, iar apoi pe baza acestei matrici construim
arborele de compresie.


Pentru cerinta -c1 vom calcula statisticile cerute, iar pentru cerinta -c2
vom scrie in fisierul de output, primit ca argument in linia de comanda,
varianta comprimata a fisierului, in format binar.
Dupa oricare dintre acceste doua cerinte eliberam memoria folosita pentru
rezolvarea problemei


Pentru rezolvarea cerintei -d, construim arborele cu ajutorul unei
cozi, iar apoi pe baza arborelui construim matricea asociata imaginii,
dupa care scriem in fisierul de output primit ca argument in linie de
comanda, in format binar, rezultatele obtinute in aceasta matrice.
Apoi eliberam memoria folosita pentru rezolvarea problemei.

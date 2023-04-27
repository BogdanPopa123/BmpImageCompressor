## Tema 1 - SDA
Popa Bogdan-Florin

Timp de lucru - aproximativ 8 ore

Punctaj checker local - 100/100

Punctaj vmchecker - 100/100


Mai intai am inceput prin a declara strcturile necesare pentru
implementarea structurilor de date ce vor fi necesare in realizarea
acestei teme:

* Structul ListNode reprezinta nodul pentru o lista dublu-inlantuita,
avand pointerii la adresa precedenta,adresa urmatoare, precum si
valoarea char a elementului aflat la pozitia respectiva

* Structul SimpleListNode reprezinta nodul folosit pentru stivele de
Undo si Redo, aceasta structura contine pointer la adresa urmatorului
element din lista precum si pointer catre adresa la care trebuie sa
se faca Undo sau Redo, dupa caz.

* Structul QueueNode reprezinta nodul folosit pentru a implementa
coada ce va contine comenzile de UPDATE. Aceste noduri contin pointer
catre urmatorul element din lista precum si un sir de caractere ce
reprezinta comanda stocata in coada.

* Structul Queue reprezinta coada de comenzi, aceasta continand doar
doua elemente, anume pointer catre primul si ultimul element din
lista de comenzi.

* Structul Band reprezinta banda descrisa in enuntul problemei, avand pointer catre santinela listei dublu inlantuite, precum si pointer
catre adresa indicata de deget(current position).


Functiile folosite in acest program sunt:

* initSimpleList - folosita pentru initializarea celor doua stive de
undo si redo

* initQueue - folosita pentru initializarea cozii de comenzi

* initList - folosita pentru initializarea listei dublu inlantuite

* functiile de update descrise in enuntul problemei:

1. move_right - care muta pozitia degetului cu o pozitie mai la
dreapta, iar in cazul in care degetul se afla deja pe ultima pozitie
din banda, atunci se va crea un nou element cu valoarea '#', iar
degetul se va muta pe caracterul nou inserat

2. move_left - care muta pozitia degetului cu o pozitie mai la
stanga, iar in cazul in care degetul se afla deja pe prima pozitie
din banda, atunci nu se va intampla nimic

3. move_left_char <C> - Deplasarea degetului spre stanga pana cand se
intalneste pe banda caracterul <C>, dat ca parametru. In cazul in
care s-a ajuns la marginea din stanga a benzii si caracterul cautat
nu a fost gasit, se va afisa mesajul "ERROR"

4. move_right_char <C> - Deplasarea degetului spre dreapta pana cand
se intalneste pe banda caracterul <C>, dat ca parametru. In cazul in
care s-a ajuns la marginea din dreapta a benzii si caracterul cautat
nu a fost gasit, se va insera in banda caracterul "#" si pozitia
degetului va fi mutata pe acest caracter nou inserat

5. write <C> - Scrie caracterul <C>, dat ca parametru, pe pozitia
indicata de deget

6. insert_left_char <C> - insereaza un nou element in banda cu
valoarea "C" la stanga elementului indicat de deget, apoi mutam
degetul cu o pozitie la stanga. In cazul in care degetul se afla deja
pe prima pozitie, nu se poate efectua aceasta operatie, afisandu se
mesajul "ERROR" daca aceasta functie este apelata

7. insert_right_char <C> - insereaza un nou element in banda cu
valoarea "C" la dreapta elementului indicat de deget, apoi mutam
degetul cu o pozitie la dreapta.

* functiile de show descrise in enuntul problemei:

1. show_current - afiseaza elementul indicat de deget

2. show - afiseaza continutul intregii benzi, elementul indicat de
deget fiind printat intre barele verticale ||

* functiile de undo/redo - folosite pentru a efectua operatia de
undo, respectiv operatia de redo

* functii specifice pentru lucrul cu cozi/stive:

1. pushToStack - pentru a adauga un element in stiva

2. enqueue - pentru a adauga un element in coada

* functii folosite pentru a da free la elementele din listele
folosite:

1. emptyStack - folosita pentru a da free la toate elementele din
cele doua stive de undo si redo

2. emptyQueue - folosita pentru a da free la toate elementele din
coada de comenzi

3. emptyDoubleLinkedList - folosita pentru a da free la toate
elementele din lista dublu-inlantuita ce reprezinta elementele benzii


In functia main, programul se desfasoara in felul urmator: mai intai
initializam toate strcturile de date ce vor fi folosite, alocand
memorie si cu ajutorul functiilor init (lista dublu inlantuita pentru
banda, cele doua stive de undo/redo, coada cu comenzi si banda).


Apoi vom goli fisierul de output, inainte de a adauga continut in acesta.


Dupa care, vom citi numarul de comenzi, vom goli bufferul si va
incepe citirea efectiva a comenzilor. Verificam ce fel de comanda a
fost citita.


Daca este o comanda de tip UPDATE, atunci o vom adauga in coada.


Daca este comanda SHOW, atunci vom apela functia show.


Daca este comanda SHOW_CURRENT, atunci vom apela functia show_current.


Daca este comanda EXECUTE, atunci vom scoate din coada de comenzi
prima comanda si vom apela functia aferenta acesteia.


La final, adica dupa ce toate comenzile au fost tratate, vom elibera
memoria alocata si programul se va termina.
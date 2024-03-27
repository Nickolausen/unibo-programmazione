#### - ESERCIZIO 1
_Si vuole implementare un algoritmo di apprendimento automatico per rinforzo: il Q-learning._[^1]

L’obiettivo del **Q-learning** è quello di adattarsi iterativamente al problema da risolvere migliorando la scelta delle azioni da eseguire. Il problema è caratterizzato da un agente, un insieme di stati _S_ e un insieme di azioni _A_, effettuando le quali l'agente si muove da uno stato ad un altro stato. Ogni stato fornisce all'agente una ricompensa. L'obiettivo dell'agente è quello di massimizzare la ricompensa totale.

In particolare, immaginare di dover allenare un robot a percorrere nel minor tempo possibile un labirinto disseminato di bombe e sorgenti di energia, data una posizione iniziale e una posizione finale che deve raggiungere. Il sistema di punteggio/premio è il seguente:
- Il robot perde 1 punto a ogni passo (serve a favorire la scelta dei percorsi più brevi e a raggiunge l'obiettivo il più velocemente possibile)
- Se il robot calpesta una mina, perde 100 punti e la partita finisce.
- Se il robot raggiunge una sorgente di energia guadagna 1 punto.
- Se il robot raggiunge l'obiettivo finale ottiene 100 punti.

L’ambiente di gioco deve essere modellato usando una tabella Q (**Q-table**) dove le colonne rappresentano le azioni (destra, sinistra, alto, basso) e le righe rappresentano gli stati (iniziale, vuoto, energia, mina, finale)[^2]. Ogni valore della Q-table rappresenterà la massima ricompensa futura attesa che il robot otterrà se compirà quell'azione in quello stato. Si tratta di un processo iterativo, poiché è necessario migliorare la tabella Q a ogni iterazione. Inizialmente la Q-table sarà inizializzata con valori 0, sarà poi iterativamente migliorata usando l’algoritmo di Q-learning.

L’algoritmo deve procedere secondo i seguenti passi:

1. inizializzazione della Q-table
2. scelta di un’azione
3. esecuzione dell’azione
4. misurazione della ricompensa
5. aggiornamento della Q-table
Vedere i dettagli di come aggiornare i valori della Q-table e un esempio di gioco ad esempio dal seguente sito: https://www.freecodecamp.org/news/an-introduction-to-q-learning-reinforcement-learning-14ac0b4493cc/

#### - ESERCIZIO 2
Scrivere un programma C dove sono inizializzate una variabile di tipo `int`, una di tipo `float`, una di tipo `double`, una di tipo `char`, ed un array di 5 interi (precisamente con i valori 10, 20, 30, 40, 50). Inizializzare un puntatore per ciascuna di queste variabili. Assegnare ad ogni variabile un valore tramite l'utilizzo della funzione `scanf()`. Visualizzare il valore di ogni variabile in due modi: prima tramite accesso diretto alla variabile e a seguito tramite l'utilizzo del suo puntatore (accesso indiretto). Visualizzare la posizione in memoria della variabile tramite l'utilizzo diretto della variabile e tramite il suo puntatore. Visualizzare la posizione in memoria del puntatore.

Modificare il contenuto di ogni variabile e mostrare nuovamente le varie informazioni. Porre attenzione nel mostrare messaggi di output dettagliati che chiariscano ciò che si visualizza, in modo che il programma risulti un valido ausilio per spiegare il funzionamento dei puntatori.

---
[^1]: _Una buona reference online dal punto di vista teorico del funzionamento del Q-Learning è la seguente: https://www.baeldung.com/cs/epsilon-greedy-q-learning_

[^2]: _La consegna parla di una Q-Table come matrice di 4 colonne (le direzioni percorribili dal robot) e di 5 stati; per come l'abbiamo strutturata noi, abbiamo considerato gli stati come ogni singola cella del labirinto, avendo quindi in totale NRROW * NRCOL righe (dove NRROW e NRCOL sono rispettivamente le righe e colonne del labirinto);_
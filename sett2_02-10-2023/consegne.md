#### - ESERCIZIO 1
Scrivere un programma C che mostri l’utilizzo di tutti gli operatori studiati. Il programma deve inoltre mostrare il comportamento scorretto che si ottiene utilizzando tipi non appropriati alla dimensione delle variabili, quello che si ottiene usando più operatori con side effect all’interno della stessa istruzione, quello che si ottiene quando le regole di conversione implicita sono applicate e quando si supera il range dei valori disponibili per un tipo di dato.

Il programma deve poi mostrare l’utilizzo di tutte le funzioni matematiche della libreria `math.h`.
 
#### - ESERCIZIO 2
L’utente pensa ad un numero e il computer lo deve indovinare compiendo le seguenti operazioni.

- L’utente fissa un intervallo entro cui generare il valore da indovinare (min, max). Se i valori inseriti non rispettano il vincolo $0 < min \leq max$ l’operazione di lettura va ripetuta.
- L’utente pensa ad un numero compreso tra min e max.
- Il programma cerca di indovinare la scelta dell’utente e propone un numero. A seconda della situazione l’utente deve dire al programma se
    - il numero da indovinare è più piccolo;
    - il numero da indovinare è più grande;
    - ha indovinato.

Scrivere una versione di programma in cui non c'è limite al numero di tentativi che il computer può fare per indovinare il numero e scriverne un'altra in cui invece viene posto tale limite.

Il programma deve stampare il numero di tentativi fatti.
#### - ESERCIZIO 1
Scrivere un programma che simuli l’“effetto decriptazione dati” presentato nel 1992 nel film Sneakers. L’effetto è presente a partire dal minuto 0.35 nella seguente clip del film:

https://www.youtube.com/watch?v=F5bAa6gFvLs&t=35s

Il vostro programma dovrà occuparsi di chiedere all’utente una stringa e di visualizzare in tempi successivi versioni via via più simili alla stringa iniziale.


#### - ESERCIZIO 2
Scrivere un programma C che riceva in ingresso due parole inserite da tastiera. Si consideri che ciascuna parola può contenere al massimo 30 caratteri. Il programma deve essere *case sensitive*, cioè deve distinguere lettere minuscole da lettere maiuscole e deve essere in grado anche di analizzare numeri, simboli e segni di punteggiatura. Il programma deve sostituire ogni occorrenza della seconda parola nella prima parola con il carattere ’*’. 

Ad esempio, inserite le stringhe:

`abchdfffchdchdtlchd` e `chd`

il programma deve visualizzare la stringa:

`ab*fff**tl*`

Scrivere due versioni: la prima deve ignorare la presenza della libreria `string.h` e quindi dovete lavorare esplicitamente su ogni singolo carattere delle stringhe. La seconda deve usare le funzioni della libreria `string.h` per determinare la lunghezza e per ricercare sotto-stringhe all'interno di una stringa
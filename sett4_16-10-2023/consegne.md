#### - ESERCIZIO 1
Siano dati due vettori di interi di lunghezza differente. Scrivere un programma C che inserisca i valori da tastiera e che lo faccia anche generandoli in maniera pseudo-casuale. Il programma deve poi generare un terzo vettore contenente l’intersezione tra i due vettori di input. Implementare sia la variante in cui le ripetizioni di un elemento nei vettori di input vengono riportate anche nel vettore risultato, sia quella in cui le ripetizioni non sono inserite nel risultato. Implementare poi la generazione di un quarto vettore contenente l'unione dei due vettori di input. 

Il programma deve inoltre stampare gli indirizzi di memoria occupati dagli elementi dei vettori e la loro dimensione totale in termini di numero di byte.


#### - ESERCIZIO 2
Scrivete un programma che generi una “passeggiata aleatoria” (random walk) in un array bidimensionale di dimensione $10 \times 10$. L’array sarà riempito di caratteri (inizialmente da punti). Il programma dovrà muoversi di elemento in elemento spostandosi ogni volta di un passo in direzione su, giù, destra o sinistra. Gli elementi visitati andranno etichettati con le lettere dalla A alla Z, nell’ordine in cui vengono visitati. E’ importante controllare ad ogni passo che la passeggiata non esca dall’array e che non ritorni su posizioni già visitate. Quando si verifica una di queste condizioni, provare le altre direzioni. Se tutte e quattro le direzioni sono bloccate, il programma deve terminare.

Ecco un esempio di funzionamento completo:

|   |   |   |   |   |   |   |   |   |   |
|---|---|---|---|---|---|---|---|---|---|
| A | . | . | . | . | . | . | . | . | . |
| B | C | D | . | . | . | . | . | . | . |
| . | F | E | . | . | . | . | . | . | . |
| H | G | . | . | . | . | . | . | . | . |
| I | . | . | . | . | . | . | . | . | . |
| J | . | . | . | . | . | . | . | Z | . |
| K | . | . | R | S | T | U | V | Y | . |
| L | M | P | Q | . | . | . | W | X | . |
| . | N | O | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . | . | . |


Ecco un esempio di uscita prematura dal programma:

|   |   |   |   |   |   |   |   |   |   |
|---|---|---|---|---|---|---|---|---|---|
| A | B | G | H | I | . | . | . | . | . |
| . | C | F | . | J | K | . | . | . | . |
| . | D | E | . | M | L | . | . | . | . |
| . | . | . | . | N | O | . | . | . | . |
| . | . | W | X | *Y* | P | Q | . | . | . |
| . | . | V | U | T | S | R | . | . | . |
| . | . | . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . | . | . |

*Y* è bloccata in tutte le direzioni quindi non c’è modo di inserire Z.
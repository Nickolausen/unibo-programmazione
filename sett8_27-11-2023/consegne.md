#### - ESERCIZIO 1
Realizzare un programma che permetta all’utente di interagire con l’algoritmo di Machine Learning **Find-S**. Il problema è quello di decidere se aspettare o meno che si liberi un tavolo quando si va al ristorante sulla base dei seguenti attributi:

| Attributo      | Descrizione                                        |
|----------------|----------------------------------------------------|
| Alternativa    | C’è un ristorante nei paraggi (vero, falso)       |
| Bar            | Il ristorante ha un’area bar per l’attesa (vero, falso) |
| Giorno         | Giorno della settimana in cui si vuole andare al ristorante (vero se venerdì oppure sabato, falso diversamente) |
| Fame           | Siamo affamati (vero, falso)                      |
| Affollato     | Quante persone sono presenti nel ristorante (nessuno, qualcuno, pieno) |
| Prezzo         | Categoria di costo del ristorante ($, $$, $$$)     |
| Pioggia        | Fuori sta piovendo (vero, falso)                   |
| Prenotazione   | Abbiamo prenotato (vero, falso)                   |
| Tipo           | Tipo di ristorante (italiano, francese, fast-food, thai) |
| Attesa stimata| Stima del tempo di attesa (<10, 10-29, 30-60, >60) |

L’algoritmo deve lavorare sia con lettura da file che con inserimento dati dell’utente, opzione specificata da riga di comando. La fase di training deve leggere il training set da file specificato da riga di comando. Il file di training contiene una riga per ogni ipotesi di allenamento. Se l’inserimento dati avviene da tastiera, l’utente dovrà essere guidato all’inserimento delle ipotesi di allenamento.

Al termine della fase di training, l’algoritmo deve dare all’utente la possibilità di testare il modello appreso. Per ogni nuova ipotesi fornita da linea di comando, il programma deve mostrare il valore della funzione obiettivo `Aspettiamo()` e l’utente deve indicare se il valore è corretto o meno. In base all’indicazione dell’utente, il programma deve acquisire la nuova ipotesi ed eventualmente ri-allenare il modello.


#### - ESERCIZIO 2
Realizzare l'esercizio organizzando il codice in funzioni. Porre particolare attenzione all'usabilità del codice guidando gli inserimenti dell'utente e mostrando output ben descritti.
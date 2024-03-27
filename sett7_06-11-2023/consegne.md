#### - ESERCIZIO 1
L'algoritmo **k-nearest neighbors** (KNN) è un algoritmo di apprendimento automatico supervisionato utilizzato per risolvere sia problemi di classificazione che di regressione. L'algoritmo KNN presuppone che oggetti con caratteristiche simili si trovino nelle immediate vicinanze, cioè poco distanti fra loro nello spazio dove sono rappresentate le caratteristiche degli oggetti.

L'algoritmo KNN chiede di valutare la somiglianza degli elementi più vicini e, a maggioranza, classifica l’elemento. La somiglianza viene definita in base a una metrica di distanza tra due punti di dati. Una scelta popolare è la distanza euclidea, ma è possibile valutare altre misure in base al proprio dataset, ad esempio, Manhattan, Chebyshev, Hamming, etc.

Per trovare la classe di appartenenza di un dato in ingresso, si esegue un loop su ogni esempio di training. Per ogni esempio viene calcolata la distanza tra esempio e ingresso usando la metrica desiderata. Infine, si prendono i k esempi con distanza minore e si contano le classificazioni di questi esempi. Vince la classificazione con maggior numero di esempi tra i k trovati.

Si veda, ad esempio, https://www.geeksforgeeks.org/k-nearest-neighbours/ per una descrizione più dettagliata dell’algoritmo.

Algoritmo:

1. Scegliere il valore di K, cioè il numero di vicini più prossimi che verrà utilizzato per fare la previsione

2. Calcolare la distanza tra quel punto e tutti i punti dell'insieme di training

3. Selezionare i K vicini più prossimi in base alle distanze calcolate

4. Assegnare l'etichetta della classe maggioritaria al nuovo punto

5. Ripetere i passaggi da 2 a 4 per tutti i punti dati dell'insieme di test

6. Valutare l'accuratezza dell'algoritmo (usando il 25% dei dati del dataset dato).

Usare l'algoritmo KNN per prevedere se un prestito bancario verrà rimborsato in base ai dati del cliente, usando il 75% dei dati relativi ai prestiti presenti in un dataset composto di 10.000 dati di prestiti con informazioni sulla struttura del prestito, sul mutuatario e sul fatto che il prestito sia stato rimborsato per intero. I dati sono stati estratti da LendingClub.com, una società che mette in contatto i mutuatari con gli investitori. Le informazioni presenti nel dataset sono:

| Indice | Campo             | Descrizione                                                                                                                                   |
|--------|-------------------|-----------------------------------------------------------------------------------------------------------------------------------------------|
| 0      | `credit_policy`     | 1 se il cliente soddisfa i criteri di sottoscrizione del credito; 0 altrimenti.                                                               |
| 1      | `purpose`           | Lo scopo del prestito.                                                                                                                        |
| 2      | `int_rate`          | Il tasso di interesse del prestito (ai mutuatari più rischiosi vengono assegnati tassi di interesse più elevati).                             |
| 3      | `installment`       | Le rate mensili dovute dal mutuatario se il prestito viene finanziato.                                                                        |
| 4      | `log_annual_inc`    | Il log naturale del reddito annuo autodichiarato del mutuatario.                                                                              |
| 5      | `dti`               | Il rapporto debito/reddito del mutuatario (importo del debito diviso per il reddito annuale).                                                 |
| 6      | `fico`              | Il punteggio di credito FICO del mutuatario.                                                                                                  |
| 7      | `days_with_cr_line` | Il numero di giorni in cui il debitore ha avuto una linea di credito.                                                                         |
| 8      | `revol_bal`         | Il saldo revolving del debitore (importo non pagato alla fine del ciclo di fatturazione della carta di credito).                              |
| 9      | `revol_util`        | Il tasso di utilizzo della linea revolving del debitore (l'importo della linea di credito utilizzata rispetto al credito totale disponibile). |
| 10     | `inq_last_6mths`    | Il numero di richieste di informazioni da parte dei creditori negli ultimi 6 mesi.                                                            |
| 11     | `delinq_2yrs`       | Il numero di volte in cui il debitore è stato in ritardo di oltre 30 giorni con i pagamenti negli ultimi 2 anni.                              |
| 12     | `pub_rec`           | Il numero di registri pubblici in deroga del mutuatario.                                                                                      |
| 13     | `not_fully_paid`    | 1 se il prestito non è stato completamente pagato; 0 altrimenti.                                                                              |

Il dataset è presente nel file credit a disposizione su virtuale.

I dati di ogni prestito devono essere gestiti tramite un'apposita struttura dati.


#### - ESERCIZIO 2
Gestire i dati di ogni prestito dell'esercizio 1 tramite un'apposita struttura dati. Organizzare l'intero programma utilizzando le funzioni.
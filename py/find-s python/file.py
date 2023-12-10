def find_s_algorithm(dataset):
    # Inizializza l'ipotesi più specifica
    hypothesis = [' '] * (len(dataset[0]) - 1)

    # Itera attraverso il dataset
    for row in dataset:
        if row[10] == 'vero':  # Considera solo gli esempi positivi
            for i in range(len(row) - 1):
                if hypothesis[i] == ' ':
                    hypothesis[i] = row[i]
                else:
                    if hypothesis[i] != row[i]:
                        hypothesis[i] = '?'  # Aggiorna l'ipotesi se necessario

    return hypothesis

# Dataset
# Alternativa, Bar,Giorno, Fame, Affollato, Prezzo, Pioggia, Prenotazione, Tipo, Attesa stimata
dataset = [
    ['vero', 'vero', 'vero', 'vero', 'pieno', '$$', 'falso', 'vero', 'italiano', '>60','vero'],
    ['vero', 'falso', 'sabato', 'vero', 'qualcuno', '$', 'falso', 'vero', 'francese', '30-60','falso'],
    ['falso', 'vero', 'venerdì', 'falso', 'nessuno', '$$$', 'vero', 'falso', 'fast-food', '<10','falso'],
    ['vero', 'vero', 'domenica', 'falso', 'qualcuno', '$', 'falso', 'falso', 'thai', '10-29','falso'],
    ['falso', 'falso', 'lunedì', 'vero', 'pieno', '$$$', 'vero', 'vero', 'italiano', '>60','falso'],
    ['vero', 'falso', 'martedì', 'vero', 'nessuno', '$$', 'falso', 'falso', 'fast-food', '<10','falso'],
    ['falso', 'falso', 'vero', 'falso', 'qualcuno', '$$', 'falso', 'vero', 'thai', '10-29','falso'],
    ['falso', 'falso', 'vero', 'falso', 'pieno', '$', 'vero', 'falso', 'francese', '30-60','falso'],
    ['falso', 'vero', 'vero', 'falso', 'qualcuno', '$', 'falso', 'vero', 'italiano', '10-29','falso'],
    ['vero', 'vero', 'falso', 'vero', 'qualcuno', '$', 'vero', 'falso', 'italiano', '30-60','falso'],
    ['falso', 'vero', 'vero', 'falso', 'qualcuno', '$$$', 'vero', 'falso', 'fast-food', '30-60','falso'],
    ['falso', 'falso', 'vero', 'falso', 'pieno', '$', 'falso', 'vero', 'francese', '>60','falso'],
    ['vero', 'falso', 'vero', 'falso', 'pieno', '$$', 'falso', 'vero', 'francese', '10-29','vero'],
    ['vero', 'vero', 'vero', 'falso', 'nessuno', '$$', 'falso', 'vero', 'italiano', '>60','falso'],
    ['falso', 'falso', 'vero', 'vero', 'nessuno', '$', 'falso', 'falso', 'thai', '>60','falso'],
    ['falso', 'falso', 'vero', 'falso', 'nessuno', '$$$', 'vero', 'falso', 'fast-food', '30-60','falso']
]

# Esegui l'algoritmo Find-S
result_hypothesis = find_s_algorithm(dataset)

# Stampa l'ipotesi finale
print("              : Alternativa, Bar,Giorno, Fame, Affollato, Prezzo, Pioggia, Prenotazione, Tipo, Attesa stimata")
print("Ipotesi finale:", result_hypothesis)
import random

def generate_random_example():
    # Genera un esempio casuale
    alternativa = random.choice(['vero', 'falso'])
    bar = random.choice(['vero', 'falso'])
    giorno = random.choice(['vero' if random.random() < 0.5 else 'falso'])
    fame = random.choice(['vero', 'falso'])
    affollato = random.choice(['nessuno', 'qualcuno', 'pieno'])
    prezzo = random.choice(['$', '$$', '$$$'])
    pioggia = random.choice(['vero', 'falso'])
    prenotazione = random.choice(['vero', 'falso'])
    tipo = random.choice(['italiano', 'francese', 'fast-food', 'thai'])
    attesa_stimata = random.choice(['<10', '10-29', '30-60', '>60'])

    return [alternativa, bar, giorno, fame, affollato, prezzo, pioggia, prenotazione, tipo, attesa_stimata]

def generate_dataset(num_examples):
    # Genera un dataset con il numero specificato di esempi
    dataset = [generate_random_example() for _ in range(num_examples)]
    return dataset

# Genera un dataset con 10 esempi
generated_dataset = generate_dataset(10)

# Stampa il dataset generato
for example in generated_dataset:
    print(example)
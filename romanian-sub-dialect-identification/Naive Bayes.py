import numpy as np
from sklearn.naive_bayes import MultinomialNB
import time
import datetime
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics import confusion_matrix

now = datetime.datetime.now()
t1 = time.perf_counter()
print(f'A inceput programul(train samples) la {now.hour} si {now.minute}')

# TRAIN TXT
# Salvăm label-urile de antrenare într-un vector, iar propozițiile într-o matrice
train_labels = np.loadtxt("train_labels.txt", dtype = int, usecols = 1)

train_samples = []
train_id = []

with open("train_samples.txt", mode="r", encoding="utf-8") as f:
    linii = f.readlines()

for linie in linii:
    id, prop= linie.split('\t')
    train_id.append(id)
    train_samples.append(prop)

train_samples_original = np.array(train_samples)
train_id_original = np.array(train_id)

t2 = time.perf_counter()
print(f'S-a ajuns aici (test samples) in {t2-t1} secunde')

# TEST TXT
# Salvăm propozițiile de testare într-o matrice
test_labels = np.loadtxt("validation_labels.txt", dtype = int, usecols = 1)

test_samples = []
test_id = []

with open("validation_samples.txt", mode="r", encoding="utf-8") as f:
    linii = f.readlines()

for linie in linii:
    id, prop= linie.split('\t')
    test_id.append(id)
    test_samples.append(prop)

test_samples = np.array(test_samples)
test_id = np.array(test_id)

t3 = time.perf_counter()
print(f'S-a ajuns aici (TfidfVectorizer) in {t3-t2} secunde')

# Primul vectorizer va fi folosit pentru primii doi clasificatori NB
tfidf_vectorizer = TfidfVectorizer(max_df = 0.3, min_df = 1, lowercase=False, token_pattern='\S+', ngram_range=(1, 2), analyzer='word')
train_tfidf = tfidf_vectorizer.fit_transform(train_samples_original)
test_tfidf = tfidf_vectorizer.transform(test_samples)

tNB = time.perf_counter()
print(f'S-a ajuns aici (NB) in {tNB-t3} secunde')

# fit si predict, salvăm predicțiile în all_predictions
naive_bayes = MultinomialNB(alpha = 0.1).fit(train_tfidf, train_labels)
predictions_naive_bayes = naive_bayes.predict(test_tfidf)
print(np.mean(predictions_naive_bayes == test_labels))

confusion_mat = confusion_matrix(test_labels, predictions_naive_bayes)
print("Confusion matrix:")
print(confusion_mat)

# positive = 1; negative = 0
TP = confusion_mat[1][1]
FP = confusion_mat[0][1]
FN = confusion_mat[1][0]

Precizie = TP / (TP + FP)
Recall = TP / (TP + FN)
Fscore = 2 * Precizie * Recall / (Precizie + Recall)
print(Fscore)

now = datetime.datetime.now()
tend = time.perf_counter()
print(f'S-a terminat in {tend-t1} secunde la {now.hour} si {now.minute}')
import numpy as np
from sklearn.svm import SVC
from sklearn.naive_bayes import MultinomialNB
import time
import datetime
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier
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

# Primul vectorizer va fi folosit pentru primii doi clasificatori NB și KNN,
# iar cel de-al doilea va fi folosit pentru logistic regression si SVC
tfidf_vectorizer = TfidfVectorizer(max_df = 0.3, min_df = 1, lowercase=False, token_pattern='\S+', ngram_range=(1, 2), analyzer='word')
train_tfidf = tfidf_vectorizer.fit_transform(train_samples_original)
test_tfidf = tfidf_vectorizer.transform(test_samples)

tfidf_vectorizer2 = TfidfVectorizer(max_df = 0.3, min_df = 1, lowercase=False, token_pattern='\S+', ngram_range=(5, 8), analyzer='char')
train_tfidf2 = tfidf_vectorizer2.fit_transform(train_samples_original)
test_tfidf2 = tfidf_vectorizer2.transform(test_samples)

# all_predictions va reține toate predicțiile făcute de clasificatori, pentru a putea
# face suma label-urilor pentru fiecare propoziție
all_predictions = []

tNB = time.perf_counter()
print(f'S-a ajuns aici (NB) in {tNB-t3} secunde')

# fit si predict, salvăm predicțiile în all_predictions
naive_bayes = MultinomialNB(alpha = 0.1).fit(train_tfidf, train_labels)
predictions_naive_bayes = naive_bayes.predict(test_tfidf)
all_predictions.append(predictions_naive_bayes)

tKNN = time.perf_counter()
print(f'S-a ajuns aici (KNN) in {tKNN-tNB} secunde')

# analog KNN
knn = KNeighborsClassifier(n_neighbors = 10).fit(train_tfidf, train_labels)
predictions_knn = knn.predict(test_tfidf)
all_predictions.append(predictions_knn)

tKRR = time.perf_counter()
print(f'S-a ajuns aici (KRR) in {tKRR-tKNN} secunde')

# analog logistic regression doar că folosește celelalte date (train_tfidf2)
log_reg = LogisticRegression(C = 100, max_iter = 1500).fit(train_tfidf2, train_labels)
predictions_log_reg = log_reg.predict(test_tfidf2)
all_predictions.append(predictions_log_reg)

tSVC = time.perf_counter()
print(f'S-a ajuns aici (SVC) in {tSVC-tKRR} secunde')

# analog SVC
svm = SVC(kernel = 'linear').fit(train_tfidf2, train_labels)
predictions_svm = svm.predict(test_tfidf2)
all_predictions.append(predictions_svm)

tALL = time.perf_counter()
print(f'S-a ajuns aici (all_predictions) in {tALL-tSVC} secunde')

# în momentul acesta, ar trebui să avem 4 linii a câte {len(test_samples)} coloane;
# all_predictions[i][j] = x, unde i este clasificatorul folosit, j este propoziția actuală și x e label-ul (ori 0 ori 1)
all_predictions = np.array(all_predictions)

# facem suma pe coloane (adunăm label-urile)
sums = np.sum(all_predictions, axis = 0)

# dacă valoarea e 0, respectiv 4 în vectorul sums (toata coloana a fost ori plină cu 0 ori plină cu 1),
# băgăm indicele label-ului în index0, respectiv index4
index0 = np.where(sums == 0)
index4 = np.where(sums == 4)

# PRECIZARE: np.where salvează conținutul ca și tuplu
# Din această cauză, pentru a accesa vectorul trebuie folosit index0[0], respectiv index4[0]
# Lungimile vectorilor
lung0 = len(index0[0])
lung4 = len(index4[0])

# Cum index0 conține pozițiile tuturor label-urilor care dau 0 (de la toți clasificatorii),
# vom adăuga la datele de antrenare și propozițiile de pe aceste poziții
for _ in index0:
  for i in _:
    train_samples.append(test_samples[i])

# În label-urile pentru antrenare vom adăuga câte un 0 pentru fiecare propoziție pe care am avut-o
train_labels = np.append(train_labels, np.zeros((lung0), dtype = int))

# Analog pentru index4 și label-urile sale
for _ in index4:
  for i in _:
    train_samples.append(test_samples[i])

train_labels = np.append(train_labels, np.full((lung4), 1))

# Noile date de antrenare
train_samples_new = np.array(train_samples)

tTFIDF = time.perf_counter()
print(f'S-a ajuns aici (Tfidf nou) in {tTFIDF-tALL} secunde')

# Repetăm procesul de preprocesare
tfidf_vectorizer_new = TfidfVectorizer(max_df = 0.3, min_df = 1, lowercase=False, token_pattern='\S+', ngram_range=(1, 2), analyzer='word')
train_tfidf_new = tfidf_vectorizer_new.fit_transform(train_samples_new)
test_tfidf_new = tfidf_vectorizer_new.transform(test_samples)

# Repetăm procesul de prezicere
naive_bayes = MultinomialNB(alpha = 0.1).fit(train_tfidf_new, train_labels)
predictions_naive_bayes = naive_bayes.predict(test_tfidf_new)
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

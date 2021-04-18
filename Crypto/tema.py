from cryptography.hazmat.primitives.ciphers import algorithms, modes, Cipher
from cryptography.hazmat.primitives import padding
import cv2
import sys
import secrets
import numpy as np

def criptare(img_str, settings_str, enc_img_str):
    secret_key = secrets.randbits(128)
    IV = secrets.randbits(128)

    f = open(settings_str, "w")
    f.write(str(secret_key) + "\n")
    f.write(str(IV) + "\n")

    secret_key = secret_key.to_bytes(16, 'big')
    IV = IV.to_bytes(16, 'big')

    cipher = Cipher(algorithms.AES(secret_key), modes.CBC(IV))
    encryptor = cipher.encryptor()

    img = cv2.imread(img_str)
    (lin, col, bit_depth) = np.shape(img)
    img_enc = np.array(img)

    padding_img = [] # lista pentru salvarea padding-ului
    for i in range(lin): # parcurgem linie cu linie
        for j in range(0, col, 5): # parcurgem coloana cu un salt de 5
            padder = padding.PKCS7(128).padder() # padder din libraria cryptography, va adauga x biti pana ajunge la 128

            pixels = [] # lista pentru pastrarea valorilor RGB a celor n pixeli
            for k in range(5): # luam doar 5 pixeli
                if j + k < col: # verificam sa nu trecem de sfarsitul imaginii
                    pixels.append(img[i][j + k][0])
                    pixels.append(img[i][j + k][1])
                    pixels.append(img[i][j + k][2])
                else:
                    break

            len_pad = 16 - len(pixels) # lungimea paddingului
            pixels = [int(x).to_bytes(1, 'big') for x in pixels] # convertim fiecare valoarea in byte

            block = b''
            for pixel in pixels:
                block += pixel # concatenam valorile

            block = padder.update(block) + padder.finalize() # aplicam padding
            block_crypt = encryptor.update(block) # criptam

            for k in range(len_pad - 1, -1, -1):
                padding_img.append(block_crypt[15 - k]) # conteaza ordinea in care salvam paddingul

            for k in range(5):
                if j + k < col:
                    img_enc[i][j + k][0] = block_crypt[k * 3] # inlocuim in imaginea criptata
                    img_enc[i][j + k][1] = block_crypt[k * 3 + 1]
                    img_enc[i][j + k][2] = block_crypt[k * 3 + 2]
                else:
                    break


    cv2.imwrite(enc_img_str, img_enc)
    f = open(settings_str, "a")
    for pad in padding_img:
        f.write(str(pad) + "\n")
    f.close()

def decriptare(img_str, settings_str, enc_img_str):
    print('------------ decriptare --------------')

    enc_img = cv2.imread(img_str)
    (lin, col, bit_depth) = np.shape(enc_img)
    dec_img = np.array(enc_img)

    f = open(settings_str, "r")
    secret_key = int(f.readline())
    IV = int(f.readline())

    padding_img = []
    for x in f:
        padding_img.append(int(x))

    secret_key = secret_key.to_bytes(16, 'big')
    IV = IV.to_bytes(16, 'big')


    cipher = Cipher(algorithms.AES(secret_key), modes.CBC(IV))
    decryptor = cipher.decryptor()

    padd = 0
    for i in range(lin):
        for j in range(0, col, 5):
            pixels = []
            for k in range(5):
                if j + k < col:
                    pixels.append(enc_img[i][j + k][0])
                    pixels.append(enc_img[i][j + k][1])
                    pixels.append(enc_img[i][j + k][2])
                else:
                    break

            while len(pixels) < 16:
                pixels.append(padding_img[padd])
                padd += 1

            pixels = [int(x).to_bytes(1, 'big') for x in pixels]

            block = b''
            for pixel in pixels:
                block += pixel

            block_decrypt = decryptor.update(block)

            for k in range(5):
                if j + k < col:
                    dec_img[i][j + k][0] = block_decrypt[k * 3]
                    dec_img[i][j + k][1] = block_decrypt[k * 3 + 1]
                    dec_img[i][j + k][2] = block_decrypt[k * 3 + 2]
                else:
                    break

    cv2.imwrite(enc_img_str, dec_img)

if __name__ == "__main__":
    print("criptare(<nume_imagine>, <txt-ul unde se salveaza datele>, <nume_imagine_criptata>)")
    print("decriptare(<nume_imagine_criptata>, <txt-ul de unde se iau datele>, <nume_imagine_decriptata>)")
    # criptare("linux.png", "settings_linux_cbc.txt", "linux_enc_cbc.png")
    # decriptare("linux_enc_cbc.png", "settings_linux_cbc.txt", "linux_dec_cbc.png")
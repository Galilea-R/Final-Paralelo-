import pandas as pd
import numpy as np
import re
import matplotlib.pyplot as plt
import os
import string
import csv

# Nombre en el que están guardados los libros
etiquetas = ["libro1", 
             "libro2", 
             "libro3", 
             "libro4", 
             "libro5",
             "libro6"]

# Lista en el que se guardarán todos los libros
corpus = []

"""
    Función que elimina las palabras de un texto que coincidan con otro.
    En este caso, se utilizará para eliminar stopwords y "basura"
"""
def remove_words(text, words):
    text = re.sub(r'[^a-zA-Z0-9_]', ' ', text)
    text_words = text.split(',')
    text_words = [w for w in text_words if w not in words]
    text = ' '.join(text_words)
    return text

if __name__ == "__main__":
    directorio_actual = os.getcwd()
    os.chdir(f'{directorio_actual}/data')
    # Leemos el archivo con las stopwords
    with open('stopwords.txt', 'r') as f:
        stopwords = f.read().split()
    # Leemos cada uno de los archivos 
    for etiqueta in etiquetas:
        archivo = open(etiqueta + ".txt", "r", encoding="utf-8")
        libro = archivo.read()
        archivo.close()
        libro_filtrado = remove_words(libro.lower(), stopwords)
        corpus.append(libro_filtrado)
        # Guaradamos los libros filtrados
        with open(f"""{etiqueta}.csv""", 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(libro_filtrado.split())  # Divide el texto filtrado en palabras utilizando la coma como delimitador

    corpus = np.array(corpus)
    df_corpus = pd.DataFrame({"documento": corpus, 
                            "categoria": etiquetas})
    # Guardamos todas las palabras de los libros en un conjunto
    todas_las_palabras = set(" ".join(df_corpus["documento"]).split())
    # Convertimos el conjuto a una lista
    todas_las_palabras = list(todas_las_palabras)
    # Guardamos el vocabulario de palabras en un csv
    with open('palabras.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(todas_las_palabras) 
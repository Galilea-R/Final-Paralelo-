# Final-Paralel

Este es el proyecto final de computo paralelo y en la nube de Sebastian Yamil Castellanos Gómez 198090 y Galilea Resendis González 196811. El proyecto se basa en hacer una bolsa de palabras con MPI para el análisis de texto de manera serial y paralelizada, como parte de las especificaciones se debe de alcanzar un speedup mínimo de 1.2 con la versión paralelizada.

El proyecto lo corrimos en una computadora asus zenbook pro duo con un procesador de 12ª generación intel core i9, con 32 de RAM y 20 núcleos.

El objetivo es procesar un conjunto de libros 6 en total, extraer su vocabulario y generar una matriz de Bolsa de Palabras. Se evaluarán los tiempos de ejecución entre las versiones serial y paralela con el propósito de medir la eficiencia de la paralelización. Este análisis permitirá cuantificar el speed-up y comprender su impacto en el rendimiento del sistema.

Para la entrada tendremos: 
1) Listado de nombres de los archivos (que están en formato txt) donde se encuentran las palabras a contar 
2) Archivo con el vocbulario y su tamaño (que se generó previamente con computo_paralelo_bolsa_de_palabras.ipynb)
3) Número de procesos a utilizar que debe ser igual al número de archivos a introducir 

Para la salida tendremos:
Una archivo con la matriz de Bolsa de Palabras en formato csv 

Adicionalmente hay una gráfica mostrando el speed up 

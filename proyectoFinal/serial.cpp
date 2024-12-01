#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iterator>
#include <cctype>

using namespace std;
int main (int argc, char *argv[]) {
    // Número de iteraciones del algoritmo para calcular el tiempo promedio posteriormente
    const int ejecuciones = 10; 
    double total_time = 0.0;
    for (int i = 0; i < ejecuciones; i++){
        // Tomamos el primer tiempo
        auto  start_time = chrono::high_resolution_clock::now(); 
        std::string vocabFile = "data/palabras.csv";
        std::ifstream vocabStream(vocabFile);
        std::string line;
        // Leemos el archivo de vocabulario y almacenamos las palabras en un vector
        std::vector<std::string> vocabulary;
        while (std::getline(vocabStream, line))
        {
            std::istringstream ss(line);
            std::string word;
            while (std::getline(ss, word, ','))
            {
                vocabulary.push_back(word);
            }
        }
        if (vocabulary.empty()) {
            cerr << "El archivo de palabras está vacío" << endl;
            return 1;
        }
        // Aquí sacamos el tamaño del vocabulario.
        int tamanio = vocabulary.size();        
        // Creamos la matriz de que almacenará las palabras y el recuento de ellas para cada libros
        vector<vector<string>> matriz(7, vector<string>(tamanio));
        // Copiamos vocabulary a la primera fila de la matriz.
        copy(vocabulary.begin(), vocabulary.end(), matriz[0].begin()); 

        // Declaramos en un vector el nombre de los archivos donde están los libros
        std::vector<std::string> files = {
                "data/libro1.csv",
                "data/libro2.csv",
                "data/libro3.csv",
                "data/libro4.csv",
                "data/libro5.csv",
                "data/libro6.csv"
                };

        // Iniciamos el ciclo para contar las palabras por libro
        for (int i = 0; i < files.size(); i++) {
            // Inicializamos el diccionario para el libro
            map<string, int> dictionary;
            for (const string& word : vocabulary) {
                dictionary.insert({word, 0});
            }
            // Leemos línea por línea y actualizar el diccionario
            std::ifstream vocabStream(files[i]);
            std::string line;
            while (std::getline(vocabStream, line))
            {
                std::istringstream ss(line);
                std::string word;
                while (std::getline(ss, word, ','))
                {
                    if (dictionary.count(word) > 0) {
                        dictionary[word]++;
                    }
                }
            }

            // Copiamos los valores del diccionario al vector correspondienre a la matriz 
            // que tiene los resultados
            for (int j = 0; j < vocabulary.size(); j++) {
                string palabra = vocabulary[j];
                if (dictionary.count(palabra) > 0) {
                    string num_cuenta = std::to_string(dictionary[palabra]);
                    matriz[1+i][j] = num_cuenta;
                }
            }
        }

        // Escribimos la matriz en un archivo CSV
        ofstream csvFile("data/resultados_serial.csv");
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < tamanio; j++) {
                csvFile << matriz[i][j];
                if (j != tamanio - 1) {
                    csvFile << ",";
                }
            }
            csvFile << std::endl;
        }
        csvFile.close();
        
        // Tomamos el tiempo nuevamente y sumamos el tiempo de la iteración en el tiempo total
        auto end_time = chrono::high_resolution_clock::now(); 
        double iteration_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        total_time += iteration_time; 
    }
    // Calculamos el tiempo promedio y lo guardamos en un csv que se usará para graficar
    double avg_time = (total_time / ejecuciones)/1000; 
    std::cout << "Promedio de tiempo de ejecucion: " << avg_time << " segundos" << std::endl;
    std::ofstream csv_file("data/tiempo_serial.csv");
        if (csv_file.is_open()){
            csv_file << avg_time;
            csv_file.close();
        }
    return 0;
}

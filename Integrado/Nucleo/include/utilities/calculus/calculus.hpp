#if !defined(CALCULUS_HPP)
#define CALCULUS_HPP

// Cópia da função map(), porém com suporte à valores do tipo double
double map_double(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Verifica se um ou mais valores de um vetor é true ou 1
// (vetor de booleanos) vector -> Vetor à ser analisado
// (int) length -> Tamanho dos vetores
bool checkTrueOnArray(bool vector[], int length) {
    for (int index = 0; index < length; index++) {
        if (vector[index] == 0) {
            ;
        } else {
            return true;
        }
    }
    return false;
}

// Calcula o erro atralado à leitura dos sensores de acordo com os pesos de cada sensor
// OS VETORES DE LEITURA E DE PESO PRECISAM TER A MESMA DIMENSÃO
// (vetor de booleanos) readingVector -> Vetor das leituras
// (vetor de inteiros) weightVector -> Vetor dos pesos
// (int) length -> Tamanho dos vetores
double calculateError(bool readingVector[], int weightVector[], int length) {
    double sum = 0.;
    double readings = 0.;
    for (int index = 0; index < length; index++) {
        if (readingVector[index] == 1) {
            sum += weightVector[index];
            readings += 1;
        }
    }
    return sum / readings;
}
#endif  // CALCULUS_HPP

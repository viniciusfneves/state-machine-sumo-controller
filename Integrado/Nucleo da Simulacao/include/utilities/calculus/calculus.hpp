#if !defined(CALCULUS_HPP)
#define CALCULUS_HPP

// Cópia da função map(), porém com suporte à valores do tipo double
double map_double(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Soma os valores de um vetor de booleanos
// return (int)
int sumArray(bool vector[], int quantity)
{
    int sum = 0;
    for (int index = 0; index < quantity; index++)
    {
        sum += vector[index];
    }
    return sum;
}

// Verifica se um ou mais valores de um vetor é true ou 1
// (vetor de booleanos) vector -> Vetor à ser analisado
// (int) lenght -> Tamanho do vetor
bool verifyArray(bool vector[], int lenght)
{
    int reading = sumArray(vector, lenght);
    if (reading == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
#endif // CALCULUS_HPP

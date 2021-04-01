#if !defined(CALCULUS_HPP)
#define CALCULUS_HPP

double map_double(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int sumArray(bool vector[], int quantity)
{
    int sum = 0;
    for (int index = 0; index < quantity; index++)
    {
        sum += vector[index];
    }
    return sum;
}

#endif // CALCULUS_HPP

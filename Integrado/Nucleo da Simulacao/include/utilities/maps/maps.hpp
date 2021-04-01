#if !defined(MAPS_HPP)
#define MAPS_HPP

double map_double(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif // MAPS_HPP

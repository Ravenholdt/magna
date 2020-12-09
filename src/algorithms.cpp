#include <math.h>

#include "algorithms.h"

#include <iostream>

#define PI  3.14159265359
#define G   6.674e-11         // Gravitational constant

float calculateDeltaV(float mass, float radius, float atmosphere)
{
    float period = calculateOrbitalPeriod(mass, radius);
    float velocity = calculateOrbitalVelocity(period, radius);
    return velocity * 1.2 + atmosphere * 0.2;
}

float calculateGravity(float mass, float radius){ return (G * mass) / pow(radius, 2); }
float calculateOrbitalPeriod(float mass, float distance){ return 2.0 * 3.14 * sqrt( pow(distance, 3) / (mass * G) ); }
float calculateOrbitalVelocity(float orbitalPeriod, float distance) { return (2 * PI * distance) / orbitalPeriod; }

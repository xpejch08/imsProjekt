#include "simlib.h"

struct PopulationModel {
    // Parametry modelu
    Parameter r;
    Parameter K;
    Parameter l;
    Parameter a;
    Expression dynamics;  // Dynamika populace
    Integrator population; // Populace divočáků

    PopulationModel(double r_value, double K_value, double l_value, double a_value) :
            r(r_value), K(K_value), l(l_value), a(a_value),
            dynamics(r * population * (1 - population / K) - l * population - a * population),
            population(dynamics, 100 /* Počáteční hodnota populace */) {}

};

PopulationModel model(0.5, 500000, 0.1, 0.1); // Vytvoření modelu s počátečními parametry

void Sample() {  // Výstup z modelu
    Print("%g %g\n", T.Value(), model.population.Value());
}
Sampler s(Sample, 1); // Vzorkování každých 0.1 jednotek času

int main() {
    SetOutput("population.dat");
    _Print("# Population Model\n");
    Init(0, 10 * 365);  // inicializace (např. 10 let)
    SetStep(1e-6, 1);   // nastavení kroku simulace
    Run();              // spuštění simulace
}

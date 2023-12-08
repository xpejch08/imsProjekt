#include "simlib.h"

struct SIRModel {
    Parameter beta;  // Infection rate
    Parameter gamma; // Recovery rate
    double N;        // Total population

    Integrator S; // Susceptible population
    Integrator I; // Infected population
    Integrator R; // Recovered population

    // constructor
    SIRModel(double beta_value, double gamma_value, double N_value, double S0, double I0, double R0) :
        beta(beta_value), gamma(gamma_value), N(N_value),
        S(-beta * S * I / N, S0), //equation for s
        I(beta * S * I / N - gamma * I, I0), //equation for i
        R(gamma * I, R0) {} //equation for r

};

// Initial conditions
double initial_susceptible = 730; // 730 people who have the potential to be infected, according to the table
double initial_infected = 270;     // 270 infected
double initial_recovered = 0;    // 0recovered for start

// Total population
double total_population = 1000;

// Model parameters
double transmission_rate = 0.3;  // Beta
double recovery_rate = 0.43;      // Gamma

// Instantiate the SIR model
SIRModel model(transmission_rate, recovery_rate, total_population, initial_susceptible, initial_infected, initial_recovered);

// Function to output the results
void Sample() {
    Print("%g %g %g %g\n", T.Value(), model.S.Value(), model.I.Value(), model.R.Value());
}
Sampler s(Sample, 1);

int main() {
    SetOutput("population.dat");
    Print("# SIR Model\n");
    Init(0, 100);  // 100 time units
    SetStep(1e-6, 0.1);
    Run();
    return 0;
}

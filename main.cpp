#include <vector>
#include "simlib.h"
#include <cstring>

int getParams(int argc, char *argv[]){
    if (argc<2){
        return 1;
    }
    if (strcmp(argv[1],"exp1")==0){
        return 1;
    }else if((strcmp(argv[1],"exp2")==0)){
        return 2;
    }else if((strcmp(argv[1],"exp3")==0)){
        return 3;
    }else if((strcmp(argv[1],"exp4")==0)){
        return 4;
    }else if((strcmp(argv[1],"exp5")==0)){
        return 5;
    }
    return 1;
}


struct SIRModel {


    Parameter beta;  // Infection rate
    Parameter gamma; // Recovery rate
    Parameter mRHIV; // Mortality rate related to HIV
    Parameter mRALL; // Mortality rate related to HIV
    double N;        // Total population

    Integrator S; // Susceptible population
    Integrator I; // Infected population
    Integrator R; // Recovered population
    Integrator DHIV; // Dead population
    Integrator DALL; // Dead population

    // constructor
    SIRModel(double beta_value, double gamma_value, double N_value, double S0, double I0, double R0, double DHIV0, double DALL0, double mRHIV_value, double mRALL_value):
            beta(beta_value), gamma(gamma_value), mRHIV(mRHIV_value), mRALL(mRALL_value), N(N_value),
            S(-beta * S * I / N, S0), //equation for s
            I(beta * S * I / N - gamma * I, I0), //equation for i
            R(gamma * I, R0), //equation for r
            DHIV(mRHIV * I, DHIV0),
            DALL(mRALL * I, DALL0) {} //equation for death rate only related to hiv

    void updateModel(double beta_value, double gamma_value, double N_value, double S0, double I0, double R0, double DHIV0, double mRHIV_value, double DALL0, double mRALL_value) {
        beta = beta_value;
        gamma = gamma_value;
        N = N_value;
        mRHIV = mRHIV_value;
        mRALL = mRALL_value;

        // Initialize the Integrators with new values
        S.Init(S0);
        I.Init(I0);
        R.Init(R0);
        DHIV.Init(DHIV0);
        DALL.Init(DALL0);
    }

};
//load conditions based on experiment
std::vector<double> loadConditions(int x){
    // Initial conditions
    double initial_susceptible = 730; // 730 people who have the potential to be infected, according to the table
    double initial_infected = 270;     // 270 infected
    double initial_recovered = 0;    // 0recovered for start
    // Total population
    double total_population = 1000;
    // Model parameters
    double transmission_rate = 0.3;  // Beta
    double recovery_rate = 0.43;      // Gamma

    double initial_dead_hiv = 0; //0 dead for start
    double mortality_rate_hiv = 0.02906976744; //mortality rate HIV

    double initial_dead_all = 0; //0 dead for start
    double mortality_rate_all = 0.0053; //mortality rate
    if(x==1) { //experiment 1, base case
        mortality_rate_hiv = 0;
        mortality_rate_all = 0;
    }

    if(x==2) { //experiment 2, people that know they have hiv
        transmission_rate = 0.35;
        mortality_rate_hiv = 0;
        mortality_rate_all = 0;
    }
    if(x==3) { //experiment 3, people that don't know they have hiv
        transmission_rate = 0.28;
        mortality_rate_hiv = 0;
        mortality_rate_all = 0;
    }
    if(x==4) { //experiment 4, updated recovery rate
        recovery_rate = 0.48;
    }

    if(x==5) { //experiment 5, infecting half of the population
        initial_infected = 500;// 1 infected
        initial_susceptible = 500;
    }
    return {transmission_rate, recovery_rate, total_population, initial_susceptible, initial_infected, initial_recovered, initial_dead_hiv, mortality_rate_hiv, initial_dead_all, mortality_rate_all};
}
// Instantiate the SIR model
SIRModel model(0.3,0.43,1000,730,270,0, 0, 0.0047, 0, 0.0123);

// Function to output the results
void Sample() {
    Print("%g %g %g %g %g %g\n", T.Value(), model.S.Value(), model.I.Value(), model.R.Value(), model.DHIV.Value(), model.DALL.Value());

}
Sampler s(Sample, 1);

int main(int argc, char *argv[]) {
    std::vector <double> conds;
    conds = loadConditions(getParams(argc,argv));
    SetOutput("population.dat");
    Print("# SIR Model\n");
    model.updateModel(conds[0], conds[1], conds[2], conds[3], conds[4], conds[5], conds[6], conds[7], conds[8], conds[9]);



    Init(0, 10);  // 100 time units
    SetStep(1e-6, 0.1);
    Run();
    return 0;
}

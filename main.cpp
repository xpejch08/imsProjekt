#include <simlib.h>
#include <iostream>
#include <stdio.h>

int oldestPig = 0;
class Pig : public Process {
    bool isFemale;
    bool isAlive = true;
    int pigIndex;
    int litterCount = 0;
    int expecting;
    bool prohibited = false;
    int prohibitedexpire;
    double expecteddeliveryday;
    int age;
    void Behavior() {
        if(0==Time){ //31.3.
            if(Random()<0.40733661){ //theres more under 1 years old than adult pigs (sele)
                age = int(Uniform(365,3650));
            }else{
                age = int(Uniform(0,365));
            }

        }else{
            age=0;
            prohibited = true;
            prohibitedexpire = 90; //pigs under 3 months are prohibited to shoot (asi trosku bullshit :) )
        }
        if(Random() < 0.45){ //pigs are more likely to be male
            isFemale = true;
        } else {
            isFemale = false;
        }
        // Pigs live 10 years
        while(age < 3650) {
            age++;
            if(oldestPig < pigIndex){
                oldestPig = pigIndex;
                std::cout << "PigIndex: " << pigIndex << "Female pig, Age: " << age << "PigCount: " << pigAmount << std::endl;
            }
            if (isAlive && prohibitedexpire==age){ //no longer protected from hunters
                prohibited = false;
                prohibitedexpire = 0;
            }

            if (isAlive && expecteddeliveryday == age){
                for(int i =0; i< expecting;++i){
                    (new Pig)->Activate(); //new offspring is born when mother is still alive and his birth has come
                    pigAmount++;
                    std::cout << "born" << std::endl;
                }
                expecteddeliveryday = 0;
                expecting = 0;
            }
            if (isAlive && isFemale && age >= 240 && age <= 730 && expecting==0) { // Females reproduce between 8-24 months
                if (Random() < 0.6 && isInBreedingSeason() && (litterCount < 2)) {
                    litterCount++;
                    std::cout << "intercourse" << std::endl;
                    int offspring = int(Normal(7.5, 2.5)); // Average litter size
                    for(int i = 0; i <= offspring; ++i) {
                        expecting++;
                    }
                    expecteddeliveryday = age + 120; //planned birth date
                    prohibited = true;
                    prohibitedexpire = age + 120 + 485; //piglets are with their mother for 18 months, mothers with pigs are protected from hunters
                }
            }
            if( isAlive && !prohibited && Random() < 0.008423402){  //  ( 184328 / 59953 / 365) 307% chance of getting shot each year
                if(isAlive){
                    pigAmount--;
                }
                std::cout << "shot" << std::endl; // dying from being shot
                Terminate(); // pig died
                isAlive = false;
            }
            if(age % 365 == 0){ //can be pregnant again
                litterCount = 0;
            }
            // dying
            if (isAlive && Random() < 0.0002886172890222971) { // 10%chance dying each year
                if(isAlive){
                    pigAmount--;
                }
                std::cout << "natural causes" << std::endl;
                Terminate(); // pig died
                isAlive = false;
            }

            // next birth cycle
            Wait(1);
        }
        Terminate();
        isAlive = false;

    }

    bool isInBreedingSeason() {
        int dayOfYear = age % 365;
        return ((dayOfYear >= 305 || dayOfYear <=31) || ((dayOfYear <= 122 || dayOfYear >= 275) && Random() < 0.005));
        //slight chance of mating outside main mating months

    }
public:
    Pig() : pigIndex(nextPigIndex++) { // Assign a unique index to each pig
    }
    static int pigAmount;
    static int nextPigIndex;
};

int Pig::pigAmount = 61915; //pocet prasat 2023
int Pig::nextPigIndex = 0;

//class PigPopulation : public Process {
//    void Behavior() {
//        int simTime = 0;
//        while (simTime < 365 ) {
//            simTime--;
//            // Podmínky pro rozmnožování prasat
//            if (shouldReproduce()) {
//                int numberOfNewPigs = removeSomePigsFromPopulation(calculateNumberOfNewPigs());
//                for (int i = 0; i < numberOfNewPigs; ++i) {
//                    (new Pig)->Activate(Time + Exponential(365)); // Aktivace nových prasat v populaci
//                }
//            }
//
//
//            // Čekání na další událost (např. další rok)
//            Wait(Exponential(365)); // Například 365 dní pro simulaci jednoho roku
//        }
//    }
//    bool shouldReproduce() {
//        // Zde implementujte logiku, která určuje, zda prasata mohou rozmnožovat
//        return true; // Příklad: vždy vrací true
//    }
//
//    int calculateNumberOfNewPigs() {
//        // Zde implementujte logiku pro výpočet počtu nových prasat
//        return Normal(10, 2); // Příklad: průměrně 10 nových prasat s nějakou variabilitou
//    }
//
//    bool shouldSomePigsDie() {
//        // Zde implementujte logiku, která určuje, zda by některá prasata měla umřít
//        return Random() < 0.05; // Příklad: 5% šance na úmrtnost v populaci
//    }
//    int removeSomePigsFromPopulation(int removeSome){
//        return removeSome - Normal(10, 2);
//    }
//};

int main() {
    Init(0, 365 );  // Inicializace simulace na 10 let
    for(int i = 0; i < Pig::pigAmount; ++i) {  // Předpokládejme počáteční populaci 50 prasat
        (new Pig)->Activate();
    }
    Run();  // Spuštění simulace


    std::cout << "Počet prasat po roce: " << Pig::pigAmount << std::endl;

    SIMLIB_statistics.Output();
}

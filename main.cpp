#include <simlib.h>
#include <iostream>
#include <stdio.h>

int oldestPig = 0;
class Pig : public Process {
    bool isFemale;
    bool isAlive = true;
    int pigIndex;
    int litterCount = 0;
    int age;
    void Behavior() {
        age = 0;
        if(Random() < 0.5){
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

            if (isAlive && isFemale && age >= 240 && age <= 730) { // Females reproduce between 8-24 months
                if (Random() < 0.6 && isInBreedingSeason() && (litterCount < 2)) {
                    litterCount++;
                    int offspring = int(Normal(7.5, 2.5)); // Average litter size
                    for(int i = 0; i < offspring; ++i) {
                        (new Pig)->Activate(Time + 365); // Offspring mature after 1 year
                        pigAmount++;
                    }
                }
            }
            if(age % 365 == 0){
                litterCount = 0;
            }
            // dying
            if (isAlive && Random() < 0.0002886172890222971) { // 10%chance dying each year
                if(isAlive){
                    pigAmount--;
                }
                Terminate(); // pig died
                isAlive = false;
            }

            // next birth cycle
            Wait(1);
        }

    }

    bool isInBreedingSeason() {
        int dayOfYear = age % 365;
        return dayOfYear >= 305 || dayOfYear <= 31; // Breeding season from November to January
    }
public:
    Pig() : pigIndex(nextPigIndex++) { // Assign a unique index to each pig
    }
    static int pigAmount;
    static int nextPigIndex;
};

int Pig::pigAmount = 50;
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
    Init(0, 365);  // Inicializace simulace na 10 let
    for(int i = 0; i < 59808; ++i) {  // Předpokládejme počáteční populaci 50 prasat
        (new Pig)->Activate();
    }
    Run();  // Spuštění simulace


    std::cout << "Počet prasat po roce: " << Pig::pigAmount - 173000 << std::endl;

    SIMLIB_statistics.Output();
}

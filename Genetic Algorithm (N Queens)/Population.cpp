//
//  Population.cpp
//  Genetic Algorithm (N Queens)
//
//  Created by Uon Liaquat on 11/04/2019.
//  Copyright © 2019 Uon Liaquat. All rights reserved.
//
#include "Chromosome.cpp"
class Population{
private:
    int populationSize = 100;
    Chromosome chromosomes[populationSize];
public:
    Chromosome* GetChromsomes(){
        return chromosomes;
    }
    
    int GetPopulationSize(){
        return populationSize;
    }
};

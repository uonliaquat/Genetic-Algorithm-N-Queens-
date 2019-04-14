//
//  main.cpp
//  Genetic Algorithm (N Queens)
//
//  Created by Uon Liaquat on 07/04/2019.
//  Copyright © 2019 Uon Liaquat. All rights reserved.
//

#include <iostream>
#include "GeneticAlgorithm.cpp"
#define ITERATION_RATE 100

using namespace std;

int main(){
    srand( (unsigned int) time(NULL) );
    GeneticAlgorithm genetic;
    GeneticAlgorithm::Population population = genetic.InitializePopulation();
    for(int i = 0; i < ITERATION_RATE; i++){
        if(genetic.isFound(population)){
            break;
        }
        GeneticAlgorithm::Chromosome * c1 = genetic.CrossOver(population);
        GeneticAlgorithm::Chromosome * c2 = genetic.Mutation(population);
        GeneticAlgorithm::Chromosome * c3 = genetic.SelectFittest(population);
        
        GeneticAlgorithm::Population newPopulation;
        int index1 = 0, index2 = 0;
        for(int i = 0; i < POPULATION_SIZE; i++){
            if(i < CROSS_OVER_RATE){
                newPopulation.SetChromosome(c1[i], i);
            }
            else if(i < CROSS_OVER_RATE + MUTATION_RATE){
                newPopulation.SetChromosome(c2[index1], i);
                index1++;
            }
            else{
                newPopulation.SetChromosome(c3[index2], i);
                index2++;
            }
        }
        population = newPopulation;
        cout<<endl<<endl<<"Generation: " + to_string(i)<<endl<<endl;
        genetic.PrintPopulation(population);
    }
    
}

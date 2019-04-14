//
//  GeneticAlgorithm.cpp
//  Genetic Algorithm (N Queens)
//
//  Created by Uon Liaquat on 11/04/2019.
//  Copyright © 2019 Uon Liaquat. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <algorithm>

#define POPULATION_SIZE 100
#define CROSS_OVER_RATE 96
#define MUTATION_RATE 2
#define FITNESS_RATE 2

using namespace std;



class GeneticAlgorithm{
public:
    class Chromosome{
    private:
        unsigned char arr[3];
        int fitnessVal;
    public:
        unsigned char* GetArr(){
            return arr;
        }
        void SetArr(unsigned char arr[3]){
            this->arr[0] = arr[0];
            this->arr[1] = arr[1];
            this->arr[2] = arr[2];
        }
        int GetFitnessValue(){
            return fitnessVal;
        }
        void SetFitnessValue(int value){
            fitnessVal = value;
        }
        
    };
    
public:
    class Population{
    private:
        Chromosome chromosomes[POPULATION_SIZE];
    public:
        Chromosome* GetChromsomes(){
            return chromosomes;
        }
        void SetChromosome(Chromosome chromo, int index){
            chromosomes[index] = chromo;
        }
        
    };
    
public:
    Population InitializePopulation(){
        Population population;
        for(int i = 0; i < POPULATION_SIZE; i++){
            unsigned char temp[3];
            for(int j = 0; j < 3; j++){
                temp[j] = rand()% 255 + 0;
            }
            population.GetChromsomes()[i].SetArr(temp);
            population.GetChromsomes()[i].SetFitnessValue(FitnessFun(SplitQueens(temp)));
        }
        return population;
    }
    
    Population Sort(Population population){
        for(int i = 0; i < POPULATION_SIZE; i++){
            for(int j = 0; j < POPULATION_SIZE; j++){
                if(population.GetChromsomes()[i].GetFitnessValue() < population.GetChromsomes()[j].GetFitnessValue()){
                    Chromosome chromo = population.GetChromsomes()[i];
                    population.GetChromsomes()[i] = population.GetChromsomes()[j];
                    population.GetChromsomes()[j] = chromo;
                }
            }
        }
        return population;
    }
    
    Chromosome * CrossOver(Population population){
        Population sortedPopulation = Sort(population);
        Chromosome * chromosome = new Chromosome[CROSS_OVER_RATE];
        for(int i = 0; i < CROSS_OVER_RATE; i++){
            unsigned char arr[3];
            //child1
            arr[0] = sortedPopulation.GetChromsomes()[i].GetArr()[0];
            arr[2] = sortedPopulation.GetChromsomes()[i+1].GetArr()[2];
            unsigned char temp1 = sortedPopulation.GetChromsomes()[i].GetArr()[1] & 0b11110000;
            unsigned char temp2 = sortedPopulation.GetChromsomes()[i + 1].GetArr()[1] & 0b00001111;
            arr[1] = temp1 + temp2;
            chromosome[i].SetArr(arr);
            chromosome[i].SetFitnessValue(FitnessFun(SplitQueens(arr)));
            
            //child2
            arr[0] = sortedPopulation.GetChromsomes()[i + 1].GetArr()[0];
            arr[2] = sortedPopulation.GetChromsomes()[i].GetArr()[2];
            temp1 = sortedPopulation.GetChromsomes()[i + 1].GetArr()[1] & 0b11110000;
            temp2 = sortedPopulation.GetChromsomes()[i].GetArr()[1] & 0b00001111;
            arr[1] = temp1 + temp2;
            chromosome[i + 1].SetArr(arr);
            chromosome[i + 1].SetFitnessValue(FitnessFun(SplitQueens(arr)));
        }
        return chromosome;
    }
    
    Chromosome *  Mutation(Population population){
        Chromosome * chromosome = new Chromosome[MUTATION_RATE];
        for(int i = 0; i < MUTATION_RATE; i++){
            int chromosome_index = rand()% (POPULATION_SIZE - 1) + 0;
            int arr_index = rand()% 2 + 0;
            int bit_index = rand()% 7 + 0;
            int temp = 1;
            temp = temp << bit_index;
            chromosome[i].SetArr(population.GetChromsomes()[chromosome_index].GetArr());
            chromosome[i].GetArr()[arr_index] = population.GetChromsomes()[chromosome_index].GetArr()[arr_index] ^ (0b11111111 & temp);
            chromosome[i].SetFitnessValue(FitnessFun(SplitQueens(chromosome[i].GetArr())));
        }
        return chromosome;
    }
    
    Chromosome * SelectFittest(Population population){
        Chromosome * chromosome = new Chromosome[FITNESS_RATE];
        Population sortedPopulation = Sort(population);
        for(int i = 0; i < FITNESS_RATE; i++){
            chromosome[i] = sortedPopulation.GetChromsomes()[i];
        }
        return chromosome;
    }
    
    bool isFound(Population population){
        Population sortedPopulation = Sort(population);
        if(sortedPopulation.GetChromsomes()[0].GetFitnessValue() == 0){
            cout<<"Solution:"<<endl;
            for(int i = 0; i < 3; i++){
                bitset<8> bits(sortedPopulation.GetChromsomes()[0].GetArr()[i]);
                cout<<bits;
            }
            cout<<endl;
            return true;
        }
        return false;
    }
    
    unsigned char * SplitQueens(unsigned char arr[3]){
        unsigned char * queen = new unsigned char[8];
        unsigned char binary = 0b11100000;
        unsigned char shift = 5;
        int arr_index = 0;
        for(int i = 0; i < 8; i++){
            queen[i] = (arr[arr_index] & binary) >> shift;
            shift = shift - 3;
            binary = binary >> 3;
            if(i == 1){
                i++;
                arr_index++;
                shift = 4;
                binary = 0b01110000;
            }
            else if(i == 4){
                i++;
                arr_index++;
                shift = 3;
                binary = 0b00111000;
            }
        }
        queen[2] = (int)((arr[0] & 0b00000011) << 1) + ((arr[1] & 0b10000000) >> 7);
        queen[5] = (int)((arr[1] & 0b00000001) << 2) + ((arr[2] & 0b11000000) >> 6);
        return queen;
    }
    
    int FitnessFun(unsigned char queen[8]){
        int fitnessVal = 0;
        for(int i = 0; i < 8; i++){
            for(int j = i+1; j < 8; j++){
                    if((queen[i] == queen[j]) || abs(i - j) == abs((int)queen[i] - (int)queen[j])){
                        fitnessVal++;
                        break;
                    }
            }
        }
        delete queen;
        return fitnessVal;
    }
    
    void PrintPopulation(Population population){
        for(int i = 0; i < POPULATION_SIZE; i++){
            for(int j = 0; j < 3; j++){
                bitset<8> bitset(population.GetChromsomes()[i].GetArr()[j]);
                cout<<bitset;
            }
            cout<<"     Fitness Value: "<<population.GetChromsomes()[i].GetFitnessValue()<<endl;
        }
    }
};

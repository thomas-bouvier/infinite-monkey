#ifndef DNA_H
#define DNA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  char * genes;
  short int length;
  int fitness;
} DNA;

DNA * new_dna(short int length);

double calc_dna_fitness(DNA * dna, char * target);

DNA * crossover(DNA * dna_a, DNA * dna_b);
void mutate(DNA * dna, float mutation_rate);

void print_dna(DNA * dna, int verbose);

#endif

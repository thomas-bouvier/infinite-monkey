#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dna.h"

#define POPULATION_MAX  2000
#define PERFECT_SCORE   1

typedef DNA * Population;

typedef struct Simulation {
  char * target;
  short int nb_chars;
  float mutation_rate;
  Population * population;
  int generations;
  int finished;
  char * best;
  double best_fitness;
} Simulation;

Simulation * new_simulation(char * target, float mutation_rate);
Population * new_population(Simulation * simulation);

void generate(Simulation * simulation);
void calc_fitness(Simulation * simulation);
int evaluate(Simulation * simulation);

DNA * accept_reject(Simulation * simulation, double max_fitness);

void print_population(Population * population, int verbose);
void print_best(Simulation * simulation, int verbose);

int get_generations(Simulation * simulation);
int is_finished(Simulation * simulation);
char * get_best(Simulation * simulation);
double get_best_fitness(Simulation * simulation);

int random_at_most(int limit);

#endif

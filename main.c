#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simulation.h"

int main() {
  char * target;
  float mutation_rate;
  short nb_chars;

  Simulation * simulation = NULL;
  Population * population = NULL;

  srand(time(NULL));

  target = "to be or not to be to be or not to be";
  mutation_rate = 0.01;

  simulation = new_simulation(target, mutation_rate);
  population = new_population(simulation);

  while (is_finished(simulation) == 0) {
    generate(simulation);
    calc_fitness(simulation);
    evaluate(simulation);

    printf("\nGeneration %d\n", simulation->generations);
    print_best(simulation, 1);
  }

  return EXIT_SUCCESS;
}

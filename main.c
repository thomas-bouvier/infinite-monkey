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

  target = "j aime l electronique mais pas le prof";
  mutation_rate = 0.5;
  nb_chars = 40;

  simulation = new_simulation(target, nb_chars, mutation_rate);
  population = new_population(simulation);

  while (is_finished(simulation) == 0) {
    /*
    printf("\n");
    printf("===========================================\n");
    printf("-------------------------------------------\n");
    printf("Generation %d\n", simulation->generations);
    printf("-------------------------------------------\n");
    */

    generate(simulation);
    calc_fitness(simulation);
    evaluate(simulation);

    printf("%d\n", simulation->generations);
    //print_population(simulation->population, 1);
    print_best(simulation, 1);
  }

  return EXIT_SUCCESS;
}

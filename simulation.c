#include "simulation.h"

DNA * accept_reject(Simulation * simulation, int max_fitness) {
  int index;
  int r;
  int safe;
  DNA * dna = NULL;

  safe = 0;

  while (1) {
    index = floor(random_at_most(POPULATION_MAX));
    dna = simulation->population[index];

    r = random_at_most(max_fitness);
    if (r <= dna->fitness)
      return dna;

    ++safe;
    if (safe > 10000) {
      fprintf(stderr, "Infinite loop in rejection function\n");
      exit(0);
    }
  }
}

Simulation * new_simulation(char * target, short int nb_chars, float mutation_rate) {
  Simulation * simulation = NULL;

  if ((simulation = (Simulation *) malloc(sizeof(Simulation))) == (Simulation *) NULL) {
      fprintf(stderr, "Allocation error\n");
      exit(0);
  }

  simulation->target = target;
  simulation->nb_chars = nb_chars;
  simulation->mutation_rate = mutation_rate;

  simulation->generations = 0;
  simulation->finished = 0;

  simulation->best_fitness = 0;

  return simulation;
}

Population * new_population(Simulation * simulation) {
  int i;
  Population * population = NULL;

  if ((population = (Population *) malloc(sizeof(DNA) * POPULATION_MAX)) == (Population *) NULL) {
      fprintf(stderr, "Allocation error\n");
      exit(0);
  }

  for (i = 0; i < POPULATION_MAX; ++i)
    population[i] = new_dna(simulation->nb_chars);

  simulation->population = population;
  calc_fitness(simulation);

  return population;
}

void generate(Simulation * simulation) {
  int max_fitness;
  int i;

  DNA * dna_a = NULL;
  DNA * dna_b = NULL;
  DNA * dna_c = NULL;

  max_fitness = 0;
  for (i = 0; i < POPULATION_MAX; ++i) {
    if (simulation->population[i]->fitness > max_fitness)
      max_fitness = simulation->population[i]->fitness;
  }

  for (i = 0; i < POPULATION_MAX; ++i) {
    dna_a = accept_reject(simulation, max_fitness);
    dna_b = accept_reject(simulation, max_fitness);

    dna_c = crossover(dna_a, dna_b);
    mutate(dna_c, simulation->mutation_rate);

    simulation->population[i] = dna_c;
  }

  simulation->generations++;
}

void calc_fitness(Simulation * simulation) {
  int i;
  for (i = 0; i < POPULATION_MAX; ++i)
    calc_dna_fitness(simulation->population[i], simulation->target);
}

int evaluate(Simulation * simulation) {
  double max_fitness;
  int i;
  int index;

  max_fitness = 0;
  for (i = 0; i < POPULATION_MAX; ++i) {
    if (simulation->population[i]->fitness > max_fitness) {
      index = i;
      max_fitness = simulation->population[i]->fitness;
    }
  }

  simulation->best = simulation->population[index]->genes;
  simulation->best_fitness = max_fitness;

  max_fitness /= 40;
  if (max_fitness >= PERFECT_SCORE)
    simulation->finished = 1;

  return simulation->finished;
}

void print_population(Population * population, int verbose) {
  int i;
  for (i = 0; i < POPULATION_MAX; ++i) {
    print_dna(population[i], verbose);
  }
}

void print_best(Simulation * simulation, int verbose) {
  if (verbose == 1)
    printf("%s (fitness = %f)\n", get_best(simulation), get_best_fitness(simulation));
  else
    printf("%s\n", get_best(simulation));
}

int get_generations(Simulation * simulation) {
  return simulation->generations;
}

int is_finished(Simulation * simulation) {
  return simulation->finished;
}

char * get_best(Simulation * simulation) {
  return simulation->best;
}

double get_best_fitness(Simulation * simulation) {
  return simulation->best_fitness;
}

int random_at_most(int limit) {
  int r;
  int d;

  if (limit == 0) return 0;

  d = RAND_MAX / limit;
  limit *= d;

  do {
    r = rand();
  } while (r >= limit);

  return r / d;
}

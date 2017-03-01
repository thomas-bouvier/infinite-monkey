#include "dna.h"

static inline unsigned randomlt27() {
  long l;
  do {
    l = rand();
  } while (l >= (RAND_MAX / 27) * 27);
 return (unsigned) (l % 27);
}

static char random_char() {
  return "abcdefghijklmnopqrstuvwxyz "[randomlt27() % 27];
}

static void random_populate(char * genes, short int length) {
  int i;
  for (i = 0; i < length; ++i) {
    *(genes + i) = random_char();
  }
}

DNA * new_dna(short int length) {
  DNA * dna = NULL;

  if ((dna = (DNA *) malloc(sizeof(DNA))) == (DNA *) NULL) {
    fprintf(stderr, "Allocation error\n");
    exit(0);
  }

  if ((dna->genes = malloc(sizeof(char) * (length + 1))) == NULL) {
    fprintf(stderr, "Allocation error\n");
    exit(0);
  }

  random_populate(dna->genes, length);
  dna->genes[length + 1] = '\0';

  dna->length = length;
  dna->fitness = 0;

  return dna;
}

double calc_dna_fitness(DNA * dna, char * target) {
  int count = 0;
  int i;

  for (i = 0; i < dna->length; ++i) {
    if (dna->genes[i] == *(target + i))
      ++count;
  }

  dna->fitness = ((double) count) / ((double) dna->length);
  dna->fitness = pow(dna->fitness, 1.0);

  return dna->fitness;
}

DNA * crossover(DNA * dna_a, DNA * dna_b) {
  int i;
  int midpoint;
  DNA * dna_c = NULL;

  if (dna_a->length != dna_b->length) {
    fprintf(stderr, "DNAs don't share the same length\n");
    exit(0);
  }

  dna_c = new_dna(dna_a->length);

  //midpoint = floor(random_at_most(dna_a->length));
  midpoint = dna_a->length / 2;

  for (i = 0; i < dna_a->length; ++i) {
    if (i > midpoint)
      dna_c->genes[i] = dna_a->genes[i];
    else
      dna_c->genes[i] = dna_b->genes[i];
  }

  return dna_c;
}

void mutate(DNA * dna, float mutation_rate) {
  int i;
  double random;

  random = 0;
  for (i = 0; i < dna->length; ++i) {
    random = (double) rand() / RAND_MAX;
    if (random < mutation_rate)
      dna->genes[i] = random_char();
  }
}

void print_dna(DNA * dna, int verbose) {
  printf("%s", dna->genes);

  if (verbose)
    printf(" (fitness = %.2f%%)\n", dna->fitness);
  else
    printf("\n");
}

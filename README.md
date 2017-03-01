# Infinite Monkey

Demonstration of using a genetic algorithm to perform a search

## Step 0: The Population
Create an empty population
Fill it with DNA encoded objects (pick random values to start)

## Step 1: Selection
Create an empty mating pool
For every member of the population, evaluate its fitness based on some criteria/function, and add it to the mating pool in a manner consistant with its fitness, i.e. the more fit it is the more times it appears in the mating pool, in order to be more likely picked for reproduction.

# Step 2: Reproduction Create a new empty population
Fill the new population by executing the following steps:
* Pick two "parent" objects from the mating pool.
* Crossover -- create a "child" object by mating these two parents.
* Mutation -- mutate the child's DNA based on a given probability.
* Add the child object to the new population.
Replace the old population with the new population

# Step 3: Repeat

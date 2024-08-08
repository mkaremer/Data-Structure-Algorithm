import numpy as np
import matplotlib.pyplot as plt

def init_population(size=100):
    population = []
    # Loop through the number of individuals required
    for _ in range(size):
        single_array = np.random.permutation(8)
        population.append(single_array) 
    return population

def fitness_func(single_array):
    n = len(single_array)
    non_attacking = 0 

    # Loop over each pair of queens once
    for i in range(n):
        for j in range(i + 1, n):
            # Check if queens are not attacking each other diagonally
            if abs(single_array[i] - single_array[j]) != j - i:
                # Check if queens are not in the same row
                if single_array[i] != single_array[j]:
                    # If both conditions are met, they are non-attacking
                    non_attacking += 1

    return non_attacking


def select_parents(population, fitnesses):
    # Calculate the total fitness of the population 
    total_fitness = sum(fitnesses)
    
    # Create a list of probabilities for selecting each single_array
    probabilities = []
    for fitness in fitnesses:
        probability = fitness / total_fitness  # Normalize single_array fitness
        probabilities.append(probability)

    # Select two parents from the population based on their probabilities
    parent_indices = np.random.choice(len(population), size=2, p=probabilities, replace=False)
    parent1 = population[parent_indices[0]]
    parent2 = population[parent_indices[1]]

    return parent1, parent2

def crossover(parent1, parent2):
    # Randomly select a point to perform crossover. 
    point = np.random.randint(1, 7)

    # Create the first and second child:
    child1 = np.concatenate([parent1[:point], parent2[point:]])
    child2 = np.concatenate([parent2[:point], parent1[point:]])

    return child1, child2

def mutate(child, mutation_rate=0.01):
    # Check if mutation should occur, based on the mutation rate
    if np.random.rand() < mutation_rate:
        # Select a random index in the child array to mutate
        idx = np.random.randint(8) 

        # Generate a new value 
        new_value = np.random.randint(8) 
        child[idx] = new_value

    return child

def run_genetic_algorithm(pop_size=100, generations=500, mutation_rate=0.01):
    best_fitness = []
    avg_fitness = []

    population = init_population(pop_size)

    # Loop over each generation to produce new population
    for _ in range(generations):
        # Calculate the fitness for each single_array in the population
        fitnesses = [fitness_func(ind) for ind in population]
        best_fitness.append(max(fitnesses))
        avg_fitness.append(np.mean(fitnesses))

        new_population = []
        
        # generate new population until reach full size again
        while len(new_population) < pop_size:
            parent1, parent2 = select_parents(population, fitnesses)
            child1, child2 = crossover(parent1, parent2)
            
            # Mutate the offspring and add them to the new population
            new_population.append(mutate(child1, mutation_rate))
            new_population.append(mutate(child2, mutation_rate))
        
        # Replace the old population with new population
        population = new_population

    #plot the results
    plt.plot(best_fitness, label='Best Fitness')
    plt.plot(avg_fitness, label='Average Fitness')
    plt.xlabel('Generation')
    plt.ylabel('Fitness')
    plt.title('Fitness over Generations')
    plt.legend()
    plt.show()

    # return population, best_fitness, avg_fitness
    return population

# Run the genetic algorithm
solution = run_genetic_algorithm()
if solution:
    print("Solution found:", solution)
else:
    print("No solution found.")
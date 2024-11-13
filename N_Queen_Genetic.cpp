#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <numeric>

// Global variables and random number generation setup
std::random_device rd;
std::mt19937 gen(rd());
int nq = 8; // Fixed number of queens for predefined boards
int maxFitness;

// Predefined board configurations
std::vector<std::vector<int>> getPredefinedBoards() {
    return {
        {1, 2, 3, 4, 5, 6, 7, 8},  // Linear arrangement
        {8, 7, 6, 5, 4, 3, 2, 1},  // Reverse arrangement
        {2, 4, 6, 8, 1, 3, 5, 7},  // Alternating pattern
        {4, 2, 7, 3, 6, 8, 1, 5},  // Random arrangement 1
        {3, 6, 2, 7, 1, 4, 8, 5},  // Random arrangement 2
        {5, 2, 4, 7, 3, 8, 6, 1},  // Random arrangement 3
        {3, 7, 2, 8, 5, 1, 4, 6},  // Random arrangement 4
        {4, 1, 5, 8, 2, 7, 3, 6},  // Random arrangement 5
        {2, 5, 7, 1, 3, 8, 6, 4},  // Random arrangement 6
        {3, 6, 4, 2, 8, 5, 7, 1}   // Random arrangement 7
    };
}

// Calculate fitness of a chromosome
int fitness(const std::vector<int>& chromosome) {
    // Calculate horizontal collisions
    int horizontal_collisions = 0;
    for (int i = 1; i <= nq; i++) {
        int count = std::count(chromosome.begin(), chromosome.end(), i);
        if (count > 1) {
            horizontal_collisions += (count - 1);
        }
    }
    horizontal_collisions /= 2;

    // Calculate diagonal collisions
    std::vector<int> left_diagonal(2 * nq, 0);
    std::vector<int> right_diagonal(2 * nq, 0);

    for (int i = 0; i < nq; i++) {
        left_diagonal[i + chromosome[i] - 1]++;
        right_diagonal[nq - i + chromosome[i] - 2]++;
    }

    double diagonal_collisions = 0;
    for (int i = 0; i < 2 * nq - 1; i++) {
        int counter = 0;
        if (left_diagonal[i] > 1) {
            counter += left_diagonal[i] - 1;
        }
        if (right_diagonal[i] > 1) {
            counter += right_diagonal[i] - 1;
        }
        diagonal_collisions += counter / (double)(nq - std::abs(i - nq + 1));
    }

    return maxFitness - (horizontal_collisions + diagonal_collisions);
}

// Calculate probability for selection
double probability(const std::vector<int>& chromosome) {
    return (double)fitness(chromosome) / maxFitness;
}

// Random selection based on probability
std::vector<int> random_pick(const std::vector<std::vector<int>>& population, const std::vector<double>& probabilities) {
    double total = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    std::uniform_real_distribution<> dis(0, total);
    double r = dis(gen);
    double upto = 0;

    for (size_t i = 0; i < population.size(); i++) {
        if (upto + probabilities[i] >= r) {
            return population[i];
        }
        upto += probabilities[i];
    }
    return population.back();
}

// Reproduction (crossover)
std::vector<int> reproduce(const std::vector<int>& x, const std::vector<int>& y) {
    std::uniform_int_distribution<> dis(0, nq - 1);
    int c = dis(gen);

    std::vector<int> child(nq);
    for (int i = 0; i < c; i++) {
        child[i] = x[i];
    }
    for (int i = c; i < nq; i++) {
        child[i] = y[i];
    }
    return child;
}

// Mutation
std::vector<int> mutate(std::vector<int> x) {
    std::uniform_int_distribution<> dis_pos(0, nq - 1);
    std::uniform_int_distribution<> dis_val(1, nq);
    int c = dis_pos(gen);
    int m = dis_val(gen);
    x[c] = m;
    return x;
}

// Print chromosome and its fitness
void print_chromosome(const std::vector<int>& chrom) {
    std::cout << "Chromosome = [";
    for (int i = 0; i < nq; i++) {
        std::cout << chrom[i];
        if (i < nq - 1) std::cout << ", ";
    }
    std::cout << "], Fitness = " << fitness(chrom) << std::endl;
}

// Print the chess board
void print_board(const std::vector<int>& chromosome) {
    std::cout << "\nBoard Configuration:\n";
    std::cout << "  ";
    for (int i = 0; i < nq; i++) std::cout << i + 1 << " ";
    std::cout << "\n";

    for (int i = 0; i < nq; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < nq; j++) {
            if (chromosome[j] == i + 1) {
                std::cout << "Q ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

// Genetic algorithm main function
std::vector<std::vector<int>> genetic_queen(std::vector<std::vector<int>>& population) {
    const double mutation_probability = 0.03;
    std::vector<std::vector<int>> new_population;
    std::vector<double> probabilities;

    // Calculate probabilities
    for (const auto& chromosome : population) {
        probabilities.push_back(probability(chromosome));
    }

    // Create new population
    while (new_population.size() < population.size()) {
        std::vector<int> x = random_pick(population, probabilities);
        std::vector<int> y = random_pick(population, probabilities);
        std::vector<int> child = reproduce(x, y);

        std::uniform_real_distribution<> dis(0.0, 1.0);
        if (dis(gen) < mutation_probability) {
            child = mutate(child);
        }

        new_population.push_back(child);

        if (fitness(child) == maxFitness) {
            std::cout << "\nSolution found!\n";
            print_chromosome(child);
            print_board(child);
            break;
        }
    }

    return new_population;
}

int main() {
    maxFitness = (nq * (nq - 1)) / 2;

    // Get predefined boards
    std::vector<std::vector<int>> population = getPredefinedBoards();

    std::cout << "Initial board configurations:\n";
    for (size_t i = 0; i < population.size(); i++) {
        std::cout << "\nBoard " << i + 1 << ":\n";
        print_chromosome(population[i]);
        print_board(population[i]);
    }

    int generation = 1;
    bool solution_found = false;
    std::vector<int> solution;

    // Main loop
    while (!solution_found && generation <= 1000) {
        std::cout << "\n=== Generation " << generation << " ===\n";
        population = genetic_queen(population);

        // Find best fitness in current generation
        int max_fitness = 0;
        for (const auto& chrom : population) {
            int current_fitness = fitness(chrom);
            if (current_fitness > max_fitness) {
                max_fitness = current_fitness;
                solution = chrom;
            }
            if (current_fitness == maxFitness) {
                solution_found = true;
                break;
            }
        }

        std::cout << "Best chromosome in generation " << generation << ":\n";
        print_chromosome(solution);
        print_board(solution);

        generation++;
    }

    if (solution_found) {
        std::cout << "\nSolution found in generation " << generation - 1 << "!\n";
    } else {
        std::cout << "\nNo perfect solution found after " << generation - 1 << " generations.\n";
        std::cout << "Best solution found:\n";
    }

    print_chromosome(solution);
    print_board(solution);

    return 0;
}

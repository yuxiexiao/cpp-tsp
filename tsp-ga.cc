# include "tsp-ga.hh"
# include <cstdlib>
# include <set>

using namespace std;


// Implements the genetic algorithm for the travelling salesman problem



// Constructor that initializes the genome from the specified visit order
TSPGenome::TSPGenome(const vector<int> &ordering) {
    order = ordering;
    circuitLen = -1;
}


// Constructor that takes the number of points that will be visited, and
// generates a random order in those points. The circuit length is initialized
// to -1.
TSPGenome::TSPGenome(int numPoints) {
    for (int i = 0; i < numPoints; i++) {
        order.push_back(i);
    }
    random_shuffle(order.begin(), order.end());
    circuitLen = -1;
}


// Destructor - TSPGenome allocates no dynamic resources
TSPGenome::~TSPGenome() {
    // no op
}


// Accessors
vector<int> TSPGenome::getOrder() const {
    return order;
}


double TSPGenome::getCircuitLength() const{
    return circuitLen;
}


// Mutators

// updates the circuitLength given the input points vector and the current
// order
void TSPGenome::computeCircuitLength(const vector<Point> points) {
    circuitLen = 0;
    for (unsigned int i = 0; i < order.size(); i++){
        circuitLen += points[order[i]].distanceTo(points[order[(i + 1) %
                                             (order.size())]]);
    }
}


// mutate the ordering by swapping two random indices in the order vector
void TSPGenome::mutate() {
    // generate two different random indices
    int randa;
    int randb;
    randa = rand() % order.size();
    randb = rand() % order.size();
    if (order.size() > 1){
        while (randa == randb) {
            randb = rand() % order.size();
        }
    }
    swap(order[randa], order[randb]);
}


// return an offspring of the two specified genomes by taking the first random
// i elements of the first genome and filling in the offspring with additional
// non-repeating elements of the second genome.
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
    int index = rand() % g1.getOrder().size();
    vector<int> offspring;
    set<int> s;

    // copy the first j = index elements into a new genome called offspring.
    // fill a set s for the elements in offspring so we can avoid repeats
    for (int j = 0; j < index; j++){
        s.insert(g1.getOrder()[j]);
        offspring.push_back(g1.getOrder()[j]);
    }

    int added = 0;

    for (int i = 0; i < g2.getOrder().size(); i++) {
        // add the member of g2 into offspring if it's not already in it
        if (s.count(g2.getOrder()[i]) == 0) {
            offspring.push_back(g2.getOrder()[i]);
            s.insert(g2.getOrder()[i]);
            added++;
        }
        // break if offspring is filled
        if (added == g1.getOrder().size() - index) {
            break;
        }
    }

    return(TSPGenome(offspring));
}


// returns true if g1's circuit lenght is longer than g2's
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2) {
    return (g1.getCircuitLength() < g2.getCircuitLength());
}


// Generates an initial population of random genomes. This function finds a
// short path using a genetic algorithm, and prints every ten generation's
// shortest path.
TSPGenome findAShortPath(const vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations) {
    int gen = 0;
    vector<TSPGenome> population;

    // generate an initial population of random genomes of size populationSize
    for (int i = 0; i < populationSize; i++) {
        population.push_back(TSPGenome(points.size()));
    }
    while (gen < numGenerations) {
        // iterate over the population and compute the circuit lengths
        for (int i = 0; i < populationSize; i++) {
            population[i].computeCircuitLength(points);
        }

        // sort the population according to their circuitLengths (increasing)
        sort(population.begin(), population.end(), isShorterPath);

        // every 10 generations, print the current shortest path
        if (gen % 10 == 0) {
            cout << "Generation " << gen << ": shortest path is "
                 << population[0].getCircuitLength() << endl;
        }

        // keeps the top N = keepPopulation fittest members, and replace the
        // remaining members with new genomes produced from the fittest ones.
        int g1, g2;
        for (int i = keepPopulation; i < populationSize; i++) {
            g1 = rand() % keepPopulation;
            g2 = rand() % keepPopulation;
            if (keepPopulation > 1) {
                while (g1 == g2) {
                    g2 = rand() % keepPopulation;
                }
            }
            population[i] = crosslink(population[g1], population[g2]);
        }

        // apply N = numMutations mutations to random members of the
        // population. Does not mutate the fittest member of the population.
        int rand1;
        for (int j = 0; j < numMutations; j++) {
            rand1 = 1 + rand() % (populationSize - 1);
            population[rand1].mutate();
        }
        gen++;
    }
    return population[0];
}

//
// This function takes a vector of ints as input and prints it in the form:
//  [int1, int2, int3,...int n]
//
void printVector(const vector<int>& toPrint) {
    cout << "[";
    for (unsigned int i = 0; i < toPrint.size() - 1; i++) {
        cout << toPrint[i] << " ";
    }
    cout << toPrint[toPrint.size() - 1] << "]" <<endl;
}










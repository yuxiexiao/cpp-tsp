#include <vector>
#include "Point.hh"

using namespace std;

// A class  to solve the TSP with a genetic algorithm
class TSPGenome {

private:
    vector<int> ordering;
    double circuitLen;
public:
    // constructors
    TSPGenome(const vector<int> &order);
    TSPGenome(int numPoints);

    // destructor
    ~TSPGenome();

    // accessor methods
    vector <int> getOrder() const;
    double getCircuitLength() const;

    // mutator methods
    void computeCircuitLength(const vector<Point> &points) const;
    void mutate();
};

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);
TSPGenome findAShortPath(const vector<Point> &points,
                         int populationSize, int numGenerations,
                         int keepPopulation, int numMutations);

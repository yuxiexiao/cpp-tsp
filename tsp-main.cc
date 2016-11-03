# include "tsp-ga.hh"
# include <ctime>


using namespace std;

// main.cc file that implements genetic algorithm to solve TSP

// prints usage errors
void usage(const char *progname) {
    cout << "usage: " << progname << " population generation keep mutate"
         << endl;
    cout << "\tpopulation is an integer > 0 specifying pop. size"
         << endl;
    cout << "\tgeneration is an integer >0 specifying how many gen. to run"
         << endl;
    cout << "\t keep is a float in range 0-1 that specifies percent to keep"
         << endl;
    cout << "\t mutate is a nonnegative float for average mutations per member"
         << endl;
}


int main(int argc, char **argv) {
    // make sure there are 4 arguments
    if (argc != 5) {
        usage(argv[0]);
        return 1;
    }

    int pop = (int) atoi(argv[1]);
    int gen = (int) atoi(argv[2]);
    float keep = (float) atof(argv[3]);
    float mutate = (float) atof(argv[4]);

    // make sure arguments are in the correct range
    if (pop < 1 || gen < 1 || keep < 0 || keep > 1 || mutate < 0) {
        usage(argv[0]);
        return 1;
    }

    // get the Points from input
    double x, y, z;
    int n;
    vector<Point> points;

    cout << "How many points?" << endl;
    cin>> n;

    for (int i = 0; i < n; i ++) {
        cout << "Enter Point " << i << endl;
        cin >> x >> y >> z;
        points.push_back(Point(x, y, z));
    }
    // seed the random number generator
    srand(time(nullptr));

    TSPGenome path(n);
    path = findAShortPath(points, pop, gen, int((keep * pop) + 1),
                          int(mutate * pop));

    cout << "Shortest path: ";
    printVector(path.getOrder());
    cout << "Distance: " << path.getCircuitLength() << endl;

}



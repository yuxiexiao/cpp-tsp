#include "Point.hh"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


using namespace std;

//
// This functions takes as input a vector of points and a vector of an order.
// It returns the length of the path that traverses the circuit according
// to the order of points specified.
//
double circuitLength(const vector<Point> &points, const vector<int> &order) {
    double length = 0;
    for (unsigned int i = 0; i < order.size(); i++){
        length += points[order[i]].distanceTo(points[order[(i + 1) %
                                             (order.size())]]);
    }
    return length;
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


//
// This function takes a vector of points as input, and returns the path
// through them that yields the shortest distance. The path is returned as a
// vector of ints of the order to visit each point. This funciton uses a
// brute force algorithm to permute all paths and get their lengths.
//
vector<int> findShortestPath(const vector<Point> &points) {
    vector<int> order(points.size());
    vector<int> bestPath(points.size());
    double shortestLen;
    double currentLen;

    // initialize order with [0, 1, 2, 3, ... n]
    for (unsigned int i = 0; i < points.size(); i++) {
        order[i] = i;
    }

    shortestLen = circuitLength(points, order);
    currentLen = shortestLen;
    bestPath = order;

    vector<int> orderCopy(order);

    // permute all paths and find the shortest length
    while (next_permutation(orderCopy.begin(), orderCopy.end())){
        currentLen = circuitLength(points, orderCopy);
        if (currentLen < shortestLen) {
            shortestLen = currentLen;
            bestPath = orderCopy;
        }
    }

    return bestPath;
}


int main() {
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

  cout << "Best order:";
  printVector(findShortestPath(points));
  cout << "Shortest distance:"
       << circuitLength(points, findShortestPath(points)) << endl;

}
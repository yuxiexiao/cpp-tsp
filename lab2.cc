#include "Point.hh"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithms>


using namespace std;

double circuitLength(const vector<Point> &points, const vector<int> &order) {
	double length = 0;
	for (unsigned int i = 0; i < order.size(); i++){
		length += points[order[i]].distanceTo(points[order[(i+1)%
											  (order.size() - 1)]);
	}
}

vector<int> findShortestPath(const vector<Point> &points) {
	vector<int> order(points.size());
	double shortestLen;
	double currentLen;
	vector<int> bestPath(points.size());

	iota(order.begin(), order.end(), 0); // fills order with (0,1,2 .. N -1)
	shortestLen = circuitLength(points, order);
	currentLen = shortestLen;
	bestPath = order;

	vector<int> > orderCopy(order);

	while (next_permutation(orderCopy.begin(), orderCopy.end())){
		currentLen = circuitLength(points, orderCopy);
		if (currentLen < shortestLen) {
			shortestLen = currentLen;
			bestPath = orderCopy;
		}
	}

	return bestPath;
}

void printVector(const vector<int>& toPrint) {
	cout << "[";
	for (unsigned int i = 0; i < toPrint.size() - 1; i++) {
		cout << toPrint[i] << " ";
	}
	cout << toPrint[toPrint.size() - 1] << "]";
}


int main() {
  double x, y, z;
  int n;
  cout << "How many points?" << endl;
  cin>> n;
  vector<int> points(n);

  for (unsigned int i = 0; i < n; i ++) {
  	cout << "Enter Point" << i << endl;
  	cin >> x >> y >> z;
  	points.push_back(Point(x, y, z));
  }
  cout << "Best order:" << printVector(findShortestPath(points)) << endl;
  cout << "Shortest distance:"
   	   << circuitLength(points, findShortestPath(points)) << endl;

}
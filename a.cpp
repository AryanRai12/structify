#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;


int findIntersections(vector<float> radians, vector<string> points) {
	// Since for every chord, there are 2 points, no of chords, will be half of the points.
	int n = points.size() >> 1;
	// Assuming, every distinct chord intersect with each other. No of intersections = Nc2.
	int max_intersections = (n*(n-1)) >> 1;
	// Now, we need to subtract those intersections which did not happen.
	// Case 1: If a chord ends at ei, and any chord which starts later than ei, ith chord won't intersect it.
	// Case 2: If a chord starts later than si, but finishes before ei, in that case also, 
	// 			there will be no intersection.
	// Assuming the coordinates follows, notations s_x, and e_x.
	unordered_map<int, int> no_int, start_ind;
	int ind = 0;
	for(string &point: points) {
		// Setting 0 for every chord, for which currently it does not intersect.
		int key = stoi(point.substr(2, point.size() - 2)); // removing s_ or e_
		no_int[key] = 0;
		if(point[0] == 's') {
			start_ind[key] = ind++;
		}
	}
	// Case 1 Logic
	// For this we can simpy iterate the points array from backwards, and keep a count of s_x and if we 
	// encounter any e_y, then we know that for this point, the current count of s_x is the no of those chords
	// which starts after it finishes.
	int starts = 0;
	for(int i = (n << 1) - 1; i >= 0; --i) {
		if(points[i][0] == 's') ++starts;
		else {
			int key = stoi(points[i].substr(2, point.size() - 2));
			no_int[key] = starts;
		}
	}
	// Case 2 Logic
	int ends = 0;
	for(int i = 0; i < (n << 1); ++i) {
		int key = stoi(points[i].substr(2, point.size() - 2));
		if(points[i][0] == 'e') ++ends;
		no_int[key] = end - 1;
	}
	int subtractions = 0;
	for(auto i = no_int.begin(); i != no_int.end(); ++i) {
		subtractions += i->second;
	}
	return max_intersections - subtractions;
}

int main() {
	vector<string> points;
	vector<float> radians;
	cout << findIntersections(radians, points) << endl;
	return 0;
}

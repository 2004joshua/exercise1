#include "gps_calculator.h"
#include <cmath> 
#include <iomanip>
#include <limits>
#include <string> 
#include <cctype> 
#include <algorithm>
#include <stdexpecpt>

double M_PI 3.1415 
const double EARTH_RADIUS_KM = 6371.0;

using namespace std; 


// converts to radians
double toRadians(double x) {
  return x * M_PI / 180.0; 
}

static inline void trim(string &s) {

	// Left trim 
	s.erase(s.begin(), find_if(s.begin(), s.end(), 
            [](unsigned char c){ return !isspace(c); }));

	// Right trim 
	 s.erase(find_if(s.rbegin(), s.rend(),
            [](unsigned char c){ return !isspace(c); }).base(), s.end());
}

double parseCoordinates(const string &input){
	// check if all indices are numbers
	string s = input; 

	trim(s); 

	if(s.empty()) {
		cerr << "This string is empty...\n"; 

		return -200; // Error code for empty string 
	}

	if(!s.empty() && s.back() == u8'°') {
  	s.pop_back(); 
    trim(s);
  }

	double sign = 1.0; 
	if(!s.empty()) {
		char c = s.back(); 
		switch(c) {
			case 'N': 
			case 'E': 
				// Treat normally but pop the back 
				s.pop_back(); 
				trim(s); 
				break; 

			case 'S': 
			case 'W': 
				// South and west cause negative angles
				sign = -1.0; 
				s.pop_back(); 
				trim(s); 
				break; 

			default: 
				// Procede like normal
				break; 
		}
	}

	try {
		size_t pos = 0; 
		double val = stod(s, &pos); 
		
		if(pos != s.size()) {
			cerr << "Invalid format: Extra characters in string...\n"; 
			return -201; // Invalid format
		}

		return toRadians(val * sign); 
	}

	catch(const invalid_argument&) {
		cerr << "Invalid Format: Could not convert to double \n ";
		return -201; 
	}

	catch(const out_of_range&) {
		cerr << "Value is out of range...\n"; 
		return -202; 
	}
}

// Calculates the distance between two coordinate points
double haversine_formula(const string &lat1, const string &lon1, const string &lat2, const string &lon2) {	

  double latA = parseCoordinates(lat1); 
	double latB = parseCoordinates(lat2); 
	double lonA = parseCoordinates(lon1); 
	double lonB = parseCoordinates(lon2);

	
	if(latA == -200 || latB == -200 || lonA == -200 || lonB == -200) {
		cerr << "Empty string inputs...\n"; 
		return -1; 
	}

	if(latA == -201 || latB == -201 || lonA == -201 || lonB == -201) {
		cerr << "Invalid input coordinates..,\n"; 
		return -1; 
	}


	if(latA == -202 || latB == -202 || lonA == -202 || lonB == -202) {
		cerr << "Input is out of range (-90, 90) Lat, (-180, 180) Lon...\n "; 
		return -1; 
	}
  double delta_lat = latB - latA; 
  double delta_lon = lonB - lonA; 

  double a = pow(sin(delta_lat / 2), 2) + cos(latA) * cos(latB) * pow(sin(delta_lon / 2), 2); 
  double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 

  return c * EARTHS_RADIUS_KM; 
}


// solves for the shortest distances then returns an array 
vector<double> shortest_distance_finder(const vector<pair<string, string>> &ArrayA, const vector<pair<string, string>> &ArrayB) {	
	int sizeA = ArrayA.size(), sizeB = ArrayB.size();

	vector<double> distances(sizeA); 
	
	for(int i = 0; i < sizeA; i++) {
		double shortest_distance = numeric_limits<double>::max(); 

		for(int j = 0; j < sizeB; j++) {
			double temp = haversine_formula(
				ArrayA[i].first, 
				ArrayA[i].second, 
				ArrayB[j].first, 
				ArrayB[j].second
			); 

			if(temp < shortest_distance) {
				shortest_distance = temp; 
			}
		}

		distances[i] = shortest_distance; 
	}


	return distances; 
}

void print_distances(const vector<double> &distances) {
	cout << "["; 
	
	for(int i = 0 ; i < distances.size(); i++) {
		cout << distances[i]; 
		
		if(i != (distances.size() - 1)) {
			cout << ", "; 
		} 
	}

	cout << "] \n"; 
} 

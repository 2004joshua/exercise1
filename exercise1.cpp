#include "exercise.h"
#include <cmath> 
#include <iomanip>
#include <limits>

// converts to radians
double toRadians(double x) {
  return x * M_PI / 180.0; 
}

// Calculates the distance between two coordinate points
double haversine_formula(double lat1, double lon1, double lat2, double lon2) {
  lat1 = toRadians(lat1); 
  lon1 = toRadians(lon1); 
  lat2 = toRadians(lat2); 
  lon2 = toRadians(lon2); 

  double delta_lat = lat2 - lat1; 
  double delta_lon = lon2 - lon1; 

  double a = pow(sin(delta_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(delta_lon / 2), 2); 
  double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 

  return c * EARTHS_RADIUS; 
}

// solves for the shortest distances then returns an array 
std::vector<double> shortest_distance_finder(double start[][2], double dest[][2], int size_start, int size_dest) {
  
  std::vector<double> distances(size_start); 

  // used to have a high number so we can find the correct distance
  double shortest_distance; 
  for(int i = 0; i < size_start; i++) {
    shortest_distance = std::numeric_limits<double>::max(); 
    for(int j = 0; j < size_dest; j++) {
      double temp = haversine_formula(start[i][0], start[i][1], dest[j][0], dest[j][1]);

      if(temp < shortest_distance) {
        shortest_distance = temp; 
      }
    }

    distances[i] = shortest_distance; 
  }

  return distances; 
}

void print_distances(std::vector<double> distances) {
  std::cout << "Printing distances array.......\n [ "; 
  for(int i = 0; i < distances.size(); i++) {
    std::cout << std::fixed << std::setprecision(2) << distances[i] << " "; 
  }

  std::cout << "]\n"; 
} 

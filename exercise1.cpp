#include <iostream>
#include <cmath> 
#include <iomanip>
#include <limits>

#define EARTHS_RADIUS 6371.0

int idx = 0; 

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

double shortest_distance(int idx, int destination_array_size, double start[][2], double dest[][2]) {
  double shortest_distance = std::numeric_limits<double>::max(); 

  for(int i = 0; i < destination_array_size; i++) {
    double temp = haversine_formula(start[idx][0], start[idx][1], dest[i][0], dest[i][1]);

    if(temp < shortest_distance) {
      shortest_distance = temp; 
    }
  }

  return shortest_distance; 
}

int main() { 
  
  int s1, s2; 
  
  std::cout << "What's the size of the start array? "; 
  std::cin >> s1; 

  std::cout << "What's the size of the destination array? "; 
  std::cin >> s2; 

  double start[s1][2], dest[s2][2]; 

  // Lets fill up the input arrays
  std::cout << "Start Array...\n"; 
  for(int i = 0; i < s1; i++) { 
    std::cout << "What's the latitude: "; 
    std::cin >> start[i][0]; 
    
    std::cout << "What's the longitude: "; 
    std::cin >> start[i][1]; 
  }

  std::cout << "Destination Array...\n"; 
  for(int i = 0; i < s2; i++) { 
    std::cout << "What's the latitude: "; 
    std::cin >> dest[i][0]; 
    
    std::cout << "What's the longitude: "; 
    std::cin >> dest[i][1]; 
  }

  double record_distances[s1]; 

  for(int i = 0; i < s1; i++) {
    record_distances[i] = shortest_distance(i, s2, start, dest); 
    std::cout << std::fixed << std::setprecision(2) << record_distances[i] << " ";
  }

  std::cout << std::endl; 

  return 0; 
}
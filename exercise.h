#ifndef EXERCISE1_H
#define EXERCISE1_H

#include <iostream>
#include <vector>

#define EARTHS_RADIUS 6371.0
#define MAX_ARRAY_SIZE 100

double toRadians(double x); 
double haversine_formula(double lat1, double lon1, double lat2, double lon2);
std::vector<double> shortest_distance_finder(double start[][2], double dest[][2], int size_start, int size_dest);
void print_distances(std::vector<double> distances);

#endif
#ifndef GPS_CALCULATOR_H
#define GPS_CALCULATOR_H

#include <iostream>
#include <vector>
#include <utility> 
#include <string>

double toRadians(double x);

double parseCoordinates(const string &input); 

double haversine_formula(const string &lat1, const string &lon1, const string &lat2, const string &lon2); 

vector<double> shortest_distance_finder
	(const vector<pair<string, string>> &ArrayA, const vector<pair<string, string>> &ArrayB); 

void print_distances(std::vector<double> &distances);

void readCsvFile(const string &csvFile);

#endif

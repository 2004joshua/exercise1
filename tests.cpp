#include <iostream> 
#include "exercise.h"

int main() {
    // Test Case 1
    double start1[][2] = {
        {40.712776, -74.005974},
        {34.052235, -118.243683}
    };
    double dest1[][2] = {
        {48.856613, 2.352222},
        {35.689487, 139.691711}
    };
    std::vector<double> distances1 = shortest_distance_finder(start1, dest1, 2, 2);
    print_distances(distances1);

    // Test Case 2
    double start2[][2] = {
        {51.507222, -0.127647},
        {19.432608, -99.133209},
        {-33.868820, 151.209290}
    };
    double dest2[][2] = {
        {55.755825, 37.617298},
        {28.613939, 77.209023},
        {35.689487, 139.691711}
    };
    std::vector<double> distances2 = shortest_distance_finder(start2, dest2, 3, 3);
    print_distances(distances2);

    // Test Case 3
    double start3[][2] = {
        {37.774929, -122.419418},
        {1.352083, 103.819839},
        {52.520008, 13.404954},
        {41.902782, 12.496366}
    };
    double dest3[][2] = {
        {48.856613, 2.352222},
        {39.904202, 116.407394},
        {-34.603722, -58.381592}
    };
    std::vector<double> distances3 = shortest_distance_finder(start3, dest3, 4, 3);
    print_distances(distances3);

    // Test Case 4
    double start4[][2] = {
        {35.689487, 139.691711},
        {40.416775, -3.703790}
    };
    double dest4[][2] = {
        {55.755825, 37.617298},
        {37.983810, 23.727539},
        {34.052235, -118.243683}
    };
    std::vector<double> distances4 = shortest_distance_finder(start4, dest4, 2, 3);
    print_distances(distances4);

    // Test Case 5
    double start5[][2] = {
        {-23.550520, -46.633308},
        {55.953251, -3.188267},
        {48.856613, 2.352222}
    };
    double dest5[][2] = {
        {40.712776, -74.005974},
        {35.689487, 139.691711}
    };
    std::vector<double> distances5 = shortest_distance_finder(start5, dest5, 3, 2);
    print_distances(distances5);

    // Test Case 6
    double start6[][2] = {
        {59.934280, 30.335099},
        {25.761681, -80.191788}
    };
    double dest6[][2] = {
        {35.676192, 139.650311},
        {45.464204, 9.189982},
        {38.907192, -77.036873}
    };
    std::vector<double> distances6 = shortest_distance_finder(start6, dest6, 2, 3);
    print_distances(distances6);

    // Test Case 7
    double start7[][2] = {
        {13.756331, 100.501762},
        {52.229676, 21.012229}
    };
    double dest7[][2] = {
        {40.730610, -73.935242},
        {34.052235, -118.243683},
        {19.432608, -99.133209}
    };
    std::vector<double> distances7 = shortest_distance_finder(start7, dest7, 2, 3);
    print_distances(distances7);

    // Test Case 8
    double start8[][2] = {
        {55.755825, 37.617298},
        {-22.906847, -43.172897},
        {41.385064, 2.173404}
    };
    double dest8[][2] = {
        {35.689487, 139.691711},
        {37.774929, -122.419418}
    };
    std::vector<double> distances8 = shortest_distance_finder(start8, dest8, 3, 2);
    print_distances(distances8);

    // Test Case 9
    double start9[][2] = {
        {35.689487, 139.691711},
        {51.165691, 10.451526}
    };
    double dest9[][2] = {
        {48.856613, 2.352222},
        {55.755825, 37.617298},
        {-34.603722, -58.381592}
    };
    std::vector<double> distances9 = shortest_distance_finder(start9, dest9, 2, 3);
    print_distances(distances9);

    // Test Case 10
    double start10[][2] = {
        {31.230391, 121.473701},
        {39.904202, 116.407394}
    };
    double dest10[][2] = {
        {55.755825, 37.617298},
        {28.704060, 77.102493}
    };
    std::vector<double> distances10 = shortest_distance_finder(start10, dest10, 2, 2);
    print_distances(distances10);

    return 0;
}
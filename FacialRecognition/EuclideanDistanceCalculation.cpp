#include "EuclideanDistanceCalculation.h"
#include <cmath>
#include <vector>

double calculateEuclideanDistance(const std::vector<int>& hist1, const std::vector<int>& hist2) {
    double sum = 0.0;
    for (size_t i = 0; i < hist1.size(); ++i) {
        sum += std::pow(hist1[i] - hist2[i], 2);
    }
    return std::sqrt(sum);
}
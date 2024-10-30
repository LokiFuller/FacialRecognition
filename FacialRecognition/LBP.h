#ifndef LBP_H
#define LBP_H

#include <vector>

std::vector<int> calculateLBP(const std::vector<unsigned char>& image, int width, int height);
std::vector<int> calculateHistogram(const std::vector<int>& lbpImage, int width, int height, int gridX, int gridY);

#endif // LBP_H
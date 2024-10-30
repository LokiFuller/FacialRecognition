#include "LBP.h"
#include <vector>

std::vector<int> calculateLBP(const std::vector<unsigned char>& image, int width, int height) {
    std::vector<int> lbpImage(width * height, 0);

    int radius = 1;
    int neighbors = 8;
    int gridX = 8;
    int gridY = 8;

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            unsigned char center = image[y * width + x];
            int lbpCode = 0;

            lbpCode |= (image[(y - 1) * width + (x - 1)] >= center) << 7;
            lbpCode |= (image[(y - 1) * width + x] >= center) << 6;
            lbpCode |= (image[(y - 1) * width + (x + 1)] >= center) << 5;
            lbpCode |= (image[y * width + (x + 1)] >= center) << 4;
            lbpCode |= (image[(y + 1) * width + (x + 1)] >= center) << 3;
            lbpCode |= (image[(y + 1) * width + x] >= center) << 2;
            lbpCode |= (image[(y + 1) * width + (x - 1)] >= center) << 1;
            lbpCode |= (image[y * width + (x - 1)] >= center) << 0;

            lbpImage[y * width + x] = lbpCode;
        }
    }
    return lbpImage;
}

std::vector<int> calculateHistogram(const std::vector<int>& lbpImage, int width, int height, int gridX, int gridY) {
    std::vector<int> histogram(gridX * gridY * 256, 0);
    int cellWidth = width / gridX;
    int cellHeight = height / gridY;

    for (int gy = 0; gy < gridY; ++gy) {
        for (int gx = 0; gx < gridX; ++gx) {
            int startX = gx * cellWidth;
            int startY = gy * cellHeight;

            for (int y = startY; y < startY + cellHeight; ++y) {
                for (int x = startX; x < startX + cellWidth; ++x) {
                    int lbpValue = lbpImage[y * width + x];
                    histogram[gy * gridX * 256 + gx * 256 + lbpValue]++;
                }
            }
        }
    }
    return histogram;
}
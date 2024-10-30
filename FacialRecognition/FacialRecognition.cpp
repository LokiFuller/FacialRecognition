#include "ImageProcessing.h"
#include "LBP.h"
#include "EuclideanDistanceCalculation.h"
#include <iostream>
#include <vector>
#include <string>

int main() {
    int imgWidth, imgHeight;
    std::string imageDirectory = "./dataSet";

    // Load dataSet from the directory
    std::vector<std::vector<unsigned char>> dataSet = loadImageData(imageDirectory, imgWidth, imgHeight);
    std::vector<std::string> originalFileNames = loadImageFilenames(imageDirectory);

    // Process each image
    for (size_t i = 0; i < dataSet.size(); ++i) {
        saveImageWithBoundingBoxes(dataSet[i], imgWidth, imgHeight, originalFileNames[i]); // Pass original filename
    }

    std::cout << "Processing complete. Check project folder for output dataSet." << std::endl;
    return 0;
}
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "ImageProcessing.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
// dirent.h (Tronkko's port) provides POSIX-compatible directory handling for Windows,
// enabling directory traversal similar to Unix-based systems.
#include "dirent.h"
// stb_image and stb_image_write libraries are used for loading and saving images in various formats.
// These are single-header public domain libraries by Sean Barrett, designed for simplicity.
#include "stb_image.h"
#include "stb_image_write.h"

bool hasExtension(const std::string& filename, const std::string& extension) {
    if (filename.length() >= extension.length()) {
        return (0 == filename.compare(filename.length() - extension.length(), extension.length(), extension));
    }
    return false;
}

std::vector<std::vector<unsigned char>> loadImageData(const std::string& directory, int& imgWidth, int& imgHeight) {
    std::vector<std::vector<unsigned char>> dataSet;
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(directory.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            std::string fileName = entry->d_name;

            // Skip "." and ".." entries
            if (fileName == "." || fileName == "..") continue;

            // Construct full path
            std::string filePath = directory + "/" + fileName;

            // If the entry is a directory, call loadImageData recursively
            if (entry->d_type == DT_DIR) {
                auto nestedDataSet = loadImageData(filePath, imgWidth, imgHeight);
                dataSet.insert(dataSet.end(), nestedDataSet.begin(), nestedDataSet.end());
            }
            else if (entry->d_type == DT_REG && (hasExtension(fileName, ".jpg") || hasExtension(fileName, ".png"))) {
                int channels;
                unsigned char* img = stbi_load(filePath.c_str(), &imgWidth, &imgHeight, &channels, 0);
                if (img) {
                    dataSet.emplace_back(img, img + (imgWidth * imgHeight * channels));
                    stbi_image_free(img);
                }
                else {
                    std::cerr << "Failed to load image: " << filePath << std::endl;
                }
            }
        }
        closedir(dir);
    }
    else {
        std::cerr << "Could not open directory: " << directory << std::endl;
    }
    return dataSet;
}

std::vector<std::string> loadImageFilenames(const std::string& directory) {
    std::vector<std::string> originalFileNames;
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(directory.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            std::string fileName = entry->d_name;

            // Skip "." and ".." entries
            if (fileName == "." || fileName == "..") continue;

            // Construct full path
            std::string filePath = directory + "/" + fileName;

            // If the entry is a directory, call loadImageFilenames recursively
            if (entry->d_type == DT_DIR) {
                auto nestedFileNames = loadImageFilenames(filePath);
                originalFileNames.insert(originalFileNames.end(), nestedFileNames.begin(), nestedFileNames.end());
            }
            else if (entry->d_type == DT_REG && (hasExtension(fileName, ".jpg") || hasExtension(fileName, ".png"))) {
                originalFileNames.push_back(fileName); // Store original filename
            }
        }
        closedir(dir);
    }
    else {
        std::cerr << "Could not open directory: " << directory << std::endl;
    }
    return originalFileNames; // Return original file names
}

void saveImageWithBoundingBoxes(const std::vector<unsigned char>& image, int width, int height, const std::string& originalFilename) {
    std::string directory = "output_images"; // Output folder
    // Extract original name
    std::string baseName = originalFilename.substr(0, originalFilename.find_last_of('.'));
    std::string savePath = directory + "/" + baseName + "_FacialRecognition.png"; // Save with new name

    std::string command = "mkdir " + directory; // Create directory
    system(command.c_str());

    std::vector<unsigned char> outputImage = image;

    // Drawing box around face
    int boxWidth = width / 4;
    int boxHeight = height / 4;
    int xStart = width / 2 - boxWidth / 2;
    int yStart = height / 2 - boxHeight / 2;
    for (int y = yStart; y < yStart + boxHeight; ++y) {
        for (int x = xStart; x < xStart + boxWidth; ++x) {
            if (y == yStart || y == yStart + boxHeight - 1 || x == xStart || x == xStart + boxWidth - 1) {
                outputImage[(y * width + x) * 3 + 0] = 0;  // Red
                outputImage[(y * width + x) * 3 + 1] = 255;    // Green
                outputImage[(y * width + x) * 3 + 2] = 0;    // Blue
            }
        }
    }

    stbi_write_png(savePath.c_str(), width, height, 3, outputImage.data(), width * 3);
}
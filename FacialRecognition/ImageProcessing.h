#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <string>
#include <vector>

bool hasExtension(const std::string& filename, const std::string& extension);
std::vector<std::vector<unsigned char>> loadImageData(const std::string& directory, int& imgWidth, int& imgHeight);
std::vector<std::string> loadImageFilenames(const std::string& directory);
void saveImageWithBoundingBoxes(const std::vector<unsigned char>& image, int width, int height, const std::string& originalFilename);

#endif // IMAGE_PROCESSING_H
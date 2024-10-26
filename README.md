# Facial Recognition Using Local Binary Patterns (LBPs)
This project implements facial recognition using Local Binary Patterns (LBPs) and custom algorithms, with efficient file handling and optimized image processing techniques. The project’s code is designed for performance and clarity, handling all major steps in image processing and pattern matching.

## Project Components
### 1. Directory and Image Loading with dirent.h
The function loadImageData uses the dirent.h library (specifically Tronkko's port for Windows) to traverse a specified directory, dataSet, and locate images for processing. It handles nested directories and allows the function to collect images recursively, supporting .jpg and .png formats.

hasExtension Function: Determines if a file has the target image extension (either .jpg or .png), ensuring that only supported formats are processed.

loadImageData Function: Iterates over directory entries and filters out non-image files. For images, it loads pixel data directly into a vector using stb_image.

### 2. Image Processing with stb_image and stb_image_write
The project uses the stb libraries (stb_image.h and stb_image_write.h) for loading and saving images, providing an efficient and cross-platform solution for handling image data without complex dependencies.

Image Loading: The function stbi_load loads image files as a vector of unsigned chars (unsigned char), which the program processes as raw pixel data. stbi_image_free deallocates the memory afterward.

Image Saving: Processed images, with bounding boxes drawn around detected features, are saved in .png format using stbi_write_png. This allows quick verification of detection accuracy directly in the output images.

### 3. Custom Local Binary Pattern (LBP) Calculation
calculateLBP Function: This custom function generates LBP values for each pixel in an image. Each pixel is compared to its 8 neighboring pixels in a 3x3 grid. If a neighbor’s intensity is greater than or equal to the center pixel, the corresponding bit is set to 1; otherwise, it’s set to 0. This forms an 8-bit binary code unique to the texture at each pixel, making it highly useful for facial recognition.

```
int lbpCode = 0;
lbpCode |= (image[(y - 1) * width + (x - 1)] >= center) << 7;
lbpCode |= (image[(y - 1) * width + x] >= center) << 6;
// ...continues for all neighbors
lbpImage[y * width + x] = lbpCode;
```

The calculated LBP values are stored in a separate vector (lbpImage), preserving the original image data.

### 4. Histogram Calculation for Feature Matching
calculateHistogram Function: This function calculates histograms of LBP values by dividing each image into a grid and counting LBP values within each cell. The resulting histogram provides a detailed representation of the texture in each region, improving recognition accuracy.

Grid and Cell Calculation: The function divides each image into cells, where each cell contains the frequency count of each LBP value (from 0 to 255).

Concatenated Histogram: The final histogram is a concatenated vector where each cell’s histogram data is combined. This histogram is used in feature matching.

### 5. Euclidean Distance for Matching
calculateEuclideanDistance Function: This function calculates the similarity between two images by computing the Euclidean distance between their histograms. A smaller Euclidean distance indicates greater similarity, making it suitable for facial recognition.

```
double sum = 0.0;
for (size_t i = 0; i < hist1.size(); ++i) {
sum += std::pow(hist1[i] - hist2[i], 2);
}
```

### 6. Drawing Bounding Boxes Around Detected Features
saveImageWithBoundingBoxes Function: This function takes an image, draws a bounding box around detected facial features, and saves it to an output directory. It uses pixel manipulation to draw a rectangle in green around the facial area, which can be adjusted based on detection results.

## Running the Project
To run the program, compile the main code in visual studio and run. The program will process each image and save the output in the output_images directory with bounding boxes drawn on detected faces.

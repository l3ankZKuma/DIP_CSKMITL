#include "pch.h"
#include "ImageManager.h"

#define PATH_IMAGES "/Users/bankzkuma/Desktop/CSKMITL/DIP/Lab/Midterm/images/"


template <size_t N>
int findMedian(std::array<int, N>& window, size_t size) {
    std::nth_element(window.begin(), window.begin() + size / 2, window.begin() + size);
    return window[size / 2];
}

template<int maxWindowSize>
void adaptiveMedianFilter(Image& img) {
    int width = img.width;
    int height = img.height;
    int channels = img.bitDepth / BYTE; // Assuming 8-bit per channel

    std::vector<uint8_t> output(img.width * img.height * channels);
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::mutex mtx;

    auto processChunk = [&](int startY, int endY) {
        std::array<int, maxWindowSize * maxWindowSize> windowR, windowG, windowB;

        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < width; ++x) {
                bool done = false;
                int windowSize = 1;

                while (!done && windowSize <= maxWindowSize) {
                    int halfSize = windowSize / 2;
                    size_t count = 0;

                    for (int dy = -halfSize; dy <= halfSize; ++dy) {
                        for (int dx = -halfSize; dx <= halfSize; ++dx) {
                            int nx = std::clamp(x + dx, 0, width - 1);
                            int ny = std::clamp(y + dy, 0, height - 1);
                            int index = (ny * width + nx) * channels;
                            windowR[count] = img.buf[index];
                            windowG[count] = img.buf[index + 1];
                            windowB[count] = img.buf[index + 2];
                            ++count;
                        }
                    }

                    int medianR = findMedian(windowR, count);
                    int medianG = findMedian(windowG, count);
                    int medianB = findMedian(windowB, count);

                    int zMinR = *std::min_element(windowR.begin(), windowR.begin() + count);
                    int zMaxR = *std::max_element(windowR.begin(), windowR.begin() + count);
                    int zMinG = *std::min_element(windowG.begin(), windowG.begin() + count);
                    int zMaxG = *std::max_element(windowG.begin(), windowG.begin() + count);
                    int zMinB = *std::min_element(windowB.begin(), windowB.begin() + count);
                    int zMaxB = *std::max_element(windowB.begin(), windowB.begin() + count);

                    int index = (y * width + x) * channels;
                    int zR = img.buf[index];
                    int zG = img.buf[index + 1];
                    int zB = img.buf[index + 2];

                    std::lock_guard<std::mutex> lock(mtx);
                    if (medianR > zMinR && medianR < zMaxR && medianG > zMinG && medianG < zMaxG && medianB > zMinB && medianB < zMaxB) {
                        if (zR > zMinR && zR < zMaxR && zG > zMinG && zG < zMaxG && zB > zMinB && zB < zMaxB) {
                            output[index] = zR;
                            output[index + 1] = zG;
                            output[index + 2] = zB;
                        } else {
                            output[index] = medianR;
                            output[index + 1] = medianG;
                            output[index + 2] = medianB;
                        }
                        done = true;
                    } else {
                        windowSize += 2;
                    }
                }

                if (!done) {
                    std::lock_guard<std::mutex> lock(mtx);
                    int index = (y * width + x) * channels;
                    output[index] = img.buf[index];
                    output[index + 1] = img.buf[index + 1];
                    output[index + 2] = img.buf[index + 2];
                }
            }
        }
    };

    int chunkSize = height / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * chunkSize;
        int endY = (i == numThreads - 1) ? height : startY + chunkSize;
        threads.emplace_back(processChunk, startY, endY);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::copy(output.begin(), output.end(), img.buf);
}

void applyLaplacianFilter(Image& img) {
    int width = img.width;
    int height = img.height;
    int channels = img.bitDepth / BYTE; // Assuming 8-bit per channel
    
    std::array<int, 9> kernel = {0, 1, 0, 1, -4, 1, 0, 1, 0}; // Laplacian kernel
    int kernelSize = 3;
    int halfKernelSize = kernelSize / 2;

    std::vector<uint8_t> output(img.width * img.height * channels);
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::mutex mtx;

    auto processChunk = [&](int startY, int endY) {
        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * channels;

                for (int c = 0; c < channels; ++c) {
                    int sum = 0;

                    for (int ky = -halfKernelSize; ky <= halfKernelSize; ++ky) {
                        for (int kx = -halfKernelSize; kx <= halfKernelSize; ++kx) {
                            int ny = std::clamp(y + ky, 0, height - 1);
                            int nx = std::clamp(x + kx, 0, width - 1);
                            int nIndex = (ny * width + nx) * channels + c;
                            int kIndex = (ky + halfKernelSize) * kernelSize + (kx + halfKernelSize);

                            sum += img.buf[nIndex] * kernel[kIndex];
                        }
                    }

                    int newValue = img.buf[index + c] - sum;
                    output[index + c] = std::clamp(newValue, 0, 255);
                }
            }
        }
    };

    int chunkSize = height / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * chunkSize;
        int endY = (i == numThreads - 1) ? height : startY + chunkSize;
        threads.emplace_back(processChunk, startY, endY);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::copy(output.begin(), output.end(), img.buf);
}


// Function to change colors based on histogram ranges
void changeColor(Image& img, const std::vector<int>& region, const std::vector<int>& targetColor, const std::vector<std::vector<int>>& colorRange, const std::vector<int>& notChangeColor = {}) {
    int width = img.width;
    int height = img.height;
    int channels = img.bitDepth / BYTE; // Assuming 8-bit per channel

    int targetR = targetColor[0];
    int targetG = targetColor[1];
    int targetB = targetColor[2];

    int minR = colorRange[0][0];
    int maxR = colorRange[0][1];
    int minG = colorRange[1][0];
    int maxG = colorRange[1][1];
    int minB = colorRange[2][0];
    int maxB = colorRange[2][1];

    for (int y = region[1]; y < region[3]; ++y) {
        int adjustedY = height - 1 - y; // Adjust Y coordinate to start from bottom-left
        int index = (adjustedY * width + region[0]) * channels;

        for (int x = region[0]; x < region[2]; ++x) {
            int r = img.buf[index];
            int g = img.buf[index + 1];
            int b = img.buf[index + 2];

            [[likely]]
            if (r >= minR && r <= maxR && g >= minG && g <= maxG && b >= minB && b <= maxB) {
                img.buf[index] = targetR;
                img.buf[index + 1] = targetG;
                img.buf[index + 2] = targetB;
            }

            index += channels;
        }
    }
}


void floodFill(Image& img, int x, int y, const std::vector<int>& targetColor, const std::vector<int>& fillColor, int maxFillCount) {
    int width = img.width;
    int height = img.height;
    int channels = img.bitDepth / BYTE; // Assuming 8-bit per channel

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    int fillCount = 0;

    while (!q.empty() && fillCount < maxFillCount) {
        auto [curX, curY] = q.front();
        q.pop();

        if (curX < 0 || curX >= width || curY < 0 || curY >= height || visited[curY][curX]) {
            continue;
        }

        int adjustedY = height - 1 - curY; // Adjust Y coordinate to start from bottom-left
        int index = (adjustedY * width + curX) * channels;
        int r = img.buf[index];
        int g = img.buf[index + 1];
        int b = img.buf[index + 2];

        if (r == targetColor[0] && g == targetColor[1] && b == targetColor[2]) {
            img.buf[index] = fillColor[0];
            img.buf[index + 1] = fillColor[1];
            img.buf[index + 2] = fillColor[2];
            ++fillCount;

            visited[curY][curX] = true;

            if (curX > 0) {
                q.push({curX - 1, curY}); // Left
            }
            if (curX < width - 1) {
                q.push({curX + 1, curY}); // Right
            }
            if (curY > 0) {
                q.push({curX, curY - 1}); // Up
            }
            if (curY < height - 1) {
                q.push({curX, curY + 1}); // Down
            }
        }
    }
}


void modifyRegion(Image &img,const std::vector<int> & region,const std::vector<int> &color){

        for (int y = region[1]; y < region[3]; ++y) {
            for (int x = region[0]; x < region[2]; ++x) {
                int adjustedY = img.height - 1 - y; // Adjust Y coordinate to start from bottom-left
                int index = (adjustedY * img.width + x) * img.bitDepth / BYTE;
                img.buf[index] = color[2];
                img.buf[index + 1] = color[1]; 
                img.buf[index + 2] = color[0]; 
            }
        }

}

template<int size>
void modifyPixels(Image &img) noexcept {
    std::vector<uint8_t> tempBuf(img.width * img.height * 3);
    int halfSize = size / 2;

    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            std::vector<int> rValues, gValues, bValues;

            for (int dy = -halfSize; dy <= halfSize; ++dy) {
                for (int dx = -halfSize; dx <= halfSize; ++dx) {
                    int nx = std::clamp(x + dx, 0, static_cast<int>(img.width) - 1);
                    int ny = std::clamp(y + dy, 0, static_cast<int>(img.height) - 1);
                    int color = ImageSystem::getRGB(img, nx, ny);
                    
                    rValues.push_back((color >> 16) & 0xFF);
                    gValues.push_back((color >> 8) & 0xFF);
                    bValues.push_back(color & 0xFF);
                }
            }

            // Sort the color values
            std::sort(rValues.begin(), rValues.end());
            std::sort(gValues.begin(), gValues.end());
            std::sort(bValues.begin(), bValues.end());

            // Get the median values
            int medianR = rValues[rValues.size() / 2];
            int medianG = gValues[gValues.size() / 2];
            int medianB = bValues[bValues.size() / 2];

            // Get the center pixel color
            int centerColor = ImageSystem::getRGB(img, x, y);
            int centerR = (centerColor >> 16) & 0xFF;
            int centerG = (centerColor >> 8) & 0xFF;
            int centerB = centerColor & 0xFF;

            // If the center pixel is different from the median, replace it
            if (centerR != medianR || centerG != medianG || centerB != medianB) {
                int newColor = (medianR << 16) | (medianG << 8) | medianB;
                int index = (y * img.width + x) * 3;
                tempBuf[index] = medianR;
                tempBuf[index + 1] = medianG;
                tempBuf[index + 2] = medianB;
            } else {
                // Keep the original color
                int index = (y * img.width + x) * 3;
                tempBuf[index] = centerR;
                tempBuf[index + 1] = centerG;
                tempBuf[index + 2] = centerB;
            }
        }
    }

    // Copy the modified pixels back to the original image
    std::copy(tempBuf.begin(), tempBuf.end(), img.buf);
}


int main(){

    std::string inputFileName = PATH_IMAGES "gamemaster_noise_2024.bmp";
    std::string outputFileName = PATH_IMAGES "restored_image.bmp";


    //Color
    const std::vector<int> whiteColor = {255, 255, 255};
    const std::vector<int> blackColor = {0, 0, 0};

    Image img;
    ImageSystem::initImage(img);
    if (!ImageSystem::readImage(img, inputFileName)) {
        std::cerr << "Failed to read image" << std::endl;
        return 1;
    }

    // Apply adaptive median filter
    for (int i = 0; i < (1 << 5); ++i) {
        adaptiveMedianFilter<3>(img);
    }


    // Apply adaptive median filter
    for (int i = 0; i < (1 << 5); ++i) {
        adaptiveMedianFilter<5>(img);
    }


    // Apply adaptive median filter
    for (int i = 0; i < (1 << 5); ++i) {
        adaptiveMedianFilter<7>(img);
    }

    // Apply adaptive median filter
    for (int i = 0; i < (1 << 5); ++i) {
        adaptiveMedianFilter<9>(img);
    }

    
    // Apply adaptive median filter
    for (int i = 0; i < (1 << 5); ++i) {
        adaptiveMedianFilter<11>(img);
    }




    // Apply Laplacian filter
    applyLaplacianFilter(img);


    // Define the region of the shirt and the color ranges (based on the histogram analysis)
    std::vector<int> hairRegion = {50, 0, 480, 183}; // Region for the shirt starting from bottom-left
    std::vector<int> grayColor = {128, 128, 128};
    std::vector<std::vector<int>> hairColorRange = {{0, 150}, {100, 255}, {0, 150}}; // Example color range for the shirt

    // Change shirt color
    changeColor(img, hairRegion, grayColor,hairColorRange);



    std::vector<int> skinRegion = {80,133, 512-69, 450}; // Region for the skin starting from bottom-left
    std::vector<int> lightBrownColor = {196, 164, 132};
    std::vector<std::vector<int>> skinColorRange = {{70, 160},{150,255}, {150, 220} }; // Example color range for the skin
    std::reverse(lightBrownColor.begin(), lightBrownColor.end());
    std::reverse(skinColorRange.begin(), skinColorRange.end());
    changeColor(img, skinRegion, lightBrownColor, skinColorRange);

    //mouse
    std::vector<int> mouseRegion = {233, 306, 278, 330}; // Region for the mouse starting from bottom-left
    std::vector<std::vector<int>> mouseColorRange = {{120, 180}, {200, 240}, {100,150}}; // Example color range for the shirt
    changeColor(img, mouseRegion, lightBrownColor, mouseColorRange);


    std::vector<int> mustacheRegion = {90, 277, 420, 408}; // Region for the mustache starting from bottom-left
    std::vector<int> redColor = {255, 0, 0};
    std::vector<std::vector<int>> mustacheColorRange = {{0, 150}, {150,255}, {0, 150}}; // Example color range for the shirt
    std::reverse(redColor.begin(), redColor.end());
    changeColor(img, mustacheRegion, redColor, mustacheColorRange);

    std::vector<int> shirtRegion = {46, 431,476, 512}; // Region for the shirt starting from bottom-left
    std::vector<int> blueColor = {0, 0, 255};
    std::vector<std::vector<int>> shirtColorRange =
     {{0, 100}, {150, 255}, {40, 150}}; // Example color range for the shirt
    std::reverse(shirtColorRange.begin(), shirtColorRange.end());
    std::reverse(blueColor.begin(), blueColor.end());
    changeColor(img, shirtRegion, blueColor, shirtColorRange);

    std::vector<int> bgRegion = {0, 0, 512, 512}; // Region for the background starting from bottom-left
    std::vector<int> bgColor = {113,113,113};
    std::vector<std::vector<int>> bgColorRange = {{150, 255}, {100, 255}, {100, 150}}; // Example color range for the background
    std::reverse(bgColorRange.begin(), bgColorRange.end());
    std::reverse(bgColor.begin(), bgColor.end());


    //glass
    std::vector<int> glassRegion = {95,190, 416,275}; // Region for the glass starting from bottom-left
    std::vector<int> glassColor = {0, 0, 0};
    std::vector<std::vector<int>> glassColorRange = {{0, 150}, {0,150}, {0,150}}; // Example color range for the shirt
    changeColor(img, glassRegion, glassColor, glassColorRange);

 


    // Change color to white in whiteSquaresRegion using multithreading
    auto modifyColorWhite = [&](const std::vector<int>& region) {
        for (int y = region[1]; y < region[3]; ++y) {
            for (int x = region[0]; x < region[2]; ++x) {
                int adjustedY = img.height - 1 - y; // Adjust Y coordinate to start from bottom-left
                int index = (adjustedY * img.width + x) * img.bitDepth / BYTE;
                img.buf[index] = 255; // Set red channel to 255 (white)
                img.buf[index + 1] = 255; // Set green channel to 255 (white)
                img.buf[index + 2] = 255; // Set blue channel to 255 (white)
            }
        }
    };

    std::vector<std::thread> threadsForModifyWhite;
    threadsForModifyWhite.emplace_back(modifyColorWhite, std::vector<int>{162, 240, 178, 258});
    threadsForModifyWhite.emplace_back(modifyColorWhite, std::vector<int>{179, 225, 193, 239});
    threadsForModifyWhite.emplace_back(modifyColorWhite, std::vector<int>{192, 210, 208, 224});
    threadsForModifyWhite.emplace_back(modifyColorWhite, std::vector<int>{322, 242, 339, 258});
    threadsForModifyWhite.emplace_back(modifyColorWhite, std::vector<int>{340, 226, 351, 240});
    threadsForModifyWhite.emplace_back(modifyColorWhite, std::vector<int>{352, 211, 367, 224});

    for (auto& thread : threadsForModifyWhite) {
        thread.join();
    }



    // Check and change color to white if not black in diagonal1 region
    auto modifyColorDiagonal = [&](const std::vector<int>& region) {
        for (int y = region[1]; y < region[3]; ++y) {
            for (int x = region[0]; x < region[2]; ++x) {
                int adjustedY = img.height - 1 - y; // Adjust Y coordinate to start from bottom-left
                int index = (adjustedY * img.width + x) * img.bitDepth / BYTE;
                int r = img.buf[index];
                int g = img.buf[index + 1];
                int b = img.buf[index + 2];
                if (r != 0 || g != 0 || b != 0) {
                    img.buf[index] = whiteColor[0];
                    img.buf[index + 1] = whiteColor[1];
                    img.buf[index + 2] = whiteColor[2];
                }
            }
        }
    };

    std::vector<std::thread> threadsForModifyDiagonal;
    threadsForModifyDiagonal.emplace_back(modifyColorDiagonal, std::vector<int>{153, 200, 212, 255});
    threadsForModifyDiagonal.emplace_back(modifyColorDiagonal, std::vector<int>{314,204, 366, 255});

    for (auto& thread : threadsForModifyDiagonal) {
        thread.join();
    }

    


    std::set<std::vector<int>> uniqueColors;
    uniqueColors.insert(grayColor);
    uniqueColors.insert(lightBrownColor);
    uniqueColors.insert(redColor);
    uniqueColors.insert(blueColor);
    uniqueColors.insert(blackColor);
    uniqueColors.insert(whiteColor);

    
    for(int i=0;i<512;++i){
        for(int j=0;j<512;++j){
            int index = (i * 512 + j) * 3;
            std::vector<int> color = {img.buf[index], img.buf[index+1], img.buf[index+2]};
            if(uniqueColors.find(color) == uniqueColors.end()){
                img.buf[index] = bgColor[0];
                img.buf[index+1] = bgColor[1];
                img.buf[index+2] = bgColor[2];
        }
        }
    }

    uniqueColors.insert(bgColor);


        // Change color to red in modifyRegions using multithreading
    auto modifyColorMustache = [&](const std::vector<int>& region) {
        for (int y = region[1]; y < region[3]; ++y) {
            for (int x = region[0]; x < region[2]; ++x) {
                int adjustedY = img.height - 1 - y; // Adjust Y coordinate to start from bottom-left
                int index = (adjustedY * img.width + x) * img.bitDepth / BYTE;
                img.buf[index] = 0; // Set red channel to 0 (black)
                img.buf[index + 1] = 0; // Set green channel to 0 (black)
                img.buf[index + 2] = 255; // Set blue channel to 255 (red)
            }
        }
    };

    std::vector<std::thread> threadsForModifyMustache ;
    threadsForModifyMustache.emplace_back(modifyColorMustache, std::vector<int>{193, 332, 339, 400});
    threadsForModifyMustache.emplace_back(modifyColorMustache, std::vector<int>{230, 284, 273, 300});
    threadsForModifyMustache.emplace_back(modifyColorMustache, std::vector<int>{332, 332, 380, 392});



    for (auto& thread : threadsForModifyMustache ) {
        thread.join();
    }



    // Change color to blue in modifyRegion1 using multithreading
    auto modifyColorBackground = [&](const std::vector<int>& region) {
        for (int y = region[1]; y < region[3]; ++y) {
            for (int x = region[0]; x < region[2]; ++x) {
                int adjustedY = img.height - 1 - y; // Adjust Y coordinate to start from bottom-left
                int index = (adjustedY * img.width + x) * img.bitDepth / BYTE;
                img.buf[index] = 255; // Set red channel to 0 (black)
                img.buf[index + 1] = 0; // Set green channel to 0 (black)
                img.buf[index + 2] = 0; // Set blue channel to 255 (blue)
            }
        }
    };

    std::vector<std::thread> threadsForModifyBackground;
    threadsForModifyBackground.emplace_back(modifyColorBackground, std::vector<int>{79, 451, 440, 512});

    for (auto& thread : threadsForModifyBackground) {
        thread.join();
    }



    // Check and change color to lightBrown if it is bgColor in modifyRegion2 and modifyRegion3
    auto modifyColorSkin = [&](const std::vector<int>& region) {
        for (int y = region[1]; y < region[3]; ++y) {
            for (int x = region[0]; x < region[2]; ++x) {
                int adjustedY = img.height - 1 - y; // Adjust Y coordinate to start from bottom-left
                int index = (adjustedY * img.width + x) * img.bitDepth / BYTE;
                int r = img.buf[index];
                int g = img.buf[index + 1];
                int b = img.buf[index + 2];
                if (r == bgColor[0] && g == bgColor[1] && b == bgColor[2]) {
                    img.buf[index] = lightBrownColor[0];
                    img.buf[index + 1] = lightBrownColor[1];
                    img.buf[index + 2] = lightBrownColor[2];
                }
            }
        }
    };


    std::vector<std::thread> threadsForModifySkin;
    threadsForModifySkin.emplace_back(modifyColorSkin, std::vector<int>{93, 124, 416, 332});
    threadsForModifySkin.emplace_back(modifyColorSkin, std::vector<int>{196, 406, 320, 432});
    threadsForModifySkin.emplace_back(modifyColorSkin, std::vector<int>{200, 416, 302, 437});
    threadsForModifySkin.emplace_back(modifyColorSkin, std::vector<int>{422, 211, 433, 243});




    for (auto& thread : threadsForModifySkin) {
        thread.join();
    }





   std::vector<std::thread> threadsForFloodFill;
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 124, 376, bgColor, redColor, 50);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 161, 387, bgColor, redColor, 50);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 256, 318, redColor, lightBrownColor, 50);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 407, 358, lightBrownColor, redColor, 10000);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 416, 300, lightBrownColor, redColor, 200);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 245, 443, bgColor, blueColor, 1000);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 280, 442, bgColor, blueColor, 10000);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 307, 435, bgColor, blueColor, 10000);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 320, 432, bgColor, blueColor,20);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 429, 221, bgColor, lightBrownColor,1000);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 427, 204, bgColor, lightBrownColor,50);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 263, 447, bgColor, lightBrownColor,100);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 198, 432, bgColor, lightBrownColor,100);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 96, 325, lightBrownColor, redColor,100);
    threadsForFloodFill.emplace_back(floodFill, std::ref(img), 417, 201, bgColor ,std::vector<int>{0,0,0},50);



    for(auto& thread: threadsForFloodFill){
        thread.join();
    }




    for(size_t i=0 ;i < (1<<6);++i){
        modifyPixels<3>(img);
    }






    
    for(int i=0;i<512;++i){
        for(int j=0;j<512;++j){
            int index = (i * 512 + j) * 3;
            std::vector<int> color = {img.buf[index], img.buf[index+1], img.buf[index+2]};
            if(uniqueColors.find(color) == uniqueColors.end()){
                img.buf[index] = redColor[0];
                img.buf[index+1] = redColor[1];
                img.buf[index+2] = redColor[2];
        }
        }
    }

    std::vector<std::vector<int>> redColorRange = {{255, 255}, {0, 0}, {0, 0}};
    std::vector<int> redRegion = {54,426,454,509};
    std::reverse(redColor.begin(), redColor.end());
    std::reverse(redColorRange.begin(), redColorRange.end());
    changeColor(img, redRegion, redColor, redColorRange);








    ImageSystem::write(img, outputFileName);
    ImageSystem::destroyImage(img);
    return 0;
}
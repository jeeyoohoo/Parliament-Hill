#include "Graphics.h"
#include <fstream>

int main() {
    std::ifstream input("input.ppm");
    if (!input) {
        std::cerr << "Failed to open input.ppm" << std::endl;
        return 1;
    }

    PPM image(input);
    input.close();

    //Graphics::ApplyGrayscale(image);
    //Graphics::ApplyBlur(image);
    //Graphics::ApplySharpen(image);
    //Graphics::ApplyInvert(image);
    //Graphics::AdjustBrightness(image, 75);

    //Graphics::Scale(image, 1.5f);  
    //Graphics::Rotate(image, 45.0f);  
    Graphics::Translate(image, 300, 0);

    image.SaveToImageFile("output.ppm");

    return 0;
}

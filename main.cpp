#include "Graphics.h"
#include <fstream>

int main() {

    std::ifstream input("input.ppm");
   
    PPM original(input);
    input.close();

    PPM grayscale(original);
    Graphics::ApplyGrayscale(grayscale);
    grayscale.SaveToImageFile("grayscale.ppm");


    PPM blur(original);
    Graphics::ApplyBlur(blur);
    blur.SaveToImageFile("blur.ppm");

    PPM sharpen(original);
    Graphics::ApplySharpen(sharpen);
    sharpen.SaveToImageFile("sharpen.ppm");

    PPM invert(original);
    Graphics::ApplyInvert(invert);
    invert.SaveToImageFile("invert.ppm");

    PPM bright(original);
    Graphics::AdjustBrightness(bright, 75);
    bright.SaveToImageFile("bright.ppm");

    PPM scale(original);
    Graphics::Scale(scale, 1.5f);  
    scale.SaveToImageFile("scale.ppm");

    PPM rotate(original);
    Graphics::Rotate(rotate, 45.0f);  
    rotate.SaveToImageFile("rotate.ppm");

    PPM translate(original);
    Graphics::Translate(translate, 300, 0);
    translate.SaveToImageFile("translate.ppm");

    return 0;
}

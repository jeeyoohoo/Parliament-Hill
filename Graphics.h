#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "PPM.h"
#include <cmath>

class Graphics {
public:
 
    static void ApplyGrayscale(PPM& image) {
        for (unsigned int i = 0; i < image.getSize(); ++i) {
            Pixel& p = const_cast<Pixel&>(image[i]);
            unsigned int gray = (p["red"] + p["green"] + p["blue"]) / 3;
            p = Pixel(gray, gray, gray);
        }
    }

    static void ApplyBlur(PPM& image) {
        unsigned int width = image.getWidth();
        unsigned int height = image.getHeight();
        std::vector<Pixel> blurred(image.getSize());

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                unsigned int r = 0, g = 0, b = 0, count = 0;

                for (int dy = -2; dy <= 2; ++dy) {
                    for (int dx = -2; dx <= 2; ++dx) {
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
                            const Pixel& p = image[ny * width + nx];
                            r += p["red"];
                            g += p["green"];
                            b += p["blue"];
                            ++count;
                        }
                    }
                }
                blurred[y * width + x] = Pixel(r / count, g / count, b / count);
            }
        }

        for (unsigned int i = 0; i < image.getSize(); ++i) {
            const_cast<Pixel&>(image[i]) = blurred[i];
        }
    }


    static void ApplySharpen(PPM& image) {
        unsigned int width = image.getWidth();
        unsigned int height = image.getHeight();
        std::vector<Pixel> sharpened(image.getSize());

        for (unsigned int y = 1; y < height - 1; ++y) {
            for (unsigned int x = 1; x < width - 1; ++x) {
                const Pixel& center = image[y * width + x];
                const Pixel& top = image[(y - 1) * width + x];
                const Pixel& bottom = image[(y + 1) * width + x];
                const Pixel& left = image[y * width + (x - 1)];
                const Pixel& right = image[y * width + (x + 1)];

                int r = 5 * center["red"] - top["red"] - bottom["red"] - left["red"] - right["red"];
                int g = 5 * center["green"] - top["green"] - bottom["green"] - left["green"] - right["green"];
                int b = 5 * center["blue"] - top["blue"] - bottom["blue"] - left["blue"] - right["blue"];

                r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
                g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
                b = (b < 0) ? 0 : ((b > 255) ? 255 : b);


                sharpened[y * width + x] = Pixel(r, g, b);
            }
        }

        for (unsigned int i = 0; i < image.getSize(); ++i) {
            const_cast<Pixel&>(image[i]) = sharpened[i];
        }
    }

    static void ApplyInvert(PPM& image) {
        for (unsigned int i = 0; i < image.getSize(); ++i) {
            const Pixel& p = image[i];
            Pixel inverted(255 - p["red"], 255 - p["green"], 255 - p["blue"]);
            const_cast<Pixel&>(image[i]) = inverted;
        }
    }

    static void Scale(PPM& image, float factor) {
        unsigned int newWidth = static_cast<unsigned int>(image.getWidth() * factor);
        unsigned int newHeight = static_cast<unsigned int>(image.getHeight() * factor);

        std::vector<Pixel> scaled(newWidth * newHeight);

        for (unsigned int y = 0; y < newHeight; ++y) {
            for (unsigned int x = 0; x < newWidth; ++x) {
                unsigned int srcX = std::min(static_cast<unsigned int>(x / factor), image.getWidth() - 1);
                unsigned int srcY = std::min(static_cast<unsigned int>(y / factor), image.getHeight() - 1);

                scaled[y * newWidth + x] = image[srcY * image.getWidth() + srcX];
            }
        }

        image.SetWidth(newWidth);
        image.SetHeight(newHeight);
        image.Resize(newWidth * newHeight);

        for (unsigned int i = 0; i < scaled.size(); ++i) {
            const_cast<Pixel&>(image[i]) = scaled[i];
        }
    }



    static void Rotate(PPM& image, float angleDegrees) {
        float angle = angleDegrees * M_PI / 180.0f;
        unsigned int width = image.getWidth();
        unsigned int height = image.getHeight();
        int cx = width / 2;
        int cy = height / 2;

        std::vector<Pixel> rotated(image.getSize());

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                int dx = x - cx;
                int dy = y - cy;

                int srcX = static_cast<int>(cos(angle) * dx - sin(angle) * dy + cx);
                int srcY = static_cast<int>(sin(angle) * dx + cos(angle) * dy + cy);

                if (srcX >= 0 && srcX < (int)width && srcY >= 0 && srcY < (int)height) {
                    rotated[y * width + x] = image[srcY * width + srcX];
                } else {
                    rotated[y * width + x] = Pixel(0, 0, 0);
                }
            }
        }

        for (unsigned int i = 0; i < image.getSize(); ++i) {
            const_cast<Pixel&>(image[i]) = rotated[i];
        }
    }

    static void AdjustBrightness(PPM& image, int offset) {
        for (unsigned int i = 0; i < image.getSize(); ++i) {
            const Pixel& p = image[i];
            int r = static_cast<int>(p["red"]) + offset;
            int g = static_cast<int>(p["green"]) + offset;
            int b = static_cast<int>(p["blue"]) + offset;

            r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
            g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
            b = (b < 0) ? 0 : ((b > 255) ? 255 : b);

            const_cast<Pixel&>(image[i]) = Pixel(r, g, b);
        }
    }

    static void Translate(PPM& image, int shiftX, int shiftY) {
        unsigned int width = image.getWidth();
        unsigned int height = image.getHeight();
        std::vector<Pixel> newPixels(image.getSize());

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                unsigned int newX = (x + shiftX + width) % width;
                unsigned int newY = (y + shiftY + height) % height;
                newPixels[newY * width + newX] = image[y * width + x];
            }
        }

        for (unsigned int i = 0; i < image.getSize(); ++i) {
            const_cast<Pixel&>(image[i]) = newPixels[i];
        }
    }

};

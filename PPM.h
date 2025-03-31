#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <String>
#include <sstream>
#include "Pixel.h"
 
class PPM
{
private:
       std::string comment;
       unsigned int height;
       std::string magic;
       unsigned int maxColor;
       std::vector<Pixel> pixels;
       unsigned int width;
public:
       ~PPM() {}
       std::string getComment();
       
       unsigned int getHeight();
 
       std::string getMagic();
 
       unsigned int getMaxColor();
 
       size_t getSize();
 
       unsigned int getWidth();
 
       const Pixel& operator[](unsigned int x) const; //offset
 
       const Pixel& operator[](unsigned int x); //also offset?
 
       const PPM& operator=(const PPM& a); //copy
 
       const PPM& operator=(PPM&&); //move
 
       PPM() : height(0), maxColor(255), width(0) {
       }
 
       PPM(const PPM&);
 
       PPM(std::ifstream&);
 
       PPM(PPM&&);
 
       void Resize(unsigned int);
 
       void SaveToImageFile(std::string);
 
       void SetComment(std::string);
 
       void SetHeight(unsigned int);
 
       void SetMagic(std::string);
 
       void SetMaxColor(unsigned int);
 
       void SetWidth(unsigned int);
};
 
std::string PPM::getComment()
{
       return comment;
}
 
unsigned int PPM::getHeight()
{
       return height;
}
 
std::string PPM::getMagic()
{
       return magic;
}
 
unsigned int PPM::getMaxColor()
{
       return maxColor;
}
 
size_t PPM::getSize()
{
       return pixels.size();
}
 
unsigned int PPM::getWidth()
{
       return width;
}
 
const Pixel& PPM::operator[](unsigned int x) const
{
       return pixels[x];
}
 
const Pixel& PPM::operator[](unsigned int x)
{
       return pixels[x];
}
 
const PPM& PPM::operator=(const PPM& a)
{
       this->comment = a.comment;
       this->height = a.height;
       this->magic = a.magic;
       this->maxColor = a.maxColor;
       this->pixels = a.pixels; //should be a deep copy

       this->width = a.width;
       return *this;
}
 
const PPM& PPM::operator=(PPM&& a) //still needs some work ( i forgot move semantics)
{
       this->comment = a.comment;
       a.comment = nullptr;
 
       this->height = a.height;
       a.height = 0;
 
       this->magic = a.magic;
       a.magic = nullptr;
 
       this->maxColor = a.maxColor;
       a.maxColor = 0;
 
       swap(this->pixels, a.pixels);
 
       this->width = a.width;
       a.width = 0;
       return *this;
}
 
PPM::PPM(const PPM& a)
{
       this->comment = a.comment;
       this->height = a.height;
       this->magic = a.magic;
       this->maxColor = a.maxColor;
       this->pixels = a.pixels;
       this->width = a.width;
      
}

PPM::PPM(std::ifstream& a) {
    string dimensions;
    getline(a, magic);
    getline(a, comment);
    getline(a, dimensions);
    std::stringstream dimension(dimensions);
    dimension >> width >> height;
    a >> maxColor;
    unsigned int r, g, b;
    while (a >> r >> g >> b) {
        pixels.emplace_back(r, g, b);
    }
}
 
PPM::PPM(PPM&& a)
{
       this->comment = a.comment;
       a.comment = nullptr;
 
       this->height = a.height;
       a.height = 0;
 
       this->magic = a.magic;
       a.magic = nullptr;
 
       this->maxColor = a.maxColor;
       a.maxColor = 0;
 
       this->pixels = a.pixels; //copy only the 0th element, then set a.pixels to nullptr
 
 
       this->width = a.width;
       a.width = 0;
}
 
void PPM::Resize(unsigned int newSize) {
    pixels.resize(newSize);
}

 
void PPM::SaveToImageFile(std::string s)
{
    std::ofstream out(s);
    out << magic << "\n";
    out << "# " << comment << "\n";
    out << width << " " << height << "\n";
    out << maxColor << "\n";

    for (const Pixel& p : pixels) {
        out << p["red"] << " " << p["green"] << " " << p["blue"] << "\n";
    }
}
 
void PPM::SetComment(std::string s)
{
       this->comment = s;
}
 
void PPM::SetHeight(unsigned int x)
{
       this->height = x;
}
 
void PPM::SetMagic(std::string s)
{
       this->magic = s;
}
 
void PPM::SetMaxColor(unsigned int x)
{
       this->maxColor = x;
}
 
void PPM::SetWidth(unsigned int x)
{
       this->width = x;
}

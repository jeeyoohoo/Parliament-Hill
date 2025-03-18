#include "PPM.h"
#include <iostream>
#include <string>
 
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
 
unsigned int PPM::getSize()
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
 
PPM::PPM(std::ifstream& a)
{
       a >> this->magic;
       a >> this->comment;
       a >> this->width >> this->height;
       a >> this->maxColor;
      
       unsigned char red, green, blue;
 
 
       for(int i = 0; i <= (width*height); i++)
       {
             //get RGB values out of PPM, and put them into pixels vector
             a >> red >> green >> blue;
             this->pixels.push_back(Pixel(red, green, blue));
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
 
void PPM::Resize(unsigned int x)
{
       this->width = this->width / x;
       this->height = this->height / x;
}
 
void PPM::SaveToImageFile(std::string s)
{
       //??? save for later
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
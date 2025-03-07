#pragma once
#include <Pixel.h>
#include <iostream>
#include <vector>
#include <fstream>
 
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
       std::string getComment(std::ifstream& f);
       
       unsigned int getHeight(std::ifstream& f);
 
       std::string getMagic(std::ifstream& f);
 
       unsigned int getMaxColor(std::ifstream& f);
 
       unsigned int getSize(std::ifstream& f);
 
       unsigned int getWidth(std::ifstream& f);
 
       const Pixel& operator[](unsigned int x) const; //offset
 
       const Pixel& operator[](unsigned int x); //also offset?
 
       const PPM& operator=(const PPM& a); //copy
 
       const PPM& operator=(PPM&&); //move
 
       PPM() {}
 
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

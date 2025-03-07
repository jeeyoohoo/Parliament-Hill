#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "PPM.h"
//remove pixel.h?????
#include "Pixel.h" 
using namespace std;

class Graphics
{
    public:
    const static PPM& Graphics::ApplyFilter(PPM& imageObj,const char* newFile)
    {
        //design our own filter
    }
    const static PPM& Graphics:: MakeGrayScale(PPM&imageObj)
    {
        //change RGB value of pixel to be the same for all three components
        //newValue=(r+g+b)/3
        int numberOfPixels = imageObj.height * imageObj.width;
        int numberOfOps = numberOfPixels*3;
        vector<unsigned int> greyVector;
        for(int i=0;i<numberOfOps; i+3)
        {
            unsigned int r=imageObj.pixels[i];
            unsigned int g=imageObj.pixels[i+1];
            unsigned int b= imageObj.pixels[i+2];
            unsigned int value = (r+g+b)/3;
            greyVector.emplace_back(value,value,value);
        }
    }
    const static PPM& Graphics:: RotateImage(PPM& imageObj,double degree)
    {   
        //rotate around middle point

    }
    const static PPM& Graphics:: ScaleImage(PPM& imageObj, double scaleFactor)
    {
        //uniform scaling
    }
    const static PPM& Graphics:: TranslateImage(PPM&imageObj,int x,int y)
    {
        //translation
    }
};

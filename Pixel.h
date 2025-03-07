#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pixel 
{
private:
    unsigned int red;
    unsigned int green;
    unsigned int blue;
public:
    ~Pixel()
    {
        //destructor
    }
    const unsigned int& operator[](const char*color)
    {
        //offset operator overloading
        //---keeps calling object immutable
        //---returns color number value of specified color input of current Pixel object
        if(strcmp(color,"red")==0)
        {
            return this->red;
        }
        if(strcmp(color,"green")==0)
        {
            return this->green;
        }
        if(strcmp(color,"blue")==0)
        {
            return this->blue;
        }
        else
        {
            throw("Error: only inputs which are allowed are red,green,blue.");
        }
    }
    const unsigned int& operator[](const char* color) const
    {
        //offset operator overloading
        //---returned is immutable
        //---returns color number value of specified color input to put into new Pixel object
        if(strcmp(color,"red")==0)
        {
            return this->red;
        }
        if(strcmp(color,"green")==0)
        {
            return this->green;
        }
        if(strcmp(color,"blue")==0)
        {
            return this->blue;
        }
        else
        {
            throw("Error: only inputs which are allowed are red,green,blue.");
        }
    }
    Pixel()
    {
        //default constructor
    }
    Pixel(const Pixel & obj)
    {
        //copy constructor
        red = obj.red;
        green = obj.green;
        green = obj.green;
    }
    Pixel(unsigned int red ,unsigned int green, unsigned int blue)
    {
        //parameterized constructor
        this->red= red;
        this->green = green;
        this->blue = blue;
        
    }

    //nested class
    class InputOutOfBoundsException 
    {
    private:
        const char* errorMessage;
        const char* offendingIndex;
    public:
        Pixel::InputOutOfBoundsException::InputOutOfBoundsException(const char* message,const char*index)
        {
            errorMessage=message; 
            offendingIndex = index;
        }
        const char* Pixel::InputOutOfBoundsException::returnError()
        {
            return errorMessage;
        }
        const char* Pixel::InputOutOfBoundsException::returnOffendingIndex()
        {
            return offendingIndex;
        }
    };
};
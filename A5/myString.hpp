#ifndef __MY_STRING__
#define __MY_STRING__
#include<string>
#include"src/rsdl.hpp"

using namespace std;

#define MAX_STRING_LENGTH 10
#define FONT "assets/Digitalt.ttf"

class MyString
{
  public:
    MyString(int _fontSize);
    void eraseLastChar();
    void addChar(char c);
    void drawString(Window* win , int X , int Y);
    string getString();
    void eraseAll();
  private:
    string inputString;
    int fontSize;
};
#endif
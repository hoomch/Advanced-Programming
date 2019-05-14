#include "myString.hpp"

MyString::MyString(int _fontSize): fontSize(_fontSize){}

void MyString::eraseLastChar()
{
  if(inputString.size() > 0)
      inputString.erase(inputString.size() - 1);
}

void MyString::addChar(char c)
{
  if(inputString.size() < MAX_STRING_LENGTH)
    inputString += c;
}

void MyString::drawString(Window* win , int x , int y)
{
  win->show_text(inputString, x, y, BLACK, FONT, fontSize);
}

string MyString::getString()
{
  return inputString;
}
void MyString::eraseAll(){
	inputString.clear();
}
/*!**********************************************************************
@file    main.cpp
@author  rwmc
@date    4/6/2016

@brief 
Testing main for the console-input.h file. A reasonable reference for 
using this application on a few different systems.

@copyright See LICENSE.md
************************************************************************/
#include <iostream>        // std::cout
#include "console-input.h" // KeyHit() and GetKey() and others



// Base functionality
void Test_BaseFunctionality()
{
  // Print things that are sent to console.
  while (true)
  {
    int num = KeyHit();
    if (num > 0)
    {
      // Count down to handle wide characters, or multi-character input.
      while (num--)
      {
        int lastCode = GetChar();
        std::cout << "Read Code: " << lastCode << ", Char: " << static_cast<char>(lastCode);

        if (lastCode == KEY_ESCAPE)
          return;
      }

      std::cout << '\n';
    }
  }
}

// 
void OnChar(char c)
{
  std::cout << "Character hit: " << c << '\n';
}

void OnPath(const char* path, int len)
{
  std::cout << "C test path was just recieved! " << std::string(path, len) << '\n';
}

// Application entry point
int main(int argc, char** argv)
{
  //Test_BaseFunctionality();
  while(1)
    HandleInput(OnChar, OnPath);
  return 0;
}

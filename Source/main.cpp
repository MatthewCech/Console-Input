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
#include "console-input.h" // KeyHit() and GetKey()



// Application entry point
int main(int argc, char** argv)
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
          return 0;
      }

      std::cout << '\n';
    }
  }

  return 0;
}

/*!***************************************************************************
@file    main.cpp
@author  rwmc
@date    4/6/2016

@brief 
Testing main for the console-input.h file. A reasonable reference for using
this application on a few different systems.

@copyright "Don't be a Jerk" (See LICENSE.md)
*****************************************************************************/
#include <iostream>        // std::cout
#include "console-input.h" // KeyHit() and GetKey()



// Application entry point
int main(int argc, char** argv)
{
  // Print things that are sent to console.
  while (true)
  {
    if (int num = KeyHit())
    {
      while (num--)
        std::cout << "Read Chars: " << static_cast<int>(GetChar());

      std::cout << '\n';
    }
  }

  return 0;
}

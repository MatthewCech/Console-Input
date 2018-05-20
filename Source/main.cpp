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



  /////////////////////////////////
 // Setup Functions and Objects //
/////////////////////////////////
// Test functions to bind to.
void OnChar(char c) { std::cout << "Character hit: " << c << '\n'; }
void OnPathC(const char* path, int len) { std::cout << "C test path was just recieved! " << std::string(path, len) << '\n'; }
void OnPathCPP(std::string s) { std::cout << "Cpp test path was just recieved! " << s << '\n'; }

// A class to test member function callbacks
class TestClass
{
  InputParser p_;
  void MemFunOnChar(char c) { std::cout << "Character hit from inside a class!: " << c << '\n'; }
  void MemFunOnPath(std::string s) { std::cout << "Got a path inside a class! It was: " << s << '\n'; }

public:
  void Test_CassFunctionality() 
  { 
    p_.HandleInput(this, &TestClass::MemFunOnChar, &TestClass::MemFunOnPath); 
  }
};



  ////////////////////
 // Test Functions //
////////////////////
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

// Tests global function binding for key callbacks
void Test_GlobalFunctionality()
{
  InputParser ip;

  while (true)
    ip.HandleInput(OnChar, OnPathCPP);
}

// Tests to see if member functions in classes can act as callbacks
void Test_ClassMemberFunctionality()
{
  TestClass tc;

  while (true)
    tc.Test_CassFunctionality();
}



  /////////////////////////////
 // Application entry point //
/////////////////////////////
int main(int argc, char** argv)
{
  // Confirm we can run tests
  if (argc != 2)
    return 0;

  // Run tests
  if (argv[1][0] == '1')
    Test_BaseFunctionality();
  else if (argv[1][0] == '2')
    Test_GlobalFunctionality();
  else if (argv[1][0] == '3')
    Test_ClassMemberFunctionality();

  // Exit program
  return 0;
}

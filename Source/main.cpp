/*!***************************************************************************
@file    main.cpp
@author  Reverie Wisp
@date    11/20/2016

@brief 
The application entry point and boilerplate main. 

@copyright "Don't be a Jerk" (See LICENSE.md)
*****************************************************************************/
#include <iostream>               // std::cout
#include <RUtils/Timekeeper.hpp>  // Rutils::RException



// Application entry point
int main(int argc, char** argv)
{
	// Creates objects
	RUtils::Timekeeper t;
	t.StartFrame();   
	
  // Start the timing frame and run program
	for (int i{ 0 }; i < 10; ++i)
		std::cout << "I'm printed line " << i + 1 << "!" << '\n';

	// End the timing frame and print
	t.EndFrame(); 
	std::cout << "Printing All that took: " << t.GetLastTimeMS() << "ms\n";

  // Return normally.
  return 0;
}

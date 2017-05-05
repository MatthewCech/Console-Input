/*!**********************************************************************
@file    console-input.h
@author  rwmc
@date    4/6/2016

@brief 
A wrapper allowing _getch and _kbhit windows-style functionality on 
both windows and linux! Relevant functions are KeyHit() and GetKey().

@copyright (See LICENSE.md)
************************************************************************/
#if defined(_WIN32) || defined(WIN32) || defined(WINDOWS) || defined(_WIN32_)
  #define OS_WINDOWS
#else
  #define OS_NON_WINDOWS
#endif



  /////////////////////
 // Keycode Defines //
/////////////////////
// You can compare output to characters mostly, however some
// keys are a bit harder to type - I've throw a few keycodes
// here, although note that accuracy may vary between systems.
#define KEY_BACKSPACE 8
#define KEY_TAB       9
#define KEY_ENTER     13
#define KEY_RETURN    13
#define KEY_ESCAPE    27
#define KEY_SPACE     32

// ASCII readable but inconvenient sometimes.
#define KEY_NUM_0 48
#define KEY_NUM_1 49
#define KEY_NUM_2 50
#define KEY_NUM_3 51
#define KEY_NUM_4 52
#define KEY_NUM_5 53
#define KEY_NUM_6 54
#define KEY_NUM_7 55
#define KEY_NUM_8 56
#define KEY_NUM_9 57



  /////////////////////////
 // Function Prototypes //
/////////////////////////
// Checks to see if a key was hit in the terminal.
// Returns truthy if a change was detected in the input
// queue (if a key was hit), falsy if not.
inline int KeyHit(void);  

// Gets the last character changed in the terminal.
// Returns the value of the last character changed.
inline int GetChar(void); 



  ////////////////////////////
 // Windows Implementation //
////////////////////////////
#ifdef OS_WINDOWS
#define _NO_OLDNAMES   // for MinGW
#include <conio.h>     // getch and kbhit

// standard kbhit, returns if character change is queued.
inline int KeyHit(void)  { return _kbhit();  }

// Uses wch to handle additional cases.
inline int GetChar(void) { return _getwch();  }

#endif // OS_WINDOWS



  ////////////////////////////////
 // Non-Windows Implementation //
////////////////////////////////
#ifdef OS_NON_WINDOWS

// System includes, mostly kbhit emulation
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/time.h>

// GetCH emulation + time
#include <stdio.h>
#include <termios.h>
#include <unistd.h>



// termios reference: http://man7.org/linux/man-pages/man3/termios.3.html
// More readable termios reference: https://www.mkssoftware.com/docs/man5/struct_termios.5.asp
// select reference: http://man7.org/linux/man-pages/man2/select.2.html
inline int KeyHit(void)
{
  // Recall: Define variables at the top for C
  static struct termios oldTermios; // Save off for previous terminal settings
  static struct termios newTermios; // Configured new terminal settings
  struct timeval tv;                // Timeval struct for small delays.
  int charCount = 0;                // Character count

  // Set up console.
  tcgetattr(STDIN_FILENO, &oldTermios);           // Get old settings
  newTermios = oldTermios;                        // Transfer previous settings
  newTermios.c_oflag = 0;                         // Output mode
  newTermios.c_lflag &= ~(ICANON | ECHO);         // Jupt straight to the queue and don't echo.
  newTermios.c_iflag = 0;                         // Input mode
  newTermios.c_cc[VMIN] = 1;                      // Minimum time to wait
  newTermios.c_cc[VTIME] = 1;                     // Minimum characters to wait for
  tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);  // Set newTermios
  
  // Not checking return values, because if you're having issues with 
  // accessing the stack or reading information from the stream, you
  // likely have bigger issues than this function not working.
  ioctl(0, FIONREAD, &charCount);            
  
  // Check file stream with a small delay, then return to previous state.
  tv.tv_sec = 0;     // time to delay, in Seconds.
  tv.tv_usec = 100;  // time to delay, in Microseconds
  select(STDIN_FILENO + 1, NULL, NULL, NULL, &tv); 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
  return charCount; 
}

// makes use of the getchar function. Effectively getc(stdin), 
// with quick tweaks to the terminal to prevent oops.
// getchar documentation: https://linux.die.net/man/3/getchar
// If called without a character waiting for reading, 
// you should recieve EOF.
inline int GetChar(void)
{
  // Recall: Define variables at the top for C
  struct termios oldTermios; // Save off for previous terminal settings
  struct termios newTermios; // Configured new terminal settings
  int charVal;               // The key value (as int) from stream.

  // Configure newTermios
  tcgetattr(STDIN_FILENO, &oldTermios);
  newTermios = oldTermios;
  newTermios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

  // Reset terminal and return
  charVal = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
  return charVal;
}

#endif // OS_NON_WINDOWS


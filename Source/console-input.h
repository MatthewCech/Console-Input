/*!**********************************************************************
@file    console-input.h
@author  rwmc
@date    5/4/2016

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
// Accuracy not guarenteed. Use ASCII characters when possible instead.
// Keycodes based on ASCII Values, and ASCII Scan codes.

// Main board keys
#define KEY_BACKSPACE 8
#define KEY_TAB       9
#define KEY_ENTER     13
#define KEY_RETURN    13
#define KEY_ESCAPE    27
#define KEY_SPACE     32

// Arrow Keys
#define KEY_LEFT      75 // WARNING: Also capital K
#define KEY_UP        72 // WARNING: Also capital H
#define KEY_DOWN      80 // WARNING: Also capital P
#define KEY_RIGHT     77 // WARNING: Also capital M

// Utility Keys:
#define KEY_INSERT    82 // WARNING: Also capital R
#define KEY_DELETE    83 // WARNING: Also capital S
#define KEY_HOME      71 // WARNING: Also capital G
#define KEY_END       79 // WARNING: Also captial O
#define KEY_PAGEUP    73 // WARNING: Also capital I
#define KEY_PAGEDOWN  81 // WARNING: Also captial Q

// Could not identify
//#define KEY_PRINT_SCREEN 43, when CTRL is pressed it should be 114
//#define KEY_SCROLL_LOCK  ??
//#define KEY_PAUSE        ??
//#define KEY_BREAK <would be same as pause>

// Number Input (both numpad and primary keyboard)
#define KEY_0         48
#define KEY_1         49
#define KEY_2         50
#define KEY_3         51
#define KEY_4         52
#define KEY_5         53
#define KEY_6         54
#define KEY_7         55
#define KEY_8         56
#define KEY_9         57
#define KEY_NUM_0     48
#define KEY_NUM_1     49
#define KEY_NUM_2     50
#define KEY_NUM_3     51
#define KEY_NUM_4     52
#define KEY_NUM_5     53
#define KEY_NUM_6     54
#define KEY_NUM_7     55
#define KEY_NUM_8     56
#define KEY_NUM_9     57



  /////////////////////////
 // Function Prototypes //
/////////////////////////
inline int KeyHit(void);  // Returns truthy if a key was hit.
inline int GetChar(void); // Retrieves the last key value pressed.



  ////////////////////////////
 // Windows Implementation //
////////////////////////////
#ifdef OS_WINDOWS
#define _NO_OLDNAMES   // for MinGW
#include <conio.h>     // getch and kbhit

inline int KeyHit(void)  { return _kbhit();  }
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


inline int KeyHit(void)
{
  // Recall: Define variables at the top for C
  static struct termios oldTermios; // Save off for previous terminal settings
  static struct termios newTermios; // Configured new terminal settings
  struct timeval tv;                // Timeval struct for small delays.
  int charCount = 0;                // Character count

  tcgetattr(STDIN_FILENO, &oldTermios);           // Get old settings
  newTermios = oldTermios;                        // Transfer previous settings
  newTermios.c_oflag = 0;                         // Output mode
  newTermios.c_lflag &= ~(ICANON | ECHO);         // Set new print flags
  newTermios.c_iflag = 0;                         // Input mode
  newTermios.c_cc[VMIN] = 1;                      // Minimum time to wait
  newTermios.c_cc[VTIME] = 1;                     // Minimum characters to wait for
  tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);  // Set newTermios
  ioctl(0, FIONREAD, &charCount);                 // Read number of characters
  tv.tv_sec = 0;    // time to delay, in Seconds.
  tv.tv_usec = 100; // time to delay, in Microseconds

  // Check file stream with a small delay, then return to previous state.
  select(STDIN_FILENO + 1, NULL, NULL, NULL, &tv); 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
  return charCount; 
}

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

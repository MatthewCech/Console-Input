# Console-Input
Allows for cross-platform reading of keypresses with a simple header file. Contains a very small test application to print out the key code of a given key and the character for it. Nothing has to be built - the file you are looking for is `console-input.h` in the Source folder. Designed to handle single item and string parsing for things like drag-in, and provides a small utility class for use with member function or global function callback on input.

#### What to use
- There is a single file, `console-input.h`, that can be found in the source folder. All you need to do is include this in a project!

#### Building the example
- Build on *nix with `Build.sh` or by running `Build/premake5 gmake`
- Build Test on windows for VS2017 using `Build.bat` or by running `Build/premake5 vs2017`
- If you think all of that is a bit much, you can just use the command line `g++ main.cpp -o example`.

#### Usage
- C++ only, no C support. 
- Just copy `console-input.h` into your project directory, and include it with `#include "console-input.h"`
- Check if a key was hit with `KeyHit()`, Get the key in question with `GetChar()`

#### Sample Code
```c++
#include <stdio.h>
#include "console-input.h"

int main(void)
{
  while(true)
  {
    if(KeyHit())
      printf("Key %c was pressed!", GetChar());
  }
  
  return 0;
}
```

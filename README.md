# Console-Input
Allows for cross-platform reading of keypresses with a simple header file. Contains a very small test application to print out the key code of a given key and the character for it. Nothing has to be built - the file you are looking for is `console-input.h` in the Source folder!

#### Building the test
- Build on *nix with `Build.sh` or by running `Build/premake5 gmake`
- Build Test on windows for VS2015 using `Build.bat` or by running `Build/premake5 vs2015`

#### Usage
- Works in C and C++
- Check if a key was hit with `KeyHit()`, Get the key in question with `GetChar()`

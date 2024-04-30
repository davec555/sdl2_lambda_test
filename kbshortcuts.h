#ifndef KBShortCuts_H
#define KBShortCuts_H
#include <string>
#include <map>

using namespace::std;

typedef struct func{
	void (*funcPtr)(struct keyboard_func kb);
	string desc;
} func;

struct keySymMod{
   SDL_KeyCode sym;
   SDL_Keymod mod;
};

struct keyboard_func
{
   string funcID; //unique id for keyboard callable function
   string desc; // Simple description of function
   string key; // key bound to function

   SDL_KeyCode sym; // sdl2 symbol
   string alias; // user supplied pre-aliased key
   vector<SDL_Keymod> modifierVector;
   SDL_Keymod modifier;
   vector<SDL_Keymod> ignoreModifierVector;
   SDL_Keymod ignoreModifier;
   void (*func_ptr)(struct keyboard_func kb) {};
};

class KBShortCuts {
   private:
      map<string, keySymMod> keyAliasMap;
      map<string, SDL_Keymod> keyModAliasMap;
      map<int, string> keyModSDLNames;
      map<int, string> keyModNames;
      vector<keyboard_func> keys;
      void init(void);
      
   public:
      KBShortCuts(void); //Default constructor
      ~KBShortCuts(void); //Default destructor
      void readConfig(string configFile, string noGroupSearchKey = "");
      void displayKeysConfigVals(void);
      void writeConfig(string description, string configFile);
      void checkKeys(SDL_Keysym keySym);
      map<string, func> functionMap;
};
#endif
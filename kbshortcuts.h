#ifndef KBShortCuts_H
#define KBShortCuts_H
#include <string>
#include <map>

using namespace::std;

typedef struct func{
	void (*funcPtr)(struct keyboard_func kb, vector <keyboard_func>* keys);
	string desc;
} func;

struct keySymMod{
   SDL_KeyCode sym;
   SDL_Keymod mod;
};

typedef struct GLUT_Keysym
{
    int scancode;      /**< SDL physical key code - see SDL_Scancode for details */
    string sym;            /**< SDL virtual key code - see SDL_Keycode for details */
    uint16_t mod;                 /**< current key modifiers */
    short special;
    uint32_t unused;
} GLUT_Keysym;

struct keyboard_func
{
   string funcID; //unique id for keyboard callable function
   string desc; // Simple description of function
   string key; // key bound to function

#ifndef GLUT
   SDL_KeyCode sym; // sdl2 symbol
   vector<SDL_Keymod> modifierVector;
   SDL_Keymod modifier;
   vector<SDL_Keymod> ignoreModifierVector;
   SDL_Keymod ignoreModifier;
#else
   int sym;
   vector<int> modifierVector;
   int modifier;
   vector<int> ignoreModifierVector;
   int ignoreModifier;
#endif

   string alias; // user supplied pre-aliased key
   vector<string> modifierVectorText;
   void (*func_ptr)(struct keyboard_func kb, vector<keyboard_func>* keys) {};
};

class KBShortCuts {
   private:
      map<string, keySymMod> keyAliasMap;
      map<string, SDL_Keymod> keyModAliasMap;
      map<int, string> keyModNames;
      map<int, string> keyModTextNames;
      map<int, string> specialAliasMap; // only needed for GLUT
      vector<keyboard_func> keys;
      void init(void);
      string toLowerStrCopy(string s);
      
   public:
      KBShortCuts(void); //Default constructor
      ~KBShortCuts(void); //Default destructor
      void readConfig(string configFile, string noGroupSearchKey = "");
      void displayKeysConfigVals(void);
      void writeConfig(string description, string configFile);
#ifndef GLUT
      void checkKeys(SDL_Keysym keySym);
#else
      void checkKeys(GLUT_Keysym keySym);
#endif
      map<string, func> functionMap;
};
#endif
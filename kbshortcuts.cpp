#include <SDL2/SDL.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

#include "kbshortcuts.h"
#include "config.h"

using bin = std::bitset<16>;

KBShortCuts::KBShortCuts(void){
	init();
}

KBShortCuts::~KBShortCuts(void){
}

void KBShortCuts::init(void){
	keyModSDLNames ={
		{KMOD_NONE,"KMOD_NONE"},
		{KMOD_LSHIFT,"KMOD_LSHIFT"},
		{KMOD_RSHIFT,"KMOD_RSHIFT"},
		{KMOD_LCTRL,"KMOD_LCTRL"},
		{KMOD_RCTRL,"KMOD_RCTRL"},
		{KMOD_LALT,"KMOD_LALT"},
		{KMOD_RALT,"KMOD_RALT"},
		{KMOD_LGUI,"KMOD_LGUI"},
		{KMOD_RGUI,"KMOD_RGUI"},
		{KMOD_NUM,"KMOD_NUM"},
		{KMOD_CAPS,"KMOD_CAPS"},
		{KMOD_MODE,"KMOD_MODE"},
		{KMOD_SCROLL,"KMOD_SCROLL"},
		{KMOD_CTRL,"KMOD_LCTRL|KMOD_RCTRL"},
		{KMOD_SHIFT,"KMOD_LSHIFT|KMOD_RSHIFT"},
		{KMOD_ALT,"KMOD_LALT|KMOD_RALT"},
		{KMOD_GUI,"KMOD_LGUI|KMOD_RGUI"}
	};

	keyModTextNames ={
		{KMOD_NONE,"None"},
		{KMOD_LSHIFT,"LShift"},
		{KMOD_RSHIFT,"RShift"},
		{KMOD_LCTRL,"LCtrl"},
		{KMOD_RCTRL,"RCtrl"},
		{KMOD_LALT,"LAlt"},
		{KMOD_RALT,"RAlt"},
		{KMOD_LGUI,"LGui"},
		{KMOD_RGUI,"RGui"},
		{KMOD_NUM,"NumLock"},
		{KMOD_CAPS,"CapsLock"},
		{KMOD_MODE,"Mode"},
		{KMOD_SCROLL,"ScrollLock"},
		{KMOD_CTRL,"Ctrl"},
		{KMOD_SHIFT,"Shift"},
		{KMOD_ALT,"Alt"},
		{KMOD_GUI,"Gui"}
	};

	keyAliasMap ={
		{"Enter",{SDLK_RETURN,KMOD_NONE}},
		{"<",{SDLK_COMMA,KMOD_SHIFT}},
		{">",{SDLK_PERIOD,KMOD_SHIFT}},
		{"{",{SDLK_LEFTBRACKET,KMOD_SHIFT}},
		{"}",{SDLK_RIGHTBRACKET,KMOD_SHIFT}},
		{"|",{SDLK_BACKSLASH,KMOD_SHIFT}},
		{"_",{SDLK_MINUS,KMOD_SHIFT}},
		{"+",{SDLK_EQUALS,KMOD_SHIFT}},
		{"!",{SDLK_1,KMOD_SHIFT}},
		{"@",{SDLK_2,KMOD_SHIFT}},
		{"#",{SDLK_3,KMOD_SHIFT}},
		{"$",{SDLK_4,KMOD_SHIFT}},
		{"%",{SDLK_5,KMOD_SHIFT}},
		{"^",{SDLK_6,KMOD_SHIFT}},
		{"&",{SDLK_7,KMOD_SHIFT}},
		{"*",{SDLK_8,KMOD_SHIFT}},
		{"(",{SDLK_9,KMOD_SHIFT}},
		{")",{SDLK_0,KMOD_SHIFT}},
		{":",{SDLK_SEMICOLON,KMOD_SHIFT}},
		{"~",{SDLK_BACKQUOTE,KMOD_SHIFT}},	
		{"a",{SDLK_a,KMOD_NONE}},
		{"b",{SDLK_b,KMOD_NONE}},
		{"c",{SDLK_c,KMOD_NONE}},
		{"d",{SDLK_d,KMOD_NONE}},
		{"e",{SDLK_e,KMOD_NONE}},
		{"f",{SDLK_f,KMOD_NONE}},
		{"g",{SDLK_g,KMOD_NONE}},
		{"h",{SDLK_h,KMOD_NONE}},
		{"i",{SDLK_i,KMOD_NONE}},
		{"j",{SDLK_j,KMOD_NONE}},
		{"k",{SDLK_k,KMOD_NONE}},
		{"l",{SDLK_l,KMOD_NONE}},
		{"m",{SDLK_m,KMOD_NONE}},
		{"n",{SDLK_n,KMOD_NONE}},
		{"o",{SDLK_o,KMOD_NONE}},
		{"p",{SDLK_p,KMOD_NONE}},
		{"q",{SDLK_q,KMOD_NONE}},
		{"r",{SDLK_r,KMOD_NONE}},
		{"s",{SDLK_s,KMOD_NONE}},
		{"t",{SDLK_t,KMOD_NONE}},
		{"u",{SDLK_u,KMOD_NONE}},
		{"v",{SDLK_v,KMOD_NONE}},
		{"w",{SDLK_w,KMOD_NONE}},
		{"x",{SDLK_x,KMOD_NONE}},
		{"y",{SDLK_y,KMOD_NONE}},
		{"z",{SDLK_z,KMOD_NONE}},
	};

	keyModAliasMap = {
		{"NumLock",KMOD_NUM},
		{"ScrollLock",KMOD_SCROLL},
		{"Shift",KMOD_SHIFT},
		{"LeftShift",KMOD_LSHIFT},
		{"LShift",KMOD_LSHIFT},
		{"RightShift",KMOD_RSHIFT},
		{"RShift",KMOD_RSHIFT},
		{"CapsLock",KMOD_CAPS},
		{"None",KMOD_NONE},
		{"Alt",KMOD_ALT},
		{"LeftAlt",KMOD_LALT},
		{"LAlt",KMOD_LALT},
		{"RightAlt",KMOD_RALT},
		{"RAlt",KMOD_RALT},
		{"Ctrl",KMOD_CTRL},
		{"LeftCtrl",KMOD_LCTRL},
		{"LCtrl",KMOD_LCTRL},
		{"RightCtrl",KMOD_RCTRL},
		{"RCtrl",KMOD_RCTRL},
		{"GUI",KMOD_GUI},
		{"LeftGUI",KMOD_LGUI},
		{"LGUI",KMOD_LGUI},
		{"RightGUI",KMOD_RGUI},
		{"RGUI",KMOD_RGUI}
	};

}

void KBShortCuts::readConfig(string configFile,string noGroupSearchKey){
    int myIterator = 0;
   	// read config file
	Config config(configFile,0,noGroupSearchKey);
  	
    map<string, Config*> groups = config.getGroups(); // all groups
	const string qualifierPrefix = "qualifier"; // lowercase prefix for group name
	const string ignoredQualifierPrefix = "ignoredqualifier"; // lowercase prefix for group name

	for (map<string, Config*>::iterator i = groups.begin(); i != groups.end(); ++i) {
		short qualifierHeading = 0;
		short ignoredQualifierHeading = 0;
		string groupName = i->first;
		Config* group = i->second;
		keys.emplace_back();

		if(functionMap.find(group->pString("function")) != functionMap.end()){
			//cout << function found(" << (group->pString("function")) <<")" << endl;
			keys[myIterator].func_ptr = (functionMap[group->pString("function")]).funcPtr;
			//cout << "functionMap.desc: " << ((functionMap[group->pString("function")]).desc) << endl;
			keys[myIterator].desc = (functionMap[group->pString("function")]).desc;
		} else {
			//cout << "function not found (" << (group->pString("function")) <<")" << endl;
			keys[myIterator].func_ptr = (functionMap["nothing"]).funcPtr;
			//cout << "functionMap.desc: " << ((functionMap[group->pString("function")]).desc) << endl;
			keys[myIterator].desc = "No description for " + (group->pString("function")) + ". Unknown function";
		}

/*		cout << group->pString("function") << ":" << endl;
		cout << "   Desc: " << keys[myIterator].desc << endl;
		cout << "   Key : " << group->pString("key") << endl;
*/
		keys[myIterator].funcID = group->pString("function");
		if(keyAliasMap.find(group->pString("key")) != keyAliasMap.end()){
			keys[myIterator].sym = keyAliasMap[group->pString("key")].sym;
			keys[myIterator].alias = group->pString("key");
			if(keyAliasMap[group->pString("key")].mod != KMOD_NONE){
				keys[myIterator].modifier = keyAliasMap[group->pString("key")].mod;
				keys[myIterator].modifierVector.push_back(keyAliasMap[group->pString("key")].mod);
			}
			keys[myIterator].key = SDL_GetKeyName(keys[myIterator].sym);
//			cout << "   Alias: " << SDL_GetKeyName(keys[myIterator].sym) << " " << keys[myIterator].modifier << endl;	
		} else {
			keys[myIterator].key = group->pString("key");	
		}
		
		map<string, Config*> subGroups = group->getGroups();
		for (map<string, Config*>::iterator j = subGroups.begin(); j != subGroups.end(); ++j) {
			string subGroupName = j->first;
			Config* subGroup = j->second;

			//if(keys[myIterator].modifier != KMOD_NONE){
			//	cout << "keymod: " << keys[myIterator].modifier << endl;
			//}
			if((subGroup->pString("singlequalifier") != "") && (subGroup->pString("singlequalifier") != "none")){
				//if(subGroup->pString("singlequalifier") != "none"){
				if((subGroupName.substr(0,qualifierPrefix.length()) == qualifierPrefix) && qualifierHeading == 0) {
//					cout << "   " << qualifierPrefix << ":" << endl;
					qualifierHeading = 1;
				}
//				cout << "      " << subGroup->pString("singlequalifier") << endl;
				if((keyModAliasMap.find(subGroup->pString("singlequalifier")) != keyModAliasMap.end()) && (subGroup->pString("singlequalifier") != "")){
					keys[myIterator].modifier = (SDL_Keymod)(keys[myIterator].modifier | (keyModAliasMap[subGroup->pString("singlequalifier")]));
					keys[myIterator].modifierVector.push_back((keyModAliasMap[subGroup->pString("singlequalifier")]));
					//cout << " -- " << (subGroup->pString("singlequalifier")) << " aliased to " << (keyModAliasMap[subGroup->pString("singlequalifier")]) << endl;
				} else {
					cout << "    **" << (subGroup->pString("singlequalifier")) << " not found in keyModAliasMap" << endl;
				}
				//}
			}
			if(subGroup->pString("singleignoredqualifier") != ""){
				if((subGroupName.substr(0,ignoredQualifierPrefix.length()) == ignoredQualifierPrefix) && ignoredQualifierHeading == 0) {
//					cout << "   " << ignoredQualifierPrefix << ":" << endl;
					ignoredQualifierHeading = 1;
				}
//			  	cout << "      " << subGroup->pString("singleignoredqualifier") << endl;
				if(keyModAliasMap.find(subGroup->pString("singleignoredqualifier")) != keyModAliasMap.end()){
					keys[myIterator].ignoreModifier = (SDL_Keymod)(keys[myIterator].ignoreModifier | (keyModAliasMap[subGroup->pString("singleignoredqualifier")]));
					keys[myIterator].ignoreModifierVector.push_back((keyModAliasMap[subGroup->pString("singleignoredqualifier")]));
					//cout << " -- " << (subGroup->pString("singleignoredqualifier")) << " aliased to " << (keyModAliasMap[subGroup->pString("singleignoredqualifier")]) << endl;
				} else {
					cout << "    **" << (subGroup->pString("singleignoredqualifier")) << " not found in keyModAliasMap" << endl;
				}
			}
		}
		//cout << "  Quals: " << keys[myIterator].modifier << endl;
		myIterator++;
	}
}

void KBShortCuts::displayKeysConfigVals(void){
	int numKeys = keys.size();

	for(int i=0; i < numKeys; i++){
		cout << "Function: " << keys[i].funcID << endl;
		cout << "\tDesc: " << keys[i].desc << endl;
		cout << "\tKey: " << keys[i].key;
		if(keys[i].alias != "")
			cout << " (" << keys[i].alias << ")" << endl;
		else
			cout << endl;
		if(keys[i].modifier != 0){
			cout << "\tQualifier: " << bin(keys[i].modifier) << endl;
			for (auto& v : keys[i].modifierVector){
				cout << "\t\t" << keyModSDLNames[v] << endl;
			}
		} else
			cout << "\tQualifier: <empty>" << endl;
		if(keys[i].ignoreModifier != 0){
			cout << "\tIgnoredQualifier: " << bin(keys[i].ignoreModifier) << endl;
			for (auto& v : keys[i].ignoreModifierVector){
				cout << "\t\t" << keyModSDLNames[v] << endl;
			}
		} else
			cout << "\tIgnoredQualifier: <empty>" << endl;
	}
   	
}

void KBShortCuts::writeConfig(string description, string configFile){
	int numKeys = keys.size();

	ofstream fileOut(configFile);
	if (!fileOut) {
		cerr << "cannot open output file '" << configFile << "'" << endl;
		exit(2);
	}

	fileOut << "# " << description << endl;
	for(int i=0; i < numKeys; i++){
		fileOut << endl << keys[i].funcID << " = (" << endl;
		fileOut << "#\t" << keys[i].desc << endl;
		fileOut << "\tfunction = " << keys[i].funcID << endl;
		fileOut << "\tkey = " << keys[i].key << endl;
		if(keys[i].modifier != 0){
			int qualVal = 1;
			for (auto& v : keys[i].modifierVector){
				fileOut << "\tqualifier" << qualVal << " = (" << endl;
				fileOut << "\t\tsinglequalifier = " << keyModTextNames[v] << endl;
				fileOut << "\t)" << endl;
				qualVal++;
			}
		}
		if(keys[i].ignoreModifier != 0){
			int qualVal = 1;
			for (auto& v : keys[i].ignoreModifierVector){
				fileOut << "\tignoredqualifier" << qualVal << " = (" << endl;
				fileOut << "\t\tsingleignoredqualifier = " << keyModTextNames[v] << endl;
				fileOut << "\t)" << endl;
				qualVal++;
			}
		}
		fileOut << ")" << endl;
	}

	fileOut.close();
}

void KBShortCuts::checkKeys(SDL_Keysym keySym){
	int match = 0;
	int numKeys = keys.size();
	
	for(int i=0; i < numKeys; i++){
		if(SDL_GetKeyName(keySym.sym) == keys[i].key){
			/*cout << "keyname: " << SDL_GetKeyName(keySym.sym) << endl;
			cout << "keySym.mod: " << bin(keySym.mod) << endl;
			cout << "modifier: " << bin(keys[i].modifier) << endl;
			cout << "and: " << bin((keySym.mod & keys[i].modifier)) << endl;
			cout << "nand: " << bin(!(keySym.mod & (keySsym.mod &keys[i].modifier))) << endl;
			cout << "xor: " << bin(keySym.mod xor (keySym.mod & kbShortCuts.keys[i].modifier)) << endl;
			cout << "ignoreModifier: " << bin( keys[i].ignoreModifier) << endl;
			*/
			if(((keySym.mod xor (keySym.mod & keys[i].modifier))-(keySym.mod & keys[i].ignoreModifier)) == 0){
				if(keys[i].modifier == KMOD_NONE){
					keys[i].func_ptr(keys[i]);
				} else {
					for (auto& v : keys[i].modifierVector){
						if(keySym.mod & v)
							match++;
					}
					if(match == (int)keys[i].modifierVector.size())
						keys[i].func_ptr(keys[i]);
					match = 0;
				}
			}
		}
	}
}
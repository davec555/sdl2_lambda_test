#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

#include "kbshortcuts.h"

using namespace std;
using bin = std::bitset<16>;

SDL_Window *window;
SDL_GLContext glContext;


const int width = 640;
const int height = 480;

void drawCube(float xrf, float yrf, float zrf);


void init(){

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){ 
	 	cout << "Unable to init SDL, error: " << SDL_GetError() << endl;
	 	exit(1);
	} 

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	glContext = SDL_GL_CreateContext(window);
	
	if(window == NULL){
		exit(1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

string toLowerStrCopy(string s){
	string result;
	for (char &c : s) {
		c = tolower(c);
		result = result+c;
	}
	return result;
}

void showHelp(vector<keyboard_func>* keys){
	//keys passed by ref as copies(ref) will just waste mem
	int numKeys = keys->size();

	cout << "Help text " << endl;
	for(int i=0; i < numKeys; i++){
		string mods;
		for (auto& v : (*keys)[i].modifierVectorText){
			mods = mods + v + " ";
		}

		if((((*keys)[i].alias != "") && (toLowerStrCopy((*keys)[i].key) != (*keys)[i].alias)))
			printf("%20s ",(mods + (*keys)[i].key + " (" + (*keys)[i].alias + ")").c_str());
		else
			printf("%20s ",(mods + (*keys)[i].key).c_str());
		
		cout << " - " << (*keys)[i].desc << endl;;
	}
}

int main(int argc, char *argv[], char* envp[]){   

	init();
	
	KBShortCuts kbShortCuts;

	kbShortCuts.functionMap = {
		{"rotatenegy",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Rotate -Y"}},
		{"rotateposy",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Rotate +Y"}},
		{"rotatenegx",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Rotate -X"}},
		{"rotateposx",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Rotate +X"}},		
		{"rotatenegz",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Rotate -Z"}},
		{"rotateposz",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Rotate +Z"}},
		{"togglebgcol",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle background colour between black/blue"}},
		{"togglefullscreen",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle between window/fullscreen mode"}},
		{"refreshdisplay",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Refresh the display"}},
		{"displayboundingbox",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to bounding box"}},
		{"displaypoints",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to points"}},
		{"displaywireframe",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to wireframe"}},
		{"displaywireframehiddensurface",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to hidden surface wireframe"}},
		{"displaysolid",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to solid"}},
		{"displaysolidsurfacedetail",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to surface detail solid"}},
		{"displaysolidedge",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to solid edge"}},
		{"displaysolidedgesurfacedetail",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Set display to surface detail solid edge"}},
		{"toggleantialiasing",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle anti-aliasing"}},
		{"camout",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move camera out/back"}},
		{"camin",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move camera in/forward"}},
		{"toggledetails",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle details"}},
		{"polyfactoradd",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Add to polyfactor"}},
		{"polyfactorsub",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Subtract from polyfactor"}},		
		{"showhelp",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
			showHelp(keys);
		},"Show help"}},
		{"showinfo",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Show object info"}},
		{"togglelightingnonconvex",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle non-convex polygon lighting"}},
		{"togglelighting",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle lighting"}},
		{"togglematerial",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle material"}},
		{"togglepositiontype",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle positioning between object/light"}},
		{"togglenormals",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle normals display"}},
		{"cyclenonconvex",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Cycle non-convex polygon display hide/only/show"}},
		{"loadobject",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Load a Lightwave Object (.lwo) file"}},
		{"toggleignoreenv",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle ignore/respect environmental variables"}},
		{"toggleprojection",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle projection of object between perspective/orthographic"}},
		{"toggleaxisstep",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle value of axis movement normal/strong"}},
		{"togglerotaterings",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle display of rotate rings"}},
		{"refreshlists",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Refresh display lists of object"}},
		{"resetposition",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Resets position of object"}},
		{"toggleshading",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle shading of object smooth/flat"}},
		{"toggletessellator",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Toggle tessellator for non-convex polygons"}},
		{"runspeedtest",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Runs spinning animation test"}},
		{"polyunitsadd",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Add to polyunits"}},
		{"polyunitssub",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Subtract from polyunits"}},
		{"moveposx",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move object/light to right"}},
		{"movenegx",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move object/light to left"}},
		{"moveposy",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move object/light up"}},
		{"movenegy",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move object/light down"}},
		{"moveposz",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move object/light towards viewer (zoomin)"}},
		{"movenegz",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << kb.desc << endl;
		},"Move object/light away from viewer (zoomout)"}},
		{"nothing",{[](struct keyboard_func kb, vector<keyboard_func>* keys) {
			cout << "function not found (" << kb.desc << ") - doing nothing " << endl;
		},"no function exists"}}
	};
	
	kbShortCuts.readConfig("displwo.config","key");

	bool running = true;

	float xrf = 0, yrf = 0, zrf = 0;

	while(running){ 
	  
		SDL_Event event;
	  
		while ( SDL_PollEvent(&event) ){
			switch(event.type){
				case SDL_QUIT:
					running = false;
				break;

				case SDL_KEYDOWN:
					//cout << "Keyname: " << SDL_GetKeyName(event.key.keysym.sym) << endl;
					//cout << "Scancode: " << SDL_GetScancodeName(event.key.keysym.scancode) << endl;
					//cout << "KMOD_SHIFT: " << KMOD_SHIFT << endl;
					//cout << "Modifier: " << event.key.keysym.mod << ": " << (event.key.keysym.mod & KMOD_SHIFT) << ": " << (event.key.keysym.mod & KMOD_NONE) << endl;
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							running = false;
							//kbShortCuts.displayKeysConfigVals();
							kbShortCuts.writeConfig("dispLWO Config File","displwo1.config");
						break;
						default:
							kbShortCuts.checkKeys(event.key.keysym);
						break;
					}
				break;
			} 
		}

		xrf -= 0.5; 
		yrf -= 0.5;
		zrf -= 0.5;

		drawCube(xrf, yrf, zrf);

		glFlush();
		SDL_GL_SwapWindow(window);
	}

	//Destroy context
	SDL_GL_DeleteContext( glContext );
	glContext = NULL;	

	//Destroy window	
	SDL_DestroyWindow( window );
	window = NULL;
	
	SDL_Quit();
	return 0;
}

void drawCube(float xrf, float yrf, float zrf){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);
	
	glRotatef(xrf, 1.0f, 0.0f, 0.0f);
	glRotatef(yrf, 0.0f, 1.0f, 0.0f);
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f( 1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f,  1.0f);
	glVertex3f( 1.0f, 1.0f,  1.0f);
	
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f( 1.0f,  1.0f, 1.0f);
	glVertex3f(-1.0f,  1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);

	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	
	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);

	glEnd();  

}

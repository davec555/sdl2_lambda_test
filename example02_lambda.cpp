#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <bitset>
#include <vector>

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

int main(int argc, char *argv[], char* envp[]){   

	init();
	
	KBShortCuts kbShortCuts;

	kbShortCuts.functionMap = {
		{"rotatenegy",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Rotate -Y"}},
		{"rotateposy",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Rotate +Y"}},
		{"rotatenegx",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Rotate -X"}},
		{"rotateposx",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Rotate +X"}},		
		{"rotatenegz",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Rotate -Z"}},
		{"rotateposz",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Rotate +Z"}},
		{"togglebgcol",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Toggle background colour between black/blue"}},
		{"togglefullscreen",{[](struct keyboard_func kb) {
			cout << kb.desc << endl;
		},"Toggle between window/fullscreen mode"}},
		{"nothing",{[](struct keyboard_func kb) {
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
							//kbShortCuts.writeConfig("dispLWO Config File","displwo1.config");
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

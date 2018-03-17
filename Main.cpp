#include <GL/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <assert.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL_mixer.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#include "drawfunc.cpp"
#include "gui.cpp"


enum GameMode {
  GAMEMODE_OFFICE,
  GAMEMODE_FLOOR,
};


int main (int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  SDL_Window *window = SDL_CreateWindow("TUES Tycoon",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					WINDOW_WIDTH, WINDOW_HEIGHT,
					SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  font_tex = load_font("font.data", 570, 10);
  //  Texture crep = load_image("creepy.png");
  Texture background_tex = load_image("background.png");
  Texture firstfloor_tex = load_image("hakaton.png");
  glClearColor (0, 0, 0, 1.0);

  int Budget = 100000;

  GameMode gameMode = GAMEMODE_OFFICE;
  float mousePos_x = 0;
  float mousePos_y = 0;
  bool mousePressed = false;
  int floorNumber;

  Button principleOffice = { 0.69, 0.90, 0.5, 0.095, "Principle's office" };
  Button floor1Button = { 0.69, 0.80, 0.5, 0.095, "Floor: 1" };
  Button floor2Button = { 0.69, 0.70, 0.5, 0.095, "Floor: 2" };
  Button floor3Button = { 0.69, 0.60, 0.5, 0.095, "Floor: 3" };
  Button floorAddButton = { 0.69, 0.50, 0.5, 0.095, "Add Floor" };
  
  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
    {
      printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
      exit(1);
    }

  int keeprunning = 1;
  Uint32 last_time = SDL_GetTicks();
  float time=0;

  while (keeprunning)
    {
      SDL_Event event;
      while (SDL_PollEvent(&event))
	{
	  if (event.type == SDL_QUIT)
	    {
	      keeprunning = 0;
	    }
	  else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	    {
	      //int pressed = event.type == SDL_KEYDOWN;


	      if (event.key.keysym.sym == SDLK_ESCAPE)
		{
		  keeprunning = 0;
		}
	    }
	  else if (event.type == SDL_MOUSEMOTION)
	    {
	      mousePos_x = (float)event.motion.x * 2 / WINDOW_WIDTH - 1;
	      mousePos_y = (float)event.motion.y * 2 / -WINDOW_HEIGHT + 1;
	    }
	  else if (event.type == SDL_MOUSEBUTTONDOWN) {
	    mousePressed = true;
	  }
	  else if (event.type == SDL_MOUSEBUTTONUP){
	    mousePressed = false;
	  }
	}

      Uint32 current_time = SDL_GetTicks();
      float dt = (current_time - last_time) / 1000.0;
      last_time = current_time;
      time+=dt;

      switch (gameMode)
	{
	case GAMEMODE_OFFICE:
	  {
	    glColor3f(1, 1, 1);
	    drawImage(background_tex, 0, 0, 2, 2);
	    saveText ( Budget, time);
			  
	    if (UpdateButton(&principleOffice, mousePos_x, mousePos_y, mousePressed))
	      {
		gameMode = GAMEMODE_OFFICE;
				  
	      }
	    if (UpdateButton(&floor1Button, mousePos_x, mousePos_y, mousePressed))
	      {
		floorNumber = 1;
		gameMode = GAMEMODE_FLOOR;
	      }
	    if (UpdateButton(&floor2Button, mousePos_x, mousePos_y, mousePressed))
	      {
		floorNumber = 2;
		gameMode = GAMEMODE_FLOOR;
	      }
	    if (UpdateButton(&floor3Button, mousePos_x, mousePos_y, mousePressed))
	      {
		floorNumber = 3;
		gameMode = GAMEMODE_FLOOR;
	      }
	    UpdateButton(&floorAddButton, mousePos_x, mousePos_y, mousePressed);
	  } break;

	case GAMEMODE_FLOOR:
	  {
	    glClearColor(0, 0, 0, 1);
	    glClear(GL_COLOR_BUFFER_BIT);
	    saveText ( Budget, time);

	    switch (floorNumber)
	      {
	      case 1:
		draw_text(font_tex, 0, 0, "First");
		break;
	      case 2:
		draw_text(font_tex, 0, 0, "Second");
		break;
	      case 3:
		draw_text(font_tex, 0, 0, "Third");
		break;
	      }

	    if (UpdateButton(&principleOffice, mousePos_x, mousePos_y, mousePressed))
	      {
		gameMode = GAMEMODE_OFFICE;
	      }
	    if (UpdateButton(&floor1Button, mousePos_x, mousePos_y, mousePressed))
	      {
		floorNumber = 1;
		gameMode = GAMEMODE_FLOOR;
	      }
	    if (UpdateButton(&floor2Button, mousePos_x, mousePos_y, mousePressed))
	      {
		floorNumber = 2;
		gameMode = GAMEMODE_FLOOR;
	      }
	    if (UpdateButton(&floor3Button, mousePos_x, mousePos_y, mousePressed))
	      {
		floorNumber = 3;
		gameMode = GAMEMODE_FLOOR;
	      }

	  } break;
	}

      SDL_GL_SwapWindow(window);
    }

  return 0;
}

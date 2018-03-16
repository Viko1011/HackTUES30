#include <GL/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <assert.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL_mixer.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#include "drawfunc.cpp"

int main (int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  SDL_Window *window = SDL_CreateWindow("TuesTycoon eksdi",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					WINDOW_WIDTH, WINDOW_HEIGHT,
					SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(window);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  Texture font_tex = load_font("font.data", 570, 10);
  //  Texture crep = load_image("creepy.png");
  glClearColor (0, 0, 0, 1.0);
  // int Budget;
  // int Day;
  // int Year;
  // int Month;
  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
    {
      printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
      exit(1);
    }
  

  int keeprunning = 1;
  //Uint32 last_time = SDL_GetTicks();

  while (keeprunning)
    {
      SDL_Event event;
      while (SDL_PollEvent (&event))
	{
	  if(event.type == SDL_QUIT)
	    {	     
	      keeprunning = 0;
	    }
	  else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	    {
	      //int pressed = event.type == SDL_KEYDOWN;
	     

		  if (event.key.keysym.sym == SDLK_ESCAPE)
		  {
			  keeprunning = 0;
		  }
	  }
	      
	}

      //Uint32 current_time = SDL_GetTicks();
      //float dt = (current_time - last_time) / 1000.0;
      //last_time = current_time;
     
          glColor3f(0.3, 0.3, 0.2);
          drawRect(-0.36, -0.36, 0.6, 0.6);
          glColor3f(0.8, 0.8, 0.8);
	  drawRect(-0.36, -0.36, 0.58,0.58);
	  glColor3f(0.3, 0.3, 0.2);
          drawRect(0.36, 0.36, 0.6, 0.6);
          glColor3f(0.8, 0.8, 0.8);
	  drawRect(0.36, 0.36, 0.58, 0.58);
	  glColor3f(0.3, 0.3, 0.2);
          drawRect(0.36, -0.36, 0.6, 0.6);
	  glColor3f(0.8, 0.8, 0.8);
	  drawRect(0.36, -0.36, 0.58, 0.58);
	  glColor3f(0.3, 0.3, 0.2);
          drawRect(-0.36, 0.36, 0.6, 0.6);
	  glColor3f(0.8, 0.8, 0.8);
	  drawRect(-0.36, 0.36, 0.58, 0.58);
	  glColor3f(0.3, 0.3, 0.2);
	  drawRect(0, 0, 1.32, 0.12);
	  glColor3f(0.3,0.2,0.3);
	  drawRect(0, 0, 0.12, 1.32);
	
	 
	  
      // 	  glColor3f(1, 1, 1);
      // 	  //drawImage(0, 0, 1, 1);
       	  draw_text(font_tex, -1.0, 1.0, "release-1.1");


      // 	  char budget_text[64];
      // 	  sprintf(budget_text, "Budget: %d", Budget);
      // 	  draw_text(font_tex, -1.0, 0.95, budget_text);

      // 	  char day_text[31];
      // 	  sprintf(day_text, "Day: %d", Day);
      // 	  draw_text(font_tex, -1.0, 0.90, day_text);





	  
      	  SDL_GL_SwapWindow(window);
    }

    return 0;
}
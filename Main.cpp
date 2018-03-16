#include <GL/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <assert.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL_mixer.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
struct Texture {
	int w, h;
	GLuint id;
};

Texture font_tex;

struct Button {
	float x, y, width, height;
	const char *text;
};

void drawRect(float x, float y, float width, float height) {
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(x - width / 2, y - height / 2);
	glVertex2f(x - width / 2, y + height / 2);
	glVertex2f(x + width / 2, y - height / 2);
	glVertex2f(x + width / 2, y + height / 2);
	glEnd();
}

static void
draw_text(Texture font, float x, float y,
	const char *text, int scale = 1, size_t len = 0)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, font.id);
	glColor4f(1, 1, 1, 1);

	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

	float tw = 6.0f / font.w;
	float pw = 6.0f / (WINDOW_WIDTH / 2) * scale;
	float ph = 10.0f / (WINDOW_HEIGHT / 2) * scale;
	float px = x;
	float py0 = y;

	if (!len) len = strlen(text);

	for (size_t i = 0; i < len; ++i)
	{
		int c = text[i];

		if (c == '\n')
		{
			px = x;
			py0 -= ph;
		}
		else
		{
			int char_index = c - 32;
			float tx0 = char_index * tw;
			float tx1 = tx0 + tw;
			float py1 = py0 - ph;

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(tx0, 0);
			glVertex2f(px, py0);
			glTexCoord2f(tx0, 1);
			glVertex2f(px, py1);
			px += pw;
			glTexCoord2f(tx1, 0);
			glVertex2f(px, py0);
			glTexCoord2f(tx1, 1);
			glVertex2f(px, py1);
			glEnd();
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
}

static void
draw_text_centered(Texture font, float x, float y,
	const char *text, int scale = 1)
{
	float line_height = 10.0f / (WINDOW_HEIGHT / 2) * scale;
	const char *line = text;

	while (1)
	{
		char c = *text;

		if (c == '\n' || !c)
		{
			size_t line_len = text - line;
			float pw = 6.0f / (WINDOW_WIDTH / 2) * scale;
			float line_x = x - line_len / 2.0 * pw;

			draw_text(font, line_x, y, line, scale, line_len);

			if (!c) break;

			line = text + 1;
			y -= line_height;
		}

		++text;
	}
}

static Texture
load_font(const char *filepath, int w, int h)
{
	FILE *fd = fopen(filepath, "rb");
	assert(fd);
	int size = w * h;
	unsigned char data[size];
	size_t bytes_read = fread(data, 1, size, fd);
	assert(bytes_read = size);
	fclose(fd);

	Texture texture;
	texture.w = w;
	texture.h = h;
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w, h, 0,
		GL_LUMINANCE, GL_UNSIGNED_BYTE, data);

	return texture;
}

void drawImage(float x, float y, float width, float height) {
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0, 1);
	glVertex2f(x - width / 2, y - height / 2);
	glTexCoord2f(0, 0);
	glVertex2f(x - width / 2, y + height / 2);
	glTexCoord2f(1, 1);
	glVertex2f(x + width / 2, y - height / 2);
	glTexCoord2f(1, 0);
	glVertex2f(x + width / 2, y + height / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

static Texture
load_image(const char *filepath)
{
	printf("%s\n", filepath);
	SDL_Surface *image = IMG_Load(filepath);
	assert(image);

	Texture texture;
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		image->w, image->h,
		0,
		GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	return texture;
}
void UpdateButton(Button* button , float mousePos_x, float mousePos_y) {
	if (mousePos_x > button->x - button->width / 2 &&
		mousePos_x < button->x + button->width / 2 &&
		mousePos_y > button->y - button->height / 2 &&
		mousePos_y < button->y + button->height / 2) {
		printf("button: %s\n", button->text);
		glColor3f(0.75, 0.45, 1);
		drawRect(button->x, button->y, button->width, button->height);
		draw_text(font_tex, button->x, button->y, button->text);

	}
	else
	{
		glColor3f(0.80, 0.66, 0.9);
		drawRect(button->x, button->y, button->width, button->height);
		draw_text(font_tex, button->x, button->y, button->text);
	}
}
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
  font_tex = load_font("font.data", 570, 10);
  glClearColor (0, 0, 0, 1.0);
  int Budget = 100000;
  int Day = 17;
  int Year = 2018;
  int Month = 03;
  
  Button floor1Button = { 0.69, 0.90, 0.5, 0.09, "Floor: 1" };
  Button floor2Button = { 0.69, 0.80, 0.5, 0.09, "Floor: 2" };
  Button floor3Button = { 0.69, 0.70, 0.5, 0.09, "Floor: 3" };
  Button floorAddButton = { 0.69, 0.60, 0.5, 0.09, "Add Floor" };

	int keeprunning = 1;
  float mousePos_y;
  float mousePos_x;
  //Uint32 last_time = SDL_GetTicks();

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

	  }

      //Uint32 current_time = SDL_GetTicks();
      //float dt = (current_time - last_time) / 1000.0;
      //last_time = current_time;
	  printf("%.2f\n", mousePos_x);
	  printf("%.2f\n", mousePos_y);

	  glColor3f(1, 1, 1);

	  //drawImage(0, 0, 1, 1); //(float x, float y, float width, float height)
	  draw_text(font_tex, -0.95, 0.95, "Alpha Release :DD");


	  char budget_text[64];
	  sprintf(budget_text, "Budget: %d", Budget);
	  draw_text(font_tex, -0.95, 0.90, budget_text);

	  char year_text[64];
	  sprintf(year_text, "Year: %d", Year);
	  draw_text(font_tex, -0.95, 0.85, year_text);

	  char month_text[64];
	  sprintf(month_text, "Month: %d", Month);
	  draw_text(font_tex, -0.95, 0.80, month_text);
		
	  char day_text[64];
	  sprintf(day_text, "Day: %d", Day);
	  draw_text(font_tex, -0.95, 0.75, day_text);

	  UpdateButton(&floor1Button, mousePos_x , mousePos_y);
	  UpdateButton(&floor2Button, mousePos_x, mousePos_y);
	  UpdateButton(&floor3Button, mousePos_x, mousePos_y);
	  UpdateButton(&floorAddButton, mousePos_x, mousePos_y);

	  SDL_GL_SwapWindow(window);
  }
    return 0;
}
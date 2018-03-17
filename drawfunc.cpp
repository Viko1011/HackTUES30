struct Texture {
	int w, h;
	GLuint id;
};

Texture font_tex;

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
	glColor3f(1, 1, 1);

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
	return;
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

void drawImage(Texture tex, float x, float y, float width, float height) {
	glBindTexture(GL_TEXTURE_2D, tex.id);
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
void drawOutline(float x, float y, float width, float height, float line_width) {
	drawRect(x, y + (height / 2 - line_width / 2), width, line_width);
	drawRect(x, y - (height / 2 - line_width / 2), width, line_width);
	drawRect(x - (width / 2 - line_width / 2), y, line_width, height);
	drawRect(x + (width / 2 - line_width / 2), y, line_width, height);
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

int Year = 1, Day = 1, Month = 1, Hours = 0, DayMax;

void saveText(float Budget, float time)
{
	time *= 20500;
	glColor4f(0, 0, 0, 0.2);
	drawRect(-0.95, 0.95, 0.45, 0.65);
	int Minutes = time;
	int Hours = Minutes / 60;
	int Days = Hours / 24;
	int Year = Days / 365 + 1988;
	int Month;
	Days %= 365;
	Days += 1;
	Minutes %= 60;
	Hours %= 24;
	int Day;
	
	if (Days <= 31) {
		Month = 1;
		Day = Days;
	}
	else if (Days <= 31 + 28) {
		Month = 2;
		Day = Days - 31;
	}
	else if (Days <= 31 + 28 + 31) {
		Month = 3;
		Day = Days - (31 + 28);
	}
	else if (Days <= 31 + 28 + 31 + 30) {
		Month = 4;
		Day = Days - (31 + 28 +31);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31) {
		Month = 5;
		Day = Days - (31 + 28 +31 + 30);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30) {
		Month = 6;
		Day = Days - (31 + 28 + 31 + 30 + 31);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30 + 31) {
		Month = 7;
		Day = Days - (31 + 28 + 31 + 30 + 31 + 30);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31) {
		Month = 8;
		Day = Days - (31 + 28 + 31 + 30 + 31 + 30 +31);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30) {
		Month = 9;
		Day = Days - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 31 + 30) {
		Month = 10;
		Day = Days - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 31);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30) {
		Month = 11;
		Day = Days - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31);
	}
	else if (Days <= 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31) {
		Month = 12;
		Day = Days - (31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30);
	}

	char budget_text[64];
	sprintf(budget_text, "Budget: %.2f", Budget);
	draw_text(font_tex, -0.95, 0.95, budget_text);

	char year_text[64];
	sprintf(year_text, "Year: %d", Year);
	draw_text(font_tex, -0.95, 0.90, year_text);

	char month_text[64];
	sprintf(month_text, "Month: %d", Month);
	draw_text(font_tex, -0.95, 0.85, month_text);

	char day_text[64];
	sprintf(day_text, "Day: %d", Day);
	draw_text(font_tex, -0.95, 0.80, day_text);

	char min_text[64];
	sprintf(min_text, "Minutes: %d", Minutes);
	draw_text(font_tex, -0.95, 0.70, min_text);

	char hours_text[64];
	sprintf(hours_text, "Hours: %d", Hours);
	draw_text(font_tex, -0.95, 0.75, hours_text);
}
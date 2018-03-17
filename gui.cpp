struct Button {
  float x, y, width, height;
  const char *text;
};

bool UpdateButton(Button* button, float mousePos_x, float mousePos_y, bool mousePressed) {


  if (mousePos_x > button->x - button->width / 2 &&
      mousePos_x < button->x + button->width / 2 &&
      mousePos_y > button->y - button->height / 2 &&
      mousePos_y < button->y + button->height / 2) {
    glColor3f(0.75, 0.45, 1);
    glDisable(GL_TEXTURE_2D);
    drawRect(button->x, button->y, button->width, button->height);
    draw_text(font_tex, button->x, button->y, button->text);
    if (mousePressed == true) {
      return true;
    }
  }
  else
    {
      glColor3f(0.80, 0.66, 0.9);
      drawRect(button->x, button->y, button->width, button->height);
      draw_text(font_tex, button->x, button->y, button->text);
    }

  return false;
}
void saveText (int Budget, float time)
{
  int Month;
  int Year;
  int Day=time;
  
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  char budget_text[64];
  sprintf(budget_text, "Budget: %d", Budget);
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
}



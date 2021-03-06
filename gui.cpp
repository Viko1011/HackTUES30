
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



#include <GLUT/glut.h> 

#include "Controller.h"
#include "Errors.h"

#include <stdio.h>

#define KEY_SPACE 32
#define KEY_Q 113

const char *error_msg(error error);

error error_log(const char *action, error error);

void draw_line(Vertex p0, Vertex p1);

void display_text(char *text, float x, float y, float r, float g, float b);

void display(Scene *scene);

void cap();

void processNormalKeys(unsigned char key, int xx, int yy);

void processArrowKeys(int key, int x, int y);

error create_window(int *argc, char **argv, int weight, int height, char *window_name, int x_cord, int y_cord, char *filename);

error create_object(Scene **scene_ptr, char *filename);

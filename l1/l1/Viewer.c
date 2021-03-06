#include "Viewer.h"

#include <GLUT/glut.h>
#include <stdlib.h>

#define KEY_SPACE 32
#define KEY_Q 113

double current_x_cord = 0;
double current_y_cord = 0;

const char *error_msg(error error)
{
	const char *msg = NULL;
	switch (error)
	{
		case NO_ERROR:
			return NULL;
		case FILE_CANNOT_BE_OPENED:
			msg = "file cannot be opened";
			break;
		case FILE_CONTAINS_INVALID_VALUES:
			msg = "file contains invalid values";
			break;
		case OBJECT_IS_NOT_INITIALISED:
			msg = "object is not initialised";
			break;
		case RENDERING_ERROR:
			msg = "rendering error";
			break;
		case SCENE_IS_NOT_INITIALISED:
			msg = "scene is not initialised";
			break;
		case ALLOCATION_ERROR:
			msg = "allocation error";
			break;
	}

	return msg;
}

error error_log(const char *action, error error)
{
	if (error == NO_ERROR) { return error; }
	printf("Error during '%s': %s", action, error_msg(error));
	return error;
}

void draw_line(Vertex p0, Vertex p1)
{
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(p0.x, p0.y);
		glVertex2f(p1.x, p1.y);
	glEnd();
}

void display_text(char *text, float x, float y, float r, float g, float b)
{
	glColor3f(r, g, b);
	for (int i = 0; text[i] != '\0'; i++)
	{
		glRasterPos2f(0.2*i + x, y);
    	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void display(Scene *scene) 
{ 
	glClear(GL_COLOR_BUFFER_BIT);  
	char *command_name;

	Command current_command;
	get_command(scene, &current_command);
	switch (scene->command)
	{
		case TRANSPOSE:
			command_name = "TRANSPOSE";
			break;
		case SCALE:
			command_name = "SCALE";
			break;
		case ROTATE:
			command_name = "ROTATE";
			break;
	}

	Action_data action_data = pack_rendering_data(scene, draw_line);
	controller(RENDER_OBJECT, action_data);

	display_text("Current command:", -current_x_cord+1, current_y_cord-1, 1, 1, 1);
	display_text(command_name, -current_x_cord+1, current_y_cord-1.5, 1, 1, 1);

	float r = 1, g = 1, b = 1;
	display_text("<Left/Right/Up/Down> - change values/", -0.9*current_x_cord, -current_y_cord+current_x_cord/3.5, r, g, b);
	display_text("<Space> - change the command", -0.9*current_x_cord, -current_y_cord+current_x_cord/5, r, g, b);
	display_text("<Q> - exit", -0.9*current_x_cord, -current_y_cord+current_x_cord/10, r, g, b);

	glFlush();  
}

void cap() {   }

void processNormalKeys(unsigned char key, int xx, int yy)
{
	switch (key)
	{
		case KEY_SPACE:
	    {
	    	Command current_command;
	    	get_command(&current_command);
	    	switch (current_command)
	    	{
	    		case TRANSPOSE:
	    			set_command(SCALE);
	    			break;
	    		case SCALE:
	    			set_command(ROTATE);
	    			break;
	    		case ROTATE:
	    			set_command(TRANSPOSE);
	    			break;
	    	}
	    	display(current_scene);
	    	break;
	    }
	    case KEY_Q:
	    {
	    	Action_data action_data = pack_deleting_data(current_scene);
	    	error_log("closing program", controller(DELETE_OBJECT, action_data));
	    	printf("\nExiting program...\n");
	    	exit(0);
	    }
	}
}

void processArrowKeys(int key, int x, int y)
{
	Action_data action_data;
	Command current_command;
	get_command(&current_command);
	switch (key) {
		case GLUT_KEY_LEFT:
			switch (current_command)
			{
				case TRANSPOSE:
					action_data = pack_transposing_data(-0.5, 0, 0);
					controller(TRANSPOSE_OBJECT, action_data);
					break;
				case SCALE:
					action_data = pack_scaling_data(0.95, 1, 1);
					controller(SCALE_OBJECT, action_data);
					break;
				case ROTATE:
					action_data = pack_rotating_data(-5, Z);
					controller(ROTATE_OBJECT, action_data);
					break;
			}
			break;
		case GLUT_KEY_RIGHT:
			switch (current_command)
			{
				case TRANSPOSE:
					action_data = pack_transposing_data(0.5, 0, 0);
					controller(TRANSPOSE_OBJECT, action_data);
					break;
				case SCALE:
					action_data = pack_scaling_data(current_scene, 1.2, 1, 1);
					controller(SCALE_OBJECT, action_data);
					break;
				case ROTATE:
					action_data = pack_rotating_data(current_scene, 5, Z);
					controller(ROTATE_OBJECT, action_data);
					break;
			}
			break;
		case GLUT_KEY_UP:
			switch (current_command)
            {
				case TRANSPOSE:
					action_data = pack_transposing_data(current_scene, 0, 0, 0.5);
					controller(TRANSPOSE_OBJECT, action_data);
					break;
				case SCALE:
					action_data = pack_scaling_data(current_scene, 1, 1, 1.2);
					controller(SCALE_OBJECT, action_data);
					break;
				case ROTATE:
					action_data = pack_rotating_data(current_scene, -5, X);
					controller(ROTATE_OBJECT, action_data);
					break;
			}
			break;
		case GLUT_KEY_DOWN:
			switch (current_command)
			{
				case TRANSPOSE:
					action_data = pack_transposing_data(current_scene, 0, 0, -0.5);
					controller(TRANSPOSE_OBJECT, action_data);
					break;
				case SCALE:
					action_data = pack_scaling_data(current_scene, 1, 1, 0.8);
					controller(SCALE_OBJECT, action_data);
					break;
				case ROTATE:
					action_data = pack_rotating_data(current_scene, 5, X);
					controller(ROTATE_OBJECT, action_data);
					break;
			}
			break;
	}
	display(current_scene);
}

error create_object(Scene **scene_ptr, char *filename)
{
	Action_data action_data = pack_loading_data(filename, scene_ptr);
	return error_log("loading object", controller(LOAD_OBJECT, action_data));
}

error create_window(int *argc, char **argv, int width, int height, char *window_name, int x_cord, int y_cord, char *filename)
{
	setbuf(stdout, NULL);

	Scene *new_scene = NULL;
	error error = create_object(&new_scene, filename);
	if (error != NO_ERROR) { return error; }
    current_scene = new_scene;
    
	glutInit(argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(width, height);
	glutCreateWindow(window_name);
	glutDisplayFunc(cap);

	gluOrtho2D(-x_cord, x_cord, -y_cord, y_cord);
	current_x_cord = x_cord;
	current_y_cord = y_cord;

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processArrowKeys);

	display(new_scene);

	glutMainLoop();

	return NO_ERROR;
}

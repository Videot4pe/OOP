#include "Viewer.h"

int main(int argc, char **argv)
{
	int WINDOW_WIDTH = 1400, WINDOW_HEIGHT = 1000;
	int x_cord = 10, y_cord = 10;
	char *filename = "/Users/garanya/Dropbox/Univer/OOP/l1/l1/cube.txt";

	create_window(&argc, argv, WINDOW_WIDTH, WINDOW_HEIGHT, "lab 1", x_cord, y_cord, filename);
	return 0;
}

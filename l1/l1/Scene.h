#ifndef _SCENE_
#define _SCENE_

#include "Object.h"
#include "Errors.h"

typedef enum {
	TRANSPOSE,
	SCALE,
	ROTATE,
} Command;

typedef struct {
	Object *object;
	Command command;
} Scene;

error init_scene(Scene **scene_ptr, Object *obj_ptr);
error delete_scene(Scene *scene_ptr);

error get_command(Scene *scene_ptr, Command *command);
error set_command(Scene *scene_ptr, Command new_command);

error get_object(Scene *scene_ptr, Object **object);

#endif

#ifndef Action_h
#define Action_h

#include <stdio.h>
#include "Scene.h"
#include "Object.h"
#include "Errors.h"
#include "Pack.h"
#include "Viewer.h"
#include "Controller.h"

error handleLoad(Action_data action_data);
error handleDelete(Action_data action_data);
error handleRender(Action_data action_data);
error handleTranspose(Action_data action_data);
error handleScale(Action_data action_data);
error handleRotate(Action_data action_data);

#endif /* Action_h */

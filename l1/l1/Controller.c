#include "Controller.h"

error controller(Action action, Action_data action_data)
{
    error error = NO_ERROR;
    switch (action)
    {
        case LOAD_OBJECT:
            error = handleLoad(action_data);
            break;
            
        case DELETE_OBJECT:
            error = handleDelete(action_data);
            break;
            
        case RENDER_OBJECT:
            error = handleRender(action_data);
            break;
            
        case TRANSPOSE_OBJECT:
            error = handleTranspose(action_data);
            break;
            
        case SCALE_OBJECT:
            error = handleScale(action_data);
            break;
            
        case ROTATE_OBJECT:
            error = handleRotate(action_data);
            break;
    }
    
    return error;
}


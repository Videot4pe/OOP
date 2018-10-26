#include "Action.h"

error handleLoad(Action_data action_data)
{
    Object *current_object = NULL;
    error error = NO_ERROR;
    Scene **current_scene_ptr = NULL;
    char *filename = NULL;
    unpack_loading_data(&action_data, &current_scene_ptr, &filename);
    error = load_object(filename, &current_object);
    if (error != NO_ERROR) { return error; }
    return init_scene(current_scene_ptr, current_object);
}

error handleDelete(Action_data action_data)
{
    Scene *MyScene = NULL;

    Scene *current_scene = MyScene;
    unpack_deleting_data(&action_data, &current_scene);
    return delete_scene(current_scene);
}

error handleRender(Action_data action_data)
{
    Scene *MyScene = NULL;
    Object *current_object = NULL;
    void (* draw_line)(Vertex v1, Vertex v2) = NULL;
    unpack_rendering_data(&action_data, &current_object, &draw_line);
    return render_object(current_object, draw_line);
}

error handleTranspose(Action_data action_data)
{
    Scene *MyScene = NULL;
    Object *current_object = NULL;
    double dx, dy, dz;
    unpack_transposing_data(&action_data, &current_object, &dx, &dy, &dz);
    return transpose_object(current_object, dx, dy, dz);
}

error handleScale(Action_data action_data)
{
    Scene *MyScene = NULL;
    Object *current_object = NULL;
    double kx, ky, kz;
    unpack_scaling_data(&action_data, &current_object, &kx, &ky, &kz);
    return scale_object(current_object, kx, ky, kz);
}

error handleRotate(Action_data action_data)
{
    Scene *MyScene = NULL;
    Object *current_object = NULL;
    double degrees;
    Axis axis;
    unpack_rotating_data(&action_data, &current_object, &degrees, &axis);
    return  rotate_object(current_object, degrees, axis);
}



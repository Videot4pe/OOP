#ifndef _OBJECT_
#define _OBJECT_

#include "Errors.h"

typedef enum {
    X, Y, Z
} Axis;

typedef struct {
    double x;
    double y;
    double z;
} Vertex;

typedef struct {
    int v1;
    int v2;
} Edge;

typedef struct {
    int v_num;
    Vertex *vertices;
    int e_num;
    Edge *edges;
} Object;

error set_vertex(Vertex *vertex, double x, double y, double z);
error set_edge(Edge *edge, int v1, int v2);

error transpose_vertex(Vertex *vertex, double dx, double dy, double dz);
error scale_vertex(Vertex *vertex, double kx, double ky, double kz);
error rotate_vertex(Vertex *vertex, double degrees, Axis axis);
error project_vertex(Vertex *vertex);

error get_vertex_num(Object *object, int *vertex_num);
error get_vertices(Object *object, Vertex **vertices);
error get_edge_num(Object *object, int *edge_num);
error get_edges(Object *object, Edge **edges);
error get_vertices_from_edge(Vertex *vertices, Edge *edge, Vertex *v1, Vertex *v2);

error init_object(Object *object, int vert_num, Vertex* vert_array, int edge_num, Edge* edge_array);
error load_object(char *filename, Object **obj_ptr);
error copy_object(Object **dst, Object *src);
error delete_object(Object *obj_ptr);

error transpose_object(Object *obj_ptr, double dx, double dy, double dz);
error scale_object(Object *obj_ptr, double kx, double ky, double kz);
error rotate_object(Object *obj_ptr, double degrees, Axis axis);

error render_object(Object *obj_ptr, void (*draw_line)(Vertex v1, Vertex v2));

#endif


#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

#define KING 0
#define QUEEN 1
#define ROOK 2
#define BISHOP 3
#define KNIGHT 4
#define PAWN 5
#define UNDEFINED -1

#define DARK 0
#define LIGHT 1

struct Object
{
  Model model;
  GLuint texture_id;
};

static const struct Object EmptyObject;

struct ColorableObject
{
  Model model;
  GLuint texture_id[2];
};

struct Tile
{
  struct Object object;
  vec3 position;
  int is_occupied;
};

struct Board
{
  struct Tile tile[8][8][2];
};

typedef struct Scene
{
  Camera camera;
  Material material;

  struct Board game_board;
  struct Tile *current_tile;
  
  GLuint marble_texture_id[2];
  GLuint skybox_texture_id[6];
  GLuint help_texture_id;

  struct ColorableObject chess_pieces[6];
  struct Object chess_board;
} Scene;

/**
 * Initialize the scene by loading models
 */
void init_scene(Scene *scene);

/**
 * Initialize the lighting of the scene
 */
void init_lighting();

/**
 * Initialize the current material
 */
void init_material(const Material *material);

/**
 * Draw the scene objects
 */
void draw_scene(const Scene *scene);

/**
  * Reset the scene objects
  */
void reset_scene(Scene *scene);

#endif /* SCENE_H */

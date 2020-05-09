#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

enum TYPE
{
  UNDEFINED = -1,
  KING = 0,
  QUEEN = 1,
  ROOK = 2,
  BISHOP = 3,
  KNIGHT = 4,
  PAWN = 5
};

enum COLOR
{
  DARK = 0,
  LIGHT = 1
};

struct Object
{
  Model model;
  GLuint texture_id;
  Material material;
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
  Material material[2];

  struct Board game_board;
  struct Tile *current_tile;
  
  GLuint marble_texture_id[2];
  GLuint skybox_texture_id[6];
  Material wood_material;

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
 * Set the lighting position of the scene
 */
void set_lighting_position();

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

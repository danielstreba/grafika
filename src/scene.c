#include "scene.h"
#include "draw.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_lighting()
{
  float ambient_light[] = {0.8f, 0.8f, 0.8f, 0.8f};
  float diffuse_light[] = {0.9f, 0.9f, 0.9f, 0.9f};
  float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
  float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void init_material(const Material *material)
{
  float ambient_material_color[] = {
      material->ambient.red,
      material->ambient.green,
      material->ambient.blue};

  float diffuse_material_color[] = {
      material->diffuse.red,
      material->diffuse.green,
      material->diffuse.blue};

  float specular_material_color[] = {
      material->specular.red,
      material->specular.green,
      material->specular.blue};

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void init_scene(Scene *scene)
{
  char *skybox_file_list[] =
      {
          "assets/textures/bluecloud_up.jpg",
          "assets/textures/bluecloud_dn.jpg",
          "assets/textures/bluecloud_lf.jpg",
          "assets/textures/bluecloud_rt.jpg",
          "assets/textures/bluecloud_ft.jpg",
          "assets/textures/bluecloud_bk.jpg"};

  load_skybox(scene->skybox_texture_id, skybox_file_list);

  char chess_pieces_object_list[6][3][50] =
      {
          {
              "assets/models/king.obj",
              "assets/textures/king_dark.jpg",
              "assets/textures/king_light.jpg",
          },
          {
              "assets/models/queen.obj",
              "assets/textures/queen_dark.jpg",
              "assets/textures/queen_light.jpg",
          },
          {
              "assets/models/rook.obj",
              "assets/textures/rook_dark.jpg",
              "assets/textures/rook_light.jpg",
          },
          {
              "assets/models/bishop.obj",
              "assets/textures/bishop_dark.jpg",
              "assets/textures/bishop_light.jpg",
          },
          {
              "assets/models/knight.obj",
              "assets/textures/knight_dark.jpg",
              "assets/textures/knight_light.jpg",
          },
          {
              "assets/models/pawn.obj",
              "assets/textures/pawn_dark.jpg",
              "assets/textures/pawn_light.jpg",
          }};

  load_chess_pieces(scene->chess_pieces, chess_pieces_object_list);

  scene->marble_texture_id[DARK] = load_texture("assets/textures/marble_dark.jpg");
  scene->marble_texture_id[LIGHT] = load_texture("assets/textures/marble_light.jpg");

  load_model(&(scene->chess_board.model), "assets/models/board.obj");
  scene->chess_board.texture_id = load_texture("assets/textures/board.jpg");

  scene->material.ambient.red = 1.0f;
  scene->material.ambient.green = 1.0f;
  scene->material.ambient.blue = 1.0f;

  scene->material.diffuse.red = 0.737911f;
  scene->material.diffuse.green = 0.644480f;
  scene->material.diffuse.blue = 0.539480f;

  scene->material.specular.red = 0.5f;
  scene->material.specular.green = 0.5f;
  scene->material.specular.blue = 0.5f;

  scene->material.shininess = 1.0f;

  init_lighting(scene);
  init_material(&(scene->material));

  reset_scene(scene);
}

void draw_scene(const Scene *scene)
{
  init_material(&(scene->material));

  draw_skybox(scene->skybox_texture_id, (vec3){.x = 0.0f, .y = 0.0f, .z = 0.0f}, 500.0f, 500.0f, 500.0f);
  draw_board(scene);
  draw_pieces(scene);
}

void reset_scene(Scene *scene)
{
  int i, j, k;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      for (k = 0; k < 2; k++)
      {
        scene->game_board.tile[i][j][k].object = EmptyObject;

        scene->game_board.tile[i][j][k].position.x = i;
        scene->game_board.tile[i][j][k].position.y = j;
        scene->game_board.tile[i][j][k].position.z = k * 2.0f;

        if (k == 1)
        {
          scene->game_board.tile[i][j][k].is_occupied = FALSE;
          break;
        }

        int color = j < 2 ? LIGHT : DARK;
        int type = UNDEFINED;

        switch (j)
        {
        case 0:
        case 7:
          switch (i)
          {
          case 0:
          case 7:
            type = ROOK;
            break;
          case 1:
          case 6:
            type = KNIGHT;
            break;
          case 2:
          case 5:
            type = BISHOP;
            break;
          case 3:
            type = QUEEN;
            break;
          case 4:
            type = KING;
            break;
          }
          break;
        case 1:
        case 6:
          type = PAWN;
          break;
        }

        if (type != UNDEFINED)
        {
          scene->game_board.tile[i][j][k].object.model = scene->chess_pieces[type].model;
          scene->game_board.tile[i][j][k].object.texture_id = scene->chess_pieces[type].texture_id[color];
          scene->game_board.tile[i][j][k].is_occupied = TRUE;
        }
        else
        {
          scene->game_board.tile[i][j][k].is_occupied = FALSE;
        }
      }
    }
  }

  scene->current_tile = &scene->game_board.tile[0][0][0];
}

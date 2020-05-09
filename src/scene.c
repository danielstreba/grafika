#include "scene.h"
#include "draw.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_lighting()
{
  float ambient_light[] = {0.5f, 0.5f, 0.5f, 1.0f};
  float diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
  float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

  set_lighting_position();
}

void set_lighting_position()
{
  float position[] = {-10.0f, -10.0f, 10.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void init_material(const Material *material)
{
  float ambient_material_color[] = {
      material->ambient.red,
      material->ambient.green,
      material->ambient.blue,
      material->ambient.alpha};

  float diffuse_material_color[] = {
      material->diffuse.red,
      material->diffuse.green,
      material->diffuse.blue,
      material->diffuse.alpha};

  float specular_material_color[] = {
      material->specular.red,
      material->specular.green,
      material->specular.blue,
      material->specular.alpha};

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void init_scene(Scene *scene)
{
  char *skybox_file_list[] =
      {
          "assets/textures/skybox/bluecloud_up.jpg",
          "assets/textures/skybox/bluecloud_dn.jpg",
          "assets/textures/skybox/bluecloud_lf.jpg",
          "assets/textures/skybox/bluecloud_rt.jpg",
          "assets/textures/skybox/bluecloud_ft.jpg",
          "assets/textures/skybox/bluecloud_bk.jpg"};

  char chess_pieces_object_list[6][3][50] =
      {
          {
              "assets/models/figure/king.obj",
              "assets/textures/figure/king_dark.jpg",
              "assets/textures/figure/king_light.jpg",
          },
          {
              "assets/models/figure/queen.obj",
              "assets/textures/figure/queen_dark.jpg",
              "assets/textures/figure/queen_light.jpg",
          },
          {
              "assets/models/figure/rook.obj",
              "assets/textures/figure/rook_dark.jpg",
              "assets/textures/figure/rook_light.jpg",
          },
          {
              "assets/models/figure/bishop.obj",
              "assets/textures/figure/bishop_dark.jpg",
              "assets/textures/figure/bishop_light.jpg",
          },
          {
              "assets/models/figure/knight.obj",
              "assets/textures/figure/knight_dark.jpg",
              "assets/textures/figure/knight_light.jpg",
          },
          {
              "assets/models/figure/pawn.obj",
              "assets/textures/figure/pawn_dark.jpg",
              "assets/textures/figure/pawn_light.jpg",
          }};

  scene->marble_texture_id[DARK] = load_texture("assets/textures/seamless/marble_dark.jpg");
  scene->marble_texture_id[LIGHT] = load_texture("assets/textures/seamless/marble_light.jpg");

  // Marble light material
  scene->material[LIGHT].ambient = (Color){.red = 0.87890625f - 0.25f,
                                           .green = 0.8671875f - 0.25f,
                                           .blue = 0.87890625f - 0.25f,
                                           .alpha = 1.0f};
  scene->material[LIGHT].diffuse = (Color){.red = 0.8f, .green = 0.8f, .blue = 0.8f, .alpha = 1.0f};
  scene->material[LIGHT].specular = (Color){.red = 0.5f, .green = 0.5f, .blue = 0.5f, .alpha = 1.0f};
  scene->material[LIGHT].shininess = 32.0f;

  // Marble dark material
  scene->material[DARK].ambient = (Color){.red = 0.22265625f + 0.25f,
                                          .green = 0.2890625f + 0.25f,
                                          .blue = 0.28515625f + 0.25f,
                                          .alpha = 1.0f};
  scene->material[DARK].diffuse = (Color){.red = 0.18275f, .green = 0.17f, .blue = 0.22525f, .alpha = 1.0f};
  scene->material[DARK].specular = (Color){.red = 0.5f, .green = 0.5f, .blue = 0.5f, .alpha = 1.0f};
  scene->material[DARK].shininess = 32.0f;

  // Wood material
  scene->wood_material.ambient = (Color){.red = 0.39453125f + 0.35f,
                                         .green = 0.2421875f + 0.35f,
                                         .blue = 0.1484375f + 0.35f,
                                         .alpha = 1.0f};
  scene->wood_material.diffuse = (Color){.red = 0.01f, .green = 0.01f, .blue = 0.01f, .alpha = 1.0f};
  scene->wood_material.specular = (Color){.red = 0.5f, .green = 0.5f, .blue = 0.5f, .alpha = 1.0f};
  scene->wood_material.shininess = 32.0f;

  load_skybox(scene->skybox_texture_id, skybox_file_list);
  load_chess_pieces(scene->chess_pieces, chess_pieces_object_list);

  load_model(&(scene->chess_board.model), "assets/models/board.obj");
  scene->chess_board.texture_id = load_texture("assets/textures/board.jpg");
  scene->chess_board.material = scene->material[LIGHT];

  init_lighting(scene);

  reset_scene(scene);
}

void draw_scene(const Scene *scene)
{
  set_lighting_position();

  draw_skybox(scene->skybox_texture_id, (vec3){.x = 0.0f, .y = 0.0f, .z = 0.0f}, 500.0f, 500.0f, 500.0f);
  draw_board(scene);

  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  draw_pieces(scene);
  glDisable(GL_STENCIL_TEST);
  
  draw_board_model(scene);
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
          scene->game_board.tile[i][j][k].object.material = scene->material[color];
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

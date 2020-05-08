#include "load.h"

void load_skybox(GLuint skybox_texture_id[], char *file_list[])
{
  int i;
  for (i = 0; i < 6; i++)
  {
    skybox_texture_id[i] = load_texture(file_list[i]);
  }
}

void load_chess_pieces(struct ColorableObject chess_pieces[], const char chess_pieces_object_list[6][3][50])
{
  int i;
  for (i = 0; i < 6; i++)
  {
    load_model(&(chess_pieces[i].model), chess_pieces_object_list[i][0]);
    chess_pieces[i].texture_id[DARK] = load_texture(chess_pieces_object_list[i][DARK + 1]);
    chess_pieces[i].texture_id[LIGHT] = load_texture(chess_pieces_object_list[i][LIGHT + 1]);
  }
}

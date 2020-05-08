#ifndef LOAD_CHESS_H
#define LOAD_CHESS_H

#include "scene.h"

#include <GL/gl.h>

/**
 * Load the skybox textures
 */
void load_skybox(GLuint skybox_texture_id[], char *file_list[]);

/**
 * Load the chess pieces models and textures
 */
void load_chess_pieces(struct ColorableObject chess_pieces[], const char chess_pieces_object_list[6][3][50]);

#endif /* LOAD_CHESS_H */
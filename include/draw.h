#ifndef DRAW_CHESS_H
#define DRAW_CHESS_H

#include "scene.h"

#include <GL/gl.h>

/**
 * Draw the skybox
 */
void draw_skybox(const GLuint skybox_texture_id[], vec3 position, float width, float height, float length);

/**
 * Draw the chess board
 */
void draw_board(const Scene *scene);

/**
 * Draw the chess board model
 */
void draw_board_model(const Scene *scene);

/**
 * Draw the chess pieces
 */
void draw_pieces(const Scene *scene, const int reflection);

/**
 * Draw the chess board model
 */
void draw_board_model(const Scene *scene);

/**
 * Draw the highlight to currently selected chess piece
 */
void draw_highlight(const vec3 position);

/**
 * Draw the help text
 */
void draw_help(int width, int height);

#endif /* DRAW_CHESS_H */
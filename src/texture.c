#include "texture.h"

#include <SOIL/SOIL.h>

GLuint load_texture(char *filename)
{
  // Fixes most of black lines in the edge of skybox
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  return SOIL_load_OGL_texture(filename, SOIL_LOAD_RGB, 0, 0);
}

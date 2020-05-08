#include "texture.h"

#include <SOIL/SOIL.h>

GLuint load_texture(char *filename)
{
  return SOIL_load_OGL_texture(filename, SOIL_LOAD_RGB, 0, 0);
}

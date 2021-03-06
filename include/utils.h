#ifndef UTILS_H
#define UTILS_H

/**
  * Define pseudo-boolean type
  */
#define FALSE 0
#define TRUE 1

/**
 * GLSL-like three dimensional vector
 */
typedef struct vec3
{
  float x;
  float y;
  float z;
} vec3;

/**
 * Two dimensional vector
 */
typedef struct vec2
{
  float x;
  float y;
} vec2;

/**
 * Color with RGBA components
 */
typedef struct Color
{
  float red;
  float green;
  float blue;
  float alpha;
} Color;

/**
 * Material
 */
typedef struct Material
{
  struct Color ambient;
  struct Color diffuse;
  struct Color specular;
  float shininess;
} Material;

/**
 * Calculates radian from degree
 */
double degree_to_radian(double degree);

#endif /* UTILS_H */

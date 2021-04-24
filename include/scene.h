#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "globals.h"
#endif

#ifndef CLASS_HEADER_MODEL_LOADER
#define CLASS_HEADER_MODEL_LOADER
#include "model_loader.h"
#endif

#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif

class Scene2
{
public:
  static const char *shader_vertex_filepath;
  static const char *shader_fragment_filepath;

  void BuildTrianglesAndAddToVirtualScene();
  void Render();
};

class Scene3
{
private:
  GLint model_uniform;
  GLint render_as_black_uniform;

public:
  static const char *shader_vertex_filepath;
  static const char *shader_fragment_filepath;

  void LoadShaderVariables(GLuint program_id);
  void BuildTrianglesAndAddToVirtualScene();
  void Render();
};

class Scene4
{
private:
  GLint model_uniform;
  GLint view_uniform;
  GLint projection_uniform;
  GLint object_id_uniform;
  GLint render_as_black_uniform;

  GLuint VBO_bezier_line;
  GLfloat bezier_line_coefficients[12];

  int last_frame = -1;

public:
  static const char *shader_vertex_filepath;
  static const char *shader_fragment_filepath;
  static int bezier_samples;

  float t = 0;
  float x;
  float y;
  float z;

  glm::vec3 a = glm::vec3(1.0f, 0.0f, 1.0f);
  glm::vec3 b = glm::vec3(1.0f, 3.0f, 0.0f);
  glm::vec3 c = glm::vec3(-1.0f, -2.0f, 0.0f);
  glm::vec3 d = glm::vec3(-1.0f, 1.0f, -1.0f);

  void CreateBezierLine();
  void LoadShaderVariables(GLuint program_id);
  void BuildTrianglesAndAddToVirtualScene(ObjModel *model);
  void Render();
};

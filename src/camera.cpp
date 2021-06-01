#ifndef CLASS_HEADER_SHADER
#define CLASS_HEADER_SHADER
#include "shader.h"
#endif
#include "camera.h"
using namespace std;
using namespace glm;

void FreeCamera::Enable()
{
  // Computamos a posição da câmera utilizando coordenadas esféricas.  As
  // variáveis g_CameraDistance, g_CameraPhi, e g_CameraTheta são
  // controladas pelo mouse do usuário. Veja as funções CursorPosCallback()
  // e ScrollCallback().
  quaternion.x = 2.0f * cos(phi) * sin(theta);
  quaternion.y = 2.0f * sin(phi);
  quaternion.z = 2.0f * cos(phi) * cos(theta);
  // Abaixo definimos as variáveis que efetivamente definem a câmera virtual.
  // Veja slide 165 do documento "Aula_08_Sistemas_de_Coordenadas.pdf".
  vec4 camera_lookat_l = vec4(quaternion.x + position.x, -quaternion.y + position.y, quaternion.z + position.z, 1.0f); // Ponto "l", para onde a câmera (look-at) estará sempre olhando
  vec4 camera_view_vector = camera_lookat_l - position;                                                                     // Vetor "view", sentido para onde a câmera está virada
  vec4 camera_up_vector = vec4(0.0f, 1.0f, 0.0f, 0.0f);                                                                // Vetor "up" fixado para apontar para o "céu" (eixo Y global)
  vec4 camera_right_vector = crossproduct(camera_view_vector, camera_up_vector);
  if (WPressed)
    position += 0.01f * camera_view_vector;
  if (SPressed)
    position -= 0.01f * camera_view_vector;
  if (APressed)
    position -= 0.01f * camera_right_vector;
  if (DPressed)
    position += 0.01f * camera_right_vector;

  // Computamos a matriz "View" utilizando os parâmetros da câmera para
  // definir o sistema de coordenadas da câmera.  Veja slide 169 do
  // documento "Aula_08_Sistemas_de_Coordenadas.pdf".
  view = Matrix_Camera_View(position, camera_view_vector, camera_up_vector);

  // Agora computamos a matriz de Projeção.
  // Note que, no sistema de coordenadas da câmera, os planos near e far
  // estão no sentido negativo! Veja slides 198-200 do documento
  // "Aula_09_Projecoes.pdf".
  if (g_UsePerspectiveProjection)
  {
    // Projeção Perspectiva.
    // Para definição do field of view (FOV), veja slide 234 do
    // documento "Aula_09_Projecoes.pdf".
    float field_of_view = 3.141592 / 3.0f;
    projection = Matrix_Perspective(field_of_view, g_ScreenRatio, g_FrustumNearPlane, g_FrustumFarPlane);
  }
  else
  {
    // Projeção Ortográfica.
    // Para definição dos valores l, r, b, t ("left", "right", "bottom", "top"),
    // veja slide 243 do documento "Aula_09_Projecoes.pdf".
    // Para simular um "zoom" ortográfico, computamos o valor de "t"
    // utilizando a variável g_CameraDistance.
    float t = 1.5f * g_CameraDistance / 2.5f;
    float b = -t;
    float r = t * g_ScreenRatio;
    float l = -r;
    projection = Matrix_Orthographic(l, r, b, t, g_FrustumNearPlane, g_FrustumFarPlane);
  }

  // Enviamos as matrizes "view" e "projection" para a placa de vídeo
  // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
  // efetivamente aplicadas em todos os pontos.
}

void FreeCamera::UpdateShaderUniforms(Shader shader) {
  shader.setMat4("view", view);
  shader.setMat4("projection", projection);
}
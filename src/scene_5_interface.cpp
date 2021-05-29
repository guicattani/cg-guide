#ifndef CLASS_HEADER_SCENE_GLOBALS
#define CLASS_HEADER_SCENE_GLOBALS
#include "globals_scenes.h"
#endif

#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif

void InterfaceScene5::Show()
{
  ImGui::SliderFloat3("Light Position", (float *)&g_Scene5->lightPos, -3.0f, 3.0f);

  ImGui::Text("Camera");
  ImGui::Text("Position: %f %f %f %f", (float) g_Scene5->camera->position[0],
                                       (float) g_Scene5->camera->position[1],
                                       (float) g_Scene5->camera->position[2],
                                       (float) g_Scene5->camera->position[3]);
}
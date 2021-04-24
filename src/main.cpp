#ifndef CLASS_ADD_HEADERS
#define CLASS_ADD_HEADERS
#include "headers.h"
#endif

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#pragma region[rgba(80, 80, 0, 0.2)] HEADERS
#ifndef CLASS_HEADER_MATRICES
#define CLASS_HEADER_MATRICES
#include "matrices.h"
#endif
#ifndef CLASS_HEADER_INITIALIZE_GLOBALS
#define CLASS_HEADER_INITIALIZE_GLOBALS
#include "initialize_globals.h"
#endif
#ifndef CLASS_HEADER_INITIALIZE_SCENES
#define CLASS_HEADER_INITIALIZE_SCENES
#include "initialize_scenes.h"
#endif
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif
#ifndef CLASS_HEADER_MODEL_LOADER
#define CLASS_HEADER_MODEL_LOADER
#include "model_loader.h"
#endif
#ifndef CLASS_HEADER_SHADERS
#define CLASS_HEADER_SHADERS
#include "shaders.h"
#endif
#ifndef CLASS_HEADER_CAMERA
#define CLASS_HEADER_CAMERA
#include "camera.h"
#endif
#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif
#include "scene_loader.h"
#include "callbacks.h"
#include "opengl_loader.h"

void CreateScene(int scene);
void Update(Interface interface, GLFWwindow *window);

#pragma endregion HEADERS

#pragma region[rgba(10, 10, 10, 0.5)] MAIN
int main(int, char **)
{
  // Setup window
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: glfwInit() failed.\n");
    std::exit(1);
  }

  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  InitializeOpenGL3();

  // Create window with graphics context
  GLFWwindow *window = glfwCreateWindow(800, 800, "TCC - Guilherme", NULL, NULL);
  if (window == NULL)
    return 1;

  SetCallbacks(window);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  bool err = InitializeOpenGLLoader();
  if (err)
  {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return 1;
  }
  PrintGPUInformation();

  //Seleciona a cena 4 como inicial
  g_CurrentScene = 4;
  CreateScene(g_CurrentScene);

  // Habilitamos o Z-buffer. Veja slide 108 do documento "Aula_09_Projecoes.pdf".
  glEnable(GL_DEPTH_TEST);

  // Habilitamos o Backface Culling. Veja slides 22-34 do documento "Aula_13_Clipping_and_Culling.pdf".
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  //Inicializa a Interface (Imgui)
  Interface interface = Interface(true);
  interface.Init(window, glsl_version);

  g_MainCamera = new Camera(g_ProgramId);
#pragma endregion MAIN

#pragma region[rgba(50, 100, 100, 0.2)] DRAW_LOOP
  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(g_ClearColor.x, g_ClearColor.y, g_ClearColor.z, g_ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo os shaders de vértice e fragmentos).
    glUseProgram(g_ProgramId);

    g_MainCamera->Enable();

    if (g_BackfaceCulling != g_BackfaceCullingMonitor)
    {
      if (g_BackfaceCulling)
        glEnable(GL_CULL_FACE);
      else
        glDisable(GL_CULL_FACE);
      g_BackfaceCullingMonitor = g_BackfaceCulling;
    }

    g_NowTime = glfwGetTime();
    g_DeltaTime += (g_NowTime - g_LastTime) / g_LimitFPS;
    g_LastTime = g_NowTime;

    // TODO faz sentido ter um while pra update fisico?
    // while (g_DeltaTime >= 1.0){
    //   // Update(interface, window);   // - Update function
    //   g_Updates++;
    //   g_DeltaTime--;
    // }

    if (g_SceneChanged)
    {
      CreateScene(g_CurrentScene);
      g_SceneChanged = false;
      continue;
    }

    switch (g_CurrentScene)
    {
    case 3:
      g_Scene3->Render();
      break;
    case 4:
      g_Scene4->Render();
      break;
    }

    g_Frames++;
    interface.Show(window);
    glfwSwapBuffers(window);
  }

  interface.CleanUp();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
#pragma endregion DRAW_LOOP

#pragma region[rgba(100, 0, 0, 0.3)] FUNCTIONS
void Update(Interface interface, GLFWwindow *window) {
 //PHYSICS LOGIC GO HERE
}

// TODO idealmente isso fica no scene loader, mas n consegui colocar lá sem ter problemas
void CreateScene(int scene)
{
  CreateProgramForScene(scene);
  switch (scene)
  {
  case 2:
    g_Scene2->BuildTrianglesAndAddToVirtualScene();
    break;
  case 3:
    g_Scene3->LoadShaderVariables(g_ProgramId);
    g_Scene3->BuildTrianglesAndAddToVirtualScene();
    break;
  case 4:
    g_Scene4->LoadShaderVariables(g_ProgramId);
    g_Scene4->CreateBezierLine();

    ObjModel bunnymodel("../data/bunny.obj");
    ComputeNormals(&bunnymodel);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&bunnymodel);

    ObjModel planemodel("../data/plane.obj");
    ComputeNormals(&planemodel);
    g_Scene4->BuildTrianglesAndAddToVirtualScene(&planemodel);
    break;
  }
}
#pragma endregion
#ifndef CLASS_HEADER_INTERFACE
#define CLASS_HEADER_INTERFACE
#include "interface.h"
#endif
Interface::Interface(bool show_demo_window)
{
  m_show_demo_window = show_demo_window;
}

void Interface::Init(GLFWwindow *window, const char *glsl_version)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  Globals::g_Io = &ImGui::GetIO();
  (void)Globals::g_Io;
  //Globals::g_Io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //Globals::g_Io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // LoadFonts();
}

void Interface::Show(GLFWwindow *window)
{
  Start();
  if (m_show_demo_window)
    ImGui::ShowDemoWindow(&m_show_demo_window);


  ImGui::SetNextWindowPos(ImVec2(680, 60), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);

  {
    ImGui::Begin("Details", NULL);

    switch (g_CurrentScene)
    {
    case 1:
      InterfaceScene1::ShowText();
      break;
    case 2:
      InterfaceScene2::ShowText();
      break;
    case 3:
      InterfaceScene3::ShowText();
      break;
    case 4:
      InterfaceScene4::ShowText();
      break;
    case 5:
      InterfaceScene5::ShowText();
      break;
    case 6:
      InterfaceScene6::ShowText();
      break;
    case 7:
      InterfaceScene7::ShowText();
      break;
    }
    ImGui::End();
  }

  ImGuiWindowFlags window_flags = 0;
  window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
  {
    ImGui::Begin("Settings", NULL, window_flags);

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
      if (ImGui::BeginTabItem("Scene"))
      {
        SceneLoader();
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("Camera"))
      {
        CameraSettings();
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("Debug"))
      {
        DebugSettings();
        ImGui::EndTabItem();
      }
      ImGui::EndTabBar();
    }
    ImGui::End();
  }


  // Rendering
  ImGui::Render();

  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Interface::LoadFonts()
{
  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'misc/fonts/README.txt' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //Globals::g_Io.Fonts->AddFontDefault();
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //Globals::g_Io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  //ImFont* font = Globals::g_Io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, Globals::g_Io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);
}

void Interface::CleanUp()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void Interface::Start()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Interface::SceneLoader()
{
  if (ImGui::Button("Scene 1"))
  {
    g_CurrentScene = 1;
    g_SceneChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Scene 2"))
  {
    g_CurrentScene = 2;
    g_SceneChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Scene 3"))
  {
    g_CurrentScene = 3;
    g_SceneChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Scene 4"))
  {
    g_CurrentScene = 4;
    g_SceneChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Scene 5"))
  {
    g_CurrentScene = 5;
    g_SceneChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Scene 6"))
  {
    g_CurrentScene = 6;
    g_SceneChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Scene 7"))
  {
    g_CurrentScene = 7;
    g_SceneChanged = true;
  }

  ImGui::Separator();

  switch (g_CurrentScene)
  {
  case 1:
    InterfaceScene1::ShowControls();
    break;
  case 2:
    InterfaceScene2::ShowControls();
    break;
  case 3:
    InterfaceScene3::ShowControls();
    break;
  case 4:
    InterfaceScene4::ShowControls();
    break;
  case 5:
    InterfaceScene5::ShowControls();
    break;
  case 6:
    InterfaceScene6::ShowControls();
    break;
  case 7:
    InterfaceScene7::ShowControls();
    break;
  }
}

void Interface::CameraSettings()
{
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Separator();

  // Edit 3 floats representing a color
  ImGui::Text("Change Clear Color");
  ImGui::ColorEdit3("clear color", (float *)&g_ClearColor);
  ImGui::Separator();

  ImGui::Checkbox("Perspective Projection", &g_UsePerspectiveProjection);
  ImGui::Checkbox("Backface Culling", &g_BackfaceCulling);
  ImGui::Separator();

  ImGui::Text("Frustum Settings");
  ImGui::SliderFloat("Near Plane", &g_FrustumNearPlane, -100.0f, 100.0f);
  ImGui::SliderFloat("Far Plane", &g_FrustumFarPlane, -100.0f, 100.0f);
  ImGui::Separator();
}

void Interface::DebugSettings()
{
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d vertices, %d indices (%d triangles)", ImGui::GetIO().MetricsRenderVertices, ImGui::GetIO().MetricsRenderIndices, ImGui::GetIO().MetricsRenderIndices / 3);

  ImGui::Separator();

  ImGui::Text("Current scene: %d", g_CurrentScene);
  ImGui::Text("Elapsed frames: %d", g_Frames);
  ImGui::Text("Elapsed updates: %d", g_Updates);

  ImGui::Checkbox("Show demo window", &m_show_demo_window);
}
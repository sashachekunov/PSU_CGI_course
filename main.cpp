#define GL_SILENCE_DEPRECATION


#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include"internal/shader_utils.h"
#include"internal/lb1.h"
#include"internal/lb2.h"
#include"internal/lb3.h"
#include"internal/lb4.h"
#include"internal/lb5.h"


using namespace glm;
using std :: cerr;
using std :: endl;


static void glfw_error_callback(int, const char*);
int init();
void show_lb_menu();
void destroy();


bool is_lb1 = false;
bool is_lb2 = false;
bool is_lb3 = false;
bool is_lb4 = false;
bool is_lb5 = false;

const char* glsl_version;
GLFWwindow* window;
bool err;
static bool selector = true;


int main(void)
{
    if(!init())
        return -1;
    
    /* Setup Dear ImGui context */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    /* Setup Dear ImGui style */
    ImGui::StyleColorsDark();
    /* Setup Platform/Renderer backends */
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    /* Цикл до закрытия окна */
    while (!glfwWindowShouldClose(window))
    {
		/* Clear the screen */
		glClear( GL_COLOR_BUFFER_BIT );
        glClearColor(0.1f, 0.3f, 0.2f, 0.0f);
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		/* GUI */
        show_lb_menu(); 

        if(is_lb1)
            cgi_lb1 :: lb1(window);
        if(is_lb2)
            cgi_lb2 :: lb2(window);
        if(is_lb3)
            cgi_lb3 :: lb3(window);
        if(is_lb4)
            cgi_lb4 :: lb4(window);
        if(is_lb5)
            cgi_lb5 :: lb5(window);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glBindVertexArray(0); 

    destroy();
    return 0;
}


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int init()
{
    /* Ошибки glfw */
    glfwSetErrorCallback(glfw_error_callback);
    /* Инициализация библиотеки */
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;   
    }

    /* Минимальные требуемые версии GL 3.3 + GLSL 330 */
    glsl_version = "#version 330 core";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);  // MacOS
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);  // Windows
    /* Создание окна и контекста OpenGL */
    window = glfwCreateWindow(640, 480, "CGI_CHEKINOV", NULL, NULL);
    if (!window)
    {
        cerr << "Failed to initialize GLFWwindow" << endl;
        glfwTerminate();
        return -1;
    }
    /* Передача текущего окна контексту */
    glfwMakeContextCurrent(window);
    /* Включение вертикальной синхронизации */
    glfwSwapInterval(1);
    /* Initialize OpenGL loader */
    err = gladLoadGL() == 0;
    if (err)
    {
        cerr << "Failed to initialize OpenGL loader! (glad)" << endl;
        return -1;
    }
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(10.0);

    return 1;
}

void show_lb_menu()
{
    /* Start the Dear ImGui frame */
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    /* Окно выбора лабораторных */
    {
        ImGui::Begin("LB selector", &selector);
        if (ImGui::Button("LB#1"))
        {
            if(is_lb2)  cgi_lb2 :: lb2_destroy();
            if(is_lb3)  cgi_lb3 :: lb3_destroy();
            if(is_lb4)  cgi_lb4 :: lb4_destroy();
            if(is_lb5)  cgi_lb5 :: lb5_destroy();
            if(!is_lb1)  cgi_lb1 :: lb1_init();
            is_lb1 = true;
            is_lb2 = false;
            is_lb3 = false;
            is_lb4 = false;
            is_lb5 = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("LB#2"))
        {
            if(is_lb1)  cgi_lb1 :: lb1_destroy();
            if(is_lb3)  cgi_lb3 :: lb3_destroy();
            if(is_lb4)  cgi_lb4 :: lb4_destroy();
            if(is_lb5)  cgi_lb5 :: lb5_destroy();
            if(!is_lb2)  cgi_lb2 :: lb2_init();
            is_lb1 = false;
            is_lb2 = true;
            is_lb3 = false;
            is_lb4 = false;
            is_lb5 = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("LB#3"))
        {
            if(is_lb1)  cgi_lb1 :: lb1_destroy();
            if(is_lb2)  cgi_lb2 :: lb2_destroy();
            if(is_lb4)  cgi_lb4 :: lb4_destroy();
            if(is_lb5)  cgi_lb5 :: lb5_destroy();
            if(!is_lb3)  cgi_lb3 :: lb3_init();
            is_lb1 = false;
            is_lb2 = false;
            is_lb3 = true;
            is_lb4 = false;
            is_lb5 = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("LB#4"))
        {
            if(is_lb1)  cgi_lb1 :: lb1_destroy();
            if(is_lb2)  cgi_lb2 :: lb2_destroy();
            if(is_lb3)  cgi_lb3 :: lb3_destroy();
            if(is_lb5)  cgi_lb5 :: lb5_destroy();
            if(!is_lb4)  cgi_lb4 :: lb4_init();
            is_lb1 = false;
            is_lb2 = false;
            is_lb3 = false;
            is_lb4 = true;
            is_lb5 = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("LB#5"))
        {
            if(is_lb1)  cgi_lb1 :: lb1_destroy();
            if(is_lb2)  cgi_lb2 :: lb2_destroy();
            if(is_lb3)  cgi_lb3 :: lb3_destroy();
            if(is_lb4)  cgi_lb4 :: lb4_destroy();
            if(!is_lb5)  cgi_lb5 :: lb5_init();
            is_lb1 = false;
            is_lb2 = false;
            is_lb3 = false;
            is_lb4 = false;
            is_lb5 = true;
        }
        ImGui::SameLine();
        ImGui::End();
    }
    /* Рендеринг GUI */
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

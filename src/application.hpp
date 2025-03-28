#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "display.hpp"
#include <iostream>

struct Application {
    GLFWwindow *window;

    Application(size_t width, size_t height) : window(nullptr) {
        if (!glfwInit()) {
            std::cerr << "ERR: FAILED TO INITIALIZE GLFW\n";
            exit(EXIT_FAILURE);
        }

        window = glfwCreateWindow(width, height, "Julia Sets", NULL, NULL);

        if (!window) {
            glfwTerminate();
            std::cerr << "ERR: FAILERD TO CREATE A WINDOW\n";
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();
    }

    ~Application() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (window) {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    void run() {
        Display display(1920, 1080);
        glfwMakeContextCurrent(window);
        int it = 50;
        float re = 0.0f, im = 0.0f, radius = 4.0f;

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();
            ImGui::Begin("Julia Sets");
            ImGui::DragInt("Iterations", &it, 1);
            ImGui::DragFloat("Radius", &radius, 0.001f);
            ImGui::DragFloat("Real", &re, 0.0005f);
            ImGui::DragFloat("Imaginary", &im, 0.0005f);
            ImGui::End();

            display.set_iteration(it);
            display.set_radius(radius);
            display.set_constant({re, im});

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            display.draw(width, height);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }
};

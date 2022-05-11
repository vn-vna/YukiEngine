//
// Created by vnvna on 5/9/2022.
//

#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <vector>
#include <cmath>
#include <random>
#include <iostream>
#include <thread>

#include <YukiUtil/YukiRandomMachine.hpp>

int main()
{
  if (!glfwInit())
  {
    return -1;
  }

  std::vector<float> v;
  v.reserve(1'000'000);

  long long sum = 0;

  for (int i = 0; i < 1'0; ++i)
  {
    v.emplace_back(Yuki::Utils::GetRandomMachine()->GetRandomNumber());
    std::cout << v.at(v.size() - 1) << " ";
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* mainWindow       = glfwCreateWindow(100, 100, "", nullptr, nullptr);
  GLFWwindow* offscreenContext = glfwCreateWindow(100, 100, "", nullptr, mainWindow);

  glfwMakeContextCurrent(mainWindow);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  for (int bench = 0; bench < 1; ++bench)
  {
    auto     start = std::chrono::steady_clock::now();
    unsigned vbo;

    for (int i = 0; i < 1; ++i)
    {
      glGenBuffers(1, &vbo);

      std::thread t{[&]() {
        glfwMakeContextCurrent(offscreenContext);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), v.data(), GL_STATIC_DRAW);

        std::cout << "\n";
        float* c = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
        for (int i = 0; i < v.size(); ++i)
        {
          std::cout << c[i] << ' ';
        }
      }};
      t.join();

      glDeleteBuffers(1, &vbo);
    }
    auto dur = std::chrono::steady_clock::now() - start;
    sum += std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    std::cout << "\nTime elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << "\n";
  }

  sum /= 30;
  std::cout << "Avg: " << sum << "\n";

  glfwDestroyWindow(mainWindow);
  glfwTerminate();
  return 0;
}
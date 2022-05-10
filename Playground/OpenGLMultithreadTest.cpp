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

int main()
{
  if (!glfwInit())
  {
    return -1;
  }

  std::vector<float> v;
  v.reserve(1'000'000);
  std::random_device                    rd;
  std::mt19937                          mt(rd());
  std::uniform_real_distribution<float> dist(1.0, 10.0);

  long long sum = 0;

  for (int i = 0; i < 1'000'000; ++i)
  {
    v.emplace_back(dist(mt));
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* mainWindow = glfwCreateWindow(100, 100, "", nullptr, nullptr);
  glfwMakeContextCurrent(mainWindow);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  for (int bench = 0; bench < 30; ++bench)
  {
    auto     start = std::chrono::steady_clock::now();
    unsigned vbo;

    for (int i = 0; i < 1000; ++i)
    {
      glGenBuffers(1, &vbo);

      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), v.data(), GL_STATIC_DRAW);

      glDeleteBuffers(1, &vbo);
    }
    auto dur = std::chrono::steady_clock::now() - start;
    sum += std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << "\n";
  }

  sum /= 30;
  std::cout << "Avg: " << sum << "\n";

  glfwDestroyWindow(mainWindow);
  glfwTerminate();
  return 0;
}
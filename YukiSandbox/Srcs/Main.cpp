#include "YukiCore/YukiApplication.hpp"

#include <glm/mat4x4.hpp>

int main(int, char**)
{
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();

  return 0;
}
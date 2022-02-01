#include "YukiCore/YukiApplication.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiDebug/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int, char**)
{
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();

  return 0;
}
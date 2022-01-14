#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiError.hpp"
#include "YukiCore/YukiLogger.hpp"

int main(int, char**)
{
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();
  return 0;
}
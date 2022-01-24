#include "YukiCore/YukiApplication.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiCore/YukiLogger.hpp"
#include "YukiCore/YukiThread.hpp"

int main(int, char**)
{
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();

  return 0;
}
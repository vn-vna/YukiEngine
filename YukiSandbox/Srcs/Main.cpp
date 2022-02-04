#include "YukiCore/YukiApplication.hpp"

int main(int, char**)
{
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();

  return 0;
}
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiChrono.hpp"
#include "YukiCore/YukiThread.hpp"

int main(int, char**)
{
  std::cout << Yuki::Chrono::DateTimeAsciiString() << "\n";
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();

  return 0;
}
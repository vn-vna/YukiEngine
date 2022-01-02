#include "YukiCore/Application.hpp"
#include "YukiCore/Chrono.hpp"

int main(int, char**)
{
  //std::cout << Yuki::Chrono::DateTimeAsciiString() << "\n";
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();
  return 0;
}
#include "YukiCore/Application.hpp"
#include "YukiCore/Chrono.hpp"

int main(int, char**)
{
  //std::wcout << Yuki::Chrono::DateTimeString() << L"\n";
  AutoType yukiApp = Yuki::Core::CreateYukiApp();
  yukiApp->RunApp();
  return 0;
}
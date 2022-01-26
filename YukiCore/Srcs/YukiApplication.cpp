#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiWindow.hpp"
#include "YukiCore/YukiGraphics.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiDebug/YukiLogger.hpp"

namespace Yuki::Core
{

class YUKIAPI YukiApp : IYukiApp
{
protected:
    SharedPtr<IYukiWindow>        m_pWindow;
    SharedPtr<IYukiGfxControl>    m_pGfxController;
    SharedPtr<IYukiInpControl>    m_pInputController;
    SharedPtr<Debug::IYukiLogger> m_pLogger;
    bool                          m_bAlive;

public:
    YukiApp();
    virtual ~YukiApp() = default;

    SharedPtr<IYukiGfxControl>&    GetGraphicsController() override;
    SharedPtr<IYukiInpControl>&    GetInputController() override;
    SharedPtr<IYukiWindow>&        GetWindow() override;
    SharedPtr<Debug::IYukiLogger>& GetLogger() override;

    void RunApp() override;
    void Create() override;
    void Awake() override;
    void Update() override;
    void Destroy() override;
};

} // namespace Yuki::Core

namespace Yuki::Core
{

SharedPtr<IYukiApp> g_pGlobalApplication(nullptr);

YukiApp::YukiApp()
    : m_bAlive(false),
      m_pGfxController(nullptr),
      m_pInputController(nullptr),
      m_pWindow(nullptr),
      m_pLogger(nullptr)
{
    m_pLogger          = Debug::CreateYukiLogger();
    m_pWindow          = CreateNewWindow();
    m_pInputController = CreateNewInputControl();
}

SharedPtr<IYukiGfxControl>& YukiApp::GetGraphicsController()
{
    return m_pGfxController;
}

SharedPtr<IYukiInpControl>& YukiApp::GetInputController()
{
    return m_pInputController;
}

SharedPtr<Debug::IYukiLogger>& YukiApp::GetLogger()
{
    return m_pLogger;
}

SharedPtr<IYukiWindow>& YukiApp::GetWindow()
{
    return m_pWindow;
}

void YukiApp::RunApp()
{
    try
    {
        Create();
        Awake();
        m_bAlive = true;
        while (m_bAlive)
        {
            Update();
        }
    }
    catch (const Yuki::Debug::YukiError& yer)
    {
        GetLogger()->PushErrorMessage(yer.getErrorMessage());
    }

    try
    {
        Destroy();
    }
    catch (const Yuki::Debug::YukiError& yer)
    {
        GetLogger()->PushErrorMessage(yer.getErrorMessage());
    }
}

void YukiApp::Create()
{
    GetLogger()->Create();
    GetWindow()->Create();
}

void YukiApp::Awake()
{
    GetWindow()->Awake();
}

void YukiApp::Update()
{
    GetWindow()->Update();
    if (GetWindow()->ShouldClose())
    {
        m_bAlive = false;
    }
}

void YukiApp::Destroy()
{
    GetWindow()->Destroy();
    GetLogger()->Destroy();
}

SharedPtr<IYukiApp> CreateYukiApp()
{
    g_pGlobalApplication.reset((IYukiApp*) new YukiApp());
    return g_pGlobalApplication;
}

SharedPtr<IYukiApp> GetYukiApp()
{
    return g_pGlobalApplication;
}

} // namespace Yuki::Core
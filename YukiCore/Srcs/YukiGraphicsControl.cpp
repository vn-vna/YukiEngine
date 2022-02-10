#include "YukiCore/YukiPCH.hpp"
#include "YukiCore/YukiApplication.hpp"
#include "YukiCore/YukiInputCtrl.hpp"
#include "YukiDebug/YukiError.hpp"
#include "YukiComp/YukiMesh.hpp"
#include "YukiComp/YukiCamera.hpp"
#include "YukiUtil/YukiImage.hpp"

#include "PYukiGraphicsControl.hpp"

namespace Yuki::Core
{

YukiGfxControl::YukiGfxControl()
    : m_bCreated(false)
{}

YukiGfxControl::~YukiGfxControl() = default;

void YukiGfxControl::Create()
{
    if (m_bCreated)
    {
        THROW_YUKI_ERROR(Debug::YukiGfxControlRecreationError);
    }
    m_bCreated = true;

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        THROW_YUKI_ERROR(Debug::YukiGladLoadGLLoaderError);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void YukiGfxControl::Awake()
{
    Comp::LoadMeshesFromFile("untitled.blend");
}

void YukiGfxControl::Render()
{
    // Clear screen;
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Use Default FrameBuffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.00f, 0.00f, 0.00f, 1.00f);           // Set clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear frame buffer
}

void YukiGfxControl::Destroy()
{
    if (!m_bCreated)
    {
        THROW_YUKI_ERROR(Debug::YukiGfxControlNotCreatedError);
    }
    m_bCreated = false;
}

SharedPtr<IYukiGfxControl> CreateGraphicsController()
{
    return {(IYukiGfxControl*) new YukiGfxControl, std::default_delete<IYukiGfxControl>()};
}

} // namespace Yuki::Core
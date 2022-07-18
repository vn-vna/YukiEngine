#include "YukiCore/Headers.hpp"
#include "YukiCore/Application.hpp"
#include "YukiCore/WindowManager.hpp"
#include "YukiCore/Input.hpp"
#include "YukiDebug/Errors.hpp"

#include "Private/PCamera.hpp"
#include "Private/PWindow.hpp"

// glm
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

static volatile unsigned g_CXIndex = 0;

namespace Yuki::Comp
{

using Debug::Errors;

YukiCamera::YukiCamera()
    : m_nCamID(g_CXIndex++),
      m_ViewMatrix(1.00f),
      m_ProjectionMatrix(1.00f),
      m_CamPos(0.00f, 0.00f, 0.00f),
      m_CamDirection(0.00f, 0.00f, 1.00f),
      m_CamTop(0.00f, 1.00f, 0.00f),
      m_nFOV(glm::radians(120.00f)),
      m_nAspectRatio(
          (float) YUKI_DEFAULT_WINDOW_WIDTH / YUKI_DEFAULT_WINDOW_HEIGHT
      ),
      m_nNear(0.01f),
      m_nFar(100.00f)
{}

YukiCamera::~YukiCamera() = default;

const Mat4F& YukiCamera::GetCameraViewMatrix() const
{
  return m_ViewMatrix;
}

const Mat4F& YukiCamera::GetCameraProjectionMatrix() const
{
  return m_ProjectionMatrix;
}

const Vec3F& YukiCamera::GetCameraPosition() const
{
  return m_CamPos;
}

const Vec3F& YukiCamera::GetCameraDirection() const
{
  return m_CamDirection;
}

const Vec3F YukiCamera::GetCameraTopAxis() const
{
  return glm::normalize(
      glm::cross(GetCameraHorizontalAxis(), GetCameraVerticalAxis())
  );
}

const Vec3F YukiCamera::GetCameraHorizontalAxis() const
{
  return glm::normalize(glm::cross(GetCameraVerticalAxis(), m_CamTop));
}

const Vec3F YukiCamera::GetCameraVerticalAxis() const
{
  return glm::normalize(m_CamDirection);
}

float YukiCamera::GetFieldOfView() const
{
  return m_nFOV;
}

float YukiCamera::GetViewportAspectRatio() const
{
  return m_nAspectRatio;
}

float YukiCamera::GetNearPerspective() const
{
  return m_nNear;
}

float YukiCamera::GetFarPerspective() const
{
  return m_nFar;
}

void YukiCamera::CameraRotateViewport(float rad)
{
  m_CamTop = glm::rotateZ(m_CamTop, rad);
}

void YukiCamera::CameraRotateDirection(const Vec3F& rotAxis, float rad)
{
  m_CamDirection = glm::rotate(m_CamDirection, rad, rotAxis);
}

void YukiCamera::LookAtPoint(const Vec3F& point)
{
  m_CamDirection = glm::normalize(point - m_CamPos);
}

void YukiCamera::SetCameraDirection(const Vec3F& direction)
{
  m_CamDirection = glm::normalize(direction);
}

void YukiCamera::MoveCamera(const Vec3F& mov)
{
  m_CamPos += mov;
}

void YukiCamera::SetCameraPosition(const Vec3F& position)
{
  m_CamPos = position;
}

void YukiCamera::SetFieldOfView(float fov)
{
  m_nFOV = fov;
}

void YukiCamera::SetViewportAspectRatio(float ratio)
{
  m_nAspectRatio = ratio;
}

void YukiCamera::SetViewportAspectRatio(float width, float height)
{
  m_nAspectRatio = width / height;
}

void YukiCamera::SetNearPerspective(float nNear)
{
  m_nNear = nNear;
}

void YukiCamera::SetFarPerspective(float nFar)
{
  m_nFar = nFar;
}

void YukiCamera::Update()
{
  m_ViewMatrix = glm::lookAt(m_CamPos, m_CamPos + m_CamDirection, m_CamTop);
  m_ProjectionMatrix =
      glm::perspective(m_nFOV, m_nAspectRatio, m_nNear, m_nFar);
}

SharedPtr<ICamera> CreateYukiCamera()
{
  return Core::CreateInterfaceInstance<ICamera, YukiCamera>();
}

} // namespace Yuki::Comp

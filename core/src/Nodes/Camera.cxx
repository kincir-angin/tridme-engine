#include <Nodes/Camera.h>

namespace Tridme {
  Camera::Camera(GLfloat width, GLfloat height, GLfloat nearPlane, 
                GLfloat farPlane, glm::vec3 camPos) {
    /* Camera position */
    m_cameraPosition = camPos;
    m_cameraFront 	 = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp       = glm::vec3(0.0f, 1.0f, 0.0f);

    /* Camera settings */
    zoom		 = 45.0f;
    yaw      = -90.0f;
    pitch    = 0.0f;
    speed    = 2.5f;
    near     = nearPlane;
    far      = farPlane;
    m_width  = width;
    m_height = height;

    /* Update camera matrix */
    Update();
  }

  Camera::~Camera() { }

  glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
  }

  glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(zoom), (float) m_width / (float) m_height, near, far);
  }

  glm::vec3 Camera::getCameraPosition() {
    return m_cameraPosition;
  }

  void Camera::SetPosition(glm::vec3 new_pos) {
    m_cameraPosition = new_pos;
    Update();
  }

  void Camera::Update() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_cameraFront = glm::normalize(front);
    // also re-calculate the Right and Up vector
    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
    m_cameraUp    = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
  }

  void Camera::Move(GLFWwindow* window, float dt) {
    float camSpeed = speed * dt;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      m_cameraPosition += camSpeed * m_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      m_cameraPosition -= camSpeed * m_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * camSpeed;

    Update();
  }

  void Camera::EulerAngle(double xpos, double ypos) {
    if (m_first_mouse) {
      m_last_x = xpos;
      m_last_y = ypos;
      m_first_mouse = false;
    }

    float xoffset = xpos - m_last_x;
    float yoffset = m_last_y - ypos; 
    m_last_x = xpos;
    m_last_y = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;

    Update();
  }
}
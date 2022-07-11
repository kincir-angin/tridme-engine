#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glad/include/glad.h>
#include <glfw/include/GLFW/glfw3.h>
#include <logging.h>
#include <iostream>
#include <event.h>

namespace Tridme {
  class Window {
    public: 
      Window(int w, int h, const char* t);
      ~Window();

      Window& window();

      inline void Close() { glfwSetWindowShouldClose(m_window, true); };
      inline GLFWwindow* GetInstance() { return m_window; }
      void Run();

      /* Event Handlers */
      static void KeyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);

    private:
      int m_width, m_height;
      const char* m_title;
      GLFWwindow* m_window;
      bool m_running = true;
  };
}

#endif // __WINDOW_H__
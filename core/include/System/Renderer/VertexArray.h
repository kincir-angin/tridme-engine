#ifndef _VERTEX_ARRAY_H
#define _VERTEX_ARRAY_H
#include <System/Renderer/VertexBuffer.h>
#include <error.h>

namespace Tridme {
  class VertexBufferLayout;

  class VertexArray {
    private:
      unsigned int m_renderer_id;
    public:
      VertexArray();
      ~VertexArray();

      void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

      void Bind() const;
      void Unbind() const;
  };
}

#endif
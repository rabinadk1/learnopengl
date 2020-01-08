#include <iostream>

#include "Texture.hpp"
#include "stb_image.h"

Texture::Texture(const char *path)
    : m_Filepath(path)
{
  glGenTextures(1, &m_RendererID);
  glBindTexture(GL_TEXTURE_2D, m_RendererID);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  /*
  load and generate the texture
  NOTE: Last argument to force the number of channels, **0 to not force**
  */

  unsigned char *m_LocalBuffer = stbi_load(path, &m_Width, &m_Height, &m_ChannelNumber, 0);
  if (m_LocalBuffer)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(m_LocalBuffer);
  }
  else
    std::cerr << "Failed to load texture from file " << path << std::endl;

  // Unbinding texture
  Unbind();
}

// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#include "Cubism.hpp"

#include <memory>
#include <cmath>
#include <string>

// Used by base64 decoding functions.
#include <cctype>
#include <utility>

#include "CubismFont.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#ifndef GCubismContext
std::unique_ptr<Cubism::Context> GCubismContext = nullptr;
#endif

namespace
{
  // TODO(Fouad): Check if the copyright notice here will suffice.
  // base64 decoding functions:
  
  // Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
  // Official repository: https://github.com/boostorg/beast
  namespace Base64
  {
    inline signed char const* get_inverse()
    {
      static signed char constexpr tab[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 
      };
      return &tab[0];
    }
    
    inline std::size_t constexpr decoded_size(std::size_t n) {  return n / 4 * 3; }
    
    template<class = void>
    std::pair<std::size_t, std::size_t> decode(void* dest, char const* src, std::size_t len)
    {
      char* out = static_cast<char*>(dest);
      auto in = reinterpret_cast<unsigned char const*>(src);
      unsigned char c3[3], c4[4];
      int i = 0;
      int j = 0;

      auto const inverse = get_inverse();

      while(len-- && *in != '=')
      {
        auto const v = inverse[*in];
        if(v == -1) break;
        ++in;
        c4[i] = v;
        if(++i == 4)
        {
          c3[0] =  (c4[0]        << 2) + ((c4[1] & 0x30) >> 4);
          c3[1] = ((c4[1] & 0xf) << 4) + ((c4[2] & 0x3c) >> 2);
          c3[2] = ((c4[2] & 0x3) << 6) +   c4[3];

          for(i = 0; i < 3; i++)
            *out++ = c3[i];
          i = 0;
        }
      }

      if(i)
      {
        c3[0] = ( c4[0]        << 2) + ((c4[1] & 0x30) >> 4);
        c3[1] = ((c4[1] & 0xf) << 4) + ((c4[2] & 0x3c) >> 2);
        c3[2] = ((c4[2] & 0x3) << 6) +   c4[3];

        for(j = 0; j < i - 1; j++)
          *out++ = c3[j];
      }
      return { out - static_cast<char*>(dest),in - reinterpret_cast<unsigned char const*>(src) };
    }
  }
}

namespace Cubism
{
  class Context
  {
  public:
    explicit Context(const IO& _io, unsigned int fontResolution = 512)
    : io(_io), drawList(std::make_unique<DrawList>()), mFontData()
    {
      mFontData.resolution = fontResolution;
      
      const unsigned int pixelCount = fontResolution * fontResolution;
      mFontData.textureData.resize(pixelCount);
      
      const int startGlyph = kGlyphRanges[0];
      const int glyphCount = kGlyphRanges[1] - startGlyph;
      mFontData.glyphDescriptors.resize(glyphCount);
      
      std::vector<std::uint8_t> fontBuffer;
      fontBuffer.resize(Base64::decoded_size(kFontDataAsBase64.size()));
      auto const result = Base64::decode(fontBuffer.data(), kFontDataAsBase64.data(), kFontDataAsBase64.size());
      fontBuffer.resize(result.first);
      
      stbtt_BakeFontBitmap(fontBuffer.data(),
                           0,
                           32.0f,
                           mFontData.textureData.data(),
                           fontResolution,
                           fontResolution,
                           startGlyph,
                           glyphCount,
                           reinterpret_cast<stbtt_bakedchar*>(mFontData.glyphDescriptors.data())); // Or we can avoid this and be more explicit.
    }
    
    IO io;
    std::unique_ptr<DrawList> drawList;
    FontData mFontData;
    
  private:
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
  };

  void createContext(const IO& io)
  {
    CUBISM_ASSERT_MSG(!GCubismContext, "[Cubism]: You already called createContex.");
    GCubismContext = std::make_unique<Context>(io);
  }

  void destroyContext()
  {
    GCubismContext.reset(nullptr);
    GCubismContext = nullptr;
  }

  IO& getIO()
  {
    CUBISM_ASSERT_MSG(GCubismContext, "[Cubism]: You forgot to call createContext.");
    return GCubismContext->io;
  }
  
  const FontData& getFontData()
  {
    CUBISM_ASSERT_MSG(GCubismContext, "[Cubism]: You forgot to call createContext.");
    return GCubismContext->mFontData;
  }

  void newFrame()
  {
    CUBISM_ASSERT_MSG(GCubismContext, "[Cubism]: You forgot to call createContext.");
    GCubismContext->drawList.reset(new DrawList);
  }
  
  void render()
  {
    CUBISM_ASSERT_MSG(GCubismContext, "[Cubism]: You forgot to call createContext.");
    GCubismContext->drawList->optimise();
  }

  DrawList* getDrawList()
  {
    CUBISM_ASSERT_MSG(GCubismContext, "[Cubism]: You forgot to call createContext.");
    return GCubismContext->drawList.get();
  }
  
  DrawList::DrawList() : mDrawCommands(), mVertices(), mIndices(), mMatrixStack()
  {
    // Add an identity matrix as base.
    mMatrixStack.emplace_back(1);
  }

  void DrawList::addLine(const Vec2& p1, const Vec2& p2, Color color, float thickness)
  {
    const std::vector<Vec2> points { p1, p2 };
    addPolyline(points, color, false, thickness);
  }
  
  void DrawList::addTriangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, Color color, float thickness)
  {
    const std::vector<Vec2> points { p1, p2, p3 };
    addPolyline(points, color, true, thickness);
  }
  
  void DrawList::addTriangleFilled(const Vec2& p1, const Vec2& p2, const Vec2& p3, Color color)
  {
    mDrawCommands.emplace_back();
    auto& cmd = mDrawCommands.back();
    cmd.elementCount = 3;
    cmd.indexOffset = mIndices.size();
    cmd.matrixIndex = getMatrixIndex();
    mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(2);
    mVertices.emplace_back(p1, color); mVertices.emplace_back(p2, color); mVertices.emplace_back(p3, color);
  }
  
  void DrawList::addRectangle(const Vec2& position, const Vec2& size, Color color, float thickness)
  {
    const Vec2 p1 = position;
    const Vec2 p2 = p1 + size.x * kRight;
    const Vec2 p3 = p2 + size.y * kUp;
    const Vec2 p4 = p1 + size.y * kUp;
    const std::vector<Vec2> points { p1, p2, p3, p4 };
    addPolyline(points, color, true, thickness);
  }
  
  void DrawList::addRectangleFilled(const Vec2& position, const Vec2& size, Color color)
  {
    const Vec2 p1 = position;
    const Vec2 p2 = p1 + size.x * kRight;
    const Vec2 p3 = p2 + size.y * kUp;
    const Vec2 p4 = p1 + size.y * kUp;
    
    mDrawCommands.emplace_back();
    auto& cmd = mDrawCommands.back();
    cmd.elementCount = 6;
    cmd.indexOffset = mIndices.size();
    cmd.matrixIndex = getMatrixIndex();
    
    unsigned int vertexOffset = mVertices.size();

    mIndices.push_back(vertexOffset); mIndices.push_back(vertexOffset + 1); mIndices.push_back(vertexOffset + 2);
    mIndices.push_back(vertexOffset); mIndices.push_back(vertexOffset + 2); mIndices.push_back(vertexOffset + 3);
    
    mVertices.emplace_back(p1, color);
    mVertices.emplace_back(p2, color);
    mVertices.emplace_back(p3, color);
    mVertices.emplace_back(p4, color);
  }
  
  void DrawList::addQuad(const Vec2& position, float size, Color color, float thickness)
  {
    const Vec2 dimension = size * kOne;
    addRectangle(position, dimension, color, thickness);
  }
  
  void DrawList::addQuadFilled(const Vec2& position, float size, Color color)
  {
    addRectangleFilled(position, Cubism::Vec2 {size}, color);
  }
  
  void DrawList::addNGon(const Vec2& position,
                         float radius,
                         Color color,
                         unsigned short n,
                         float thickness)
  {
    addEllipse(position, Vec2 {radius}, color, n, thickness);
  }
  
  void DrawList::addNGonFilled(const Vec2& position,
                               float radius,
                               Color color,
                               unsigned short n)
  {
    addEllipseFilled(position, Vec2 {radius}, color, n);
  }
  
  void DrawList::addCircle(const Vec2& position,
                           float radius,
                           Color color,
                           unsigned short segments,
                           float thickness)
  {
    CUBISM_ASSERT_MSG(segments > 2, "[Cubism]: Too few segments given.");
    addNGon(position, radius, color, segments, thickness);
  }
  
  void DrawList::addCircleFilled(const Vec2& position, float radius, Color color, unsigned short segments)
  {
    CUBISM_ASSERT_MSG(segments > 2, "[Cubism]: Too few segments given.");
    addNGonFilled(position, radius, color, segments);
  }
  
  void DrawList::addEllipse(const Vec2& position,
                            const Vec2& size,
                            Color color,
                            unsigned short segments,
                            float thickness)
  {
    CUBISM_ASSERT_MSG(segments > 2, "[Cubism]: Too few segments given.");
    std::vector<Vec2> points;
    points.reserve(segments);
    float step = kTwoPi / segments;
    const float rx = size.x;
    const float ry = size.y;
    for (auto i = 0; i < segments; ++i)
    {
      const float angle = i * step;
      const float x = rx * std::cosf(angle) + position.x;
      const float y = ry * std::sinf(angle) + position.y;
      points.emplace_back(x, y);
    }
    addPolyline(points, color, true, thickness);
  }
  
  void DrawList::addEllipseFilled(const Vec2& position,
                                  const Vec2& size,
                                  Color color,
                                  unsigned short segments)
  {
    CUBISM_ASSERT_MSG(segments > 2, "[Cubism]: Too few segments given.");
    mDrawCommands.emplace_back();
    auto& cmd = mDrawCommands.back();
    cmd.elementCount = segments * 3;
    cmd.indexOffset = mIndices.size();
    cmd.matrixIndex = getMatrixIndex();

    mVertices.emplace_back(position, color);
    const unsigned short vertexOffset = mVertices.size();
    
    const float rx = size.x;
    const float ry = size.y;
    float step = kTwoPi / segments;
    for (auto i = 0; i < segments; ++i)
    {
      const float angle = i * step;
      const float x = rx * std::cosf(angle) + position.x;
      const float y = ry * std::sinf(angle) + position.y;
      mVertices.emplace_back(Cubism::Vec2 {x, y}, color);
      
      mIndices.push_back(vertexOffset);
      mIndices.push_back(vertexOffset + i);
      mIndices.push_back(vertexOffset + ((i + 1) % segments));
    }
  }

  void DrawList::addPolyline(const std::vector<Vec2>& points, Color color, bool closed, float thickness)
  {
    const int size = points.size();

    int count = size;
    if (count < 2) return;

    if (!closed) --count;

    const int indexCount = count * 6;
    
    mDrawCommands.emplace_back();
    auto& cmd = mDrawCommands.back();
    cmd.elementCount = indexCount;
    cmd.indexOffset = mIndices.size();
    cmd.matrixIndex = getMatrixIndex();

    unsigned int vertexOffset = mVertices.size();
    for (int i1 = 0; i1 < count; i1++)
    {
      const int i2 = (i1 + 1) == size ? 0 : i1 + 1;
      const Vec2& p1 = points[i1];
      const Vec2& p2 = points[i2];

      Vec2 len = p2 - p1;
      CUBISM_NORMALIZE_AVOID_ZERO_D(len);
      len *= (thickness * 0.5f);

      const Vec2 r1 = Vec2(len.y, -len.x);
      const Vec2 r2 = Vec2(-len.y, len.x);

      mIndices.push_back(vertexOffset); mIndices.push_back(vertexOffset + 1); mIndices.push_back(vertexOffset + 2);
      mIndices.push_back(vertexOffset); mIndices.push_back(vertexOffset + 2); mIndices.push_back(vertexOffset + 3);

      mVertices.emplace_back(p1 + r1, color);
      mVertices.emplace_back(p2 + r1, color);
      mVertices.emplace_back(p2 + r2, color);
      mVertices.emplace_back(p1 + r2, color);

      vertexOffset += 4;
    }
  }
  
  void DrawList::addText(const std::string& text, const Vec2& position, Color color, const Vec2& offset, float size)
  {
    mDrawCommands.emplace_back();
    auto& cmd = mDrawCommands.back();
    cmd.isText = true;
    cmd.indexOffset = mIndices.size();
    cmd.matrixIndex = getMatrixIndex();
    
    const FontData fontData = Cubism::getFontData();
    const std::uint8_t firstChar = kGlyphRanges[0];
    const std::uint8_t lastChar = kGlyphRanges[1];
    
    const float uvStep = 1.0f / fontData.resolution;
    
    float x = position.x + offset.x;
    float y = position.y - offset.y;
    
    int quadCount = 0;
    
    for (char c : text)
    {
      if (c >= firstChar && c <= lastChar)
      {
        GlyphDescriptor d = fontData.glyphDescriptors[c - firstChar];
        const Vec2 db = Cubism::Vec2 {static_cast<float>(d.x1 - d.x0), static_cast<float>(d.y1 - d.y0)} * size;
        
        const Vec2 p1 = Cubism::Vec2 {x + d.xOff, y};
        const Vec2 p2 = p1 + db.x * kRight;
        const Vec2 p3 = p2 + db.y * kUp;
        const Vec2 p4 = p1 + db.y * kUp;
        
        const unsigned int vertexOffset = mVertices.size();
        mIndices.push_back(vertexOffset); mIndices.push_back(vertexOffset + 1); mIndices.push_back(vertexOffset + 2);
        mIndices.push_back(vertexOffset); mIndices.push_back(vertexOffset + 2); mIndices.push_back(vertexOffset + 3);
        
        const Vec2 uv4 {d.x0 * uvStep, d.y0 * uvStep};
        const Vec2 uv3 {d.x1 * uvStep, d.y0 * uvStep};
        const Vec2 uv2 {d.x1 * uvStep, d.y1 * uvStep};
        const Vec2 uv1 {d.x0 * uvStep, d.y1 * uvStep};

        mVertices.emplace_back(p1, color, uv1);
        mVertices.emplace_back(p2, color, uv2);
        mVertices.emplace_back(p3, color, uv3);
        mVertices.emplace_back(p4, color, uv4);
        ++quadCount;
        
        x += d.xAdvance * size;
      }
    }
    cmd.elementCount = quadCount * 6;
  }

  void DrawList::optimise()
  {
    DrawCommndsList newCmds; newCmds.emplace_back(mDrawCommands[0]); newCmds.back().elementCount = 0;
    for (const auto& cmd : mDrawCommands)
    {
      const bool cmdTypeChanged = cmd.isText != newCmds.back().isText;
      const bool cmdMatrixIndexChanged = cmd.matrixIndex != newCmds.back().matrixIndex;
      if (cmdTypeChanged || cmdMatrixIndexChanged)
        newCmds.emplace_back(cmd);
      else
        newCmds.back().elementCount += cmd.elementCount;
    }
    mDrawCommands = newCmds;
  }
}

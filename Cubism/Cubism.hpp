// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#pragma once

#ifndef CUBISM_ASSERT
#include <cassert>
#define CUBISM_ASSERT(expr) assert(expr)
#define CUBISM_ASSERT_MSG(expr, msg) assert((expr) && (msg))
#endif

#define CUBISM_UNUSED(expr) ((void)expr)
#define CUBISM_NORMALIZE_AVOID_ZERO_D(v) { const float m = Vec2::mag(v); if (m > 0.0f) v /= m; }

#define FPS_SAMPLE_COUNT 5

#include <vector>
#include <cmath>
#include <cstdint>

namespace Cubism
{
  class Context;
  struct Vec2
  {
    float x; float y;
    explicit Vec2(float t = 0.0f) : x(t), y(t) {}
    Vec2(float _x, float _y) : x(_x), y(_y) {}
    inline float& operator[](unsigned int i) { return ((&x)[i]); }
    inline const float& operator[](unsigned int i) const { return ((&x)[i]); }
    friend inline Vec2 operator+(const Vec2& lhs, const Vec2& rhs) { return Vec2(lhs.x + rhs.x, lhs.y + rhs.y); }
    inline Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    friend inline Vec2 operator-(const Vec2& v) { return Vec2(-v.x, -v.y); }
    friend inline Vec2 operator-(const Vec2& lhs, const Vec2& rhs) { return Vec2(lhs.x - rhs.x, lhs.y - rhs.y); }
    inline Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
    friend inline Vec2 operator*(float t, const Vec2& rhs) { return Vec2(rhs.x * t, rhs.y * t); }
    friend inline Vec2 operator*(const Vec2& lhs, float t) { return t * lhs; }
    inline Vec2& operator*=(float t) { x *= t; y *= t; return *this; }
    friend inline Vec2 operator*(const Vec2& lhs, const Vec2& rhs) { return Vec2(lhs.x * rhs.x, lhs.y * rhs.y); }
    inline Vec2& operator*=(const Vec2& v) { x *= v.x; y *= v.y; return *this; }
    friend inline Vec2 operator/(const Vec2& lhs, float t) { const float d = 1.0f / t; return Vec2(lhs.x * d, lhs.y * d); }
    inline Vec2& operator/=(float t) { const float d = 1.0f / t; return *this *= d; }
    static float mag(const Vec2& v) { return std::sqrtf(v.x * v.x + v.y * v.y); }
  };
  
  struct Vec3
  {
    float x; float y; float z;
    explicit Vec3(float t = 0.0f) : x(t), y(t), z(t) {}
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vec3(const Vec2& v) : x(v.x), y(v.y), z(0.0f) {}
    inline float& operator[](unsigned int i) { return ((&x)[i]); }
    inline const float& operator[](unsigned int i) const { return ((&x)[i]); }
    friend inline Vec3 operator+(const Vec3& lhs, const Vec3& rhs) { return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
    inline Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    friend inline Vec3 operator-(const Vec3& v) { return Vec3(-v.x, -v.y, -v.z); }
    friend inline Vec3 operator-(const Vec3& lhs, const Vec3& rhs) { return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
    inline Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    friend inline Vec3 operator*(float t, const Vec3& rhs) { return Vec3(rhs.x * t, rhs.y * t, rhs.z * t); }
    friend inline Vec3 operator*(const Vec3& lhs, float t) { return t * lhs; }
    inline Vec3& operator*=(float t) { x *= t; y *= t; z *= t; return *this; }
    friend inline Vec3 operator*(const Vec3& lhs, const Vec3& rhs) { return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
    inline Vec3& operator*=(const Vec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    friend inline Vec3 operator/(const Vec3& lhs, float t) { const float d = 1.0f / t; return Vec3(lhs.x * d, lhs.y * d, lhs.z * d); }
    inline Vec3& operator/=(float t) { const float d = 1.0f / t; return *this *= d; }
    static float mag(const Vec3& v) { return std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
  };
  
  struct Vec4
  {
    float x, y, z, w;
    explicit Vec4(float t = 0) : x(t), y(t), z(t), w(t) {}
    Vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    inline float& operator[](unsigned int i) { return ((&x)[i]); }
    inline const float& operator[](unsigned int i) const { return ((&x)[i]); }
    friend inline Vec4 operator+(const Vec4& lhs, const Vec4& rhs) { return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
    inline Vec4& operator+=(const Vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
    friend inline Vec4 operator-(const Vec4& v) { return Vec4(-v.x, -v.y, -v.z, -v.w); }
    friend inline Vec4 operator-(const Vec4& lhs, const Vec4& rhs) { return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
    inline Vec4& operator-=(const Vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
    friend inline Vec4 operator*(const float t, const Vec4& rhs) { return rhs * t; }
    friend inline Vec4 operator*(const Vec4& lhs, const float t) { return Vec4(lhs.x * t, lhs.y * t, lhs.z * t, lhs.w * t); }
    inline Vec4& operator*=(const float t) { x *= t; y *= t; z *= t; w *= t; return *this; }
    friend inline Vec4 operator*(const Vec4& lhs, const Vec4& rhs) { return Vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
    inline Vec4& operator*=(const Vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
    friend inline Vec4 operator/(const Vec4& lhs, const float t) { const auto d = 1.0f / t; return Vec4(lhs.x * d, lhs.y * d, lhs.z * d, lhs.w * d); }
    inline Vec4& operator/=(const float t) { const auto d = 1.0f / t; return *this *= d; }
    static float mag(const Vec4& v) { return std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
  };
  
  struct Mat4
  {
    float d[4][4];
    
    Mat4() = default;
    
    explicit Mat4(float t)
    {
      d[0][0] = t; d[0][1] = 0; d[0][2] = 0; d[0][3] = 0;
      d[1][0] = 0; d[1][1] = t; d[1][2] = 0; d[1][3] = 0;
      d[2][0] = 0; d[2][1] = 0; d[2][2] = t; d[2][3] = 0;
      d[3][0] = 0; d[3][1] = 0; d[3][2] = 0; d[3][3] = t;
    }
    
    Mat4(const Vec4& v1, const Vec4& v2, const Vec4& v3, const Vec4& v4)
    {
      d[0][0] = v1.x; d[0][1] = v1.y; d[0][2] = v1.z; d[0][3] = v1.w;
      d[1][0] = v2.x; d[1][1] = v2.y; d[1][2] = v2.z; d[1][3] = v2.w;
      d[2][0] = v3.x; d[2][1] = v3.y; d[2][2] = v3.z; d[2][3] = v3.w;
      d[3][0] = v4.x; d[3][1] = v4.y; d[3][2] = v4.z; d[3][3] = v4.w;
    }
    
    Mat4(float a00, float a01, float a02, float a03,
         float a10, float a11, float a12, float a13,
         float a20, float a21, float a22, float a23,
         float a30, float a31, float a32, float a33)
    {
      d[0][0] = a00; d[0][1] = a10; d[0][2] = a20; d[0][3] = a30;
      d[1][0] = a01; d[1][1] = a11; d[1][2] = a21; d[1][3] = a31;
      d[2][0] = a02; d[2][1] = a12; d[2][2] = a22; d[2][3] = a32;
      d[3][0] = a03; d[3][1] = a13; d[3][2] = a23; d[3][3] = a33;
    }
    
    Mat4(const Mat4& other)
    {
      d[0][0] = other(0, 0); d[1][0] = other(0, 1); d[2][0] = other(0, 2); d[3][0] = other(0, 3);
      d[0][1] = other(1, 0); d[1][1] = other(1, 1); d[2][1] = other(1, 2); d[3][1] = other(1, 3);
      d[0][2] = other(2, 0); d[1][2] = other(2, 1); d[2][2] = other(2, 2); d[3][2] = other(2, 3);
      d[0][3] = other(3, 0); d[1][3] = other(3, 1); d[2][3] = other(3, 2); d[3][3] = other(3, 3);
    }
    
    Mat4& operator=(const Mat4& other)
    {
      if (this != &other)
      {
        d[0][0] = other(0, 0); d[1][0] = other(0, 1); d[2][0] = other(0, 2); d[3][0] = other(0, 3);
        d[0][1] = other(1, 0); d[1][1] = other(1, 1); d[2][1] = other(1, 2); d[3][1] = other(1, 3);
        d[0][2] = other(2, 0); d[1][2] = other(2, 1); d[2][2] = other(2, 2); d[3][2] = other(2, 3);
        d[0][3] = other(3, 0); d[1][3] = other(3, 1); d[2][3] = other(3, 2); d[3][3] = other(3, 3);
      }
      return *this;
    }
    
    inline Vec4& operator[](unsigned int column) { return *reinterpret_cast<Vec4*>(d[column]); }
    inline const Vec4& operator[](unsigned int column) const { return *reinterpret_cast<const Vec4*>(d[column]); }
    inline float& operator()(unsigned int i, unsigned int j) { return d[j][i]; }
    inline const float& operator()(unsigned int i, unsigned int j) const { return d[j][i]; }
    friend inline Mat4 operator+(const Mat4& lhs, const Mat4& rhs) { return Mat4(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]); }
    
    inline Mat4& operator+=(const Mat4& m)
    {
      d[0][0] += m(0, 0); d[1][0] += m(0, 1); d[2][0] += m(0, 2); d[3][0] += m(0, 3);
      d[0][1] += m(1, 0); d[1][1] += m(1, 1); d[2][1] += m(1, 2); d[3][1] += m(1, 3);
      d[0][2] += m(2, 0); d[1][2] += m(2, 1); d[2][2] += m(2, 2); d[3][2] += m(2, 3);
      d[0][3] += m(3, 0); d[1][3] += m(3, 1); d[2][3] += m(3, 2); d[3][3] += m(3, 3);
      return *this;
    }
    
    inline Mat4 operator-() const
    {
      return Mat4(-d[0][0], -d[1][0], -d[2][0], -d[3][0],
                  -d[0][1], -d[1][1], -d[2][1], -d[3][1],
                  -d[0][2], -d[1][2], -d[2][2], -d[3][2],
                  -d[0][3], -d[1][3], -d[2][3], -d[3][3]);
    }
    
    friend inline Mat4 operator-(const Mat4& lhs, const Mat4& rhs) { return Mat4(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]); }
    
    inline Mat4& operator-=(const Mat4& m)
    {
      d[0][0] -= m(0, 0); d[1][0] -= m(0, 1); d[2][0] -= m(0, 2); d[3][0] -= m(0, 3);
      d[0][1] -= m(1, 0); d[1][1] -= m(1, 1); d[2][1] -= m(1, 2); d[3][1] -= m(1, 3);
      d[0][2] -= m(2, 0); d[1][2] -= m(2, 1); d[2][2] -= m(2, 2); d[3][2] -= m(2, 3);
      d[0][3] -= m(3, 0); d[1][3] -= m(3, 1); d[2][3] -= m(3, 2); d[3][3] -= m(3, 3);
      return *this;
    }
    
    inline Mat4 operator*(const float t) const
    {
      return Mat4(d[0][0] * t, d[1][0] * t, d[2][0] * t, d[3][0] * t,
                  d[0][1] * t, d[1][1] * t, d[2][1] * t, d[3][1] * t,
                  d[0][2] * t, d[1][2] * t, d[2][2] * t, d[3][2] * t,
                  d[0][3] * t, d[1][3] * t, d[2][3] * t, d[3][3] * t);
    }
    
    friend inline Mat4 operator*(const float t, const Mat4& m) { return m * t; }
    
    inline Mat4& operator*=(const float t)
    {
      d[0][0] *= t; d[1][0] *= t; d[2][0] *= t; d[3][0] *= t;
      d[0][1] *= t; d[1][1] *= t; d[2][1] *= t; d[3][1] *= t;
      d[0][2] *= t; d[1][2] *= t; d[2][2] *= t; d[3][2] *= t;
      d[0][3] *= t; d[1][3] *= t; d[2][3] *= t; d[3][3] *= t;
      return *this;
    }
    
    inline Vec4 operator*(const Vec4& v) const
    {
      return Vec4(d[0][0] * v.x + d[1][0] * v.y + d[2][0] * v.z + d[3][0] * v.w,
                  d[0][1] * v.x + d[1][1] * v.y + d[2][1] * v.z + d[3][1] * v.w,
                  d[0][2] * v.x + d[1][2] * v.y + d[2][2] * v.z + d[3][2] * v.w,
                  d[0][3] * v.x + d[1][3] * v.y + d[2][3] * v.z + d[3][3] * v.w);
    }
    
    friend inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
    {
      // TODO(Fouad): Consider unrolling?
      Mat4 result;
      for (unsigned int i = 0; i < 4; ++i)
      {
        for (unsigned int j = 0; j < 4; ++j)
        {
          result[j][i] =
          lhs(i, 0) * rhs(0, j) + lhs(i, 1) * rhs(1, j) + lhs(i, 2) * rhs(2, j) + lhs(i, 3) * rhs(3, j);
        }
      }
      return result;
    }
    
    inline Mat4 operator/(const float t) const { const auto d = 1.0f / t; return *this * d; }
    friend inline Mat4 operator/(const float t, const Mat4& m) { return m * t; }
    inline Mat4& operator/=(const float t) { const auto d = 1.0f / t; return *this *= d; }
    inline float* data() { return d[0]; }
    inline const float* data() const { return d[0]; }
  };
  
  constexpr double kPi = 3.1415926535897932384626433832795;
  constexpr double kTwoPi = 2.0 * kPi;
  constexpr float kRadToDeg = 180.0f / kPi;
  constexpr float kDegToRad = kPi / 180.0f;
  
  const Vec2 kZero {0, 0};
  const Vec2 kOne {1, 1};
  const Vec2 kRight {1, 0};
  const Vec2 kUp {0, 1};
  
  using Color = unsigned int;
  
  constexpr Color toColor(unsigned char r,
                          unsigned char g,
                          unsigned char b,
                          unsigned char a)
  {
    Color c = r;
    c |= (g << 8);
    c |= (b << 16);
    c |= (a << 24);
    return c;
  }
  
  constexpr Color kRed = toColor(255, 0, 0, 255);
  constexpr Color kGreen = toColor(0, 255, 0, 255);
  constexpr Color kBlue = toColor(0, 0, 255, 255);
  constexpr Color kBlack = toColor(0, 0, 0, 255);
  constexpr Color kWhite = toColor(255, 255, 255, 255);
  constexpr Color kYellow = toColor(255, 255, 0, 255);
  constexpr Color kMagenta = toColor(255, 0, 255, 255);
  constexpr Color kCyan = toColor(0, 255, 255, 255);
  
  using Index = unsigned int;
  struct Vertex
  {
    Vertex(const Vec3& _pos, Color _col) : position(_pos), color(_col), uv() {}
    Vertex(const Vec3& _pos, Color _col, const Vec2& _uv) : position(_pos), color(_col), uv(_uv) {}
    Vec3 position;
    Color color;
    Vec2 uv;
  };

  struct DrawCommand
  {
    bool isText = false;
    unsigned int elementCount;
    unsigned int indexOffset;
    unsigned int matrixIndex;
  };

  struct GlyphDescriptor
  {
    unsigned short x0, y0, x1, y1; // Glyph Coordinates in font bitmap.
    float xOff, yOff, xAdvance;
  };
  using FontTextureData = std::vector<std::uint8_t>;
  using GlyphDescriptors = std::vector<GlyphDescriptor>;
  
  struct FontData
  {
    unsigned int resolution;
    FontTextureData textureData;
    GlyphDescriptors glyphDescriptors;
  };

  using DrawCommndsList = std::vector<DrawCommand>;
  using VerticesList = std::vector<Vertex>;
  using IndexList = std::vector<Index>;
  using MatrixStack = std::vector<Mat4>;
  
  class DrawList
  {
  public:
    friend class Context;
    DrawList();
    void addLine(const Vec2& p1, const Vec2& p2, Color color, float thickness = 1.0f);
    void addTriangle(const Vec2& p1, const Vec2& p2, const Vec2& p3, Color color, float thickness = 1.0f);
    void addTriangleFilled(const Vec2& p1, const Vec2& p2, const Vec2& p3, Color color);
    void addRectangle(const Vec2& position, const Vec2& size, Color color, float thickness = 1.0f);
    void addRectangleFilled(const Vec2& position, const Vec2& size, Color color);
    void addQuad(const Vec2& position, float size, Color color, float thickness = 1.0f);
    void addQuadFilled(const Vec2& position, float size, Color color);
    void addNGon(const Vec2& position, float radius, Color color, unsigned short n = 5, float thickness = 1.0f);
    void addNGonFilled(const Vec2& position, float radius, Color color, unsigned short n = 5);
    void addCircle(const Vec2& position, float radius, Color color, unsigned short segments = 16, float thickness = 1.0f);
    void addCircleFilled(const Vec2& position, float radius, Color color, unsigned short segments = 16);
    void addEllipse(const Vec2& position, const Vec2& size, Color color, unsigned short segments = 16, float thickness = 1.0f);
    void addEllipseFilled(const Vec2& position, const Vec2& size, Color color, unsigned short segments = 16);
    void addPolyline(const std::vector<Vec2>& points, Color color, bool closed, float thickness = 1.0f);
    void addText(const std::string& text, const Vec2& position, Color color, const Vec2& offset, float size = 1.0f);
    inline void pushMatrix(const Mat4& mat) { mMatrixStack.push_back(mat); }
    inline Mat4& getMatrix(unsigned int index) { return mMatrixStack[index]; }
    void optimise();
  private:
    void addPolyline(Vec2* const points, int numPoints, Color color, bool closed, float thickness);
    inline unsigned int getMatrixIndex() { return mMatrixStack.size() > 0 ? mMatrixStack.size() - 1 : 0; }

  private:
    DrawList(const DrawList&) = delete;
    DrawList& operator=(const DrawList&) = delete;

  public:
    inline const DrawCommndsList& getDrawCommands() const { return mDrawCommands; }
    inline const VerticesList& getVertices() const { return mVertices; }
    inline const IndexList& getIndices() const { return mIndices; }

  private:
    DrawCommndsList mDrawCommands;
    VerticesList mVertices;
    IndexList mIndices;
    MatrixStack mMatrixStack;
  };

  struct IO
  {
    Vec2 displayPosition;
    Vec2 displaySize;
    Vec2 displayFramebufferScale;
    float deltaTime; // Time passed since last frame in ms.
    float getFps()
    {
      mAccumMs += deltaTime - mDeltaTimeSamples[dtIdx];
      mDeltaTimeSamples[dtIdx] = deltaTime; ++dtIdx %= FPS_SAMPLE_COUNT;
      return mAccumMs > 0.0f ? 1000.0f / (mAccumMs / FPS_SAMPLE_COUNT) : -1.0f;
    }
  private:
    float mDeltaTimeSamples[FPS_SAMPLE_COUNT] = {0.0f};
    unsigned int dtIdx = 0;
    float mAccumMs = 0.0f;
  };

  // Main API.
  void createContext(const IO& io);
  void destroyContext();

  IO& getIO();
  const FontData& getFontData();
  void newFrame();
  void render();
  DrawList* getDrawList();
}

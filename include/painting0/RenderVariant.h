#pragma once

#include <SM_Vector.h>
#include <SM_Matrix.h>

namespace ur { class Texture; class Texture3D; }

namespace pt0
{

enum class RenderVarType
{
    INVALID,

    BOOL,
    INT,
    FLOAT,
    SAMPLER1D,
    SAMPLER2D,
    SAMPLER3D,
    SAMPLERCUBE,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT3,
    MAT4,
};

class RenderVariant
{
public:
    RenderVariant() : type(RenderVarType::INVALID) {}
    explicit RenderVariant(bool v)  : type(RenderVarType::BOOL),  b(v) {}
    explicit RenderVariant(int  v)  : type(RenderVarType::INT),   i(v) {}
    explicit RenderVariant(float v) : type(RenderVarType::FLOAT), f(v) {}
    explicit RenderVariant(ur::Texture* tex);
    explicit RenderVariant(ur::Texture3D* tex3d);
    explicit RenderVariant(const sm::vec2& v) : type(RenderVarType::VEC2), vec2(v) {}
    explicit RenderVariant(const sm::vec3& v) : type(RenderVarType::VEC3), vec3(v) {}
    explicit RenderVariant(const sm::vec4& v) : type(RenderVarType::VEC4), vec4(v) {}
    explicit RenderVariant(const sm::mat2& v) : type(RenderVarType::MAT2), mat2(v) {}
    explicit RenderVariant(const sm::mat3& v) : type(RenderVarType::MAT3), mat3(v) {}
    explicit RenderVariant(const sm::mat4& v) : type(RenderVarType::MAT4), mat4(v) {}

    RenderVarType type;

    struct Texture
    {
        Texture() : tex(nullptr) {}

        unsigned int unit = 0;
        union
        {
            ur::Texture*   tex;
            ur::Texture3D* tex3d;
        };
    };

    union
    {
        bool     b;
        int      i;
        float    f;
        Texture  tex;
        sm::vec2 vec2;
        sm::vec3 vec3;
        sm::vec4 vec4;
        sm::mat2 mat2;
        sm::mat3 mat3;
        sm::mat4 mat4;
    };

}; // RenderVariant

}
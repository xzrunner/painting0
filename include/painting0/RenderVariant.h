#pragma once

#include <SM_Vector.h>
#include <SM_Matrix.h>

namespace ur2 { class Texture; }

namespace pt0
{

enum class RenderVarType
{
    INVALID,

    BOOL,
    INT,
    FLOAT,
    SAMPLER,
    //SAMPLER1D,
    //SAMPLER2D,
    //SAMPLER3D,
    SAMPLERCUBE,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT3,
    MAT4,
    ARRAY,
};

class RenderVariant
{
public:
    RenderVariant() : type(RenderVarType::INVALID) {}
    RenderVariant(const RenderVariant& var);
    RenderVariant& operator = (const RenderVariant& var);
    explicit RenderVariant(bool v)  : type(RenderVarType::BOOL),  b(v) {}
    explicit RenderVariant(int  v)  : type(RenderVarType::INT),   i(v) {}
    explicit RenderVariant(float v) : type(RenderVarType::FLOAT), f(v) {}
    explicit RenderVariant(const ur2::Texture* tex);
    explicit RenderVariant(const sm::vec2& v) : type(RenderVarType::VEC2), vec2(v) {}
    explicit RenderVariant(const sm::vec3& v) : type(RenderVarType::VEC3), vec3(v) {}
    explicit RenderVariant(const sm::vec4& v) : type(RenderVarType::VEC4), vec4(v) {}
    explicit RenderVariant(const sm::mat2& v) : type(RenderVarType::MAT2), mat2(v) {}
    explicit RenderVariant(const sm::mat3& v) : type(RenderVarType::MAT3), mat3(v) {}
    explicit RenderVariant(const sm::mat4& v) : type(RenderVarType::MAT4), mat4(v) {}
    explicit RenderVariant(const sm::vec3* data, size_t size);
    explicit RenderVariant(const sm::vec4* data, size_t size);
    explicit RenderVariant(const sm::mat4* data, size_t size);

    RenderVarType type;

    struct Texture
    {
        unsigned int unit = 0;
        const ur2::Texture* tex = nullptr;
    };

    struct Array
    {
        RenderVarType type = RenderVarType::INVALID;
        size_t        size = 0;
        const void*   data = nullptr;
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
        Array    array;
    };

}; // RenderVariant

}
#include "painting0/RenderVariant.h"

namespace pt0
{

RenderVariant::RenderVariant(const RenderVariant& var)
{
    memcpy(this, &var, sizeof(var));
}

RenderVariant& RenderVariant::operator = (const RenderVariant& var)
{
    memcpy(this, &var, sizeof(var));
    return *this;
}

RenderVariant::RenderVariant(const ur::Texture* tex)
    : type(RenderVarType::SAMPLER)
{
    this->tex.tex = tex;
}

RenderVariant::RenderVariant(const sm::vec3* data, size_t size)
    : type(RenderVarType::ARRAY)
{
    array.type = RenderVarType::VEC3;
    array.size = size;
    array.data = data;
}

RenderVariant::RenderVariant(const sm::vec4* data, size_t size)
    : type(RenderVarType::ARRAY)
{
    array.type = RenderVarType::VEC4;
    array.size = size;
    array.data = data;
}

RenderVariant::RenderVariant(const sm::mat4* data, size_t size)
    : type(RenderVarType::ARRAY)
{
    array.type = RenderVarType::MAT4;
    array.size = size;
    array.data = data;
}

}
#include "painting0/RenderVariant.h"

namespace pt0
{

RenderVariant::RenderVariant(ur::Texture* tex)
    : type(RenderVarType::SAMPLER2D)
{
    this->tex.tex = tex;
}

RenderVariant::RenderVariant(ur::Texture3D* tex3d)
    : type(RenderVarType::SAMPLER3D)
{
    this->tex.tex3d = tex3d;
}

RenderVariant::RenderVariant(const sm::mat4* data, size_t size)
    : type(RenderVarType::ARRAY)
{
    array.type = RenderVarType::MAT4;
    array.size = size;
    array.data = data;
}

}
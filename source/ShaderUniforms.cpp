#include "painting0/ShaderUniforms.h"
#include "painting0/RenderVariant.h"

#include <unirender2/ShaderProgram.h>
#include <unirender2/Uniform.h>
#include <unirender2/Texture.h>

namespace pt0
{

void ShaderUniforms::AddVar(const std::string& name, const RenderVariant& var)
{
    auto stat = m_vars.insert({ name, var });
    if (!stat.second) {
        stat.first->second = var;
    }
}

const RenderVariant* ShaderUniforms::FetchVar(const std::string& name) const
{
    auto itr = m_vars.find(name);
    if (itr == m_vars.end()) {
        return nullptr;
    } else {
        return &itr->second;
    }
}

void ShaderUniforms::SetVar(const std::string& name, const RenderVariant& var)
{
    auto itr = m_vars.find(name);
    if (itr == m_vars.end()) {
        return;
    }

    memcpy(&itr->second, &var, sizeof(var));
}

void ShaderUniforms::Bind(const ur2::ShaderProgram& shader) const
{
    for (auto& var : m_vars)
    {
        auto& name = var.first;
        auto u = shader.QueryUniform(name);
        if (!u) {
            continue;
        }

        auto& val = var.second;
        switch (val.type)
        {
        case RenderVarType::BOOL:
        {
            const int i = val.b ? 1 : 0;
            u->SetValue(&i);
        }
            break;
        case RenderVarType::INT:
        {
            const int i = val.i;
            u->SetValue(&i);
        }
            break;
        case RenderVarType::FLOAT:
        {
            const float f = val.f;
            u->SetValue(&f);
        }
            break;
        case RenderVarType::SAMPLER:
        {
            assert(val.tex.tex);
            int i = val.tex.tex->GetTexID();
            u->SetValue(&i);
        }
            break;
        case RenderVarType::SAMPLERCUBE:
            break;
        case RenderVarType::VEC2:
            u->SetValue(val.vec2.xy, 2);
            break;
        case RenderVarType::VEC3:
            u->SetValue(val.vec3.xyz, 3);
            break;
        case RenderVarType::VEC4:
            u->SetValue(val.vec4.xyzw, 4);
            break;
        case RenderVarType::MAT2:
            u->SetValue(val.mat2.x, 2 * 2);
            break;
        case RenderVarType::MAT3:
            u->SetValue(val.mat3.x, 3 * 3);
            break;
        case RenderVarType::MAT4:
            u->SetValue(val.mat4.x, 4 * 4);
            break;
        case RenderVarType::ARRAY:
        {
            switch (val.array.type)
            {
            case RenderVarType::VEC3:
                u->SetValue(static_cast<const sm::vec3*>(val.array.data)->xyz, 3 * val.array.size);
                break;
            case RenderVarType::VEC4:
                u->SetValue(static_cast<const sm::vec4*>(val.array.data)->xyzw, 4 * val.array.size);
                break;
            case RenderVarType::MAT4:
                u->SetValue(static_cast<const sm::mat4*>(val.array.data)->x, 4 * 4 * val.array.size);
                break;
            }
            break;
        }
        }
    }
}

}
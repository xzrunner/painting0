#include "painting0/ShaderUniforms.h"
#include "painting0/RenderVariant.h"

#include <unirender/Shader.h>
#include <unirender/Blackboard.h>
#include <unirender/RenderContext.h>

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

void ShaderUniforms::Bind(const ur::Shader& shader) const
{
    for (auto& var : m_vars)
    {
        auto& name = var.first;
        auto& val = var.second;
        switch (val.type)
        {
        case RenderVarType::BOOL:
            shader.SetInt(name, val.b ? 1 : 0);
            break;
        case RenderVarType::INT:
            shader.SetInt(name, val.i);
            break;
        case RenderVarType::FLOAT:
            shader.SetFloat(name, val.f);
            break;
        case RenderVarType::SAMPLER1D:
            break;
        case RenderVarType::SAMPLER2D:
        {
            assert(val.tex.tex);
            int tex_id = val.tex.tex->TexID();
            ur::Blackboard::Instance()->GetRenderContext().BindTexture(tex_id, 0);
        }
        break;
        case RenderVarType::SAMPLER3D:
            break;
        case RenderVarType::SAMPLERCUBE:
            break;
        case RenderVarType::VEC2:
            shader.SetVec2(name, val.vec2.xy);
            break;
        case RenderVarType::VEC3:
            shader.SetVec3(name, val.vec3.xyz);
            break;
        case RenderVarType::VEC4:
            shader.SetVec4(name, val.vec4.xyzw);
            break;
        case RenderVarType::MAT2:
            // todo
            break;
        case RenderVarType::MAT3:
            shader.SetMat3(name, val.mat3.x);
            break;
        case RenderVarType::MAT4:
            shader.SetMat4(name, val.mat4.x);
            break;
        case RenderVarType::ARRAY:
        {
            switch (val.array.type)
            {
            case RenderVarType::VEC3:
                shader.SetVec3Array(name, static_cast<const sm::vec3*>(val.array.data)->xyz, val.array.size);
                break;
            case RenderVarType::VEC4:
                shader.SetVec3Array(name, static_cast<const sm::vec4*>(val.array.data)->xyzw, val.array.size);
                break;
            case RenderVarType::MAT4:
                shader.SetMat4Array(name, static_cast<const sm::mat4*>(val.array.data)->x, val.array.size);
                break;
            }
            break;
        }
        }
    }
}

}
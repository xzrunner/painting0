#pragma once

#include "painting0/ShaderUniforms.h"

namespace pt0
{

class Shader;

class Material
{
public:
    Material() {}

    void AddVar(const std::string& name, const RenderVariant& var) { m_uniforms.AddVar(name, var); }
    const RenderVariant* FetchVar(const std::string& name) const { return m_uniforms.FetchVar(name); }

    auto& GetAllVars() const { return m_uniforms.GetAllVars(); }
    void SetVar(const std::string& name, const RenderVariant& var) { m_uniforms.SetVar(name, var); }

    void Bind(const ur::Shader& shader) const { m_uniforms.Bind(shader); }

private:
    ShaderUniforms m_uniforms;

}; // Material

}
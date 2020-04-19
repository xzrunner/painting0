#pragma once

#include "painting0/RenderVariant.h"

#include <map>
#include <memory>

namespace ur2 { class ShaderProgram; }

namespace pt0
{

class ShaderUniforms
{
public:
    void AddVar(const std::string& name, const RenderVariant& var);
    const RenderVariant* FetchVar(const std::string& name) const;

    auto& GetAllVars() const { return m_vars; }
    void SetVar(const std::string& name, const RenderVariant& var);

    void Bind(const ur2::ShaderProgram& shader) const;

private:
    std::map<std::string, RenderVariant> m_vars;

}; // ShaderUniforms

}
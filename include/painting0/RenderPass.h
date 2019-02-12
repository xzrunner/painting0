#pragma once

#include "painting0/RenderVariant.h"
#include "painting0/Material.h"

#include <map>
#include <memory>

namespace pt0
{

class RenderPass
{
public:
    RenderPass() {}

    void AddParams(const std::string& name, const RenderVariant& var) {
        m_params.insert({ name, var });
    }

private:
    std::shared_ptr<Material> m_material = nullptr;

    std::map<std::string, RenderVariant> m_params;

}; // RenderPass

}
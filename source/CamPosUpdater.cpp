#include "painting0/CamPosUpdater.h"

#include <unirender2/ShaderProgram.h>

namespace pt0
{

CamPosUpdater::CamPosUpdater(const ur2::ShaderProgram& shader,
                             const std::string& name)
{
    m_uniform = shader.QueryUniform(name);
}

void CamPosUpdater::Update(const ur2::Context& ctx, const ur2::DrawState& draw,
                           const void* scene)
{
}

}
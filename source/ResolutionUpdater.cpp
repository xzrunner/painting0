#include "painting0/ResolutionUpdater.h"

#include <unirender2/ShaderProgram.h>

namespace pt0
{

ResolutionUpdater::ResolutionUpdater(const ur2::ShaderProgram& shader,
                                     const std::string& name)
{
    m_uniform = shader.QueryUniform(name);
}

void ResolutionUpdater::Update(const ur2::Context& ctx, const ur2::DrawState& draw,
                               const void* scene)
{
}

}
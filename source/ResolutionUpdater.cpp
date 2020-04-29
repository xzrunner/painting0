#include "painting0/ResolutionUpdater.h"

#include <unirender/ShaderProgram.h>

namespace pt0
{

ResolutionUpdater::ResolutionUpdater(const ur::ShaderProgram& shader,
                                     const std::string& name)
{
    m_uniform = shader.QueryUniform(name);
}

void ResolutionUpdater::Update(const ur::Context& ctx, const ur::DrawState& draw,
                               const void* scene)
{
}

}
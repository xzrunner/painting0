#include "painting0/ModelMatUpdater.h"

#include <unirender/ShaderProgram.h>
#include <unirender/Uniform.h>

namespace pt0
{

ModelMatUpdater::ModelMatUpdater(const ur::ShaderProgram& shader,
                                 const std::string& name)
{
    m_uniform = shader.QueryUniform(name);
}

void ModelMatUpdater::Update(const ur::Context& ctx, const ur::DrawState& draw, const void* scene)
{
}

void ModelMatUpdater::Update(const sm::mat4& mat)
{
    if (m_uniform) {
        m_uniform->SetValue(mat.x, 4 * 4);
        m_mat = mat;
    }
}

}
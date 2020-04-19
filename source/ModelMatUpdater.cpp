#include "painting0/ModelMatUpdater.h"

#include <unirender2/ShaderProgram.h>
#include <unirender2/Uniform.h>

namespace pt0
{

ModelMatUpdater::ModelMatUpdater(const ur2::ShaderProgram& shader,
                                 const std::string& name)
{
    m_uniform = shader.QueryUniform(name);
}

void ModelMatUpdater::Update(const sm::mat4& mat)
{
    if (m_uniform) {
        m_uniform->SetValue(mat.x, 4 * 4);
    }
}

}
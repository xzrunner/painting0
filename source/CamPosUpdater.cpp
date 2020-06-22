#include "painting0/CamPosUpdater.h"

#include <unirender/ShaderProgram.h>
#include <unirender/Uniform.h>

namespace pt0
{

CamPosUpdater::CamPosUpdater(const ur::ShaderProgram& shader,
                             const std::string& name)
{
    m_uniform = shader.QueryUniform(name);
}

void CamPosUpdater::Update(const ur::Context& ctx, const ur::DrawState& draw,
                           const void* scene)
{
}

void CamPosUpdater::Update(const sm::vec3& pos)
{
	if (m_uniform) {
		m_uniform->SetValue(pos.xyz, 3);
	}
}

}
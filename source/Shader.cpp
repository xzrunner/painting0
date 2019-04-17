#include "painting0/Shader.h"
#include "painting0/GlobalClock.h"

namespace pt0
{

Shader::Shader(ur::RenderContext* rc, const Params& params)
	: ur::Shader(rc, params.vs, params.fs, params.textures, params.va_list)
	, m_uniform_names(params.uniform_names)
{
    if (params.uniform_names.IsExist(UniformTypes::Time) ||
        params.uniform_names.IsExist(UniformTypes::SineTime) ||
        params.uniform_names.IsExist(UniformTypes::CosTime) ||
        params.uniform_names.IsExist(UniformTypes::DeltaiTme)) {
        m_time_update = std::make_unique<TimeUpdate>(this);
    }
}

void Shader::UpdateModelMat(const sm::mat4& mat)
{
	if (m_model_mat_valid && mat == m_model_mat) {
		return;
	}
    m_model_mat_valid = true;
	m_model_mat = mat;

	Use();

    auto name = m_uniform_names.Query(UniformTypes::ModelMat);
    if (!name.empty()) {
        SetMat4(name, mat.x);
    }
}

void Shader::UpdateTime(float t, float dt, float smooth_dt)
{
	assert(m_time_update);

	if (t == m_time_update->t && dt == m_time_update->dt && smooth_dt == m_time_update->smooth_dt) {
		return;
	}
	m_time_update->t         = t;
	m_time_update->dt        = dt;
	m_time_update->smooth_dt = smooth_dt;

	Use();

    std::string name;
    name = m_uniform_names.Query(UniformTypes::Time);
	if (!name.empty()) {
		float val[] = { t / 20, t, t * 2, t * 3 };
		SetVec4(name, val);
	}

    name = m_uniform_names.Query(UniformTypes::SineTime);
	if (!name.empty()) {
		float val[] = { sin(t / 8), sin(t / 4), sin(t / 2), sin(t) };
		SetVec4(name, val);
	}

    name = m_uniform_names.Query(UniformTypes::CosTime);
	if (!name.empty()) {
		float val[] = { cos(t / 8), cos(t / 4), cos(t / 2), cos(t) };
		SetVec4(name, val);
	}

    name = m_uniform_names.Query(UniformTypes::DeltaiTme);
	if (!name.empty()) {
		float val[] = { dt, 1 / dt, smooth_dt, 1 / smooth_dt };
		SetVec4(name, val);
	}
}

//////////////////////////////////////////////////////////////////////////
// class Shader::TimeUpdate
//////////////////////////////////////////////////////////////////////////

Shader::TimeUpdate::TimeUpdate(Shader* shader)
{
	conn_tick = GlobalClock::Instance()->DoOnTick(boost::bind(&Shader::UpdateTime, shader, _1, _2, _3));
}

Shader::TimeUpdate::~TimeUpdate()
{
	conn_tick.disconnect();
}

}
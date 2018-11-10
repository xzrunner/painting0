#include "painting0/Shader.h"
#include "painting0/GlobalClock.h"

namespace pt0
{

Shader::Shader(ur::RenderContext* rc, const Params& params)
	: ur::Shader(rc, params.vs, params.fs, params.textures, params.va_list)
	, m_uniform_names(params.uniform_names)
{
	if (params.utime_names) {
		m_time_update = std::make_unique<TimeUpdate>(this, *params.utime_names);
	}
}

void Shader::UpdateModelMat(const sm::mat4& mat)
{
	if (mat == m_model_mat) {
		return;
	}
	m_model_mat = mat;

	Use();

	SetMat4(m_uniform_names.model_mat.c_str(), mat.x);
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
	if (m_time_update->unames.time.empty() && m_time_update->unames.sine_time.empty() &&
		m_time_update->unames.cos_time.empty() && m_time_update->unames.delta_time.empty()) {
		return;
	}

	Use();

	if (!m_time_update->unames.time.empty()) {
		float val[] = { t / 20, t, t * 2, t * 3 };
		SetVec4(m_time_update->unames.time, val);
	}
	if (!m_time_update->unames.sine_time.empty()) {
		float val[] = { sin(t / 8), sin(t / 4), sin(t / 2), sin(t) };
		SetVec4(m_time_update->unames.sine_time, val);
	}
	if (!m_time_update->unames.cos_time.empty()) {
		float val[] = { cos(t / 8), cos(t / 4), cos(t / 2), cos(t) };
		SetVec4(m_time_update->unames.cos_time, val);
	}
	if (!m_time_update->unames.delta_time.empty()) {
		float val[] = { dt, 1 / dt, smooth_dt, 1 / smooth_dt };
		SetVec4(m_time_update->unames.delta_time, val);
	}
}

//////////////////////////////////////////////////////////////////////////
// class Shader::TimeUpdate
//////////////////////////////////////////////////////////////////////////

Shader::TimeUpdate::TimeUpdate(Shader* shader, const UniformTimeNames& unames)
	: unames(unames)
{
	conn_tick = GlobalClock::Instance()->DoOnTick(boost::bind(&Shader::UpdateTime, shader, _1, _2, _3));
}

Shader::TimeUpdate::~TimeUpdate()
{
	conn_tick.disconnect();
}

}
#include "painting0/Shader.h"
#include "painting0/GlobalClock.h"

// todo: rm dependence of shaderlab
#include <shaderlab/Blackboard.h>
#include <shaderlab/RenderContext.h>
#include <shaderlab/ShaderMgr.h>

namespace pt0
{

Shader::Shader(ur::RenderContext* rc, const Params& params)
	: ur::Shader(rc, params.vs, params.fs, params.textures, params.va_list)
	, m_uniform_names(params.uniform_names)
{
	m_conn_tick = GlobalClock::Instance()->DoOnTick(boost::bind(&Shader::UpdateTime, this, _1, _2, _3));
}

Shader::~Shader()
{
	m_conn_tick.disconnect();
}

void Shader::UpdateTime(float t, float dt, float smooth_dt)
{
	if (t == m_t && dt == m_dt && smooth_dt == m_smooth_dt) {
		return;
	}
	m_t         = t;
	m_dt        = dt;
	m_smooth_dt = smooth_dt;
	if (m_uniform_names.time.empty() && m_uniform_names.sine_time.empty() &&
		m_uniform_names.cos_time.empty() && m_uniform_names.delta_time.empty()) {
		return;
	}

	auto& shader_mgr = sl::Blackboard::Instance()->GetRenderContext().GetShaderMgr();
	shader_mgr.SetShader(sl::EXTERN_SHADER);
	shader_mgr.BindRenderShader(nullptr, sl::EXTERN_SHADER);

	Use();

	if (!m_uniform_names.time.empty()) {
		float val[] = { t / 20, t, t * 2, t * 3 };
		SetVec4(m_uniform_names.time, val);
	}
	if (!m_uniform_names.sine_time.empty()) {
		float val[] = { sin(t / 8), sin(t / 4), sin(t / 2), sin(t) };
		SetVec4(m_uniform_names.sine_time, val);
	}
	if (!m_uniform_names.cos_time.empty()) {
		float val[] = { cos(t / 8), cos(t / 4), cos(t / 2), cos(t) };
		SetVec4(m_uniform_names.cos_time, val);
	}
	if (!m_uniform_names.delta_time.empty()) {
		float val[] = { dt, 1 / dt, smooth_dt, 1 / smooth_dt };
		SetVec4(m_uniform_names.delta_time, val);
	}
}

}
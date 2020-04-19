#include "painting0/TimeUpdater.h"
#include "painting0/GlobalClock.h"

#include <unirender2/ShaderProgram.h>
#include <unirender2/Uniform.h>

namespace pt0
{

TimeUpdater::TimeUpdater(const ur2::ShaderProgram& shader,
                         const std::string& time_name,
                         const std::string& sine_time_name,
                         const std::string& cos_time_name,
                         const std::string& delta_time_name)
{
    m_conn_tick = GlobalClock::Instance()->DoOnTick(boost::bind(&TimeUpdater::UpdateTime, this, _1, _2, _3));

    m_u_time       = shader.QueryUniform(time_name);
    m_u_sine_time  = shader.QueryUniform(sine_time_name);
    m_u_cos_time   = shader.QueryUniform(cos_time_name);
    m_u_delta_time = shader.QueryUniform(delta_time_name);
}

void TimeUpdater::Update(const ur2::Context& ctx, const ur2::DrawState& draw, const void* scene)
{
    m_conn_tick.disconnect();
}

void TimeUpdater::UpdateTime(float t, float dt, float smooth_dt)
{
    if (t != m_t)
    {
        if (m_u_time) {
            float val[] = { t / 20, t, t * 2, t * 3 };
            m_u_time->SetValue(val, 4);
        }

        if (m_u_sine_time) {
            float val[] = { sin(t / 8), sin(t / 4), sin(t / 2), sin(t) };
            m_u_sine_time->SetValue(val, 4);
        }

        if (m_u_cos_time) {
            float val[] = { cos(t / 8), cos(t / 4), cos(t / 2), cos(t) };
            m_u_cos_time->SetValue(val, 4);
        }

        m_t = t;
    }

    if (dt != m_dt || smooth_dt != m_smooth_dt)
    {
        if (m_u_delta_time) {
            float val[] = { dt, 1 / dt, smooth_dt, 1 / smooth_dt };
            m_u_delta_time->SetValue(val, 4);
        }
    }
}

}
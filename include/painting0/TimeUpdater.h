#pragma once

#include <unirender/UniformUpdater.h>

#include <boost/signals2.hpp>

namespace ur { class ShaderProgram; class Uniform; }

namespace pt0
{

class TimeUpdater : public ur::UniformUpdater
{
public:
    TimeUpdater(const ur::ShaderProgram& shader,
        const std::string& time_name, const std::string& sine_time_name,
        const std::string& cos_time_name, const std::string& delta_time_name);
    virtual ~TimeUpdater();

    virtual ur::UpdaterID UpdaterTypeID() const override {
        return ur::GetUpdaterTypeID<TimeUpdater>();
    }

    virtual void Update(const ur::Context& ctx,
        const ur::DrawState& draw, const void* scene = nullptr) override;

private:
    void UpdateTime(float t, float dt, float smooth_dt);

private:
    boost::signals2::connection m_conn_tick;

    float m_t         = 0;
    float m_dt        = 0;
    float m_smooth_dt = 0;

    std::shared_ptr<ur::Uniform> m_u_time       = nullptr;
    std::shared_ptr<ur::Uniform> m_u_sine_time  = nullptr;
    std::shared_ptr<ur::Uniform> m_u_cos_time   = nullptr;
    std::shared_ptr<ur::Uniform> m_u_delta_time = nullptr;

}; // TimeUpdater

}
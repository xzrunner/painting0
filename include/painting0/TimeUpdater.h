#pragma once

#include <unirender2/UniformUpdater.h>

#include <boost/signals2.hpp>

namespace ur2 { class ShaderProgram; class Uniform; }

namespace pt0
{

class TimeUpdater : public ur2::UniformUpdater
{
public:
    TimeUpdater(const ur2::ShaderProgram& shader,
        const std::string& time_name, const std::string& sine_time_name,
        const std::string& cos_time_name, const std::string& delta_time_name);

    virtual ur2::UpdaterID UpdaterTypeID() const override {
        return ur2::GetUpdaterTypeID<TimeUpdater>();
    }

    virtual void Update(const ur2::Context& ctx,
        const ur2::DrawState& draw, const void* scene = nullptr) override;

private:
    void UpdateTime(float t, float dt, float smooth_dt);

private:
    boost::signals2::connection m_conn_tick;

    float m_t         = 0;
    float m_dt        = 0;
    float m_smooth_dt = 0;

    std::shared_ptr<ur2::Uniform> m_u_time       = nullptr;
    std::shared_ptr<ur2::Uniform> m_u_sine_time  = nullptr;
    std::shared_ptr<ur2::Uniform> m_u_cos_time   = nullptr;
    std::shared_ptr<ur2::Uniform> m_u_delta_time = nullptr;

}; // TimeUpdater

}
#pragma once

#include <unirender2/UniformUpdater.h>

#include <string>

namespace ur2 { class ShaderProgram; class Uniform; }

namespace pt0
{

class CamPosUpdater : public ur2::UniformUpdater
{
public:
    CamPosUpdater(const ur2::ShaderProgram& shader,
        const std::string& name);

    virtual ur2::UpdaterID UpdaterTypeID() const override {
        return ur2::GetUpdaterTypeID<CamPosUpdater>();
    }

    virtual void Update(const ur2::Context& ctx,
        const ur2::DrawState& draw, const void* scene = nullptr) override;

private:
    std::shared_ptr<ur2::Uniform> m_uniform = nullptr;

}; // CamPosUpdater

}
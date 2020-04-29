#pragma once

#include <unirender/UniformUpdater.h>

#include <string>

namespace ur { class ShaderProgram; class Uniform; }

namespace pt0
{

class CamPosUpdater : public ur::UniformUpdater
{
public:
    CamPosUpdater(const ur::ShaderProgram& shader,
        const std::string& name);

    virtual ur::UpdaterID UpdaterTypeID() const override {
        return ur::GetUpdaterTypeID<CamPosUpdater>();
    }

    virtual void Update(const ur::Context& ctx,
        const ur::DrawState& draw, const void* scene = nullptr) override;

private:
    std::shared_ptr<ur::Uniform> m_uniform = nullptr;

}; // CamPosUpdater

}
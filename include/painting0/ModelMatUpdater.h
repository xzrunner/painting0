#pragma once

#include <SM_Matrix.h>
#include <unirender/UniformUpdater.h>

#include <string>

namespace ur { class ShaderProgram; class Uniform; }

namespace pt0
{

class ModelMatUpdater : public ur::UniformUpdater
{
public:
    ModelMatUpdater(const ur::ShaderProgram& shader,
        const std::string& name);

    virtual ur::UpdaterID UpdaterTypeID() const override {
        return ur::GetUpdaterTypeID<ModelMatUpdater>();
    }

    virtual void Update(const ur::Context& ctx,
        const ur::DrawState& draw, const void* scene = nullptr) override;

    void Update(const sm::mat4& mat);

    auto& GetValue() const { return m_mat; }

public:
    class Snapshot
    {
    public:
        Snapshot(ModelMatUpdater& updater)
            : m_updater(updater), m_mat(updater.m_mat) {}

        void Restore() {
            m_updater.Update(m_mat);
        }

    private:
        ModelMatUpdater& m_updater;

        sm::mat4 m_mat;

    }; // Snapshot

private:
    std::shared_ptr<ur::Uniform> m_uniform = nullptr;

    sm::mat4 m_mat;

}; // ModelMatUpdater

}
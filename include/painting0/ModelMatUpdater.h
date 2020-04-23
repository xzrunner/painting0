#pragma once

#include <SM_Matrix.h>
#include <unirender2/UniformUpdater.h>

#include <string>

namespace ur2 { class ShaderProgram; class Uniform; }

namespace pt0
{

class ModelMatUpdater : public ur2::UniformUpdater
{
public:
    ModelMatUpdater(const ur2::ShaderProgram& shader,
        const std::string& name);

    virtual ur2::UpdaterID UpdaterTypeID() const override {
        return ur2::GetUpdaterTypeID<ModelMatUpdater>();
    }

    virtual void Update(const ur2::Context& ctx,
        const ur2::DrawState& draw, const void* scene = nullptr) override;

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
    std::shared_ptr<ur2::Uniform> m_uniform = nullptr;

    sm::mat4 m_mat;

}; // ModelMatUpdater

}
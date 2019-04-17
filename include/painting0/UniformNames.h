#pragma once

#include <map>
#include <string>

namespace pt0
{

enum class UniformTypes
{
    ModelMat,
    ViewMat,
    ProjMat,

    Resolution,
    CamPos,

    Time,
    SineTime,
    CosTime,
    DeltaiTme,
};

class UniformNames
{
public:
    std::string Query(UniformTypes type) const {
        auto itr = m_map2name.find(type);
        return itr == m_map2name.end() ? "" : itr->second;
    }

    void Add(UniformTypes type, const std::string& name) {
        m_map2name.insert({ type, name });
    }

    bool IsExist(UniformTypes type) const {
        return m_map2name.find(type) != m_map2name.end();
    }

private:
    std::map<UniformTypes, std::string> m_map2name;

}; // UniformNames

}
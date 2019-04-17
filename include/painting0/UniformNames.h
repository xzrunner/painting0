#pragma once

#include <map>
#include <string>

namespace pt0
{

enum UniformTypes
{
    U_MODEL_MAT,
    U_VIEW_MAT,
    U_PROJ_MAT,

    U_RESOLUTION,
    U_CAM_POS,

    U_TIME,
    U_SINE_TIME,
    U_COS_TIME,
    U_DELTA_TIME,

    U_MAX_COUNT,
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
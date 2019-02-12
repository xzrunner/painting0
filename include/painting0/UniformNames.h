#pragma once

#include <array>

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

typedef std::array<std::string, UniformTypes::U_MAX_COUNT> UniformNames;

}
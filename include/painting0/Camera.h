#pragma once

#include <SM_Matrix.h>

#include <memory>

#include <boost/noncopyable.hpp>

namespace pt0
{

using CamTypeID = size_t;

namespace Internal
{
inline size_t GetUniqueCamTypeID() noexcept
{
    static CamTypeID id{ 0u };
    return id++;
}
}

template <typename T>
inline CamTypeID GetCamTypeID() noexcept
{
    static_assert(std::is_base_of<Camera, T>::value,
        "T must inherit from Camera");

    static CamTypeID type_id{Internal::GetUniqueCamTypeID()};
    return type_id;
}

class Camera : boost::noncopyable
{
public:
	virtual ~Camera() {}

	virtual CamTypeID TypeID() const = 0;

	virtual void OnSize(float width, float height) = 0;

	virtual void Bind() const = 0;

	virtual sm::mat4 GetModelViewMat() const = 0;
	virtual sm::mat4 GetProjectionMat() const = 0;

	virtual void Reset() = 0;

}; // Camera

using CameraPtr = std::shared_ptr<Camera>;

}
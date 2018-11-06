#pragma once

#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(push)
#pragma warning(disable:4996)
#endif

#include <unirender/Shader.h>

#include <boost/signals2.hpp>

namespace pt0
{

class Shader : public ur::Shader
{
public:
	struct UniformNames
	{
		std::string model_mat;
		std::string view_mat;
		std::string proj_mat;
	};

	struct UniformTimeNames
	{
		std::string time;
		std::string sine_time;
		std::string cos_time;
		std::string delta_time;
	};

	struct Params
	{
		Params(const std::vector<std::string>& textures,
			const std::vector<ur::VertexAttrib>& va_list)
			: textures(textures), va_list(va_list) {}

		const char* vs = nullptr;
		const char* fs = nullptr;
		const std::vector<std::string>& textures;
		const std::vector<ur::VertexAttrib>& va_list;

		UniformNames uniform_names;
		std::unique_ptr<UniformTimeNames> utime_names = nullptr;
	};

public:
	Shader(ur::RenderContext* rc, const Params& params);

private:
	void UpdateTime(float t, float dt, float smooth_dt);

protected:
	UniformNames m_uniform_names;

private:
	struct TimeUpdate
	{
		TimeUpdate(Shader* shader, const UniformTimeNames& unames);
		~TimeUpdate();

		UniformTimeNames unames;

		boost::signals2::connection conn_tick;

		float t = 0;
		float dt = 0;
		float smooth_dt = 0;
	};

private:
	std::unique_ptr<TimeUpdate> m_time_update = nullptr;

}; // Shader

}

#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(pop)
#endif
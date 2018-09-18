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
	};

public:
	Shader(ur::RenderContext* rc, const Params& params);
	virtual ~Shader();

private:
	void UpdateTime(float t, float dt, float smooth_dt);

protected:
	UniformNames m_uniform_names;

private:
	boost::signals2::connection m_conn_tick;

	// cache
	float m_t = 0, m_dt = 0, m_smooth_dt = 0;

}; // Shader

}

#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(pop)
#endif
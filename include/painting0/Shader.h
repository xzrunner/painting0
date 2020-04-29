//#pragma once
//
//#if defined(_MSC_VER) && _MSC_VER >= 1400
//#pragma warning(push)
//#pragma warning(disable:4996)
//#endif
//
//#include "painting0/UniformNames.h"
//
//#include <SM_Matrix.h>
//#include <unirender/ShaderProgram.h>
//
//#include <boost/signals2.hpp>
//
//#include <rttr/registration>
//
//namespace pt0
//{
//
//class Shader : public ur::ShaderProgram
//{
//public:
//	struct Params
//	{
//		Params(const std::vector<std::string>& textures,
//			const std::vector<ur::VertexAttrib>& va_list)
//			: textures(textures), va_list(va_list) {}
//
//		const char* vs = nullptr;
//		const char* fs = nullptr;
//		const std::vector<std::string>& textures;
//		const std::vector<ur::VertexAttrib>& va_list;
//
//        UniformNames uniform_names;
//	};
//
//public:
//	Shader(ur::RenderContext* rc, const Params& params);
//
//	void UpdateModelMat(const sm::mat4& mat);
//
//    auto GetUniformName(UniformTypes type) const {
//        return m_uniform_names.Query(type);
//    }
//
//private:
//	void UpdateTime(float t, float dt, float smooth_dt);
//
//protected:
//    UniformNames m_uniform_names;
//
//private:
//	struct TimeUpdate
//	{
//		TimeUpdate(Shader* shader);
//		~TimeUpdate();
//
//		boost::signals2::connection conn_tick;
//
//		float t = 0;
//		float dt = 0;
//		float smooth_dt = 0;
//	};
//
//private:
//    bool m_model_mat_valid = false;
//	sm::mat4 m_model_mat;
//
//	std::unique_ptr<TimeUpdate> m_time_update = nullptr;
//
//    RTTR_ENABLE()
//
//}; // Shader
//
//}
//
//#if defined(_MSC_VER) && _MSC_VER >= 1400
//#pragma warning(pop)
//#endif
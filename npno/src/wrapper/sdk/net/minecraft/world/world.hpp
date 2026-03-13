#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class world : public jni::object
	{
	public:
		explicit world(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_player_entities() const
			-> std::vector<std::unique_ptr<jni::entity_player>>
		{
			return get_field<jni::list>("playerEntities")->get()->to_vector<jni::entity_player>();
		}
	};
}
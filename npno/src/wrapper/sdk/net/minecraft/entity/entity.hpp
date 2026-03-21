#pragma once

#include <easy_jni/easy_jni.hpp>

namespace jni
{
	class entity : public jni::object
	{
	public:
		explicit entity(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_unique_id() const
			-> std::unique_ptr<jni::uuid>
		{
			return get_method<jni::uuid>(mapping::entity::getUniqueID)->call();
		}

		auto is_dead() const
			-> bool
		{
			return get_field<bool>(mapping::entity::isDead)->get();
		}

		auto set_custom_nametag(const std::string& value) const
			-> void
		{
			get_method<void, std::string>(mapping::entity::setCustomNameTag)->call(value);
		}

		auto set_invisible(const bool value) const
			-> void
		{
			get_method<void, bool>(mapping::entity::setInvisible)->call(value);
		}

		auto set_position(const double x, const double y, const double z) const
			-> void
		{
			get_method<void, double, double, double>(mapping::entity::setPosition)->call(x, y, z);
		}

		auto get_pos_x() const
			-> double
		{
			return get_field<double>(mapping::entity::posX)->get();
		}

		auto get_pos_y() const
			-> double
		{
			return get_field<double>(mapping::entity::posY)->get();
		}

		auto get_pos_z() const
			-> double
		{
			return get_field<double>(mapping::entity::posY)->get();
		}

		auto get_entity_id() const
			-> int
		{
			return get_field<int>(mapping::entity::entityId)->get();
		}

		auto set_always_render_nametag(const bool value) const
			-> void
		{
			get_method<void, bool>(mapping::entity::setAlwaysRenderNameTag)->call(value);
		}
	};
}
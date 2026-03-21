#pragma once

#include <easy_jni/easy_jni.hpp>

#include "../../item/item_stack.hpp"

namespace jni
{
	class inventory_player final : public jni::object
	{
	public:
		explicit inventory_player(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto armor_item_in_slot(const int value) const
			-> std::unique_ptr<jni::item_stack>
		{
			return get_method<jni::item_stack, int>(mapping::inventory_player::armorItemInSlot)->call(value);
		}
	};
}
#pragma once

#include "../../feature.hpp"

namespace npno
{
	class module : public npno::feature
	{
	public:
		module(const bool enable = false);

		virtual ~module();

		virtual auto on_load_world()
			-> void = 0;

		auto is_enable() const
			-> bool;

	protected:
		bool enable;
	};
}
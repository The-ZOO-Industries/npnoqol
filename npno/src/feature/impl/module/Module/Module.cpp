#include "Module.hpp"

Module::Module(const bool enable)
	: Feature()
	, enable{ enable }
{

}

Module::~Module() = default;

auto Module::IsEnable() const -> bool
{
	return this->enable;
}

auto Module::SetEnable(const bool state) -> void
{
	this->enable = state;
}
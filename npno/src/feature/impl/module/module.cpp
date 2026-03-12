#include "module.hpp"

npno::module::module(const bool enable)
    : npno::feature()
    , enable{ enable }
{

}

npno::module::~module() = default;

auto npno::module::is_enable() const
    -> bool
{
    return this->enable;
}
#include "hypixel_gametype_module.hpp"

npno::hypixel_gametype_module::hypixel_gametype_module(const hypixel_gametype::gametype gametype)
	: npno::module{ false }
	, gametype{ gametype }
{

}

npno::hypixel_gametype_module::~hypixel_gametype_module() = default;\

auto npno::hypixel_gametype_module::on_load_world()
	-> void
{
	hypixel_gametype::current_gametype = hypixel_gametype::gametype::LOBBY;

	this->player_cache.clear();
}

auto npno::hypixel_gametype_module::get_gametype() const
	-> hypixel_gametype::gametype
{
	return this->gametype;
}
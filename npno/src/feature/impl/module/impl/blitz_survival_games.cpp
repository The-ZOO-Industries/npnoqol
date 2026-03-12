#include "blitz_survival_games.hpp"

npno::blitz_survival_games::blitz_survival_games()
	: npno::hypixel_gametype_module{ hypixel_gametype::gametype::BLITZSURVIVALGAMES }
{

}

npno::blitz_survival_games::~blitz_survival_games() = default;

auto npno::blitz_survival_games::update()
	-> void
{
	std::println("you are playing bsg");
}
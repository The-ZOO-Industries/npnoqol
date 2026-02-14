#include "WorldClient.h"

WorldClient::WorldClient(maps::WorldClient instance)
    : World(maps::World(instance.object_instance, instance.is_global()))
{

}

WorldClient::~WorldClient() = default;

std::unique_ptr<Scoreboard> WorldClient::GetScoreboard() const
{
    maps::Scoreboard scoreboard = maps::WorldClient(this->instance.object_instance).getScoreboard.call();
    maps::Scoreboard globalScoreboard{ scoreboard.object_instance, true };
    return std::make_unique<Scoreboard>(globalScoreboard);
}

std::unique_ptr<EntityPlayer> WorldClient::GetPlayerEntityByName(const std::string& name) const
{
    jstring jname = JavaUtil::StringToJString(name);
    maps::String nameStr{ jname };
    maps::EntityPlayer player = maps::WorldClient(this->instance.object_instance).getPlayerEntityByName.call(nameStr);
    maps::EntityPlayer globalPlayer{ player.object_instance, true };
    return std::make_unique<EntityPlayer>(globalPlayer);
}
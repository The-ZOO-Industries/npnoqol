#include "WorldClient.h"

WorldClient::WorldClient(const jobject instance)
    : World(instance)
{

}

WorldClient::~WorldClient() = default;

std::unique_ptr<Scoreboard> WorldClient::GetScoreboard() const 
{
    jni::frame f;

    return std::make_unique<Scoreboard>(jni::make_global(maps::WorldClient(this->instance).getScoreboard.call()));
}

std::unique_ptr<EntityPlayer> WorldClient::GetPlayerEntityByName(const std::string& name) const
{
    jni::frame f;

    return std::make_unique<EntityPlayer>(jni::make_global(maps::WorldClient(this->instance).getPlayerEntityByName.call(JavaUtil::StringToJString(name))));
}
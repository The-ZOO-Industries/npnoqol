#include "WorldClient.h"

WorldClient::WorldClient(const jobject instance)
    : World(instance)
{

}

WorldClient::~WorldClient() = default;

auto WorldClient::GetScoreboard() const -> std::unique_ptr<Scoreboard>
{
    jni::frame f;

    return std::make_unique<Scoreboard>(jobject(maps::Scoreboard(maps::WorldClient(this->instance).getScoreboard.call(), true)));
}

auto WorldClient::GetPlayerEntityByName(const std::string& name) const -> std::unique_ptr<EntityPlayer>
{
    jni::frame f;

    return std::make_unique<EntityPlayer>(jobject(maps::EntityPlayer(maps::WorldClient(this->instance).getPlayerEntityByName.call(JavaUtil::StringToJString(name)), true)));
}
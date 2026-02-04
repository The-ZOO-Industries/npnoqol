#include "World.h"

World::World(const jobject instance)
    : JavaClass(instance)
{

}

World::~World() = default;

std::unique_ptr<WorldInfo> World::GetWorldInfo() const
{
    jni::frame f;

    return std::make_unique<WorldInfo>(jobject(maps::WorldInfo(maps::World(this->instance).worldInfo.get(), true)));
}

std::vector<std::unique_ptr<EntityPlayer>> World::GetPlayerEntities() const
{
    jni::frame f;

    std::vector<std::unique_ptr<EntityPlayer>> playerList;

    maps::List listWrapper = maps::World(this->instance).playerEntities.get();

    std::vector<maps::Object> vec = ((maps::Collection)listWrapper).toArray.call().to_vector();

    for (maps::Object& obj : vec)
    {
        playerList.emplace_back(std::make_unique<EntityPlayer>(jobject(maps::EntityPlayer(obj, true))));
    }

    return playerList;
}

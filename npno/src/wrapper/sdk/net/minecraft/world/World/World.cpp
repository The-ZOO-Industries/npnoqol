#include "World.h"

World::World(const jobject instance)
    : JavaClass(instance)
{

}

World::~World() = default;

std::unique_ptr<WorldInfo> World::GetWorldInfo() const
{
    jni::frame f;

    return std::make_unique<WorldInfo>(jni::make_global(maps::World(this->instance).worldInfo.get()));
}

std::vector<std::unique_ptr<EntityPlayer>> World::GetPlayerEntities() const
{
    jni::frame f;
    
    std::vector<std::unique_ptr<EntityPlayer>> playerList;

    maps::List playerEntities = maps::World(this->instance).playerEntities.get();
    std::vector<maps::Object> vec = playerEntities.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        playerList.emplace_back(std::make_unique<EntityPlayer>(jni::make_global(obj)));
    }

    return playerList;
}
#include "World.h"

World::World(maps::World instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

World::~World() = default;

std::unique_ptr<WorldInfo> World::GetWorldInfo() const
{
    maps::WorldInfo worldInfo = maps::World(this->instance.object_instance).worldInfo.get();
    maps::WorldInfo globalWorldInfo{ worldInfo.object_instance, true };
    return std::make_unique<WorldInfo>(globalWorldInfo);
}

std::vector<std::unique_ptr<EntityPlayer>> World::GetPlayerEntities() const
{
    std::vector<std::unique_ptr<EntityPlayer>> playerList;

    maps::List listWrapper = maps::World(this->instance.object_instance).playerEntities.get();
    maps::Collection collection{ listWrapper.object_instance, listWrapper.is_global() };
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::EntityPlayer player{ obj.object_instance, true };
        playerList.emplace_back(std::make_unique<EntityPlayer>(player));
    }

    return playerList;
}
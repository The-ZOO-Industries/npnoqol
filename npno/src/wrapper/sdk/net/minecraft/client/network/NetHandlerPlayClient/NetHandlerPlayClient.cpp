#include "NetHandlerPlayClient.h"

NetHandlerPlayClient::NetHandlerPlayClient(maps::NetHandlerPlayClient instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

NetHandlerPlayClient::~NetHandlerPlayClient() = default;

std::vector<std::unique_ptr<NetworkPlayerInfo>> NetHandlerPlayClient::GetPlayerInfoMap() const
{
    std::vector<std::unique_ptr<NetworkPlayerInfo>> playerList{};

    maps::Collection collection = maps::NetHandlerPlayClient(this->instance.object_instance).getPlayerInfoMap.call();
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::NetworkPlayerInfo playerInfo{ obj.object_instance, true };
        playerList.push_back(std::make_unique<NetworkPlayerInfo>(playerInfo));
    }

    return playerList;
}
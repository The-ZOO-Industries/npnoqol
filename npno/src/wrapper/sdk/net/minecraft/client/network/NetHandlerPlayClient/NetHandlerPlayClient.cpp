#include "NetHandlerPlayClient.h"

NetHandlerPlayClient::NetHandlerPlayClient(const jobject instance)
    : JavaClass(instance)
{

}

NetHandlerPlayClient::~NetHandlerPlayClient() = default;

auto NetHandlerPlayClient::GetPlayerInfoMap() const -> std::vector<std::unique_ptr<NetworkPlayerInfo>>
{
    jni::frame f;

    std::vector<std::unique_ptr<NetworkPlayerInfo>> playerList{};

    maps::Collection collection = maps::NetHandlerPlayClient(this->instance).getPlayerInfoMap.call();
    std::vector<maps::Object> vec = maps::Collection(collection, true).toArray.call().to_vector();

    for (maps::Object& obj : vec)
    {
        playerList.push_back(std::make_unique<NetworkPlayerInfo>(jobject(maps::NetworkPlayerInfo(obj, true))));
    }

    return playerList;
}
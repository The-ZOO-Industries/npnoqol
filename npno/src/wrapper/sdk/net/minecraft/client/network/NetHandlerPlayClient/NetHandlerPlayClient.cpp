#include "NetHandlerPlayClient.h"

NetHandlerPlayClient::NetHandlerPlayClient(const jobject instance) 
    : JavaClass(instance) 
{
    
}

NetHandlerPlayClient::~NetHandlerPlayClient() = default;

std::vector<std::unique_ptr<NetworkPlayerInfo>> NetHandlerPlayClient::GetPlayerInfoMap() const 
{
    jni::frame f;
    std::vector<std::unique_ptr<NetworkPlayerInfo>> playerList;

    maps::Collection collection = maps::NetHandlerPlayClient(this->instance).getPlayerInfoMap.call();
    std::vector<maps::Object> vec = collection.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        playerList.push_back(std::make_unique<NetworkPlayerInfo>(jni::make_global(obj)));
    }

    return playerList;
}
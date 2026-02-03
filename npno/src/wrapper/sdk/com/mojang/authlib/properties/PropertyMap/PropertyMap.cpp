#include "PropertyMap.h"

PropertyMap::PropertyMap(const jobject instance)
    : JavaClass(instance)
{

}

PropertyMap::~PropertyMap() = default;

std::vector<std::unique_ptr<Property>> PropertyMap::GetValues() const
{
    jni::frame f;

    std::vector<std::unique_ptr<Property>> properties;

    maps::Collection collection = maps::PropertyMap(this->instance).values.call();
    std::vector<maps::Object> vec = collection.toArray().to_vector();

    for (maps::Object& obj : vec)
    {
        properties.push_back(std::make_unique<Property>(jobject(maps::Property(obj, true))));
    }

    return properties;
}
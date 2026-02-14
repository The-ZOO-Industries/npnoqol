#include "PropertyMap.h"

PropertyMap::PropertyMap(maps::PropertyMap instance)
    : JavaClass(maps::Object(instance.object_instance, instance.is_global()))
{

}

PropertyMap::~PropertyMap() = default;

std::vector<std::unique_ptr<Property>> PropertyMap::GetValues() const
{
    std::vector<std::unique_ptr<Property>> properties;

    maps::Collection collection = maps::PropertyMap(this->instance.object_instance).values.call();
    jni::array<maps::Object> array = collection.toArray.call();
    std::vector<maps::Object> vec = array.to_vector();

    for (maps::Object& obj : vec)
    {
        maps::Property property{ obj.object_instance, true };
        properties.push_back(std::make_unique<Property>(property));
    }

    return properties;
}
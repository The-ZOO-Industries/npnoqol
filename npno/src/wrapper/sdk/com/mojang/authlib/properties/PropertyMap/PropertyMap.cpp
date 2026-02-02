#include "PropertyMap.h"

#include "../../src/wrapper/sdk/java/util/Collection/Collection.h"

PropertyMap::PropertyMap(const jobject instance)
    : JavaClass("com/mojang/authlib/properties/PropertyMap", instance)
{
    this->Init();
}

PropertyMap::~PropertyMap() = default;

void PropertyMap::Init()
{
    std::call_once(oflag, [this]
        {
            valuesMethodID = Jvm::env->GetMethodID(this->javaClass, "values", "()Ljava/util/Collection;");
        });
}

std::vector<std::unique_ptr<Property>> PropertyMap::GetValues() const
{
    std::vector<std::unique_ptr<Property>> properties;

    const jobject collectionLocal = Jvm::env->CallObjectMethod(this->instance, valuesMethodID);

    const std::unique_ptr<Collection> getProperty = std::make_unique<Collection>(collectionLocal);
    const jobjectArray arrayLocal = static_cast<jobjectArray>(getProperty->ToArray());

    for (jint i = 0; i < getProperty->Size(); ++i)
    {
        const jobject elementLocal = Jvm::env->GetObjectArrayElement(arrayLocal, i);
        properties.push_back(std::make_unique<Property>(elementLocal));
        Jvm::env->DeleteLocalRef(elementLocal);
    }

    Jvm::env->DeleteLocalRef(arrayLocal);
    Jvm::env->DeleteLocalRef(collectionLocal);

    return properties;
}
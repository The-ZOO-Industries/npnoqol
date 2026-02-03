#pragma once

#include <meta_jni/meta_jni.hpp>

namespace maps
{
    BEGIN_KLASS_DEF(Object, "java/lang/Object")
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(String, "java/lang/String")
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(Collection, "java/util/Collection")
        jni::method<jint, "size"> size{ *this };
        jni::method<jni::array<Object>, "toArray"> toArray{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF_EX(List, "java/util/List", Collection)
        jni::method<Object, "get", jni::NOT_STATIC, jint> get{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(UUID, "java/util/UUID")
        jni::method<jint, "version"> version{ *this };
        jni::method<String, "toString"> toString{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(GameProfile, "com/mojang/authlib/GameProfile")
        jni::method<String, "getName"> getName{ *this };
        jni::method<PropertyMap, "getProperties"> getProperties{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(Property, "com/mojang/authlib/properties/Property")
        jni::method<String, "getValue"> getValue{ *this };
        jni::method<String, "getName"> getName{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(PropertyMap, "com/mojang/authlib/properties/PropertyMap")
        jni::method<Collection, "values"> values{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF_EX(ChatComponentText, "net/minecraft/util/ChatComponentText", IChatComponent)
        jni::constructor<String> constructor{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(IChatComponent, "net/minecraft/util/IChatComponent")
        jni::method<String, "getFormattedText"> getFormattedText{ *this };
        jni::method<String, "getUnformattedText"> getUnformattedText{ *this };
    END_KLASS_DEF()

    BEGIN_KLASS_DEF(World, "net/minecraft/world/World")
        jni::field<WorldInfo, "worldInfo"> worldInfo{ *this };
        jni::field<List, "playerEntities"> playerEntities{ *this };
    END_KLASS_DEF()
}
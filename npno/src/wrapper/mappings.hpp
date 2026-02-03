#pragma once

#include <meta_jni/meta_jni.hpp>

namespace maps
{
    KLASS_DECLARATION(Object, "java/lang/Object");
    KLASS_DECLARATION(String, "java/lang/String");
    KLASS_DECLARATION(Collection, "java/util/Collection");
    KLASS_DECLARATION(List, "java/util/List");
    KLASS_DECLARATION(UUID, "java/util/UUID");
    KLASS_DECLARATION(Property, "com/mojang/authlib/properties/Property");
    KLASS_DECLARATION(PropertyMap, "com/mojang/authlib/properties/PropertyMap");
    KLASS_DECLARATION(GameProfile, "com/mojang/authlib/GameProfile");
    KLASS_DECLARATION(IChatComponent, "net/minecraft/util/IChatComponent");
    KLASS_DECLARATION(ChatComponentText, "net/minecraft/util/ChatComponentText");
    KLASS_DECLARATION(ChatLine, "net/minecraft/client/gui/ChatLine");
    KLASS_DECLARATION(GuiNewChat, "net/minecraft/client/gui/GuiNewChat");
    KLASS_DECLARATION(GuiPlayerTabOverlay, "net/minecraft/client/gui/GuiPlayerTabOverlay");
    KLASS_DECLARATION(GuiIngame, "net/minecraft/client/gui/GuiIngame");
    KLASS_DECLARATION(NetworkPlayerInfo, "net/minecraft/client/network/NetworkPlayerInfo");
    KLASS_DECLARATION(NetHandlerPlayClient, "net/minecraft/client/network/NetHandlerPlayClient");
    KLASS_DECLARATION(PotionEffect, "net/minecraft/potion/PotionEffect");
    KLASS_DECLARATION(Entity, "net/minecraft/entity/Entity");
    KLASS_DECLARATION(EntityLivingBase, "net/minecraft/entity/EntityLivingBase");
    KLASS_DECLARATION(EntityPlayer, "net/minecraft/entity/player/EntityPlayer");
    KLASS_DECLARATION(EntityPlayerSP, "net/minecraft/client/entity/EntityPlayerSP");
    KLASS_DECLARATION(Score, "net/minecraft/scoreboard/Score");
    KLASS_DECLARATION(ScoreObjective, "net/minecraft/scoreboard/ScoreObjective");
    KLASS_DECLARATION(ScorePlayerTeam, "net/minecraft/scoreboard/ScorePlayerTeam");
    KLASS_DECLARATION(Scoreboard, "net/minecraft/scoreboard/Scoreboard");
    KLASS_DECLARATION(WorldInfo, "net/minecraft/world/storage/WorldInfo");
    KLASS_DECLARATION(World, "net/minecraft/world/World");
    KLASS_DECLARATION(WorldClient, "net/minecraft/client/multiplayer/WorldClient");
    KLASS_DECLARATION(Minecraft, "net/minecraft/client/Minecraft");

    BEGIN_KLASS_MEMBERS(Object)
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(String)
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(Collection)
        jni::method<jint, "size"> size{ *this };
        jni::method<jni::array<Object>, "toArray"> toArray{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS_EX(List, Collection)
        jni::method<Object, "get", jni::NOT_STATIC, jint> get{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(UUID)
        jni::method<jint, "version"> version{ *this };
        jni::method<String, "toString"> toString{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(Property)
        jni::method<String, "getValue"> getValue{ *this };
        jni::method<String, "getName"> getName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(PropertyMap)
        jni::method<Collection, "values"> values{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(GameProfile)
        jni::method<String, "getName"> getName{ *this };
        jni::method<PropertyMap, "getProperties"> getProperties{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(IChatComponent)
        jni::method<String, "getFormattedText"> getFormattedText{ *this };
        jni::method<String, "getUnformattedText"> getUnformattedText{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS_EX(ChatComponentText, IChatComponent)
        jni::constructor<String> constructor{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(ChatLine)
        jni::field<jint, "chatLineID"> chatLineID{ *this };
        jni::field<IChatComponent, "lineString"> lineString{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(GuiNewChat)
        jni::field<List, "chatLines"> chatLines{ *this };
        jni::method<void, "refreshChat"> refreshChat{ *this };
        jni::method<void, "deleteChatLine", jni::NOT_STATIC, jint> deleteChatLine{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(GuiPlayerTabOverlay)
        jni::method<String, "getPlayerName", jni::NOT_STATIC, NetworkPlayerInfo> getPlayerName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(GuiIngame)
        jni::field<GuiNewChat, "persistantChatGUI"> persistantChatGUI{ *this };
        jni::field<GuiPlayerTabOverlay, "overlayPlayerList"> overlayPlayerList{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(NetworkPlayerInfo)
        jni::method<GameProfile, "getGameProfile"> getGameProfile{ *this };
        jni::method<IChatComponent, "getDisplayName"> getDisplayName{ *this };
        jni::method<void, "setDisplayName", jni::NOT_STATIC, IChatComponent> setDisplayName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(NetHandlerPlayClient)
        jni::method<Collection, "getPlayerInfoMap"> getPlayerInfoMap{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(PotionEffect)
        jni::method<jint, "getDuration"> getDuration{ *this };
        jni::method<jint, "getAmplifier"> getAmplifier{ *this };
        jni::method<String, "getEffectName"> getEffectName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(Entity)
        jni::method<jboolean, "isSprinting"> isSprinting{ *this };
        jni::method<jboolean, "isSneaking"> isSneaking{ *this };
        jni::method<jboolean, "isInvisible"> isInvisible{ *this };
        jni::method<jboolean, "isEating"> isEating{ *this };
        jni::method<jboolean, "isRiding"> isRiding{ *this };
        jni::method<UUID, "getUniqueID"> getUniqueID{ *this };
        jni::method<String, "getName"> getName{ *this };
        jni::method<void, "addChatMessage", jni::NOT_STATIC, IChatComponent> addChatMessage{ *this };
        jni::field<jboolean, "onGround"> onGround{ *this };
        jni::field<jfloat, "rotationYaw"> rotationYaw{ *this };
        jni::field<jfloat, "rotationPitch"> rotationPitch{ *this };
        jni::field<jfloat, "prevRotationYaw"> prevRotationYaw{ *this };
        jni::field<jfloat, "prevRotationPitch"> prevRotationPitch{ *this };
        jni::field<jdouble, "posX"> posX{ *this };
        jni::field<jdouble, "posY"> posY{ *this };
        jni::field<jdouble, "posZ"> posZ{ *this };
        jni::field<jdouble, "lastTickPosX"> lastTickPosX{ *this };
        jni::field<jdouble, "lastTickPosY"> lastTickPosY{ *this };
        jni::field<jdouble, "lastTickPosZ"> lastTickPosZ{ *this };
        jni::field<jdouble, "motionX"> motionX{ *this };
        jni::field<jdouble, "motionY"> motionY{ *this };
        jni::field<jdouble, "motionZ"> motionZ{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS_EX(EntityLivingBase, Entity)
        jni::method<jfloat, "getHealth"> getHealth{ *this };
        jni::method<jfloat, "getMaxHealth"> getMaxHealth{ *this };
        jni::method<jfloat, "getAbsorptionAmount"> getAbsorptionAmount{ *this };
        jni::method<Collection, "getActivePotionEffects"> getActivePotionEffects{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS_EX(EntityPlayer, EntityLivingBase)
        jni::method<jboolean, "isSpectator"> isSpectator{ *this };
        jni::method<jboolean, "isBlocking"> isBlocking{ *this };
        jni::method<jboolean, "canAttackPlayer", jni::NOT_STATIC, EntityPlayer> canAttackPlayer{ *this };
        jni::method<String, "getCustomNameTag"> getCustomNameTag{ *this };
        jni::method<GameProfile, "getGameProfile"> getGameProfile{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS_EX(EntityPlayerSP, EntityPlayer)
        jni::field<NetHandlerPlayClient, "sendQueue"> sendQueue{ *this };
        jni::method<void, "sendChatMessage", jni::NOT_STATIC, String> sendChatMessage{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(Score)
        jni::method<jint, "getScorePoints"> getScorePoints{ *this };
        jni::method<String, "getPlayerName"> getPlayerName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(ScoreObjective)
        jni::method<String, "getName"> getName{ *this };
        jni::method<String, "getDisplayName"> getDisplayName{ *this };
        jni::method<void, "setDisplayName", jni::NOT_STATIC, String> setDisplayName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(ScorePlayerTeam)
        jni::method<String, "getColorPrefix"> getColorPrefix{ *this };
        jni::method<String, "getColorSuffix"> getColorSuffix{ *this };
        jni::method<String, "getTeamName"> getTeamName{ *this };
        jni::method<Collection, "getMembershipCollection"> getMembershipCollection{ *this };
        jni::method<void, "setNamePrefix", jni::NOT_STATIC, String> setNamePrefix{ *this };
        jni::method<void, "setNameSuffix", jni::NOT_STATIC, String> setNameSuffix{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(Scoreboard)
        jni::method<jboolean, "addPlayerToTeam", jni::NOT_STATIC, String, String> addPlayerToTeam{ *this };
        jni::method<ScorePlayerTeam, "getTeam", jni::NOT_STATIC, String> getTeam{ *this };
        jni::method<ScorePlayerTeam, "getPlayersTeam", jni::NOT_STATIC, String> getPlayersTeam{ *this };
        jni::method<ScorePlayerTeam, "createTeam", jni::NOT_STATIC, String> createTeam{ *this };
        jni::method<ScoreObjective, "getObjectiveInDisplaySlot", jni::NOT_STATIC, jint> getObjectiveInDisplaySlot{ *this };
        jni::method<Collection, "getTeams"> getTeams{ *this };
        jni::method<Collection, "getSortedScores", jni::NOT_STATIC, ScoreObjective> getSortedScores{ *this };
        jni::method<void, "removeTeam", jni::NOT_STATIC, ScorePlayerTeam> removeTeam{ *this };
        jni::method<void, "removePlayerFromTeam", jni::NOT_STATIC, String, ScorePlayerTeam> removePlayerFromTeam{ *this };
        jni::method<void, "setObjectiveInDisplaySlot", jni::NOT_STATIC, jint, ScoreObjective> setObjectiveInDisplaySlot{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(World)
        jni::field<WorldInfo, "worldInfo"> worldInfo{ *this };
        jni::field<List, "playerEntities"> playerEntities{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS_EX(WorldClient, World)
        jni::method<Scoreboard, "getScoreboard"> getScoreboard{ *this };
        jni::method<EntityPlayer, "getPlayerEntityByName", jni::NOT_STATIC, String> getPlayerEntityByName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(WorldInfo)
        jni::field<jlong, "randomSeed"> randomSeed{ *this };
        jni::field<jlong, "worldTime"> worldTime{ *this };
        jni::field<String, "worldName"> worldName{ *this };
    END_KLASS_MEMBERS()

    BEGIN_KLASS_MEMBERS(Minecraft)
        jni::field<Minecraft, "theMinecraft", jni::STATIC> theMinecraft{ *this };
        jni::field<EntityPlayerSP, "thePlayer"> thePlayer{ *this };
        jni::field<WorldClient, "theWorld"> theWorld{ *this };
        jni::field<GuiIngame, "ingameGUI"> ingameGUI{ *this };
    END_KLASS_MEMBERS()
}
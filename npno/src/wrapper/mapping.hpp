#pragma once

#include "mapping_json.hpp"

#include <string>
#include <map>

#include <nlohmann/json.hpp>
#include <easy_jni/easy_jni.hpp>

namespace mapping
{
	enum class mapping_mode : std::int8_t
	{
		MCP,
		OBF,
		SRG
	};

	inline mapping_mode mode{ mapping_mode::MCP };

	namespace game_profile
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getName{ nullptr };
	}

	namespace entity_player_sp
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* sendChatMessage{ nullptr };
		inline const char* addChatMessage{ nullptr };
		inline const char* sendQueue{ nullptr };
	}

	namespace gui_ingame
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* persistantChatGUI{ nullptr };
	}

	namespace gui_new_chat
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* printChatMessage{ nullptr };
	}

	namespace world_client
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getScoreboard{ nullptr };
		inline const char* getPlayerEntityByName{ nullptr };
		inline const char* addEntityToWorld{ nullptr };
	}

	namespace net_handler_play_client
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getPlayerInfoMap{ nullptr };
	}

	namespace network_player_info
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getGameProfile{ nullptr };
		inline const char* getDisplayName{ nullptr };
		inline const char* setDisplayName{ nullptr };
	}

	namespace minecraft
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* theMinecraft{ nullptr };
		inline const char* thePlayer{ nullptr };
		inline const char* theWorld{ nullptr };
		inline const char* ingameGUI{ nullptr };
		inline const char* loadWorld{ nullptr };
	}

	namespace entity_armor_stand
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };
	}

	namespace entity_player
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getName{ nullptr };
		inline const char* inventory{ nullptr };
	}

	namespace inventory_player
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* armorItemInSlot{ nullptr };
	}

	namespace entity
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getUniqueID{ nullptr };
		inline const char* isDead{ nullptr };
		inline const char* setCustomNameTag{ nullptr };
		inline const char* setInvisible{ nullptr };
		inline const char* setPosition{ nullptr };
		inline const char* posX{ nullptr };
		inline const char* posY{ nullptr };
		inline const char* posZ{ nullptr };
		inline const char* entityId{ nullptr };
		inline const char* setAlwaysRenderNameTag{ nullptr };
	}

	namespace entity_living_base
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getHealth{ nullptr };
		inline const char* getMaxHealth{ nullptr };
		inline const char* getAbsorptionAmount{ nullptr };
		inline const char* getActivePotionEffects{ nullptr };
	}

	namespace item_stack
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getDisplayName{ nullptr };
	}

	namespace potion_effect
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getDuration{ nullptr };
		inline const char* getEffectName{ nullptr };
	}

	namespace i_score_objective_criteria
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };
	}

	namespace score
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* scorePoints{ nullptr };
	}

	namespace score_dummy_criteria
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };
	}

	namespace score_objective
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* name{ nullptr };
		inline const char* displayName{ nullptr };
	}

	namespace score_player_team
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getTeamName{ nullptr };
		inline const char* getMembershipCollection{ nullptr };
		inline const char* getColorPrefix{ nullptr };
		inline const char* getColorSuffix{ nullptr };
		inline const char* setNamePrefix{ nullptr };
		inline const char* setNameSuffix{ nullptr };
	}

	namespace scoreboard
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getTeams{ nullptr };
		inline const char* getTeam{ nullptr };
		inline const char* createTeam{ nullptr };
		inline const char* removePlayerFromTeam{ nullptr };
		inline const char* removeTeam{ nullptr };
		inline const char* getPlayersTeam{ nullptr };
		inline const char* addPlayerToTeam{ nullptr };
		inline const char* setObjectiveInDisplaySlot{ nullptr };
		inline const char* getObjectiveInDisplaySlot{ nullptr };
		inline const char* getScoreObjectives{ nullptr };
		inline const char* getObjective{ nullptr };
		inline const char* addScoreObjective{ nullptr };
		inline const char* getValueFromObjective{ nullptr };
	}

	namespace chat_component_text
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };
	}

	namespace i_chat_component
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* getFormattedText{ nullptr };
		inline const char* getUnformattedText{ nullptr };
	}

	namespace world
	{
		inline const char* clazz{ nullptr };
		inline const char* signature{ nullptr };

		inline const char* playerEntities{ nullptr };
	}

	static auto load_class_mappings(const nlohmann::json& jclass, const char** class_target, const char** signature)
		-> void
	{
		if (jclass.is_null() || jclass.is_discarded())
		{
			std::println("[ERROR] load_class_mappings received null/missing JSON node");
			return;
		}

		std::string target;
		switch (mode)
		{
		case mapping_mode::MCP:
			target = jclass["mcp"].get<std::string>();
			break;
		case mapping_mode::OBF:
			target = jclass["obf"].get<std::string>();
			break;
		case mapping_mode::SRG:
			target = jclass["mcp"].get<std::string>();
			break;
		}

		*class_target = _strdup(target.c_str());
		*signature = _strdup(("L" + target + ";").c_str());
	}

	static auto load_attributes(const nlohmann::json& attributes, std::map<std::string, const char**> mapping)
		-> void
	{
		for (auto& [key, value] : attributes.items())
		{
			if (mapping.contains(key))
			{
				std::string val;
				switch (mode)
				{
				case mapping_mode::MCP:
					val = value["mcp"].get<std::string>();
					break;
				case mapping_mode::OBF:
					val = value["obf"].get<std::string>();
					break;
				case mapping_mode::SRG:
					val = value["srg"].get<std::string>();
					break;
				}
				*mapping[key] = _strdup(val.c_str());
			}
		}
	}

	static auto init()
		-> bool
	{
		const jclass mc_class{ jni::get_class("net/minecraft/client/Minecraft") };
		if (mc_class)
		{
			jfieldID fieldID{ jni::get_env()->GetStaticFieldID(mc_class, "theMinecraft", "Lnet/minecraft/client/Minecraft;") };
			if (fieldID)
			{
				std::println("[INFO] Using MCP mapping");
				mode = mapping_mode::MCP;
			}
			else
			{
				fieldID = jni::get_env()->GetStaticFieldID(mc_class, "field_71432_P", "Lnet/minecraft/client/Minecraft;");
				if (fieldID)
				{
					std::println("[INFO] Using SRG mapping");
					mode = mapping_mode::SRG;
				}
				else
				{
					std::println("[INFO] Cannot inject in this client");
					return false;
				}
			}
		}
		else if (jni::get_class("ave"))
		{
			std::println("[INFO] Using OBF mapping");
			mode = mapping_mode::OBF;
		}
		else
		{
			std::println("[INFO] Cannot inject in this client");
			return false;
		}

		auto jsonObject = nlohmann::json::parse(mapping::json);
		auto& classesArray = jsonObject["Classes"];

		auto& gameProfileData = classesArray["net_minecraft_util_GameProfile"];
		load_class_mappings(gameProfileData, &game_profile::clazz, &game_profile::signature);
		load_attributes(gameProfileData["attributes"],
			{
				{"getName", &game_profile::getName}
			});

		auto& entityPlayerSPData = classesArray["net_minecraft_client_entity_EntityPlayerSP"];
		load_class_mappings(entityPlayerSPData, &entity_player_sp::clazz, &entity_player_sp::signature);
		load_attributes(entityPlayerSPData["attributes"],
			{
				{"sendChatMessage", &entity_player_sp::sendChatMessage},
				{"addChatMessage",  &entity_player_sp::addChatMessage},
				{"sendQueue",       &entity_player_sp::sendQueue}
			});

		auto& guiIngameData = classesArray["net_minecraft_client_gui_GuiIngame"];
		load_class_mappings(guiIngameData, &gui_ingame::clazz, &gui_ingame::signature);
		load_attributes(guiIngameData["attributes"],
			{
				{"persistantChatGUI", &gui_ingame::persistantChatGUI}
			});

		auto& guiNewChatData = classesArray["net_minecraft_client_gui_GuiNewChat"];
		load_class_mappings(guiNewChatData, &gui_new_chat::clazz, &gui_new_chat::signature);
		load_attributes(guiNewChatData["attributes"],
			{
				{"printChatMessage", &gui_new_chat::printChatMessage}
			});

		auto& worldClientData = classesArray["net_minecraft_client_multiplayer_WorldClient"];
		load_class_mappings(worldClientData, &world_client::clazz, &world_client::signature);
		load_attributes(worldClientData["attributes"],
			{
				{"getScoreboard",         &world_client::getScoreboard},
				{"getPlayerEntityByName", &world_client::getPlayerEntityByName},
				{"addEntityToWorld",      &world_client::addEntityToWorld}
			});

		auto& netHandlerData = classesArray["net_minecraft_client_network_NetHandlerPlayClient"];
		load_class_mappings(netHandlerData, &net_handler_play_client::clazz, &net_handler_play_client::signature);
		load_attributes(netHandlerData["attributes"],
			{
				{"getPlayerInfoMap", &net_handler_play_client::getPlayerInfoMap}
			});

		auto& networkPlayerInfoData = classesArray["net_minecraft_client_network_NetworkPlayerInfo"];
		load_class_mappings(networkPlayerInfoData, &network_player_info::clazz, &network_player_info::signature);
		load_attributes(networkPlayerInfoData["attributes"],
			{
				{"getGameProfile", &network_player_info::getGameProfile},
				{"getDisplayName", &network_player_info::getDisplayName},
				{"setDisplayName", &network_player_info::setDisplayName}
			});

		auto& minecraftData = classesArray["net_minecraft_client_Minecraft"];
		load_class_mappings(minecraftData, &minecraft::clazz, &minecraft::signature);
		load_attributes(minecraftData["attributes"],
			{
				{"theMinecraft", &minecraft::theMinecraft},
				{"thePlayer",    &minecraft::thePlayer},
				{"theWorld",     &minecraft::theWorld},
				{"ingameGUI",    &minecraft::ingameGUI},
				{"loadWorld",    &minecraft::loadWorld}
			});

		auto& entityArmorStandData = classesArray["net_minecraft_entity_item_EntityArmorStand"];
		load_class_mappings(entityArmorStandData, &entity_armor_stand::clazz, &entity_armor_stand::signature);

		auto& entityPlayerData = classesArray["net_minecraft_entity_player_EntityPlayer"];
		load_class_mappings(entityPlayerData, &entity_player::clazz, &entity_player::signature);
		load_attributes(entityPlayerData["attributes"],
			{
				{"getName",    &entity_player::getName},
				{"inventory",  &entity_player::inventory}
			});

		auto& inventoryPlayerData = classesArray["net_minecraft_entity_player_InventoryPlayer"];
		load_class_mappings(inventoryPlayerData, &inventory_player::clazz, &inventory_player::signature);
		load_attributes(inventoryPlayerData["attributes"],
			{
				{"armorItemInSlot", &inventory_player::armorItemInSlot}
			});

		auto& entityData = classesArray["net_minecraft_entity_Entity"];
		load_class_mappings(entityData, &entity::clazz, &entity::signature);
		load_attributes(entityData["attributes"],
			{
				{"posX",                   &entity::posX},
				{"posY",                   &entity::posY},
				{"posZ",                   &entity::posZ},
				{"entityId",               &entity::entityId},
				{"getUniqueID",            &entity::getUniqueID},
				{"isDead",                 &entity::isDead},
				{"setCustomNameTag",       &entity::setCustomNameTag},
				{"setInvisible",           &entity::setInvisible},
				{"setPosition",            &entity::setPosition},
				{"setAlwaysRenderNameTag", &entity::setAlwaysRenderNameTag}
			});

		auto& entityLivingBaseData = classesArray["net_minecraft_entity_EntityLivingBase"];
		load_class_mappings(entityLivingBaseData, &entity_living_base::clazz, &entity_living_base::signature);
		load_attributes(entityLivingBaseData["attributes"],
			{
				{"getHealth",              &entity_living_base::getHealth},
				{"getMaxHealth",           &entity_living_base::getMaxHealth},
				{"getAbsorptionAmount",    &entity_living_base::getAbsorptionAmount},
				{"getActivePotionEffects", &entity_living_base::getActivePotionEffects}
			});

		auto& itemStackData = classesArray["net_minecraft_item_ItemStack"];
		load_class_mappings(itemStackData, &item_stack::clazz, &item_stack::signature);
		load_attributes(itemStackData["attributes"],
			{
				{"getDisplayName", &item_stack::getDisplayName}
			});

		auto& potionEffectData = classesArray["net_minecraft_potion_PotionEffect"];
		load_class_mappings(potionEffectData, &potion_effect::clazz, &potion_effect::signature);
		load_attributes(potionEffectData["attributes"],
			{
				{"getDuration",   &potion_effect::getDuration},
				{"getEffectName", &potion_effect::getEffectName}
			});

		auto& iScoreObjCriteriaData = classesArray["net_minecraft_scoreboard_IScoreObjectiveCriteria"];
		load_class_mappings(iScoreObjCriteriaData, &i_score_objective_criteria::clazz, &i_score_objective_criteria::signature);

		auto& scoreData = classesArray["net_minecraft_scoreboard_Score"];
		load_class_mappings(scoreData, &score::clazz, &score::signature);
		load_attributes(scoreData["attributes"],
			{
				{"scorePoints", &score::scorePoints}
			});

		auto& scoreDummyCriteriaData = classesArray["net_minecraft_scoreboard_ScoreDummyCriteria"];
		load_class_mappings(scoreDummyCriteriaData, &score_dummy_criteria::clazz, &score_dummy_criteria::signature);

		auto& scoreObjectiveData = classesArray["net_minecraft_scoreboard_ScoreObjective"];
		load_class_mappings(scoreObjectiveData, &score_objective::clazz, &score_objective::signature);
		load_attributes(scoreObjectiveData["attributes"],
			{
				{"name",        &score_objective::name},
				{"displayName", &score_objective::displayName}
			});

		auto& scorePlayerTeamData = classesArray["net_minecraft_scoreboard_ScorePlayerTeam"];
		load_class_mappings(scorePlayerTeamData, &score_player_team::clazz, &score_player_team::signature);
		load_attributes(scorePlayerTeamData["attributes"],
			{
				{"getTeamName",             &score_player_team::getTeamName},
				{"getMembershipCollection", &score_player_team::getMembershipCollection},
				{"getColorPrefix",          &score_player_team::getColorPrefix},
				{"getColorSuffix",          &score_player_team::getColorSuffix},
				{"setNamePrefix",           &score_player_team::setNamePrefix},
				{"setNameSuffix",           &score_player_team::setNameSuffix}
			});

		auto& scoreboardData = classesArray["net_minecraft_scoreboard_Scoreboard"];
		load_class_mappings(scoreboardData, &scoreboard::clazz, &scoreboard::signature);
		load_attributes(scoreboardData["attributes"],
			{
				{"getTeams",                 &scoreboard::getTeams},
				{"getTeam",                  &scoreboard::getTeam},
				{"createTeam",               &scoreboard::createTeam},
				{"removePlayerFromTeam",     &scoreboard::removePlayerFromTeam},
				{"removeTeam",               &scoreboard::removeTeam},
				{"getPlayersTeam",           &scoreboard::getPlayersTeam},
				{"addPlayerToTeam",          &scoreboard::addPlayerToTeam},
				{"setObjectiveInDisplaySlot",&scoreboard::setObjectiveInDisplaySlot},
				{"getObjectiveInDisplaySlot",&scoreboard::getObjectiveInDisplaySlot},
				{"getScoreObjectives",       &scoreboard::getScoreObjectives},
				{"getObjective",             &scoreboard::getObjective},
				{"addScoreObjective",        &scoreboard::addScoreObjective},
				{"getValueFromObjective",    &scoreboard::getValueFromObjective}
			});

		auto& chatComponentTextData = classesArray["net_minecraft_util_ChatComponentText"];
		load_class_mappings(chatComponentTextData, &chat_component_text::clazz, &chat_component_text::signature);

		auto& iChatComponentData = classesArray["net_minecraft_util_IChatComponent"];
		load_class_mappings(iChatComponentData, &i_chat_component::clazz, &i_chat_component::signature);
		load_attributes(iChatComponentData["attributes"],
			{
				{"getFormattedText",   &i_chat_component::getFormattedText},
				{"getUnformattedText", &i_chat_component::getUnformattedText}
			});

		auto& worldData = classesArray["net_minecraft_world_World"];
		load_class_mappings(worldData, &world::clazz, &world::signature);
		load_attributes(worldData["attributes"],
			{
				{"playerEntities", &world::playerEntities}
			});

		return true;
	}
}
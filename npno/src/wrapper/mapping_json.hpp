#pragma once

#include <string>

namespace mapping
{
    inline const std::string json =
        R"(
{
  "Classes": {
    "net_minecraft_client_Minecraft": {
      "mcp": "net/minecraft/client/Minecraft",
      "obf": "ave",
      "attributes": {
        "theMinecraft": {"mcp": "theMinecraft", "obf": "S",  "srg": "field_71432_P"},
        "thePlayer":    {"mcp": "thePlayer",    "obf": "h",  "srg": "field_71439_g"},
        "theWorld":     {"mcp": "theWorld",     "obf": "f",  "srg": "field_71441_e"},
        "ingameGUI":    {"mcp": "ingameGUI",    "obf": "q",  "srg": "field_71456_v"},
        "loadWorld":    {"mcp": "loadWorld",    "obf": "a",  "srg": "func_71353_a"}
      }
    },
    "net_minecraft_util_GameProfile": {
      "mcp": "com/mojang/authlib/GameProfile",
      "obf": "com/mojang/authlib/GameProfile",
      "attributes": {
        "getName": {"mcp": "getName", "obf": "getName", "srg": "getName"}
      }
    },
    "net_minecraft_client_entity_EntityPlayerSP": {
      "mcp": "net/minecraft/client/entity/EntityPlayerSP",
      "obf": "bew",
      "attributes": {
        "sendChatMessage": {"mcp": "sendChatMessage", "obf": "e", "srg": "func_71165_d"},
        "addChatMessage":  {"mcp": "addChatMessage",  "obf": "a", "srg": "func_145747_a"},
        "sendQueue":       {"mcp": "sendQueue",       "obf": "a", "srg": "field_71174_a"}
      }
    },
    "net_minecraft_client_gui_GuiIngame": {
      "mcp": "net/minecraft/client/gui/GuiIngame",
      "obf": "avo",
      "attributes": {
        "persistantChatGUI": {"mcp": "persistantChatGUI", "obf": "l", "srg": "field_73840_e"}
      }
    },
    "net_minecraft_client_gui_GuiNewChat": {
      "mcp": "net/minecraft/client/gui/GuiNewChat",
      "obf": "avq",
      "attributes": {
        "printChatMessage": {"mcp": "printChatMessage", "obf": "a", "srg": "func_146227_a"}
      }
    },
    "net_minecraft_client_multiplayer_WorldClient": {
      "mcp": "net/minecraft/client/multiplayer/WorldClient",
      "obf": "bdb",
      "attributes": {
        "getScoreboard":         {"mcp": "getScoreboard",         "obf": "Z", "srg": "func_96441_U"},
        "getPlayerEntityByName": {"mcp": "getPlayerEntityByName", "obf": "a", "srg": "func_72924_a"},
        "addEntityToWorld":      {"mcp": "addEntityToWorld",      "obf": "a", "srg": "func_73027_a"}
      }
    },
    "net_minecraft_client_network_NetHandlerPlayClient": {
      "mcp": "net/minecraft/client/network/NetHandlerPlayClient",
      "obf": "bcy",
      "attributes": {
        "getPlayerInfoMap": {"mcp": "getPlayerInfoMap", "obf": "d", "srg": "func_175106_d"}
      }
    },
    "net_minecraft_client_network_NetworkPlayerInfo": {
      "mcp": "net/minecraft/client/network/NetworkPlayerInfo",
      "obf": "bdc",
      "attributes": {
        "getGameProfile": {"mcp": "getGameProfile", "obf": "a", "srg": "func_178845_a"},
        "getDisplayName": {"mcp": "getDisplayName", "obf": "k", "srg": "func_178854_k"},
        "setDisplayName": {"mcp": "setDisplayName", "obf": "a", "srg": "func_178859_a"}
      }
    },
    "net_minecraft_entity_item_EntityArmorStand": {
      "mcp": "net/minecraft/entity/item/EntityArmorStand",
      "obf": "um",
      "attributes": {}
    },
    "net_minecraft_entity_player_EntityPlayer": {
      "mcp": "net/minecraft/entity/player/EntityPlayer",
      "obf": "wn",
      "attributes": {
        "inventory": {"mcp": "inventory", "obf": "bi", "srg": "field_71071_by"},
        "getName":   {"mcp": "getName",   "obf": "e_", "srg": "func_70005_c_"}
      }
    },
    "net_minecraft_entity_player_InventoryPlayer": {
      "mcp": "net/minecraft/entity/player/InventoryPlayer",
      "obf": "wm",
      "attributes": {
        "armorItemInSlot": {"mcp": "armorItemInSlot", "obf": "e", "srg": "func_70440_f"}
      }
    },
    "net_minecraft_entity_Entity": {
      "mcp": "net/minecraft/entity/Entity",
      "obf": "pk",
      "attributes": {
        "posX":                  {"mcp": "posX",                  "obf": "s",  "srg": "field_70165_t"},
        "posY":                  {"mcp": "posY",                  "obf": "t",  "srg": "field_70163_u"},
        "posZ":                  {"mcp": "posZ",                  "obf": "u",  "srg": "field_70161_v"},
        "entityId":              {"mcp": "entityId",              "obf": "",   "srg": "field_145783_c"},
        "getUniqueID":           {"mcp": "getUniqueID",           "obf": "aK", "srg": "func_110124_au"},
        "isDead":                {"mcp": "isDead",                "obf": "I",  "srg": "field_70128_L"},
        "setCustomNameTag":      {"mcp": "setCustomNameTag",      "obf": "a",  "srg": "func_96094_a"},
        "setInvisible":          {"mcp": "setInvisible",          "obf": "e",  "srg": "func_82142_c"},
        "setPosition":           {"mcp": "setPosition",           "obf": "b",  "srg": "func_70107_b"},
        "setAlwaysRenderNameTag":{"mcp": "setAlwaysRenderNameTag","obf": "g",  "srg": "func_174805_g"}
      }
    },
    "net_minecraft_entity_EntityLivingBase": {
      "mcp": "net/minecraft/entity/EntityLivingBase",
      "obf": "pr",
      "attributes": {
        "getHealth":              {"mcp": "getHealth",              "obf": "bn", "srg": "func_110143_aJ"},
        "getMaxHealth":           {"mcp": "getMaxHealth",           "obf": "bu", "srg": "func_110138_aP"},
        "getAbsorptionAmount":    {"mcp": "getAbsorptionAmount",    "obf": "bN", "srg": "func_110139_bj"},
        "getActivePotionEffects": {"mcp": "getActivePotionEffects", "obf": "bl", "srg": "func_70651_bq"}
      }
    },
    "net_minecraft_item_ItemStack": {
      "mcp": "net/minecraft/item/ItemStack",
      "obf": "zx",
      "attributes": {
        "getDisplayName": {"mcp": "getDisplayName", "obf": "q", "srg": "func_82833_r"}
      }
    },
    "net_minecraft_potion_PotionEffect": {
      "mcp": "net/minecraft/potion/PotionEffect",
      "obf": "pf",
      "attributes": {
        "getDuration":   {"mcp": "getDuration",   "obf": "b", "srg": "func_76459_b"},
        "getEffectName": {"mcp": "getEffectName", "obf": "g", "srg": "func_76453_d"}
      }
    },
    "net_minecraft_scoreboard_IScoreObjectiveCriteria": {
      "mcp": "net/minecraft/scoreboard/IScoreObjectiveCriteria",
      "obf": "auu",
      "attributes": {}
    },
    "net_minecraft_scoreboard_Score": {
      "mcp": "net/minecraft/scoreboard/Score",
      "obf": "aum",
      "attributes": {
        "scorePoints": {"mcp": "scorePoints", "obf": "e", "srg": "field_96655_e"}
      }
    },
    "net_minecraft_scoreboard_ScoreDummyCriteria": {
      "mcp": "net/minecraft/scoreboard/ScoreDummyCriteria",
      "obf": "aus",
      "attributes": {}
    },
    "net_minecraft_scoreboard_ScoreObjective": {
      "mcp": "net/minecraft/scoreboard/ScoreObjective",
      "obf": "auk",
      "attributes": {
        "name":        {"mcp": "name",        "obf": "b", "srg": "field_96684_b"},
        "displayName": {"mcp": "displayName", "obf": "e", "srg": "field_96683_d"}
      }
    },
    "net_minecraft_scoreboard_ScorePlayerTeam": {
      "mcp": "net/minecraft/scoreboard/ScorePlayerTeam",
      "obf": "aul",
      "attributes": {
        "getTeamName":             {"mcp": "getTeamName",             "obf": "c", "srg": "func_96669_c"},
        "getMembershipCollection": {"mcp": "getMembershipCollection", "obf": "d", "srg": "func_96670_d"},
        "getColorPrefix":          {"mcp": "getColorPrefix",          "obf": "e", "srg": "func_96668_e"},
        "getColorSuffix":          {"mcp": "getColorSuffix",          "obf": "f", "srg": "func_96663_f"},
        "setNamePrefix":           {"mcp": "setNamePrefix",           "obf": "b", "srg": "func_96666_b"},
        "setNameSuffix":           {"mcp": "setNameSuffix",           "obf": "c", "srg": "func_96662_c"}
      }
    },
    "net_minecraft_scoreboard_Scoreboard": {
      "mcp": "net/minecraft/scoreboard/Scoreboard",
      "obf": "auo",
      "attributes": {
        "getTeams":                  {"mcp": "getTeams",                  "obf": "g", "srg": "func_96525_g"},
        "getTeam":                   {"mcp": "getTeam",                   "obf": "d", "srg": "func_96508_e"},
        "createTeam":                {"mcp": "createTeam",                "obf": "e", "srg": "func_96527_f"},
        "removePlayerFromTeam":      {"mcp": "removePlayerFromTeam",      "obf": "a", "srg": "func_96512_b"},
        "removeTeam":                {"mcp": "removeTeam",                "obf": "d", "srg": "func_96511_d"},
        "getPlayersTeam":            {"mcp": "getPlayersTeam",            "obf": "h", "srg": "func_96509_i"},
        "addPlayerToTeam":           {"mcp": "addPlayerToTeam",           "obf": "a", "srg": "func_151392_a"},
        "setObjectiveInDisplaySlot": {"mcp": "setObjectiveInDisplaySlot", "obf": "a", "srg": "func_96530_a"},
        "getObjectiveInDisplaySlot": {"mcp": "getObjectiveInDisplaySlot", "obf": "a", "srg": "func_96539_a"},
        "getScoreObjectives":        {"mcp": "getScoreObjectives",        "obf": "c", "srg": "func_96514_c"},
        "getObjective":              {"mcp": "getObjective",              "obf": "b", "srg": "func_96518_b"},
        "addScoreObjective":         {"mcp": "addScoreObjective",         "obf": "a", "srg": "func_96535_a"},
        "getValueFromObjective":     {"mcp": "getValueFromObjective",     "obf": "c", "srg": "func_96529_a"}
      }
    },
    "net_minecraft_util_ChatComponentText": {
      "mcp": "net/minecraft/util/ChatComponentText",
      "obf": "fa",
      "attributes": {}
    },
    "net_minecraft_util_IChatComponent": {
      "mcp": "net/minecraft/util/IChatComponent",
      "obf": "eu",
      "attributes": {
        "getFormattedText":   {"mcp": "getFormattedText",   "obf": "d", "srg": "func_150254_d"},
        "getUnformattedText": {"mcp": "getUnformattedText", "obf": "c", "srg": "func_150260_c"}
      }
    },
    "net_minecraft_world_World": {
      "mcp": "net/minecraft/world/World",
      "obf": "adm",
      "attributes": {
        "playerEntities": {"mcp": "playerEntities", "obf": "j", "srg": "field_73010_i"}
      }
    }
  }
}

)";
}
/*****************************************************************************
    MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/

#pragma pack(push)
#pragma pack(8)

#include "ArrayClass.h"
#include "SharedClasses.h"

namespace EQData
{

// ***************************************************************************
// Defines
// ***************************************************************************

#define AllClassesMASK		0xFFFF
#define WarriorMASK			0x0001
#define ClericMASK			0x0002
#define RogueMASK			0x0100
#define WizardMASK			0x0400

enum PlayerClass
{
    Unknown=                            0,
    Warrior=                            1,
    Cleric=                             2,
    Paladin=                            3,
    Ranger=                             4,
    Shadowknight=                       5,
    Druid=                              6,
    Monk=                               7,
    Bard=                               8,
    Rogue=                              9,
    Shaman=                            10,
    Necromancer=                       11,
    Wizard=                            12,
    Mage=                              13,
    Enchanter=                         14,
    Beastlord=                         15,
    Berserker=                         16,
	Mercenary=                         17,
    TotalClasses=                      17,
};
// class 20 through 35 are the NPC GMs (same class order as above)
// class 41   Merchant
// class 60   LDoN Recruiter
// class 61   LDoN Merchant
// class 63   Tribute Master
// class 67   DoN Merchant (Norrath's Keepers)
// class 68   DoN Merchant (Dark Reign)

typedef struct _ClassInfo
{
    bool CanCast;
    bool PureCaster;
    bool PetClass;
    bool DruidType;
    bool NecroType;
    bool ClericType;
    bool ShamanType;
	bool MercType;
    char RaidColorOrder;
    PCHAR Name;
    PCHAR ShortName;
	PCHAR UCShortName;
} CLASSINFO, *PCLASSINFO;

static _ClassInfo ClassInfo[]=
{
    {0,0,0,0,0,0,0,0,0,"","",""},                         //unk
    {0,0,0,0,0,0,0,0,13,"Warrior","war","WAR"},           //war
    {1,1,0,0,0,1,0,0,2,"Cleric","clr","CLR"},             //clr
    {1,0,0,0,0,1,0,0,8,"Paladin","pal","PAL"},            //pal
    {1,0,0,1,0,0,0,0,9,"Ranger","rng","RNG"},             //rng
    {1,0,0,0,1,0,0,0,11,"Shadowknight","shd","SHD"},      //shd
    {1,1,0,1,0,0,0,0,3,"Druid","dru","DRU"},              //dru
    {0,0,0,0,0,0,0,0,6,"Monk","mnk","MNK"},               //mnk
    {1,0,0,0,0,0,0,0,0,"Bard","brd","BRD"},               //brd
    {0,0,0,0,0,0,0,0,10,"Rogue","rog","ROG"},             //rog
    {1,1,1,0,0,0,1,0,12,"Shaman","shm","SHM"},            //shm
    {1,1,1,0,1,0,0,0,7,"Necromancer","nec","NEC"},        //nec
    {1,1,0,0,0,0,0,0,14,"Wizard","wiz","WIZ"},            //wiz
    {1,1,1,0,0,0,0,0,5,"Mage","mag","MAG"},               //mag
    {1,1,0,0,0,0,0,0,4,"Enchanter","enc","ENC"},          //enc
    {1,0,1,0,0,0,1,0,1,"Beastlord","bst","BST"},          //bst
    {0,0,0,0,0,0,0,0,15,"Berserker","ber","BER"},         //ber
	{1,1,0,0,0,0,0,1,16,"Mercenary","mer","MER"},         //mer
};

#define BI_TARGETABLE                   1
#define BI_TRIGGER                      2 
#define BI_TRAP                         4
#define BI_TIMER                        8

//door types
#define EQSWITCH_STANDARD					0    
#define EQSWITCH_STANDARD_METAL				1    
#define EQSWITCH_STANDARD_STONE				2    
#define EQSWITCH_STANDARD_CLOCKWISE			5
#define EQSWITCH_STANDARD_CLOCKWISE_METAL	6
#define EQSWITCH_STANDARD_CLOCKWISE_STONE	7
#define EQSWITCH_STANDARD_STONE_COLLIDING	8
//no idea what 9 is I couln't find one thats 9
#define EQSWITCH_SMALL_SLIDING				10
#define EQSWITCH_SMALL_SLIDING_METAL		11
#define EQSWITCH_SMALL_SLIDING_STONE		12
#define EQSWITCH_MEDIUM_SLIDING				15
#define EQSWITCH_MEDIUM_SLIDING_METAL		16
#define EQSWITCH_MEDIUM_SLIDING_STONE		17
#define EQSWITCH_LARGE_SLIDING				20
#define EQSWITCH_LARGE_SLIDING_METAL		21
#define EQSWITCH_LARGE_SLIDING_STONE		22
#define EQSWITCH_GIANT_SLIDING				25
#define EQSWITCH_GIANT_SLIDING_METAL		26
#define EQSWITCH_GIANT_SLIDING_STONE		27
#define EQSWITCH_DRAWBRIDGE					30
#define	EQSWITCH_TRAP						35
#define	EQSWITCH_PULLTRAP					36
#define EQSWITCH_LEVER						40
#define	EQSWITCH_TOGGLE_BUTTON				45
#define EQSWITCH_PRESSURE_PLATE				50 // if u step or touch this it keep the door open, move away and it closes.
#define EQSWITCH_DAMAGE_PLATE				51 // if you stand on this it damages you.
//no idea what 52,53,54,55 is
#define EQSWITCH_GUILD_CHEST				56
#define EQSWITCH_TELEPORTER					57
#define EQSWITCH_KEY_TELEPORTER				58
#define EQSWITCH_ELEVATOR					59
#define EQSWITCH_SMALL_SLIDE_UPWARDS		60
#define EQSWITCH_SMALL_SLIDE_UPWARDS_METAL	61
#define EQSWITCH_SMALL_SLIDE_UPWARDS_STONE	62
#define EQSWITCH_MEDIUM_SLIDE_UPWARDS		65
#define EQSWITCH_MEDIUM_SLIDE_UPWARDS_METAL	66
#define EQSWITCH_MEDIUM_SLIDE_UPWARDS_STONE	67
//no idea what 68,69 is
#define EQSWITCH_LARGE_SLIDE_UPWARDS		70
#define EQSWITCH_LARGE_SLIDE_UPWARDS_METAL	71
#define EQSWITCH_LARGE_SLIDE_UPWARDS_STONE	72
#define EQSWITCH_GIANT_SLIDE_UPWARDS		75
#define EQSWITCH_GIANT_SLIDE_UPWARDS_METAL	76
#define EQSWITCH_GIANT_SLIDE_UPWARDS_STONE	77
#define EQSWITCH_DIAGONAL_UP_RIGHT			78
#define EQSWITCH_DIAGONAL_UP_LEFT			79
#define EQSWITCH_DIAGONAL_DOWN_RIGHT		80
#define EQSWITCH_DIAGONAL_DOWN_LEFT			81
#define EQSWITCH_GIANT_UP_OR_DOWN			82
#define EQSWITCH_GIANT_UP_OR_DOWN_METAL		83
#define EQSWITCH_GIANT_UP_OR_DOWN_STONE		84
//85-109 more doors?
#define EQSWITCH_BUTTON						109
//and more?
#define EQSWITCH_TRADER_PLATFORM			153
#define EQSWITCH_BARTER_PLATFORM			154
#define EQSWITCH_BARTER_TRADER_PLATFORM		155
//and even more...
#define EQSWITCH_BOOK						158//opens bookwindow
#define EQSWITCH_REALESTATE_NEIGHBORHOOD	159
#define EQSWITCH_REALESTATE_PLOT			160
#define EQSWITCH_REALESTATE_EXIT			161

typedef struct _BodyInfo
{
    PCHAR Name;
    DWORD Flags;
} BODYINFO, *PBODYINFO;

#define SPAWN_PLAYER                    0
#define SPAWN_NPC                       1
#define SPAWN_CORPSE                    2
//#define SPAWN_ANY                       3
//#define SPAWN_PET                       4

#define SKILL_PICKLOCK					35

#define ITEM_NORMAL1                    0x0031
#define ITEM_NORMAL2                    0x0036
#define ITEM_NORMAL3                    0x315f
#define ITEM_NORMAL4                    0x3336
#define ITEM_NORMAL5                    0x0032
#define ITEM_NORMAL6                    0x0033
#define ITEM_NORMAL7                    0x0034
#define ITEM_NORMAL8                    0x0039
#define ITEM_CONTAINER                  0x7900
#define ITEM_CONTAINER_PLAIN            0x7953
#define ITEM_BOOK                       0x7379

#define ITEMITEMTYPE_FOOD               0x0e 
#define ITEMITEMTYPE_WATER              0x0f
#define ITEMITEMTYPE_SCROLL				0x14
#define ITEMITEMTYPE_ALCOHOL            0x26 
#define ITEMITEMTYPE_POISON             0x2a 
#define ITEMITEMTYPE_AUGUMENT           0x36 

#define ITEMEFFECTTYPE_COMBAT           0x00 
#define ITEMEFFECTTYPE_INVENTORY1       0x01 // Bards need to stop sing to cast 
#define ITEMEFFECTTYPE_WORN             0x02 
#define ITEMEFFECTTYPE_INVENTORY2       0x03 
#define ITEMEFFECTTYPE_MUSTEQUIP        0x04 // Bards need to stop sing to cast 
#define ITEMEFFECTTYPE_INVENTORY3       0x05 

#define SKILLMINDAMAGEMOD_BASH          0x00 
#define SKILLMINDAMAGEMOD_BACKSTAB      0x01 
#define SKILLMINDAMAGEMOD_DRAGONPUNCH   0x02 
#define SKILLMINDAMAGEMOD_EAGLESTRIKE   0x03 
#define SKILLMINDAMAGEMOD_FLYINGKICK    0x04 
#define SKILLMINDAMAGEMOD_KICK          0x05 
#define SKILLMINDAMAGEMOD_ROUNDKICK     0x06 
#define SKILLMINDAMAGEMOD_TIGERCLAW     0x07 
#define SKILLMINDAMAGEMOD_FRENZY        0x08 

//Heroic Mods
#define HEROIC_MOD_SPELL_SHIELDING      0x4
#define HEROIC_MOD_COMBAT_EFFECTS       0x5
#define HEROIC_MOD_MELEE_SHIELDING      0x6
#define HEROIC_MOD_DAMAGE_SHIELDING     0x7
#define HEROIC_MOD_DOT_SHIELDING        0x8
#define HEROIC_MOD_DAMAGE_SHIELD_MITIG  0x9
#define HEROIC_MOD_AVOIDANCE            0xa
#define HEROIC_MOD_ACCURACY             0xb
#define HEROIC_MOD_STUN_RESIST          0xc
#define HEROIC_MOD_STRIKETHROUGH        0xd

#define COLOR_DEFAULT                   0x00
#define COLOR_DARKGREY                  0x01
#define COLOR_DARKGREEN                 0x02
#define COLOR_DARKBLUE                  0x03
#define COLOR_PURPLE                    0x05
#define COLOR_LIGHTGREY                 0x06

#define CONCOLOR_GREY                   0x06
#define CONCOLOR_GREEN                  0x02
#define CONCOLOR_LIGHTBLUE              0x12
#define CONCOLOR_BLUE                   0x04
#define CONCOLOR_BLACK                  0x14
#define CONCOLOR_WHITE                  0x0a
#define CONCOLOR_YELLOW                 0x0f
#define CONCOLOR_RED                    0x0d

#define USERCOLOR_SAY                   0xFF +   1 //  1  - Say
#define USERCOLOR_TELL                  0xFF +   2 //  2  - Tell
#define USERCOLOR_GROUP                 0xFF +   3 //  3  - Group
#define USERCOLOR_GUILD                 0xFF +   4 //  4  - Guild
#define USERCOLOR_OOC                   0xFF +   5 //  5  - OOC
#define USERCOLOR_AUCTION               0xFF +   6 //  6  - Auction
#define USERCOLOR_SHOUT                 0xFF +   7 //  7  - Shout
#define USERCOLOR_EMOTE                 0xFF +   8 //  8  - Emote
#define USERCOLOR_SPELLS                0xFF +   9 //  9  - Spells (meming, scribing, casting, etc.)
#define USERCOLOR_YOU_HIT_OTHER         0xFF +  10 //  10 - You hit other
#define USERCOLOR_OTHER_HIT_YOU         0xFF +  11 //  11 - Other hits you
#define USERCOLOR_YOU_MISS_OTHER        0xFF +  12 //  12 - You miss other
#define USERCOLOR_OTHER_MISS_YOU        0xFF +  13 //  13 - Other misses you
#define USERCOLOR_DUELS                 0xFF +  14 //  14 - Some broadcasts (duels)
#define USERCOLOR_SKILLS                0xFF +  15 //  15 - Skills (ups, non-combat use, etc.)
#define USERCOLOR_DISCIPLINES           0xFF +  16 //  16 - Disciplines or special abilities
#define USERCOLOR_UNUSED001             0xFF +  17 //  17 - Unused at this time
#define USERCOLOR_DEFAULT               0xFF +  18 //  18 - Default text and stuff you type
#define USERCOLOR_UNUSED002             0xFF +  19 //  19 - Unused at this time
#define USERCOLOR_MERCHANT_OFFER        0xFF +  20 //  20 - Merchant Offer Price
#define USERCOLOR_MERCHANT_EXCHANGE     0xFF +  21 //  21 - Merchant Buy/Sell
#define USERCOLOR_YOUR_DEATH            0xFF +  22 //  22 - Your death message
#define USERCOLOR_OTHER_DEATH           0xFF +  23 //  23 - Others death message
#define USERCOLOR_OTHER_HIT_OTHER       0xFF +  24 //  24 - Other damage other
#define USERCOLOR_OTHER_MISS_OTHER      0xFF +  25 //  25 - Other miss other
#define USERCOLOR_WHO                   0xFF +  26 //  26 - /who command
#define USERCOLOR_YELL                  0xFF +  27 //  27 - yell for help
#define USERCOLOR_NON_MELEE             0xFF +  28 //  28 - Hit for non-melee
#define USERCOLOR_SPELL_WORN_OFF        0xFF +  29 //  29 - Spell worn off
#define USERCOLOR_MONEY_SPLIT           0xFF +  30 //  30 - Money splits
#define USERCOLOR_LOOT                  0xFF +  31 //  31 - Loot message
#define USERCOLOR_RANDOM                0xFF +  32 //  32 - Dice Roll (/random)
#define USERCOLOR_OTHERS_SPELLS         0xFF +  33 //  33 - Others spells
#define USERCOLOR_SPELL_FAILURE         0xFF +  34 //  34 - Spell Failures (resists, fizzles, missing component, bad target, etc.)
#define USERCOLOR_CHAT_CHANNEL          0xFF +  35 //  35 - Chat Channel Messages
#define USERCOLOR_CHAT_1                0xFF +  36 //  36 - Chat Channel 1
#define USERCOLOR_CHAT_2                0xFF +  37 //  37 - Chat Channel 2
#define USERCOLOR_CHAT_3                0xFF +  38 //  38 - Chat Channel 3
#define USERCOLOR_CHAT_4                0xFF +  39 //  39 - Chat Channel 4
#define USERCOLOR_CHAT_5                0xFF +  40 //  40 - Chat Channel 5
#define USERCOLOR_CHAT_6                0xFF +  41 //  41 - Chat Channel 6
#define USERCOLOR_CHAT_7                0xFF +  42 //  42 - Chat Channel 7
#define USERCOLOR_CHAT_8                0xFF +  43 //  43 - Chat Channel 8
#define USERCOLOR_CHAT_9                0xFF +  44 //  44 - Chat Channel 9
#define USERCOLOR_CHAT_10               0xFF +  45 //  45 - Chat Channel 10
#define USERCOLOR_MELEE_CRIT            0xFF +  46 //  46 - Melee Crits
#define USERCOLOR_SPELL_CRIT            0xFF +  47 //  47 - Spell Crits
#define USERCOLOR_TOO_FAR_AWAY          0xFF +  48 //  48 - Too far away (melee)
#define USERCOLOR_NPC_RAMPAGE           0xFF +  49 //  49 - NPC Rampage
#define USERCOLOR_NPC_FLURRY            0xFF +  50 //  50 - NPC Furry
#define USERCOLOR_NPC_ENRAGE            0xFF +  51 //  51 - NPC Enrage
#define USERCOLOR_ECHO_SAY              0xFF +  52 //  52 - say echo
#define USERCOLOR_ECHO_TELL             0xFF +  53 //  53 - tell echo
#define USERCOLOR_ECHO_GROUP            0xFF +  54 //  54 - group echo
#define USERCOLOR_ECHO_GUILD            0xFF +  55 //  55 - guild echo
#define USERCOLOR_ECHO_OOC              0xFF +  56 //  56 - group echo
#define USERCOLOR_ECHO_AUCTION          0xFF +  57 //  57 - auction echo
#define USERCOLOR_ECHO_SHOUT            0xFF +  58 //  58 - shout echo
#define USERCOLOR_ECHO_EMOTE            0xFF +  59 //  59 - emote echo
#define USERCOLOR_ECHO_CHAT_1           0xFF +  60 //  60 - chat 1 echo
#define USERCOLOR_ECHO_CHAT_2           0xFF +  61 //  61 - chat 2 echo
#define USERCOLOR_ECHO_CHAT_3           0xFF +  62 //  62 - chat 3 echo
#define USERCOLOR_ECHO_CHAT_4           0xFF +  63 //  63 - chat 4 echo
#define USERCOLOR_ECHO_CHAT_5           0xFF +  64 //  64 - chat 5 echo
#define USERCOLOR_ECHO_CHAT_6           0xFF +  65 //  65 - chat 6 echo
#define USERCOLOR_ECHO_CHAT_7           0xFF +  66 //  66 - chat 7 echo
#define USERCOLOR_ECHO_CHAT_8           0xFF +  67 //  67 - chat 8 echo
#define USERCOLOR_ECHO_CHAT_9           0xFF +  68 //  68 - chat 9 echo
#define USERCOLOR_ECHO_CHAT_10          0xFF +  69 //  69 - chat 10 echo
#define USERCOLOR_RESERVED              0xFF +  70 //  70 - "unused at this time" 
#define USERCOLOR_LINK                  0xFF +  71 //  71 - item links 
#define USERCOLOR_RAID                  0xFF +  72 //  72 - raid 
#define USERCOLOR_PET                   0xFF +  73 //  73 - my pet 
#define USERCOLOR_DAMAGESHIELD          0xFF +  74 //  74 - damage shields 
#define USERCOLOR_LEADER                0xFF +  75 //  75 - LAA-related messages 
#define USERCOLOR_PETRAMPFLURRY         0xFF +  76 //  76 - pet rampage/flurry 
#define USERCOLOR_PETCRITS              0xFF +  77 //  77 - pet's critical hits 
#define USERCOLOR_FOCUS                 0xFF +  78 //  78 - focus item activation 
#define USERCOLOR_XP                    0xFF +  79 //  79 - xp gain/loss 
#define USERCOLOR_SYSTEM                0xFF +  80 //  80 - system broadcasts etc 
#define USERCOLOR_PET_SPELLS            0xFF +  81 //  81 - pet spells
#define USERCOLOR_PET_RESPONSES         0xFF +  82 //  82 - pet responses
#define USERCOLOR_ITEM_SPEECH           0xFF +  83 //  83 - item speech
#define USERCOLOR_STRIKETHROUGH         0xFF +  84 //  84 - strikethrough messages
#define USERCOLOR_STUN                  0XFF +  85 //  85 - stun messages
#define USERCOLOR_RESERVED2             0xFF +  86 //  86 - "unused at this time" (or unknown!?)
#define USERCOLOR_FELLOWSHIP            0xFF +  87 //  87 - fellowship messages
#define USERCOLOR_NPC_SPEECH            0xFF +  88 //  88 - npc dialogue
#define USERCOLOR_NPC_SPEECH_TO_YOU     0xFF +  89 //  89 - npc dialogue to you
#define USERCOLOR_GUILD_MSG             0xFF +  90 //  90 - guild messages

#define DEITY_Bertoxxulous              201
#define DEITY_BrellSerilis              202
#define DEITY_CazicThule                203
#define DEITY_ErollisiMarr              204
#define DEITY_Bristlebane               205
#define DEITY_Innoruuk                  206
#define DEITY_Karana                    207
#define DEITY_MithanielMarr             208
#define DEITY_Prexus                    209
#define DEITY_Quellious                 210
#define DEITY_RallosZek                 211
#define DEITY_RodcetNife                212
#define DEITY_SolusekRo                 213
#define DEITY_TheTribunal               214
#define DEITY_Tunare                    215
#define DEITY_Veeshan                   216
#define NUM_DEITIES                     16

#define ITEMTYPE_NORMAL                 0
#define ITEMTYPE_PACK                   1
#define ITEMTYPE_BOOK                   2

#define COMP_NONE                       0
#define COMP_EQ                         1
#define COMP_NE                         2
#define COMP_GT                         3
#define COMP_LT                         4
#define COMP_GE                         5
#define COMP_LE                         6
#define COMP_CONT                       7
#define COMP_NOTCONT                    8
#define COMP_BITAND                     9
#define COMP_BITOR                      10

#define COMP_TYPE_STRING                0
#define COMP_TYPE_NUMERIC               1
#define COMP_TYPE_BIT                   2

#define CMD_MQ                          1
#define CMD_EQ                          2        

#define LASTFIND_NOTFOUND               96
#define LASTFIND_PRIMARY                97

#define EVENT_CHAT                      0
#define EVENT_TIMER                     1
#define EVENT_CUSTOM                    2
#define EVENT_EVAL                      3
#define EVENT_EXEC                      4
#define EVENT_PULSE                     5
#define EVENT_SHUTDOWN                  6
#define EVENT_BREAK                     7
#define NUM_EVENTS                      8

#define CHAT_SAY                        1
#define CHAT_TELL                       2
#define CHAT_OOC                        4
#define CHAT_SHOUT                      8
#define CHAT_AUC                        16
#define CHAT_GUILD                      32
#define CHAT_GROUP                      64
#define CHAT_CHAT                       128
#define CHATEVENT(x)                    (gEventChat & x)

#define FILTERSKILL_ALL                 0
#define FILTERSKILL_INCREASE            1
#define FILTERSKILL_NONE                2

#define FILTERMACRO_ALL                 0
#define FILTERMACRO_ENHANCED            1
#define FILTERMACRO_NONE                2
#define FILTERMACRO_MACROENDED			3


#define MAX_STRING                      2048
#define MAX_VARNAME                     64

// Defines for CXWnd WindowStyle
#define CWS_VSCROLL                     0x1
#define CWS_HSCROLL                     0x2
#define CWS_TITLE                       0x4
#define CWS_CLOSE                       0x8
#define CWS_TILEBOX                     0x10
#define CWS_MINIMIZE                    0x20
#define CWS_BORDER                      0x40
#define CWS_RELATIVERECT                0x80
#define CWS_AUTOSTRETCHV                0x100
#define CWS_RESIZEALL                   0x200
#define CWS_TRANSPARENT                 0x400
#define CWS_USEMYALPHA                  0x800
#define CWS_DOCKING                     0x1000
#define CWS_TOOLTIP_NODELAY             0x2000
#define CWS_FRAMEWND                    0x4000
#define CWS_NOHITTEST                   0x8000
#define CWS_QMARK                       0x10000
#define CWS_NOMOVABLE                   0x20000
#define CWS_MAXIMIZE                    0x40000
#define CWS_AUTOVSCROLL                 0x80000
#define CWS_AUTOHSCROLL                 0x100000
#define CWS_CLIENTMOVABLE               0x200000
#define CWS_AUTOSTRETCH                 0x400000
#define CWS_TRANSPARENTCONTROL          0x800000
#define CWS_RESIZEBORDER          CWS_BORDER | CWS_RESIZEALL
#define ToggleBit(field,bit)            field^=bit;
#define BitOn(field,bit)                field|=bit;
#define BitOff(field,bit)               field&=~bit;
#define BitSet(field,bit)					field|=(1<<bit);
#define BitClear(field,bit)				field&=~(1<<bit);
// End CXWnd WindowStyle Defines

enum ALT_Currency {
	ALTCURRENCY_DOUBLOONS = 10,//10 - TBS
	ALTCURRENCY_ORUX,//11 - TBS
	ALTCURRENCY_PHOSPHENES,//12 - TBS
	ALTCURRENCY_PHOSPHITES,//13 - TBS
	ALTCURRENCY_FAYCITES,//14 - SoF
	ALTCURRENCY_CHRONOBINES,//15 - SoD
	ALTCURRENCY_SILVERTOKENS,//16 - UF
	ALTCURRENCY_GOLDTOKENS,//17 - UF
	ALTCURRENCY_MCKENZIE,//18 - SoD
	ALTCURRENCY_BAYLE,//19 - SoD
	ALTCURRENCY_RECLAMATION,//20 - EQ
	ALTCURRENCY_BRELLIUM,//21 - UF
	ALTCURRENCY_MOTES,//22 - HoT
	ALTCURRENCY_REBELLIONCHITS,//23 - VoA
	ALTCURRENCY_DIAMONDCOINS,//24 - VoA
	ALTCURRENCY_BRONZEFIATS,//25 - VoA
	ALTCURRENCY_VOUCHER,//26 - TDS (Expediant Voucher?)
	ALTCURRENCY_VELIUMSHARDS,//27 - RoF
	ALTCURRENCY_CRYSTALLIZEDFEAR,//28 - RoF
	ALTCURRENCY_SHADOWSTONES,//29 - RoF
	ALTCURRENCY_DREADSTONES,//30 - RoF
	ALTCURRENCY_MARKSOFVALOR,//31 - CoTF
	ALTCURRENCY_MEDALSOFHEROISM,//32 - CoTF
	ALTCURRENCY_COMMEMORATIVE_COINS,//33 - VoA
	ALTCURRENCY_FISTSOFBAYLE,//34 - CoTF
	ALTCURRENCY_NOBLES,//35 - EQ
	ALTCURRENCY_ENERGYCRYSTALS,//36 - TDS
	ALTCURRENCY_PIECESOFEIGHT,//37 - TDS
	ALTCURRENCY_REMNANTSOFTRANQUILITY,//38 - TBM
	ALTCURRENCY_BIFURCATEDCOIN,//39 - TBM
	ALTCURRENCY_ADOPTIVE,//40 - EQ
	ALTCURRENCY_SATHIRSTRADEGEMS,//41 - EOK
	ALTCURRENCY_ANCIENTSEBILISIANCOINS,//42 - EOK
	ALTCURRENCY_BATHEZIDTRADEGEMS,//43 - ROS
	ALTCURRENCY_ANCIENTDRACONICCOIN,//44 - ROS
	ALTCURRENCY_FETTERREDIFRITCOINS,//45 - TBL
	ALTCURRENCY_ENTWINEDDJINNCOINS,//46 - TBL
	ALTCURRENCY_CRYSTALLIZEDLUCK//47 - TBL
};

enum MOUSE_DATA_TYPES {
   MD_Unknown = -1,
   MD_Button0Click=0,
   MD_Button1Click,
   MD_Button0,
   MD_Button1
};

//eqmule Mar 05 2019 Test
//KeypressHandler__HandleKeyUp_x has this one
#define nEQMappableCommands             0x222
//found using __BindList_x
#define nNormalEQMappableCommands       (nEQMappableCommands - 0x16)

#define MAX_PC_LEVEL                    115
#define MAX_NPC_LEVEL                   200
#define MAX_SPELL_LEVEL					255
#define NUM_SPELL_GEMS                  0xe
#define NUM_SPELL_SETS                  30
#define NUM_BUFF_SLOTS					0x61
#define NUM_LONG_BUFFS                  0x2a
#define NUM_SHORT_BUFFS                 0x37
#define NUM_RACES                       17
#define NUM_SLOTDATA                    0x6
#define NUM_BLOCKED_BUFFS               40
#define NUM_BAG_SLOTS					10

#define EQ_EXPANSION(x)                 (1 << (x - 1))
#define EXPANSION_RoK                   EQ_EXPANSION(1)
#define EXPANSION_SoV                   EQ_EXPANSION(2)
#define EXPANSION_SoL                   EQ_EXPANSION(3)
#define EXPANSION_PoP                   EQ_EXPANSION(4)
#define EXPANSION_LoY                   EQ_EXPANSION(5)
#define EXPANSION_LDoN                  EQ_EXPANSION(6)
#define EXPANSION_GoD                   EQ_EXPANSION(7)
#define EXPANSION_OoW                   EQ_EXPANSION(8)
#define EXPANSION_DoN                   EQ_EXPANSION(9)
#define EXPANSION_DoD                   EQ_EXPANSION(10)
#define EXPANSION_PoR                   EQ_EXPANSION(11)
#define EXPANSION_TSS                   EQ_EXPANSION(12)
#define EXPANSION_TBS                   EQ_EXPANSION(13)
#define EXPANSION_SoF                   EQ_EXPANSION(14)
#define EXPANSION_SoD                   EQ_EXPANSION(15)
#define EXPANSION_UFT                   EQ_EXPANSION(16)
#define EXPANSION_HoT                   EQ_EXPANSION(17)
#define EXPANSION_VoA                   EQ_EXPANSION(18)
#define EXPANSION_RoF                   EQ_EXPANSION(19)
#define EXPANSION_CotF                  EQ_EXPANSION(20)
#define EXPANSION_TDS                   EQ_EXPANSION(21)
#define EXPANSION_TBM                   EQ_EXPANSION(22)
#define EXPANSION_EoK                   EQ_EXPANSION(23)
#define EXPANSION_RoS                   EQ_EXPANSION(24)
#define EXPANSION_TBL                   EQ_EXPANSION(25)
#define EXPANSION_TOV                   EQ_EXPANSION(26)
#define NUM_EXPANSIONS                  26

#if _MSC_VER < 1600
#define nullptr                         NULL
#endif

#define CALC_1TICK						107
#define CALC_2TICK						108
#define CALC_5TICK						120
#define CALC_12TICK						122
#define CALC_RANDOM						123

#define SPA_HP                          0
#define SPA_AC                          1
#define SPA_MOVEMENTRATE                3
#define SPA_CHA							10
#define SPA_HASTE                       11
#define SPA_MANA                        15
#define SPA_VAMPIRISM                   45
#define SPA_CHANGE_FORM                 58
#define SPA_EYE_OF_ZOMM					67
#define SPA_MAGNIFICATION               87
#define SPA_PLAYERSIZE                  89
#define SPA_SUMMONCORPSE                91
#define SPA_BARDOVERHASTE               98
#define SPA_HEALDOT                     100
#define SPA_COMPLETEHEAL                101
#define SPA_SUMMON_MOUNT                113
#define SPA_SPELLDAMAGE                 124
#define SPA_HEALING                     125
#define SPA_REAGENTCHANCE               131
#define SPA_SPELLMANACOST               132
#define SPA_STACKING_BLOCK              148
#define SPA_REMOVE_DETRIMENTAL          154
#define SPA_MIRROR   					156
#define SPA_SPELL_GUARD					161
#define SPA_MELEE_GUARD					162
#define SPA_DOUBLEATTACK                177
#define SPA_STUNRESIST                  195
#define SPA_PROCMOD                     200
#define SPA_DIVINEREZ                   232
#define SPA_METABOLISM                  233
#define SPA_NOSPELL                     254
#define SPA_TRIPLEBACKSTAB              258
#define SPA_INCREASE_CASTING_LEVEL      272
#define SPA_DOTCRIT                     273
#define SPA_HEALCRIT                    274
#define SPA_MENDCRIT                    275
#define SPA_FLURRY                      279
#define SPA_PETFLURRY                   280
#define SPA_SPELLCRITCHANCE             294
#define SPA_INCSPELLDMG                 296
#define SPA_DAMAGECRITMOD               302
#define SPA_SHIELDBLOCKCHANCE           320
#define SPA_NO_MOVE_HP                  334
#define SPA_MANA_IGNITE					401
#define SPA_ENDURANCE_IGNITE			402
#define SPA_LIMIT_HP        			408
#define SPA_LIMIT_MANA					409
#define SPA_LIMIT_ENDURANCE				410
#define SPA_AC2                         416
#define SPA_MANA2                       417
#define SPA_IMPROVED_TAUNT              444
#define SPA_DOT_GUARD					450
#define SPA_MELEE_THRESHOLD_GUARD		451
#define SPA_SPELL_THRESHOLD_GUARD		452
#define SPA_TRIGGER_BEST_SPELL_GROUP	470
#define SPA_SPELLDAMAGETAKEN			483

#define TT_PBAE                         0x04
#define TT_TARGETED_AE                  0x08
#define TT_AE_PC_V2                     0x28
#define TT_DIRECTIONAL                  0x2a

#define EQHeading(heading) (int)(((heading + 16) % 256) / 32) * 2


// ***************************************************************************
// Structures
// ***************************************************************************

typedef struct _MOUSESPOOF {
   MOUSE_DATA_TYPES     mdType;
   DWORD                dwData;
   struct _MOUSESPOOF   *pNext;
} MOUSESPOOF, *PMOUSESPOOF;

typedef struct _MOUSECLICK {
   BYTE Confirm[8];         // DO NOT WRITE TO THIS BYTE
   BYTE Click[8];         // Left = 0, Right = 1, etc
} MOUSECLICK, *PMOUSECLICK;

typedef struct _UILOCATION {
   DWORD x;
   DWORD y;
   DWORD w;
   DWORD h;
   CHAR error[MAX_STRING];
} UILOCATION, *PUILOCATION;

//5-15-2003   eqmule
typedef struct _CXSTR {
/*0x00*/   DWORD   Font;            // maybe, dont know.  04 = Window 01 = button
/*0x04*/   DWORD   MaxLength;
/*0x08*/   DWORD   Length;
/*0x0c*/   BOOL    Encoding;        // 0: ASCII, 1:Unicode
/*0x10*/   PCRITICAL_SECTION pLock;
/*0x14*/   CHAR    Text[1];         // Stub, can be anywhere from Length to MaxLength (which is how much is malloc'd to this CXStr)
} CXSTR, *PCXSTR;

#define ITEM_NAME_LEN                   0x40
#define LORE_NAME_LEN                   0x50

// size is 0x64 02-16-2007
typedef struct _ITEMSPELLS { 
/*0x00*/ DWORD SpellID; 
/*0x04*/ BYTE  RequiredLevel; 
/*0x05*/ BYTE  EffectType; //bIsActivated
/*0x08*/ DWORD EffectiveCasterLevel;
/*0x0c*/ DWORD MaxCharges;
/*0x10*/ DWORD CastTime;
/*0x14*/ DWORD TimerID;//RecastTime
/*0x18*/ DWORD RecastType;
/*0x1c*/ DWORD ProcRate;//chance to proc
/*0x20*/ CHAR  OtherName[0x40];//some kind of override
/*0x60*/ DWORD OtherID;//Description ID
/*0x64*/ 
} ITEMSPELLS, *PITEMSPELLS;

class ArmorProperties
{
public:
/*0x00*/ UINT Type;
/*0x04*/ UINT Variation;
/*0x08*/ UINT Material;
/*0x0c*/ UINT NewArmorID;
/*0x10*/ UINT NewArmorType;
/*0x14*/
};
struct AugSocket
{
	int Type;
	bool bVisible;
	bool bInfusible;
};
class ItemSocketData
{
public:
	AugSocket Sockets[6];
};
//ItemDefinition class
//CItemInfo__CItemInfo
//to check this look at ItemBase__ResetItemInstance_x
// actual size: 0x704 Nov  6 2018 Test (see 63F00F) - eqmule
// actual size: 0x70c Oct 31 2018 Beta (see 7291CC) - eqmule
// actual size: 0x6D8 Apr 08 2020 Test (see 67384F) - eqmule
typedef struct _ITEMINFO {
	/*0x0000*/ CHAR         Name[ITEM_NAME_LEN];
	/*0x0040*/ CHAR         LoreName[LORE_NAME_LEN];
	/*0x0090*/ CHAR         AdvancedLoreName[0x20];
	//*0x00b0*/ CHAR         IDFile[0x1e];
	//*0x00ce*/ CHAR         IDFile2[0x1e];
	/*0x00b0*/ int			IDFile;//check these i dont know what they are yet...
	/*0x00b4*/ int			IDFile2;//?
	/*0x00b8*/ DWORD        ItemNumber;//see 8B65D5
	/*0x00bc*/ DWORD        EquipSlots;//see 8B64F6 apr 08 2020 test //its position, where it can be equipped
	/*0x00c0*/ DWORD        Cost;
	/*0x00c4*/ DWORD        IconNumber;//for sure
	/*0x00c8*/ BYTE         eGMRequirement;//todo figure out this enum
	/*0x00c9*/ bool         bPoofOnDeath;
	/*0x00cc*/ DWORD        Weight;
	/*0x00d0*/ bool         NoRent; // 0=temp, 1=default
	/*0x00d1*/ bool         NoDrop; // 0=no drop, 1=can drop	
	/*0x00d2*/ bool         Attuneable;//8B58A5 apr 08 2020 test
	/*0x00d3*/ bool         Heirloom;//8B7E32 apr 08 2020 test
	/*0x00d4*/ bool         Collectible;
	/*0x00d5*/ bool         NoDestroy;
	/*0x00d6*/ bool         bNoNPC;
	/*0x00d7*/ bool         NoZone;
	/*0x00d8*/ DWORD        MakerID;//0-?? I did up to 12, I think it asks server for the name see 883655 in 11 jun 2018 test - eqmule
	/*0x00dc*/ bool         NoGround;
	/*0x00dd*/ bool         bNoLoot;
	/*0x00de*/ bool         MarketPlace;
	/*0x00df*/ bool         bFreeSlot;
	/*0x00e0*/ bool         bAutoUse;//8B7C65 08 apr 2020 test
	/*0x00e4*/ int			Unknown0x00e4;
	/*0x00e8*/ BYTE         Size;//8B66C0 08 apr 2020 test
	/*0x00e9*/ BYTE         Type;//fs
	/*0x00ea*/ bool         TradeSkills;//886EC5 11 jun 2018 test
	/*0x00ec*/ int	        Lore;//-1=Lore 0=Not Lore >=1=Lore Group see 8B8312 in 08 apr 2020 test
	/*0x00f0*/ int	        LoreEquipped;//8B8382 08 apr 2020 test
	/*0x00f4*/ bool         Artifact;
	/*0x00f5*/ bool         Summoned;
	/*0x00f6*/ CHAR         SvCold;
	/*0x00f7*/ CHAR         SvFire;//8848B0 jun 11 2018 test
	/*0x00f8*/ CHAR         SvMagic;
	/*0x00f9*/ CHAR         SvDisease;
	/*0x00fa*/ CHAR         SvPoison;
	/*0x00fb*/ CHAR         SvCorruption;
	/*0x00fc*/ CHAR         STR;
	/*0x00fd*/ CHAR         STA;//884B20 jun 11 2018 test
	/*0x00fe*/ CHAR         AGI;
	/*0x00ff*/ CHAR         DEX;
	/*0x0100*/ CHAR         CHA;//883E20 jun 11 2018 test
	/*0x0101*/ CHAR         INT;
	/*0x0102*/ CHAR         WIS;
	/*0x0104*/ int	        HP;//884010 jun 11 2018 test
	/*0x0108*/ int	        Mana;
	/*0x010c*/ int	        AC;
	/*0x0110*/ int	        RequiredLevel;
	/*0x0114*/ int	        RecommendedLevel;
	/*0x0118*/ int	        RecommendedSkill;
	/*0x011c*/ int	        SkillModType;
	/*0x0120*/ int	        SkillModValue;
	/*0x0124*/ int	        SkillModMax;
	/*0x0128*/ int	        SkillModBonus;
	/*0x012c*/ int		    BaneDMGRace;
	/*0x0130*/ int          BaneDMGBodyType;
	/*0x0134*/ int          BaneDMGBodyTypeValue;
	/*0x0138*/ int          BaneDMGRaceValue;
	/*0x013c*/ int	        InstrumentType;
	/*0x0140*/ int	        InstrumentMod;
	/*0x0144*/ int	        Classes;
	/*0x0148*/ int	        Races;
	/*0x014c*/ int	        Diety;
	/*0x0150*/ UINT         MaterialTintIndex;
	/*0x0154*/ bool         Magic;//8B8091 apr 08 2020 test
	/*0x0155*/ BYTE         Light;
	/*0x0156*/ BYTE         Delay;
	/*0x0157*/ BYTE         ElementalFlag;//used to be called DmgBonusType;
	/*0x0158*/ BYTE         ElementalDamage;//used to be called DmgBonusVal
	/*0x0159*/ BYTE         Range;
	/*0x015c*/ DWORD        Damage;//BaseDamage
	/*0x0160*/ DWORD        BackstabDamage;
	/*0x0164*/ DWORD        HeroicSTR;
	/*0x0168*/ DWORD        HeroicINT;//883A30 jun 11 2018 test
	/*0x016c*/ DWORD        HeroicWIS;//883A90 jun 11 2018 test
	/*0x0170*/ DWORD        HeroicAGI;//8839D0 jun 11 2018 test
	/*0x0174*/ DWORD        HeroicDEX;
	/*0x0178*/ DWORD        HeroicSTA;//883A50 jun 11 2018 test
	/*0x017c*/ DWORD        HeroicCHA;//8839F0 jun 11 2018 test
	/*0x0180*/ DWORD        HealAmount;//883980 jun 11 2018 test
	/*0x0184*/ DWORD        SpellDamage;
	/*0x0188*/ int          MinLuck;
	/*0x018c*/ int          MaxLuck;
	/*0x0190*/ int	        Prestige;//8B86A6 apr 08 2020 test
	/*0x0194*/ BYTE         ItemType;
	/*0x0198*/ ArmorProperties ArmorProps;//size is 0x14
	/*0x01ac*/ ItemSocketData AugData;//size 0x30 8B7EDE apr 08 2020 test	
	/*0x01dc*/ DWORD        AugType;
	/*0x01e0*/ DWORD        AugSkinTypeMask;
	/*0x01e4*/ DWORD        AugRestrictions;
	/*0x01e8*/ DWORD        SolventItemID; //ID# of Solvent (Augs only) see 8B74F5 in apr 08 2020 -eqmule
	/*0x01ec*/ DWORD        LDTheme;
	/*0x01f0*/ DWORD        LDCost;
	/*0x01f4*/ DWORD        LDType;
	/*0x01f8*/ int          Unknown0x01f8;
	/*0x01fc*/ int          Unknown0x01fc;
	/*0x0200*/ CHAR         CharmFile[0x20];
	/*0x0220*/ FLOAT		MerchantGreedMod;
	/*0x0224*/ struct _ITEMSPELLS   Clicky;//size 0x64 see 8B7590
	/*0x0288*/ struct _ITEMSPELLS   Proc;
	/*0x02ec*/ struct _ITEMSPELLS   Worn;
	/*0x0350*/ struct _ITEMSPELLS   Focus;
	/*0x03b4*/ struct _ITEMSPELLS   Scroll;
	/*0x0418*/ struct _ITEMSPELLS   Focus2;
	/*0x047c*/ struct _ITEMSPELLS   Mount;
	/*0x04e0*/ struct _ITEMSPELLS   Illusion;
	/*0x0544*/ struct _ITEMSPELLS   Familiar;
	/*0x05a8*/ DWORD        SkillMask[5];//this is just an array but I dont have time to figure it out for now. -eqmule	
	/*0x05bc*/ DWORD        DmgBonusSkill; // SkillMinDamageMod;
	/*0x05c0*/ DWORD        DmgBonusValue; // MinDamageMod;
	/*0x05c4*/ DWORD        CharmFileID;
	/*0x05c8*/ DWORD        FoodDuration;//0-5 snack 6-20 meal 21-30 hearty 31-40 banquet 41-50 feast 51-60 enduring 60- miraculous
	/*0x05cc*/ BYTE         Combine;
	/*0x05cd*/ BYTE         Slots;
	/*0x05ce*/ BYTE         SizeCapacity;
	/*0x05cf*/ BYTE         WeightReduction;
	/*0x05d0*/ BYTE         BookType;      // 0=note, !0=book 884CF5 jun 11 2018 test
	/*0x05d1*/ BYTE         BookLang;
	/*0x05d2*/ CHAR         BookFile[0x1e];
	/*0x05f0*/ DWORD        Favor;         // Tribute Value
	/*0x05f4*/ DWORD        GuildFavor;
	/*0x05f8*/ bool         bIsFVNoDrop;
	/*0x05fc*/ DWORD        Endurance;
	/*0x0600*/ DWORD        Attack;
	/*0x0604*/ DWORD        HPRegen;
	/*0x0608*/ DWORD        ManaRegen;
	/*0x060c*/ DWORD        EnduranceRegen;
	/*0x0610*/ DWORD        Haste;
	/*0x0614*/ int          AnimationOverride;
	/*0x0618*/ int          PaletteTintIndex;
	/*0x061c*/ bool         bNoPetGive;//8B58B5 apr 08 2020 test
	/*0x061d*/ bool			bSomeProfile;
	/*0x0620*/ int			SomeIDFlag;
	/*0x0624*/ DWORD        StackSize;
	/*0x0628*/ bool         bNoStorage;//8B856F apr 08 2020 test
	/*0x062c*/ DWORD        MaxPower;
	/*0x0630*/ DWORD        Purity;//(the call it Infused but we know its a purity pct... see 774A4C apr 08 2020 test)
	/*0x0634*/ bool         bIsEpic;//8B7D51 apr 08 2020 test
	/*0x0638*/ int          RightClickScriptID;
	/*0x063c*/ int          ItemLaunchScriptID;
	/*0x0640*/ BYTE         QuestItem;//8B8745 apr 08 2020 test
	/*0x0641*/ BYTE         Expendable;
	/*0x0644*/ DWORD        Clairvoyance;
	/*0x0648*/ int          SubClass;
	/*0x064c*/ bool         bLoginRegReqItem;
	/*0x0650*/ DWORD        Placeable;
	/*0x0654*/ bool         bPlaceableIgnoreCollisions;
	/*0x0658*/ int          PlacementType;//todo: this is an enum need to figure out.
	/*0x065c*/ int          RealEstateDefID;
	/*0x0660*/ FLOAT        PlaceableScaleRangeMin;
	/*0x0664*/ FLOAT        PlaceableScaleRangeMax;
	/*0x0668*/ int          RealEstateUpkeepID;
	/*0x066c*/ int          MaxPerRealEstate;
	/*0x0670*/ CHAR			HousepetFileName[0x20];
	/*0x0690*/ int			TrophyBenefitID;
	/*0x0694*/ bool			bDisablePlacementRotation;
	/*0x0695*/ bool			bDisableFreePlacement;
	/*0x0698*/ int			NpcRespawnInterval;
	/*0x069c*/ FLOAT		PlaceableDefScale;
	/*0x06a0*/ FLOAT		PlaceableDefHeading;
	/*0x06a4*/ FLOAT		PlaceableDefPitch;
	/*0x06a8*/ FLOAT		PlaceableDefRoll;
	/*0x06ac*/ bool			bInteractiveObject;
	/*0x06ad*/ BYTE			SocketSubClassCount;
	/*0x06b0*/ int			SocketSubClass[0xa];
	/*0x06D8*/
} ITEMINFO, *PITEMINFO;

//ok this is rediculous, so I had to change this, there are 40 slot bags now and they could add more in the future
//this is now dynamic... -eqmule
typedef struct _ITEMBASEARRAY {
    struct  _CONTENTS *Item[1];
} ITEMBASEARRAY, *PITEMBASEARRAY;

class EqItemGuid
{
public:
	enum { GUID = 18 };
	EqItemGuid()
	{
		ZeroMemory(guid, sizeof(guid));
	}

	char guid[GUID];
};
enum ItemContainerInstance
{
	eItemContainerInvalid = -1,
	eItemContainerPossessions,//0
	eItemContainerBank,//1
	eItemContainerSharedBank,
	eItemContainerTrade,
	eItemContainerWorld,
	eItemContainerLimbo,//5
	eItemContainerTribute,
	eItemContainerTrophyTribute,
	eItemContainerGuildTribute,
	eItemContainerMerchant,
	eItemContainerDeleted,//10
	eItemContainerCorpse,
	eItemContainerBazaar,
	eItemContainerInspect,
	eItemContainerRealEstate,
	eItemContainerViewModPC,//15
	eItemContainerViewModBank,
	eItemContainerViewModSharedBank,
	eItemContainerViewModLimbo,
	eItemContainerAltStorage,
	eItemContainerArchived,//20
	eItemContainerMail,
	eItemContainerGuildTrophyTribute,
	eItemContainerKrono,
	eItemContainerOther,
	eItemContainerMercenaryItems,//25
    eItemContainerViewModMercenaryItems,
    eItemContainerMountKeyRingItems,
	eItemContainerViewModMountKeyRingItems,
	eItemContainerIllusionKeyRingItems,
	eItemContainerViewModIllusionKeyRingItems,//30
	eItemContainerFamiliarKeyRingItems,
	eItemContainerViewModFamiliarKeyRingItems,
	eItemContainerCursor,//33
};
class ItemIndex
{
public:
/*0x00*/ short Slot1;
/*0x02*/ short Slot2;
/*0x04*/ short Slot3;
/*0x06*/
};

class ItemGlobalIndex2
{
public:
/*0x00*/ ItemGlobalIndex2::ItemContainerInstance Location;
/*0x04*/ ItemGlobalIndex2::ItemIndex Index;
/*0x0a*/
};

class ItemArray
{
public:
/*0xa4*/	struct _ITEMBASEARRAY	*pItems;
/*0xa8*/	UINT Size;
/*0xac*/	UINT Capacity;
};

class ItemBaseContainer2
{
public:
/*0x9c*/	UINT ContentSize;
/*0xa0*/	int ItemLocation;
/*0xa4*/	ItemArray ContainedItems;
/*0xb0*/	BYTE Depth;
/*0xB2*/	short ItemSlot;
/*0xB4*/	short ItemSlot2;
/*0xB6*/	bool bDynamic;
/*0xb8*/
};

typedef struct _ItemEvolutionData
{
/*0x00*/ int	GroupID;
/*0x04*/ int	EvolvingCurrentLevel;
/*0x08*/ DOUBLE	EvolvingExpPct;
/*0x10*/ int	EvolvingMaxLevel;
/*0x14*/ int	LastEquipped;
/*0x18*/
} ItemEvolutionData, *PItemEvolutionData;

//Actual Size: 0x110 (see 0x634C7C in eqgame.exe Test dated Apr 13 2020) - eqmule
typedef struct _CONTENTS {
/*0x0000*/ void*	vtable;
/*0x0004*/ mutable int	RefCount;
/*0x0008*/ void*	punknown;
//start of ItemBase
/*0x000C*/ struct _CXSTR *	ActorTag2;
/*0x0010*/ UINT	Tint;
/*0x0014*/ int	MerchantQuantity;
/*0x0018*/ ItemGlobalIndex2 GlobalIndex; /* Size is 0xa (0xc)*/
/*0x0024*/ int	Open;
/*0x0028*/ bool	bCopied;
/*0x002C*/ UINT	ItemHash;
/*0x0030*/ int	ScriptIndex;
/*0x0034*/ bool	bConvertable;
/*0x0038*/ int	Charges;
/*0x003C*/ int	ConvertItemID;
/*0x0040*/ struct _CXSTR *ConvertItemName;
/*0x0044*/ UINT	LastCastTime;
/*0x0048*/ int	AugFlag;
/*0x004C*/ int	StackCount;
/*0x0050*/ __int64 MerchantSlot;
/*0x0058*/ struct _CXSTR *SaveString;
/*0x005C*/ bool	bItemNeedsUpdate;
/*0x0060*/ ItemBaseContainer2 Contents; /* Size is 0x1c */
/*0x007C*/ int	ArmorType;
/*0x0080*/ bool	bRealEstateItemPlaceable;
/*0x0084*/ int	OrnamentationIcon;
/*0x0088*/ bool	bDisableAugTexture;
/*0x008C*/ ArrayClass_RO<UINT> RealEstateArray;
/*0x009C*/ int	ID;
/*0x00A0*/ struct _CXSTR *	ActorTag1;
/*0x00A4*/ struct _ITEMINFO *Item1;
/*0x00A8*/ int	Power;
/*0x00AC*/ SharedPtr<ItemEvolutionData> pEvolutionData;
/*0x00B8*/ __int64 Price;
/*0x00C0*/ __int64	DontKnow;
/*0x00C8*/ int	Luck;
/*0x00CC*/ bool	bCollected;
/*0x00D0*/ int	NoDropFlag;
/*0x00D4*/ UINT	NewArmorID;
/*0x00D8*/ UINT	RespawnTime;
/*0x00DC*/ bool	bRankDisabled;
/*0x00E0*/ int	NoteStatus;
/*0x00E4*/ int	RealEstateID;
/*0x00E8*/ EqItemGuid ItemGUID;
//start of ItemClient
/*0x00FC*/ int Filler0x00FC[2];
/*0x0104*/ struct _ITEMINFO*	Item2;
/*0x0108*/ struct _CXSTR *ClientString;
/*0x010C*/ BYTE Filler0x010C[0x4];
/*0x0110*/
EQLIB_OBJECT _CONTENTS *GetContent(UINT index);
EQLIB_OBJECT ItemGlobalIndex2 &GetGlobalIndex();

	// Compatibility properties for ItemEvolutionData
	[[deprecated("Use pEvolutionData->GroupID instead")]]
	inline int get_EvolvingGroupID() { return pEvolutionData ? pEvolutionData->GroupID : 0; }
	__declspec(property(get = get_EvolvingGroupID)) int GroupID;

	[[deprecated("Use pEvolutionData->EvolvingCurrentLevel instead")]]
	inline int get_EvolvingCurrentLevel() { return pEvolutionData ? pEvolutionData->EvolvingCurrentLevel : 0; }
	__declspec(property(get = get_EvolvingCurrentLevel)) int EvolvingCurrentLevel;

	[[deprecated("Use pEvolutionData->EvolvingExpPct instead")]]
	inline double get_EvolvingExpPct() { return pEvolutionData ? pEvolutionData->EvolvingExpPct : 0.0; }
	__declspec(property(get = get_EvolvingExpPct)) double EvolvingExpPct;

	[[deprecated("Use pEvolutionData->EvolvingMaxLevel instead")]]
	inline int get_EvolvingMaxLevel() { return pEvolutionData ? pEvolutionData->EvolvingMaxLevel : 0; }
	__declspec(property(get = get_EvolvingMaxLevel)) int EvolvingMaxLevel;

	[[deprecated("Use pEvolutionData->LastEquipped instead")]]
	inline int get_LastEquipped() { return pEvolutionData ? pEvolutionData->LastEquipped : 0; }
	__declspec(property(get = get_LastEquipped)) int LastEquipped;
} CONTENTS, *PCONTENTS;

#pragma pack(push)
#pragma pack(8)
typedef union _EqGuid {
    struct {
        UINT UniqueEntityID;
		WORD WorldUniqueID;
		WORD Reserved;
    } DUMMYSTRUCTNAME;
    unsigned __int64 GUID;
} EqGuid;
#pragma pack(pop)

typedef struct _SlotData {
	LONG Slot;
	DWORD Value;
} SlotData;
// Size 0x58 20110810 - dkaa
// Size 0x58 20150326 - demonstar55
// Size 0x68 Apr 10 2018 test see 8B2FD5 - eqmule
// Size 0x68 Oct 07 2019 test see 8C9BAD - eqmule
// this is EQ_Affect
typedef struct _SPELLBUFF {
/*0x00*/ EqGuid    CasterGuid;
/*0x08*/ SlotData SlotData[NUM_SLOTDATA]; // used for book keeping of various effects (debuff counter, rune/vie damage remaining)
/*0x38*/ DWORD     Flags;
/*0x3C*/ LONG      SpellID;       // -1 or 0 for no spell..
/*0x40*/ DWORD     Duration;
/*0x44*/ DWORD     InitialDuration;
/*0x48*/ DWORD     HitCount;
/*0x4c*/ UINT      ViralTimer;		//not 100% sure this is correct
/*0x50*/ FLOAT     Modifier;      // Bard song modifier, 1.0 is default BaseDmgMod
/*0x54*/ FLOAT     Y;             // Referenced by SPA 441 (distance removal)
/*0x58*/ FLOAT     X;
/*0x5c*/ FLOAT     Z;
/*0x60*/ BYTE      Type;
/*0x61*/ BYTE      Level;//casterlevel
/*0x62*/ BYTE      ChargesRemaining; //dont think this is used anymore.
/*0x63*/ BYTE      Activatable;//dont think this is used anymore. We used to think this was DamageShield
/*0x64*/ DWORD     Unknown0x64;//not 100% sure this is correct it could be ViralTimer
/*0x68*/
} SPELLBUFF, *PSPELLBUFF;

// 20101012 - ieatacid
typedef struct _INVENTORY { 
/*0x00*/  struct    _CONTENTS* Charm;
/*0x04*/  struct    _CONTENTS* LeftEar;
/*0x08*/  struct    _CONTENTS* Head;
/*0x0c*/  struct    _CONTENTS* Face;
/*0x10*/  struct    _CONTENTS* RightEar;
/*0x14*/  struct    _CONTENTS* Neck;
/*0x18*/  struct    _CONTENTS* Shoulders;
/*0x1c*/  struct    _CONTENTS* Arms;
/*0x20*/  struct    _CONTENTS* Back;
/*0x24*/  struct    _CONTENTS* LeftWrist;
/*0x28*/  struct    _CONTENTS* RightWrist;
/*0x2c*/  struct    _CONTENTS* Range;
/*0x30*/  struct    _CONTENTS* Hands;
/*0x34*/  struct    _CONTENTS* Primary;
/*0x38*/  struct    _CONTENTS* Secondary;
/*0x3c*/  struct    _CONTENTS* LeftFinger;
/*0x40*/  struct    _CONTENTS* RightFinger;
/*0x44*/  struct    _CONTENTS* Chest;
/*0x48*/  struct    _CONTENTS* Legs;
/*0x4c*/  struct    _CONTENTS* Feet;
/*0x50*/  struct    _CONTENTS* Waist;
/*0x54*/  struct    _CONTENTS* PowerSource;
/*0x58*/  struct    _CONTENTS* Ammo;
/*0x5c*/  struct    _CONTENTS* Pack[NUM_BAG_SLOTS];
/*0x84*/  struct    _CONTENTS* Cursor;
} INVENTORY, *PINVENTORY;

//need to find this one
#define NUM_ALT_ABILITIES_ARRAY         0x1F7      
// see 4FBD46 in eqgame.exe dated oct 29 2013 test - eqmule
#define NUM_ALT_ABILITIES               0xC34F

//these two will merge when i get a chance - ieatacid wrote this?
#define AA_CHAR_MAX                     0xF5
//EQ_PC__GetAlternateAbilityId_x
//size is at 7EE7F8 in eqgame dated jun 13 2014 - eqmule
#define AA_CHAR_MAX_REAL                0x12C

typedef struct _AALIST { 
/*0x00*/ DWORD AAIndex;
/*0x04*/ DWORD PointsSpent;
/*0x08*/ DWORD ChargeSpent;        // charges spent in the last 10 min?
/*0x0c*/
} AALIST, *PAALIST;

#define NUM_INV_SLOTS                   0x21
#define NUM_BANK_SLOTS                  0x18
#define NUM_SHAREDBANK_SLOTS            0x06
#define MAX_KEYRINGITEMS			    0x1B //not really sure need to confirm this
//found in CSpellBookWnd__GetBookSlot_x (see 7A7DD7 in Nov 29 2017 Beta) -eqmule 
//Find by searching for A1 ? ? ? ? 53 83 CB FF 85 C0 in IDA 
#define NUM_BOOK_SLOTS                  0x3C0
#define NUM_COMBAT_ABILITIES            0x12c
#define BAG_SLOT_START                  23
#define ExactLocation                   0
#define NUM_SKILLS						0x64
#define CONCURRENT_SKILLS				2
#define MAX_CLASSES						0x23//35 =GM_Berzerker

typedef struct _LEADERABILITIES {
/*0x00*/ DWORD MarkNPC;
/*0x04*/ DWORD NPCHealth;
/*0x08*/ DWORD Unknown0x8;
/*0x0c*/ DWORD DelegateMA;
/*0x10*/ DWORD DelegateMarkNPC;
/*0x14*/ DWORD Unknown0x14;
/*0x18*/ DWORD InspectBuffs;
/*0x1c*/ DWORD Unknown0x1c;
/*0x20*/ DWORD SpellAwareness;
/*0x24*/ DWORD OffenseEnhancement;
/*0x28*/ DWORD ManaEnhancement;
/*0x2c*/ DWORD HealthEnhancement;
/*0x30*/ DWORD HealthRegen;
/*0x34*/ DWORD FindPathPC;
/*0x38*/ DWORD HoTT;
/*0x3c*/
} LEADERABILITIES, *PLEADERABILITIES;

typedef struct _EQC_INFO {
/* 0x0000 */    DWORD   minus4;
/* 0x0004 */    DWORD   stuff_offset;
} EQC_INFO, *PEQC_INFO;

typedef struct _CI_INFO {
/* 0x0000 */    DWORD   minus8;
/* 0x0004 */    DWORD   stuff_offset;
/* 0x0008 */    DWORD   Unknown0x8;    // 2000
/* 0x000c */    DWORD   Unknown0xc;    // 2500
/* 0x0010 */    DWORD   Unknown0x10;   // 3000
/* 0x0014 */    DWORD   Unknown0x14;   // 4000
/* 0x0018 */    DWORD   Unknown0x18;   // 10000
} CI_INFO, *PCI_INFO;
enum eProfileListType
{
	ePLT_Regular,
	cPLT_MonsterMission
};
#ifndef NEWCHARINFO
typedef struct _CI2_INFO {
/* 0x0000 */    eProfileListType ListType;
/* 0x0004 */    struct  _CHARINFO2* pCharInfo2;
/* 0x0008 */    struct  _CHARINFO2* pLast;
/* 0x000c */    struct  _CHARINFO2* pNext;
/* 0x0010 */    struct  _CHARINFO2* pPrev;
/* 0x0014 */
} CI2_INFO, *PCI2_INFO;
#endif

//size 34 i think in eqgame dated mar 23 2015 but i have no address for it atm -eqmule
typedef struct _GROUPMEMBER {
/*0x00*/ void   *vftable;
/*0x04*/ struct _CXSTR *pName;
/*0x08*/ BYTE   Mercenary;
/*0x09*/ BYTE   Unknown0x9[0x3];
/*0x0c*/ struct _CXSTR *pOwner; // name of mercenary's owner
/*0x10*/ DWORD  Level;
/*0x14*/ BYTE   Offline;//1 if groupmember is offline
/*0x15*/ BYTE   Unknown0x15[8];
/*0x1d*/ BYTE   MainTank;
/*0x1e*/ BYTE   MainAssist;
/*0x1f*/ BYTE   Puller;
/*0x20*/ BYTE   MarkNpc;
/*0x21*/ BYTE   MasterLooter;
/*0x22*/ BYTE   Unknown0x22[0x2];
/*0x24*/ DWORD  Roles;          // (Roles & 0x1) = MainTank, 0x2 = MainAssist, 0x4 = Puller 0x8 = Mark NPC 0x10 = Master Looter
/*0x28*/ BYTE   Unknown0x28[0x8];
/*0x30*/ struct _SPAWNINFO *pSpawn;
/*0x34*/
} GROUPMEMBER, *PGROUPMEMBER;

typedef struct _GROUPINFO {
/*0x00*/ void   *vftable;
/*0x04*/ struct _GROUPMEMBER *pMember[0x6];
/*0x1c*/ struct _GROUPMEMBER *pLeader;
/*0x20*/
} GROUPINFO, *PGROUPINFO;

typedef struct _BANKARRAY {
/*0x00*/ struct _CONTENTS* Bank[NUM_BANK_SLOTS];
/*0x60*/
} BANKARRAY, *PBANKARRAY;

typedef struct _SHAREDBANKARRAY {
/*0x00*/ struct _CONTENTS* SharedBank[NUM_SHAREDBANK_SLOTS];
/*0x10*/
} SHAREDBANKARRAY, *PSHAREDBANKARRAY;

typedef struct _MERCEQUIPMENT {
	/*0x00*/ struct _CONTENTS* MercEquipment[4];
	/*0x68*/
} MERCEQUIPMENT, *PMERCEQUIPMENT;

//added dec 08 2014 -eqmule
typedef struct _KEYRINGARRAY {
	union {
		/*0x00*/ struct _CONTENTS* Mounts[MAX_KEYRINGITEMS];
		/*0x00*/ struct _CONTENTS* Illusions[MAX_KEYRINGITEMS];
		/*0x00*/ struct _CONTENTS* Familiars[MAX_KEYRINGITEMS];
	};
	/*0x28*/
} KEYRINGARRAY, *PKEYRINGARRAY;

struct Point 
{
	UINT PointType;
	UINT PointSubtype;
	UINT CurrentCount;
	UINT TotalEver;
};
class CPlayerPointManager
{
public:
/*0x00*/	PVOID vfTable;
/*0x04*/	ArrayClass_RO<Point *>Points;
/*0x14*/
};
struct PointNamesEntry
{
	UINT PointTypeId;
	UINT PointSubtypeId;
	int DBStringId;
	int PointItemId;
	int ImageId;
	int MaxStackSize;
	bool bStationCashRelated;
};
class PointSystemBase
{
public:
/*0x00*/	PVOID vfTable;
/*0x04*/	ArrayClass_RO<PointNamesEntry *>PointNameEntries;
/*0x14*/
};

class PendingReward
{
public:
/*0x00*/	PVOID vfTable;
/*0x04*/	int		ID;
/*0x08*/	int		SetID;
/*0x0c*/	FLOAT	RewardAdjustment;
/*0x10*/	CHAR	RewardTitle[0x80];
/*0x90*/
};
class PendingRewardList : public DoublyLinkedList<PendingReward*>
{
public:
/*0x20*/	int	NextUID;
/*0x24*/	int MaxPending;
/*0x28*/	int ZoneMaxPending;
/*0x2c*/
};
enum ELockoutCharacterReason
{
	LCR_AllowNormalPlay,
	LCR_InvalidWornItem,
	LCR_Something,
};
struct ProgressionExperience
{
/*0x00*/	int ProgressionID;
/*0x08*/	double ProgressionExp;
/*0x10*/
};

//start of reorganisation for charinfo etc...
//todo: finish it...

template <typename TItem> class ItemContainer
{
public:
/*0x00*/	UINT Size;
/*0x04*/	int Spec;
/*0x08*/	VeArray<VePointer<TItem>> Items;
/*0x0c*/	BYTE AtDepth;
/*0x10*/	short Slots[2];
/*0x14*/	bool bDynamic;
/*0x18*/
};

class ItemBaseContainer : public ItemContainer<CONTENTS>
{
public:

};

class CharacterPropertyHash : public HashTable<int>
{
public:

};

enum eProfileType {
	ePTMain,
	ePTAlt,
	ePTMonsterMission,
	ePTUnknown
};

struct WorldLocation
{
/*0x00*/ DWORD        ZoneBoundID;
/*0x04*/ FLOAT        ZoneBoundY;
/*0x08*/ FLOAT        ZoneBoundX;
/*0x0c*/ FLOAT        ZoneBoundZ;
/*0x10*/ FLOAT        ZoneBoundHeading;
/*0x14*/
};

template <typename TheType> class TList
{
public:
/*0x00*/ TheType* pFirst;
/*0x04*/ TheType* pLast;
/*0x08*/
};
template <class Type> class TListNode
{
/*0x0004*/ Type*    pPrev;
/*0x0008*/ Type*    pNext;
/*0x000c*/ BYTE		Unknown0x000c[0xc];
};
struct CombatAbilityTimer : public TListNode<CombatAbilityTimer>
{
	int		SpellGroup;
	UINT	ExpireTimer;
};
struct AssociatedNPCSaveStringNode
{
/*0x0000*/ CHAR SaveString[0x2000];//0x1000 in older clients
/*0x2000*/ AssociatedNPCSaveStringNode *pNext;
/*0x2004*/
};
struct BandolierItemInfo
{
/*0x00*/ int ItemID;
/*0x04*/ int IconID;
/*0x08*/ CHAR Name[0x40];
/*0x48*/
};
struct BandolierSet
{
/*0x000*/ CHAR Name[0x20];
/*0x020*/ BandolierItemInfo Items[4];//0x120 = 0x48 * 4
/*0x140*/
};
struct BenefitSelection
{
/*0x00*/	int BenefitID;
/*0x04*/	int BenefitTier;
/*0x08*/
};

//BaseProfile Todo: fill it in...
class BaseProfile
{
	//has a vftable
public:
/*0x0000*/ PVOID vfTable;
/*0x0004*/ BaseProfile* pNextProfile;
/*0x0008*/ BaseProfile* pPrevProfile;
/*0x000c*/ DWORD        Unknown0x000c;
/*0x0010*/ eProfileListType	    profileListType;
/*0x0014*/ ItemBaseContainer	pInventoryArray;//size 0x1c
/*0x0030*/ ItemBaseContainer	TributeBenefitItems;
/*0x004c*/ ItemBaseContainer	TrophyTributeBenefitItems;
/*0x0068*/ TSafeArrayStatic<struct _SPELLBUFF, NUM_LONG_BUFFS>  Buff;//size 0x1110
/*0x1178*/ TSafeArrayStatic<struct _SPELLBUFF, NUM_SHORT_BUFFS> ShortBuff;//size 0x1658
//*0x27d0*/ TSafeArrayStatic<unsigned int, NUM_BUFF_SLOTS>   CasterSpellIDs;//size 0x184
//*0x2954*/ TSafeArrayStatic<unsigned int, NUM_BUFF_SLOTS>   DiseaseSpreadTimers;//size 0x184
/*0x27D0*/ TSafeArrayStatic<int, NUM_BOOK_SLOTS>    SpellBook;//size 0xf00
/*0x36d0*/ TSafeArrayStatic<int, 0x12>  MemorizedSpells;
/*0x3718*/ TSafeArrayStatic<int, NUM_SKILLS>  Skill;
/*0x38a8*/ TSafeArrayStatic<int, 0x19>  InnateSkill;
/*0x390C*/ TSafeArrayStatic<ArmorProperties, 9> CharArmorProps;//size 0xb4
/*0x39C0*/ TSafeArrayStatic<DWORD, 9>    CharTint;
/*0x39e4*/ DWORD        Gender;
/*0x39e8*/ DWORD        Race;
/*0x39ec*/ DWORD        Class;
/*0x39f0*/ HashTable<int> properties;
/*0x3a00*/ DWORD        Level;
/*0x3a04*/ DWORD        Mana;
/*0x3a08*/ DWORD        Endurance;
/*0x3a10*/ __int64      BaseHP;
/*0x3a18*/ DWORD        BaseSTR;
/*0x3a1c*/ DWORD        BaseSTA;
/*0x3a20*/ DWORD        BaseCHA;
/*0x3a24*/ DWORD        BaseDEX;
/*0x3a28*/ DWORD        BaseINT;
/*0x3a2c*/ DWORD        BaseAGI;
/*0x3a30*/ DWORD        BaseWIS;
/*0x3a34*/ int          Face;
/*0x3a38*/ DWORD        Plat;
/*0x3a3c*/ DWORD        Gold;
/*0x3a40*/ DWORD        Silver;
/*0x3a44*/ DWORD        Copper;
/*0x3a48*/ DWORD        CursorPlat;
/*0x3a4c*/ DWORD        CursorGold;
/*0x3a50*/ DWORD        CursorSilver;
/*0x3a54*/ DWORD        CursorCopper;
/*0x3a58*/ int         _max_allowed_spell_slots;
/*0x3a5c*/ int         practices;
/*0x3a60*/ int         height;
/*0x3a64*/ int         width;
/*0x3a68*/ int         length;
/*0x3a6c*/ int         view_height;
/*0x3a70*/ char        texture_type;
/*0x3a71*/ char        m_armorMat;
/*0x3a72*/ char        m_armorVariation;
/*0x3a73*/ char        headType;
/*0x3a74*/ char        caneditface;
/*0x3a78*/ int         DisciplineTimer;
/*0x3a7c*/ UINT        MendTimer;
/*0x3a80*/ int         ForageTimer;
/*0x3a84*/ int         thirstlevel;
/*0x3a88*/ int         hungerlevel;
/*0x3a8c*/ int         PotionCount;
/*0x3a90*/ int         profileType;
/*0x3a94*/ int         Shrouded;
/*0x3a98*/ int         systemId;
/*0x3a9c*/ int         designId;
/*0x3aa0*/ int         InventorySlotBitmask;
/*0x3aa4*/ UINT        CurrentProgressionID;
/*0x3aa8*/ BYTE        Unknown0x3aa8[0x54];
/*0x3afc*/ int         ParentId;
/*0x3b00*/ int         TattooIndex;
/*0x3b04*/ int         FacialAttachmentIndex;
/******************************** BaseProfile End ********************************/
/******************************** PcProfile Start ********************************/
/*0x3b08*/ TSafeArrayStatic<WorldLocation,5>			BoundLocations;//size 0x64 home_zone
/*0x3B6C*/ TSafeArrayStatic<ArmorProperties, 0x16>		ArmorType;//size 0x1b8
/*0x3D24*/ TSafeArrayStatic<AALIST, AA_CHAR_MAX_REAL>	AAList;//AlternateAbilities 0xE10
/*0x4B34*/ TSafeArrayStatic<DWORD, 0x9>					BodyColor;//0x24
/*0x4b58*/ TSafeArrayStatic<int, 0x800>					FactionTable;//factiontable 0x2000
/*0x6b58*/ TSafeArrayStatic<int, NUM_COMBAT_ABILITIES>	CombatAbilities;//KnownCombatAbilities 0x4B0
/*0x7008*/ TSafeArrayStatic<UINT, 0xF>		SpellRecastTimer;  //spell_used 0x3C
/*0x7044*/ TSafeArrayStatic<UINT, 0x19>		CombatAbilityTimers; //fs 0x64
/*0x70A8*/ TList<CombatAbilityTimer>		CombatAbilityTimersList;//size 8 for sure CombatAbilityTimersAddl
/*0x70b0*/ TSafeArrayStatic<UINT, 0x19>		LinkedSpellTimers;// 0x64 for sure, we used to call thius CombatAbilityTimes...
/*0x7114*/ TSafeArrayStatic<UINT, 0x64>		ItemRecastTimers; //0x190 for sure
/*0x72A4*/ TSafeArrayStatic<UINT, 0x64>		AATimers;//for sure
/*0x7434*/ TSafeArrayStatic<BandolierSet, 0x14>		Bandolier;//size 0x1900 = 0x140 * 0x14 for sure see 8DE476 Jan 04 2019 test
//gone in test 2019-01-04 test /*0x903C*/ TSafeArrayStatic<BandolierItemInfo, 5>	PotionBelt;//size 0x168 = 0x48 * 5
/*0x8D34*/ TSafeArrayStatic<BenefitSelection, 5>	ActiveTributeBenefits;//size 0x28 = 8 * 5 for sure see 8DE437 Jan 04 2019 test
/*0x8D5C*/ TSafeArrayStatic<BenefitSelection, 0xa>	ActiveTrophyTributeBenefits;//size 0x50 = 8 * 0xa
/*0x8DAC*/ ItemBaseContainer		GuildTributeBenefitItems;//size 0x1c for sure see 8C9D9C in 21 Sep 2018
/*0x8DC8*/ ItemBaseContainer		GuildTrophyTributeBenefitItems;//size 0x1c
/*0x8DE4*/ ArrayClass_RO<PCXSTR>	MercenarySaveStrings;//size 0x10
/*0x8DF4*/ AssociatedNPCSaveStringNode *PetSaveString;//for sure
/*0x8DF8*/ DWORD	Deity;//fs see 8DE504 Jan 04 2019 test
/*0x8DFC*/ bool		bPVPFlag;
/*0x8DFD*/ BYTE		HighestLevel;
/*0x8E00*/ DWORD	Drunkenness;//inebriation
/*0x8E04*/ BYTE		HairColor;
/*0x8E05*/ BYTE		BeardColor;
/*0x8E08*/ int		NpcTintIndex;
/*0x8E0c*/ BYTE		LeftEye;
/*0x8E0d*/ BYTE		RightEye;
/*0x8E0e*/ BYTE		Hair;
/*0x8E0f*/ BYTE		Beard;
/*0x8E10*/ BYTE		OldFace;	
/*0x8E14*/ DWORD	AAPoints;
/*0x8E18*/ CHAR		PocketPetSaveString[0x2000];//0x1000 in older clients
/*0xAE18*/ PCXSTR	ItemBuffer;
/*0xAE1C*/ UINT		LastShield;
/*0xAE20*/ bool		bSneak;
/*0xAE21*/ bool		bHide;
/*0xAE24*/ DWORD	AAPointsSpent;
/*0xAE28*/ DWORD	AAPointsAssigned[6];//none, general, arch, class, special, focus, merc
/*0xAE40*/ void	*	pPetData;//PetObjectData todo fill in
/*0xAE44*/ DWORD    PrimActor;
/*0xAE48*/ DWORD    SecdActor;
/*0xAE4C*/ bool     bUseTemplateFaction;
/*0xAE50*/ DWORD    TitlePrefixID;
/*0xAE54*/ DWORD    TitleSuffixID;
/*0xAE58*/ bool     bAreHandsMagic;
/*0xAE5c*/ DWORD    SoleEnabledZoneID;
/*0xAE60*/ DWORD    NewBodyTint;
/*0xAE64*/ DWORD    CurrentMercenaryIndex;
/*0xAE68*/
EQLIB_OBJECT VePointer<CONTENTS> BaseProfile::GetItemPossession(const ItemIndex &lIndex) const;
};

class ProfileList
{
	//has no vftable
public:
/*0x00*/	eProfileListType ListType;
/*0x04*/	BaseProfile* pFirst;
/*0x08*/	BaseProfile* pLast;
/*0x0c*/	ProfileList* pNext;
/*0x10*/	ProfileList* pPrev;
/*0x14*/
};

class CProfileManager
{
	//has no vftable
public:
/*0x00*/	ProfileList* pFirst;
/*0x04*/	eProfileListType CurProfileList;
/*0x08*/
inline const ProfileList* CProfileManager::GetCurrentProfileList() const
{
	ProfileList *pWalk = pFirst;
	while ( pWalk != NULL ) {
		if ( pWalk->ListType == CurProfileList )
		{
			return pWalk;
		}
		pWalk = pWalk->pNext;
	}
	return NULL;
}

inline const BaseProfile* CProfileManager::GetCurrentProfile() const
{
	const ProfileList *pList = GetCurrentProfileList();
	if ( pList != NULL )
	{
		return pList->pFirst;
	}
	return NULL;
}
};
struct PCTaskStatus
{
/*0x00*/	int TaskID;
/*0x04*/	int MovingStartTime;
/*0x08*/	int InitialStartTime;
/*0x0c*/	bool ElementActive[0x14];
/*0x20*/	int CurrentCounts[0x14];
/*0x70*/
};

struct MailItemData
{
/*0x00*/	UINT	SendTime;
/*0x04*/	PCXSTR	SenderName;
/*0x08*/	PCXSTR	Note;
/*0x0c*/
};

enum eDynamicZoneType
{
	eDZT_Unknown,
	eDZT_Expedition,
	eDZT_Tutorial,
	eDZT_Task,
	eDZT_Mission,
	eDZT_Quest
};

struct DynamicZoneData
{
/*0x00*/	int		DynamicZoneID;
/*0x04*/	int		SetID;
/*0x08*/	eDynamicZoneType	Type;
/*0x0c*/
};
struct TradeskillRecipeCount
{
/*0x00*/	int		SkillID;
/*0x04*/	int		RecipeCount;
/*0x08*/
};

struct DynamicZoneTimerData
{
/*0x00*/	int		DataSetID;
/*0x04*/	UINT	TimerExpiration;
/*0x08*/	int		EventID;
/*0x0c*/	int		DynamicZoneID;
/*0x10*/	DynamicZoneTimerData	*pNext;
/*0x14*/
};

//size 0x60 see 59D900 in 07 apr 2020 test -eqmule
struct PvPKill
{
/*0x00*/	CHAR VictimName[0x40];
/*0x40*/	int VictimLevel;
/*0x44*/	int Unknown0x44;
/*0x48*/	int Unknown0x48;
/*0x4C*/	DWORD VictimRace;
/*0x50*/	DWORD VictimClass;
/*0x54*/	int ZoneID;
/*0x58*/	long Lastkilltime;
/*0x5C*/	int PointsEarned;
/*0x60*/
};

struct PvPDeath
{
/*0x00*/	CHAR KillerName[0x40];
/*0x40*/	int KillerLevel;
/*0x44*/	DWORD KillerRace;
/*0x48*/	DWORD KillerClass;
/*0x4c*/	int ZoneID;
/*0x50*/	long LastDeathTime;
/*0x54*/	int PointsLost;
/*0x58*/
};

struct PvPKill24HourData : public PvPKill
{
	//nothing here?
};

enum eAreaCorner
{
	eAC_None = -1,
	eAC_TopLeftCorner,
	eAC_TopRightCorner,
	eAC_BottomLeftCorner,
	eAC_BottomRightCorner,
};

struct PCAdventureThemeStats
{
/*0x00*/	int SucceededNormal;
/*0x04*/	int FailedNormal;
/*0x08*/	int SucceededHard;
/*0x0c*/	int FailedHard;
/*0x10*/	int AdventureTotalPointsEarned;
/*0x14*/
};

struct PCAdventureData
{
/*0x000*/	int AdventureLastAdventureDefinitionSeen[5];
/*0x014*/	UINT AdventureLastAdventureDefinitionSeenTime[5];
/*0x028*/	int AdventureActiveAdventureId;
/*0x02c*/	int AdventureActiveAdventureTheme;
/*0x030*/	int AdventureActiveAdventureRisk;
/*0x034*/	int AdventureSafeReturnZoneId;
/*0x038*/	FLOAT AdventureSafeReturnX;
/*0x03c*/	FLOAT AdventureSafeReturnY;
/*0x040*/	FLOAT AdventureSafeReturnZ;
/*0x044*/	int AdventureStatAccepted;
/*0x048*/	int AdventureStatRejected;
/*0x04c*/	int AdventureStatEntered;
/*0x050*/	int AdventureStatFailedEnter;
/*0x054*/	int AdventurePointsAvailable;
/*0x058*/	int AdventurePointsAvailableMax;
/*0x05c*/	UINT AdventureLastSuccessTime;
/*0x060*/	PCAdventureThemeStats ThemeStats[6];
/*0x0d8*/
};

struct MonsterMissionTemplate
{
/*0x00*/	int		TemplateID;
/*0x04*/	int		Min;
/*0x08*/	int		Max;
/*0x0c*/	int		NumSelected;
/*0x10*/	bool	CanSelect;
/*0x14*/	CHAR	TemplateName[0x40];
/*0x54*/
};

struct PCSharedTaskData
{
/*0x00*/	int	ActiveSharedTaskID;
/*0x04*/	bool bIsMonsterMission;
/*0x08*/	PCTaskStatus Status;//size 0x70
/*0x78*/	ArrayClass_RO<MonsterMissionTemplate> Templates;//size is 0x10
/*0x88*/	FLOAT	RewardAdjustment;
/*0x8c*/
};

struct TaskTimerData
{
/*0x00*/	int GroupID;
/*0x04*/	int TimerSeconds;
/*0x08*/	UINT TimerExpiration;
/*0x0c*/	int TimerType;
/*0x10*/	int OrigTaskID;
/*0x14*/	TaskTimerData *pNext;
/*0x18*/
};

struct PCCompletedQuest
{
/*0x00*/	int QuestID;
/*0x04*/	int ElementBitmask;
/*0x08*/	UINT TimeCompleted;
/*0x0c*/
};

struct PCQuestHistoryData
{
/*0x000*/	PCCompletedQuest Quests[0x32];//size 0xc * 0x32 = 0x258
/*0x258*/
};

class StatCounter
{
public:
/*0x00*/	UINT Value;
/*0x04*/
};

class StatElapsedTime
{
public:
/*0x00*/	UINT StartTick;
/*0x04*/	UINT ElapsedTotal;
/*0x08*/	bool bCurrentState;
/*0x0c*/
};

class PCStatistics
{
public:
	enum eStatisticType {
		S_TotalExpEarned,
		S_GroupExpEarned,
		S_ExpRaidEarned,
		S_ExpSoloEarned,
		S_NonExpKills,
		S_ExpKills,
		S_ZonesVisited,
		S_ChatShouts,
		S_ChatOOCs,
		S_ChatSays,
		S_ChatGroup,
		S_ChatTells,
		S_Deaths, 
		S_Resurrections, 
		S_PlatEarned,
		S_TradeskillCombines,
		S_Forages,
		S_Quests,
		S_LastStat,
	};
/*0x000*/	StatElapsedTime StatTimeSession; //size 0xc
/*0x00c*/	StatElapsedTime StatTimeLFG;
/*0x018*/	StatElapsedTime StatTimeGrouped;
/*0x024*/	StatElapsedTime StatTimeSolo;
/*0x030*/	StatElapsedTime StatTimeRaid;
/*0x03c*/	StatElapsedTime StatTimeInBazaar;
/*0x048*/	StatCounter Statistics[S_LastStat];//size is 0x48
/*0x090*/	UINT LastUpdateTime;
/*0x094*/	CHAR PlayerName[0x40];
/*0x0d4*/	CHAR PlayerStationID[0x20];
/*0x0f4*/	int PlayerLevel;
/*0x0f8*/	DWORD PlayerRace;
/*0x0fc*/	DWORD PlayerClass;
/*0x100*/	UINT UniquePlayerID;
/*0x104*/
};

class GroupMemberStats
{
public:
	enum eStatisticType {
		S_Mez,
		S_Root,
		S_Charmed,
		S_Stunned,
		S_Slowed,
		S_FirstAgro,
		S_DmgMelee,
		S_DmgRanged,
		S_DmgSpell,
		S_DmgDot,
		S_DmgPet,
		S_DmgTaken,
		S_DmgHealed,
		S_ExpTotalEarned,
		S_Deaths,
		S_ExpKills,
		S_NonExpKills,
		S_ManaUsed,
		S_EnduranceUsed,
		S_LastStat,
	};
/*0x000*/	CHAR PlayerName[0x40];
/*0x040*/	int PlayerLevel;
/*0x044*/	int PlayerRace;
/*0x048*/	int PlayerClass;
/*0x04c*/	UINT UniquePlayerId;
/*0x050*/	UINT LastMemberUpdateTime;
/*0x054*/	PCXSTR StationID;
/*0x058*/	int PlayerGuild;
/*0x05c*/	TSafeArrayStatic<int, NUM_LONG_BUFFS> BuffIDs;//size 0xa8
/*0x104*/	TSafeArrayStatic<StatCounter, S_LastStat> Statistics;//size 0x4c
/*0x150*/
};

struct ClaimData
{
/*0x00*/	int FeatureID;
/*0x04*/	int Count;
/*0x08*/
};

class ClaimDataCollection
{
public:
/*0x00*/	ArrayClass<ClaimData> ClaimData;
/*0x10*/
};

class MercenaryAbilityInfo
{
public:
/*0x00*/	int Index;
/*0x04*/	int Cost;
/*0x08*/
};

struct CompletedAchievementData
{
/*0x00*/	int AchievementID;
/*0x04*/	UINT CompletedTimestamp;
/*0x08*/	int CompletedVersion;
/*0x0c*/
};

enum eAchievementSubReqType
{ 
	eASCRT_Invalid, 
	eASCRT_Requirement, 
	eASCRT_KillNpcRaceMat, 
	eASCRT_RightClickItem,
	eASCRT_KillNpc,
	eASCRT_Count,
};

struct AchievementSubComponentCountData
{
/*0x00*/	int AchievementID;
/*0x04*/	int ComponentID;
/*0x08*/	int RequirementID;
/*0x0c*/	eAchievementSubReqType SubReqType;
/*0x10*/	int Count;
/*0x14*/
};

struct RaidData
{
/*0x00*/	int MainAssists[3];
/*0x0c*/	CHAR MainAssistNames[3][0x40];
/*0xcc*/	int MainMarkers[3];
/*0xd8*/	int MasterLooter;
/*0xdc*/
};

// Apr 13 2020 Test -eqmule
typedef struct _FELLOWSHIPMEMBER {
/*0x00*/ EqGuid	UniqueEntityID;
/*0x08*/ CHAR		Name[0x40];
/*0x48*/ int		ZoneID;
/*0x4c*/ int		Level;
/*0x50*/ int		Class;
/*0x54*/ int		LastOn;    // FastTime() timestamp
/*0x58*/
} FELLOWSHIPMEMBER, *PFELLOWSHIPMEMBER;

// 20121128 - ieatacid 0x9e4
// Dec 13 2016 - eqmule 0x9e8 see 5C3F9F
// Apr 13 2020 Test - eqmule 0x860 see 58FA66
typedef struct _FELLOWSHIPINFO
{
/*0x000*/ int		Version;//just place holders for now, ill fix these later
/*0x004*/ int		Version2;
/*0x008*/ int		Version3;
/*0x00c*/ int		Version4;
/*0x010*/ EqGuid	FellowshipGUID;
/*0x018*/ CHAR		MotD[0x400];
/*0x418*/ int		Members;
/*0x420*/ struct _FELLOWSHIPMEMBER FellowshipMember[0xc];//yes this does start at 0x420 because the first member of _FELLOWSHIPMEMBER is a __int64 and its 8 aligned... size 0xc * 0x58 = 0x420
/*0x840*/ int		Sync;
/*0x844*/ bool		bExpSharingEnabled[0xc];
/*0x850*/ bool		bSharedExpCapped[0xc];
/*0x85c*/ int		Unknown0x85c;
/*0x860*/
} FELLOWSHIPINFO, *PFELLOWSHIPINFO;

enum ItemSpellTypes
{
	eActivatableSpell,
	eProcSpell,
	eWornSpell,
	eFocusSpell,
	eScrollSpell,
	eFocus2Spell,
	eMountSpell,
	eIllusionSpell,
	eFamiliarSpell
};

typedef struct _VECTOR2
{
	FLOAT X;
	FLOAT Y;
} VECTOR2, *PVECTOR2;

// actual size: 0x22e Feb 16 2018 test see 5F68F6 - eqmule
// actual size: 0x22d Apr 10 2018 test see 557362 - eqmule
// actual size: 0x229 May 07 2018 test see 6628CA  - eqmule
// actual size: 0x231 Oct 07 2019 test see 565BE2  - eqmule
typedef struct _SPELL { //      1     |    0   | -30  |   0    | 103  | 125
/*0x000*/   FLOAT   Range;
/*0x004*/   FLOAT   AERange;
/*0x008*/   FLOAT   PushBack;
/*0x00c*/   FLOAT   PushUp;
/*0x010*/   DWORD   CastTime;
/*0x014*/   DWORD   RecoveryTime;
/*0x018*/   DWORD   RecastTime;
/*0x01c*/   DWORD   DurationType;       //DurationFormula on Lucy
/*0x020*/   DWORD   DurationCap;
/*0x024*/   DWORD   AEDuration;
/*0x028*/   DWORD   ManaCost;
/*0x02C*/   FLOAT   Unknown0x02C; //its a float for sure see 565CB5 in eqgame oct 07 2019 -eqmule
/*0x030*/   DWORD   ReagentID[0x4];     //ReagentId1-ReagentId4d
/*0x040*/   DWORD   ReagentCount[0x4];  //ReagentCount1-ReagentCount4
/*0x050*/   DWORD   NoExpendReagent[0x4];
/*0x060*/   LONG    CalcIndex;
/*0x064*/   LONG    NumEffects;
/*0x068*/   DWORD   BookIcon;
/*0x06C*/   DWORD   GemIcon;
/*0x070*/   DWORD   DescriptionIndex;
/*0x074*/   DWORD   ResistAdj;
/*0x078*/   DWORD   Diety;
/*0x07c*/   DWORD   spaindex;
/*0x080*/   DWORD   SpellAnim;
/*0x084*/   DWORD   SpellIcon;
/*0x088*/   DWORD   DurationParticleEffect;
/*0x08c*/   DWORD   NPCUsefulness;
/*0x090*/   DWORD   ID;
/*0x094*/   DWORD   Autocast;         //SpellID of spell to instacast on caster when current spell lands on target
/*0x098*/   DWORD   Category;         //Unknown144 from lucy
/*0x09C*/   DWORD   Subcategory;      //Subcat to Category. Unknown145 from lucy
/*0x0a0*/   DWORD   Subcategory2;
/*0x0a4*/   DWORD   HateMod;          //Additional hate
/*0x0a8*/   DWORD   ResistPerLevel;//correct see 566449 oct 07 test 2019 -eqmule
/*0x0ac*/   DWORD   ResistCap;// 5665AA oct 07 test 2019 -eqmule

//need to look closer at these:
/*0x0b0*/   DWORD   EnduranceCost;      //? CA Endurance Cost
/*0x0b4*/   FLOAT   EnduranceValue;     //? lets just call it that for now see 51E139 in oct 07 test 2019 -eqmule

/*0x0B8*/   DWORD   ReuseTimerIndex;    //59F825 ID of combat timer, i think. oct 07 test 2019 -eqmule
/*0x0BC*/   DWORD   EndurUpkeep;		//4C32F0 oct 07 test 2019 -eqmule
/*0x0c0*/   DWORD   HateGenerated;      //Hate override
/*0x0c4*/   DWORD   HitCountType;
/*0x0c8*/   DWORD   HitCount;
/*0x0cc*/   DWORD   ConeStartAngle;
/*0x0d0*/   DWORD   ConeEndAngle;
/*0x0d4*/   DWORD   PvPResistBase;
/*0x0d8*/   DWORD   PvPCalc;
/*0x0dc*/   DWORD   PvPResistCap;
/*0x0e0*/   DWORD   PvPDuration;        //DurationType for PVP
/*0x0e4*/   DWORD   PvPDurationValue1;  //DurationValue1 for PVP

//*0x0e0*/   DWORD   GlobalGroup; this is gone now, this was only used to check for group type 46 before... uh, hp and mana regen effect spells i think
//see apr 10 test 2018 for reference: -eqmule
//.text:004DA714 GlobalGroup:
//.text:004DA714                 cmp     dword ptr [eax+0E0h], 46

/*0x0e8*/   DWORD   PCNPCOnlyFlag;      // no idea
/*0x0ec*/   DWORD   NPCMemCategory;
/*0x0F0*/   DWORD   SpellGroup;
/*0x0F4*/   DWORD   SpellSubGroup;		//unknown237 on Lucy it is checked at 0x76FE18 in jun 11 2014 and if 0 will ask if we want to replace our spell with a rk. x version
/*0x0F8*/   DWORD   SpellRank;			//Unknown209 on Lucy jun 11 2014 0x76FEE0 Original = 1 , Rk. II = 5 , Rk. III = 10 , I suppose if they add Rk. IV it will be 15 and so on -eqmule
/*0x0Fc*/   DWORD   SpellClass;         //Unknown222 from Lucy
/*0x100*/   DWORD   SpellSubClass;         //Unknown223 from Lucy
/*0x104*/   DWORD   SpellReqAssociationID;
/*0x108*/   DWORD   CasterRequirementID;
/*0x10c*/   DWORD   MaxResist;
/*0x110*/   DWORD   MinResist;
/*0x114*/   DWORD   MinSpreadTime;
/*0x118*/   DWORD   MaxSpreadTime;
/*0x11c*/   DWORD   SpreadRadius;
/*0x120*/   DWORD   BaseEffectsFocusCap; //song cap, maybe other things?
/*0x124*/   DWORD   CritChanceOverride;
/*0x128*/   DWORD   MaxTargets;     //how many targets a spell will affect
/*0x12c*/   DWORD   AIValidTargets;
/*0x130*/   DWORD   BaseEffectsFocusOffset;
/*0x134*/   FLOAT   BaseEffectsFocusSlope;
/*0x138*/   VECTOR2 DistanceModStart;
/*0x140*/   VECTOR2 DistanceModEnd;
/*0x148*/   FLOAT   MinRange;
/*0x14c*/   BYTE    NoNPCLOS; // NPC skips LOS checks
/*0x14d*/   BYTE    Feedbackable; // nothing uses this
/*0x14e*/   BYTE    Reflectable;
/*0x14f*/   BYTE    NoPartialSave;
/*0x150*/   BYTE    NoResist;
/*0x151*/   BYTE    UsesPersistentParticles;
/*0x152*/   BYTE    SmallTargetsOnly;
/*0x153*/   bool    DurationWindow;     //0=Long, 1=Short
/*0x154*/   BYTE    Uninterruptable;
/*0x155*/   BYTE    NotStackableDot;
/*0x156*/   BYTE    Deletable;
/*0x157*/   BYTE    BypassRegenCheck;
/*0x158*/   BYTE    CanCastInCombat;
/*0x159*/   BYTE    CanCastOutOfCombat;
/*0x15a*/   BYTE    NoHealDamageItemMod; //disable worn focus bonuses
/*0x15b*/   BYTE    OnlyDuringFastRegen;
/*0x15c*/   BYTE    CastNotStanding;
/*0x15d*/   BYTE    CanMGB;
/*0x15e*/   bool    NoDisspell;
/*0x15f*/   BYTE    AffectInanimate; //ldon trap spells etc
/*0x160*/   bool    IsSkill;
/*0x161*/   bool    bStacksWithDiscs;//this was first seen in may 8 2017 test client, its checked if it's false at 0x451790. Ex: The Monk ability 'Drunken Monkey Style' or 'Breather'. see patch notes for that patch... -eqmule
/*0x162*/   bool    ShowDoTMessage;
/*0x163*/   BYTE    ClassLevel[0x24];        //per class., yes there are allocations for 0x24 see 4B5776 in eqgame dated 12 mar 2014 -eqmule
/*0x187*/   BYTE    LightType;
/*0x188*/   BYTE    SpellType;          //0=detrimental, 1=Beneficial, 2=Beneficial, Group Only
/*0x189*/   BYTE    Resist;   //see   4B0493 in apr 16 2018 exe        //0=un 1=mr 2=fr 3=cr 4=pr 5=dr 6=chromatic 7=prismatic 8=physical(skills,etc) 9=corruption
/*0x18a*/   BYTE    TargetType;         //03=Group v1, 04=PB AE, 05=Single, 06=Self, 08=Targeted AE, 0e=Pet, 28=AE PC v2, 29=Group v2, 2a=Directional
/*0x18b*/   BYTE    CastDifficulty;
/*0x18c*/   BYTE    Skill;
/*0x18d*/   BYTE    ZoneType;           //01=Outdoors, 02=dungeons, ff=Any
/*0x18e*/   BYTE    Environment;
/*0x18f*/   BYTE    TimeOfDay;          // 0=any, 1=day only, 2=night only
/*0x190*/   BYTE    CastingAnim;
/*0x191*/   BYTE    AnimVariation;
/*0x192*/   BYTE    TargetAnim;
/*0x193*/   BYTE    TravelType;
/*0x194*/   BYTE    CancelOnSit;
/*0x195*/   bool    CountdownHeld;
/*0x196*/   CHAR    Name[0x40];//for sure see 557AAA
/*0x1d6*/   CHAR    Target[0x20];
/*0x1f6*/   CHAR    Extra[0x20];    //This is 'Extra' from Lucy (portal shortnames etc) official = NPC_FILENAME
/*0x216*/   BYTE    ShowWearOffMessage;
/*0x217*/   BYTE    NPCChanceofKnowingSpell;//if this is 0 there is no way an npc can cast this spell...
/*0x218*/   BYTE    SneakAttack;
/*0x219*/   BYTE    NotFocusable; //ignores all(?) focus effects
/*0x21a*/   BYTE    NoHate;
/*0x21b*/   BYTE    StacksWithSelf;
/*0x21c*/   BYTE    CannotBeScribed;//this is used by /outputfile missingspells see 7A57DF in Aug 10 2017 live
/*0x21d*/   BYTE    NoBuffBlock;
/*0x21e*/   int     Scribable;
/*0x222*/   BYTE    NoStripOnDeath;
/*0x223*/   BYTE    NoRemove; // spell can't be clicked off?
/*0x224*/   int     NoOverwrite; //an enum 0 = Can Be overwritten 1 = Can Only be overwritten by itself 2 = Cannot be overwritten, not even by itself
/*0x228*/   DWORD   SpellRecourseType;
/*0x22C*/   BYTE    CRC32Marker;
/*0x22D*/   FLOAT   DistanceMod; // set to (DistanceModEnd.Y- DistanceModEnd.X) / (DistanceModStart.Y - DistanceModStart.X).
/*0x231*/

} SPELL, *PSPELL;

struct FocusEffectData
{
	int Type;
	int Base;
	int Base2;
	int Slot;
};

class MercAbilityEffectsDef
{
public:
	void *vfTable;
	int	ID;
	int	AbilityID;
	int	FromID;
	int	Base;
	int	Base2;
	int	LevelMod;
	int	Cap;
	int	Slot;
};
struct CachedFocusAbility {
    FocusEffectData*pEffectData;
    int Percent;
};
class SpellCache
{
	//has no vftable
public:
	struct EffectCache {
		int SubIndex;
		int TotalPlayerEffects;
		int TotalItemEffects;
		bool bDegenerating;
		int TotalContrib;
	};
	struct AltEffectCache {
		int SubIndex;
		int AltTotal;
	};
    struct CachedFocusItem {
        PCONTENTS         pContents;
        int	Percent;
        ItemSpellTypes SpellType;
    };
    struct CachedFocusEffect {
        PSPELL     pSpell;
        int	Percent;
		short AffectIndex;
    };

    struct CachedFocusMercAbility {
        MercAbilityEffectsDef* pAbilityEffectDef;
        int Percent;
    };
/*0x00*/ HashTable<EffectCache> *pCachedEffects;
/*0x04*/ bool bCachedSpellEffects;
/*0x08*/ HashTable<AltEffectCache> *pCachedAltAbilityEffects;
/*0x0c*/ bool bCachedAltEffects;
/*0x10*/ HashTable<EffectCache> *pCachedLimitedEffects;
/*0x14*/ bool bCachedLimitedEffects;
/*0x18*/ HashTable<CachedFocusItem, __int64>		CachedFocusItems;
/*0x28*/ HashTable<CachedFocusEffect, __int64>		CachedFocusEffects;
/*0x38*/ HashTable<CachedFocusAbility, __int64>		CachedFocusAbilities;
/*0x48*/ HashTable<CachedFocusMercAbility, __int64>	CachedFocusMercAbilities;
/*0x58*/ 
};

struct ALCHEMYBONUSSKILLDATA
{
	int SkillID;
	int BonusPoints;
};

//aStartingLoad
#define CHARINFO_Size 0x2BA8 //in Apr 07 2020 (see 606918) - eqmule
//this thing here is an abomination, todo: fix it once and for all.
// its like a frankenstruct mixing in PcBase etc. 
typedef struct _CHARINFO {
/*0x0000*/ void*        vtable1;
/*0x0004*/ void*        punknown;
/*0x0008*/ struct _CI_INFO*     charinfo_info;
/*0x000c*/ void*        vftablealso;
/*0x0010*/ TSafeArrayStatic<int, 0xa>	RecentTasks;
/*0x0038*/ TSafeArrayStatic<PCTaskStatus, 1>	Tasks;
/*0x00A8*/ TSafeArrayStatic<PCTaskStatus, 0x1d>	Quests;
/*0x0D58*/ TSafeArrayStatic<BYTE, 0x320>	BitFlags;
/*0x1078*/ TSafeArrayStatic<BenefitSelection, 5> ActiveTributeBenefits;//size 0x28 8 * 5
/*0x10A0*/ TSafeArrayStatic<BenefitSelection, 0xa> ActiveTrophyTributeBenefits;
/*0x10f0*/ TSafeArrayStatic<BYTE, 0x320>	BitFlags2;
/*0x1410*/ int          pBankArraySize;
/*0x1414*/ int          pBankArraySpec;
/*0x1418*/ struct _BANKARRAY*   pBankArray;
/*0x141c*/ DWORD        NumBankSlots;//how many bank slots we have
/*0x1420*/ BYTE         Unknown0x1420[0x14];
/*0x1434*/ struct _SHAREDBANKARRAY*     pSharedBankArray;
/*0x1438*/ DWORD        NumSharedSlots;//how many sharedbank slots we have
/*0x143c*/ BYTE         Unknown0x143c[0x4c];
/*0x1488*/ struct _MERCEQUIPMENT*     pMercEquipment;
/*0x148c*/ DWORD        NumMercEquipSlots;//how many pMercEquipment slots we have
/*0x1490*/ BYTE         Unknown0x1490[0xc];
/*0x149c*/ DWORD        KeyRing1;//always 0x7d
/*0x14a0*/ DWORD        eMount;//always eItemContainerMountKeyRingItems (27)
/*0x14a4*/ struct _KEYRINGARRAY*        pMountsArray;
/*0x14a8*/ BYTE         Unknown0x14a8[0x10];
/*0x14b8*/ DWORD        KeyRing2;//always 0x7d
/*0x14bc*/ DWORD        eIllusion;//always eItemContainerIllusionKeyRingItems (29)
/*0x14c0*/ struct _KEYRINGARRAY*        pIllusionsArray;
/*0x14c4*/ BYTE         Unknown0x14c4[0x10];
/*0x14d4*/ DWORD        KeyRing3;//always 0x7d
/*0x14d8*/ DWORD        eFamiliar;//always eItemContainerViewModFamiliarKeyRingItems (31)
/*0x14dc*/ struct _KEYRINGARRAY*        pFamiliarArray;
/*0x14e0*/ BYTE         Unknown0x14e0[0x10];
/*0x14f0*/ DWORD        KeyRing4;
/*0x14f4*/ DWORD        eHeroForge;//always eItemContainerViewModHeroForgeKeyRingItems (35?)
/*0x14f8*/ struct _KEYRINGARRAY*        pHeroForgeArray;
/*0x14fc*/ BYTE         Unknown0x14fc[0xe4];//PCBase
/*0x15e0*/ __int64      GuildID;//GuildID_0
/*0x15e8*/ __int64		FellowshipID;
/*0x15f0*/ PFELLOWSHIPINFO pFellowship;
/*0x15f4*/ bool			GuildShowSprite;
/*0x15f8*/ UINT			CreationTime;
/*0x15fc*/ UINT			AccountCreationTime;
/*0x1600*/ UINT			LastPlayedTime;
/*0x1604*/ DWORD		MinutesPlayed;
/*0x1608*/ BYTE			Anonymous;
/*0x1609*/ bool			bGM;
/*0x160a*/ bool			bGMStealth;
/*0x160c*/ DWORD        AAExp;//Post60Exp
/*0x1610*/ BYTE         NobilityRank;
/*0x1611*/ BYTE         PercentEXPtoAA;
/*0x1614*/ int			AirSupply;
/*0x1618*/ int			SerialNum;
/*0x161c*/ bool			bNewCharacter;
/*0x1620*/ int			TasksAssigned;
/*0x1624*/ int			TasksCompleted;
/*0x1628*/ long			TaskRequestTimer;
/*0x162c*/ unsigned int UniquePlayerID;
/*0x1630*/ WorldLocation	DynamicZoneSafeReturnLocation;//size 0x14
/*0x1644*/ DynamicZoneTimerData* pDZTimerRoot;
/*0x1648*/ DWORD        TributeTimer;
/*0x164c*/ DWORD        BenefitTimer;
/*0x1650*/ __int64      CareerFavor;
/*0x1658*/ __int64      CurrFavor;
/*0x1660*/ BYTE         Unknown0x1660[0x104];
/*0x1764*/ DWORD        RadiantCrystals;
/*0x1768*/ int          GoodTotalPointsEarned;
/*0x176C*/ DWORD        EbonCrystals;
/*0x1770*/ BYTE         Unknown0x1770[0x710];
/*0x1E80*/ __int64      Exp;//confirmed jun 12 2017 test
/*0x1e88*/ int	        DaysEntitled;
/*0x1e8C*/ bool	        bAutoConsentGroup;
/*0x1e8D*/ bool	        bAutoConsentRaid;
/*0x1e8E*/ bool	        bAutoConsentGuild;
/*0x1e8F*/ bool	        bPrivateForEqPlayers;
/*0x1e90*/ long	        AchievementFilesModificationTime;
/*0x1e94*/ CHAR	        StationID[0x20];
/*0x1eb8*/ EqGuid       Guid;//size 8 so it MUST start at a int64 sized address.. i.e. 0 or 8
/*0x1ec0*/ bool	        bBetaBuffed;
/*0x1ec4*/ int	        Unknown0x1ebc;
/*0x1ec8*/ int	        StartingCity;
/*0x1ecc*/ int	        MainLevel;
/*0x1ed0*/ bool	        bShowHelm;
/*0x1ed8*/ __int64      LastTestCopyTime;
/*0x1ee0*/ CPlayerPointManager PointManager;//size 0x14
/*0x1ee4*/ PointSystemBase PointSystem;//size 0x14
/*0x1f08*/ UINT			LoyaltyVelocity;
/*0x1f0c*/ UINT			LoyaltyTokens;
/*0x1f10*/ bool			bHasLoyaltyInfo;
/*0x1f14*/ ArrayClass_RO<int> OwnedRealEstates;
/*0x1f24*/ ArrayClass_RO<int> OwnedItemRealEstates;
/*0x1f34*/ ArrayClass_RO<int> ArchivedRealEstates;
/*0x1f44*/ CHAR			OverridePetName[0x40];
/*0x1f84*/ bool			bCanRequestPetNameChange;
/*0x1f85*/ CHAR			OverrideFamiliarName[0x40];
/*0x1fc5*/ bool			bCanRequestFamiliarNameChange;
/*0x1fc8*/ _CXSTR		*OverrideMercName[0xb];
/*0x1Ff4*/ bool			bCanRequestMercNameChange;
/*0x1Ff8*/ PendingRewardList PendingRewards;//size 0x2c
/*0x2024*/ UINT         DowntimeReductionTime;
/*0x2028*/ UINT         DowntimeTimerStart;
/*0x202c*/ FLOAT        ActivityValue;
/*0x2030*/ UINT         NextItemId;
/*0x2034*/ _CXSTR*		SharedBank;
/*0x2038*/ _CXSTR*		BankBuffer;
/*0x203c*/ _CXSTR*		LimboBuffer;
/*0x2040*/ _CXSTR*		MercenaryBuffer;
/*0x2044*/ _CXSTR*		KeyRingBuffer[4];
/*0x2054*/ _CXSTR*		AltStorageBuffer;
/*0x2058*/ _CXSTR*      ItemOverflow;
/*0x205c*/ UINT         AltStorageTimestamp;
/*0x2060*/ ELockoutCharacterReason LCR;
/*0x2064*/ HashTable<ProgressionExperience> ProgressionExp;//size 0x10
/*0x2074*/ PCXSTR       ArchivedStorageBuffer;
/*0x2078*/ PCXSTR       MailItemsBuffer;
/*0x207c*/ PCXSTR       MailItemsDataBuffer;
/*0x2080*/ int          MailItemsOverCapWarningCount;
/*0x2084*/ ItemIndex	StatKeyRingItemIndex[4];//size 0x18
/*0x209c*/ BYTE         UseAdvancedLooting;     //0x1ff2 confirmed jun 12 2017 test               //0=off 1=on
/*0x209d*/ BYTE         MasterLootCandidate;                     //0=off 1=on
/*0x209e*/ BYTE         Unknown0x209e[0x2b6];
/*0x2354*/ DWORD        Krono;//confirmed jun 12 2017 test
/*0x2358*/ DWORD        CursorKrono;
/*0x235c*/ BYTE         Unknown0x235c[0x4];
/*0x2360*/ __int64      MercAAExp;// divide this with 3.30f and you get the percent - eqmule
/*0x2368*/ DWORD        MercAAPoints;//number of unspent merc AA points
/*0x236c*/ DWORD        MercAAPointsSpent;//number of spent merc AA points
/*0x2370*/ BYTE		    Unknown0x2370[0x48];
/*0x23b8*/ __int64      Vitality;
/*0x23c0*/ int		    AAVitality;
/*0x23c4*/ int		    Unknown0x23bc;
/*0x23c8*/ int          FPStuff[0x1e];
/*0x2440*/
/********************* PcBase End **********************/
/************ CharacterZoneClient Begin ****************/
/*0x2440*/ void*        vtable2;//vtable2_0 below aTimeIsDAndCanU (its really PcClient_CharacterZoneClient_vfTable
/*0x2444*/ struct _EQC_INFO*    eqc_info;
/*0x2448*/ struct _SPAWNINFO*   pSpawn;//pSpawn_0
/*0x244C*/ bool         bUpdateStuff;
/*0x244d*/ bool         bZoningStatProcessing;
/*0x2450*/ DWORD        ArmorClassBonus;//vtable2+10
/*0x2454*/ DWORD        CurrWeight;//vtable2+14
/*0x2458*/ int			astHitPointSendPercent;
/*0x245c*/ int			LastManaPointSendPercent;
/*0x2460*/ int			LastEndurancePointSendPercent;
/*0x2464*/ DWORD        HPBonus;//vtable2+24
/*0x2468*/ DWORD        ManaBonus;//vtable2+28
/*0x246c*/ DWORD        EnduranceBonus;//vtable2+2c
/*0x2470*/ int          EnduranceCostPerSecond;
/*0x2474*/ DWORD        CombatEffectsBonus;//vtable2+34 Combat Effects in UI
/*0x2478*/ DWORD        ShieldingBonus;//vtable2+38 Melee Shielding in UI
/*0x247c*/ DWORD        SpellShieldBonus;//vtable2+3c Spell Shielding in UI
/*0x2480*/ DWORD        AvoidanceBonus;//vtable2+40 Avoidance in UI
/*0x2484*/ DWORD        AccuracyBonus;//vtable2+44 Accuracy in UI
/*0x2488*/ DWORD        StunResistBonus;//vtable2+48 Stun Resist in UI
/*0x248c*/ DWORD        StrikeThroughBonus;//vtable2+4c Strike Through in UI
/*0x2490*/ DWORD        DoTShieldBonus;//vtable2+50 Dot Shielding in UI
/*0x2494*/ DWORD        DamageShieldMitigationBonus;//vtable2+54 Damage Shield Mitig in UI
/*0x2498*/ DWORD        DamageShieldBonus;//vtable2+58 Damage Shielding in UI
/*0x249c*/ TSafeArrayStatic<int, 9> ItemSkillMinDamageMod;//size 0x24
/*0x24c0*/ TSafeArrayStatic<int, 9> SkillMinDamageModBonus;//size 0x24
/*0x24e4*/ DWORD        HeroicSTRBonus;//vtable2+a4
/*0x24e8*/ DWORD        HeroicINTBonus;//vtable2+a8
/*0x24ec*/ DWORD        HeroicWISBonus;//vtable2+ac
/*0x24f0*/ DWORD        HeroicAGIBonus;//vtable2+b0
/*0x24f4*/ DWORD        HeroicDEXBonus;//vtable2+b4
/*0x24f8*/ DWORD        HeroicSTABonus;//vtable2+b8
/*0x24fc*/ DWORD        HeroicCHABonus;//vtable2+bc
/*0x2500*/ DWORD        HealAmountBonus;//vtable2+d8
/*0x2504*/ DWORD        SpellDamageBonus;//vtable2+dc
/*0x2508*/ int			ItemHealAmountDotMod;
/*0x250c*/ int			ItemSpellDamageDotMod;
/*0x2510*/ DWORD        ClairvoyanceBonus;//vtable2+e8
/*0x2514*/ DWORD        AttackBonus;//vtable2+ec
/*0x2518*/ DWORD        HPRegenBonus;//vtable2+f0
/*0x251c*/ DWORD        ManaRegenBonus;//vtable2+f4
/*0x2520*/ DWORD        EnduranceRegenBonus;//vtable2+f8
/*0x2524*/ DWORD        AttackSpeed;//vtable2+fc
/*0x2528*/ int			NoBuffItemHitpointAdjustment;
/*0x252c*/ int			NoBuffItemManaAdjustment;
/*0x2530*/ int			NoBuffItemEnduranceAdjustment;
/*0x2534*/ int			NoBuffItemBaseChanceProc;
/*0x2538*/ int			NoBuffItemMinDamageMod;
/*0x253c*/ int			NoBuffItemInnateSpellRune;
/*0x2540*/ int			NoBuffItemAvoidance;
/*0x2544*/ int			NoBuffItemToHit;
/*0x2548*/ int			NoBuffItemResistStunChance;
/*0x254c*/ int			NoBuffItemDotShieldingEffect;
/*0x2550*/ int			NoBuffItemStrikeThroughChance;
/*0x2554*/ int			NoBuffItemAttack;
/*0x2558*/ int			NoBuffItemHitPointRegen;
/*0x255c*/ int			NoBuffItemManaRegen;
/*0x2560*/ int			NoBuffItemEnduranceRegen;
/*0x2564*/ int			NoBuffItemDamageShield;
/*0x2568*/ int			NoBuffItemDamageShieldMitigation;
/*0x256c*/ int			NoBuffItemHaste;
/*0x2570*/ TSafeArrayStatic<int, 9>   NoBuffItemSkillMinDamageMod;//size 0x24
/*0x2594*/ bool			bOutputHpRegen;
/*0x2595*/ bool			bInvulnerable;
/*0x2596*/ bool			bOnAVehicle;//0x2420 + 0x156 see 4D94E8 in jun 11 2018 test
/*0x2598*/ EQData::SpellCache spellCache;//size 0x58
/*0x25f0*/ HashListSet<int, 0x80> DoomEffectsBySlot;//size 0x10 + (0x80 * 4)
/*0x2800*/ UINT			LastHitEval;
/*0x2804*/
/*********************** CharacterZoneClient End ***********************/
/******************* PcZoneClient Begine ******************/
/*0x2804*/ void *PcZoneClient_vfTable; //see 61A04C jun 11 test 2018
/*0x2808*/ TSafeArrayStatic<unsigned long, 3> Flags;//size 0xc
/*0x2814*/ unsigned __int32 TransfersReceived;
/*0x2818*/ int	LastLanguageSpoken;
/*0x281c*/ int CurPowerSourceDrain;
/*0x2820*/ EQList<ALCHEMYBONUSSKILLDATA*> AlchemyBaseSkillBonusList;
/*0x2830*/ UINT MomentumBalance; 
/*0x2834*/ UINT LoyaltyRewardBalance;
/*0x2838*/
/******************* PcZoneClient End ******************/
/******************* PCClient Begin ************************/
 /*0x2838*/ ExtendedTargetList*  pXTargetMgr;
 /*0x283c*/ DWORD        InCombat;
 /*0x2840*/ DWORD        Downtime;
 /*0x2844*/ DWORD        DowntimeStamp;
 /*0x2848*/ bool         bOverrideAvatarProximity;
 /*0x284c*/ struct _GROUPINFO*   pGroupInfo;
/*0x2850*/ bool         bIAmCreatingGroup;
/*0x2854*/ VeArray<VePointer<PCONTENTS>> ItemsPendingID;//size 0xc
/*0x2860*/ int          ParcelStatus;//eParcelStatus
/*0x2864*/ int          SubscriptionDays;//24BC for sure see 7A6C40 in may 11 2018 live exe
/*0x2868*/ short        BaseKeyRingSlots[4];
/*0x2870*/ bool         bPickZoneFewest;//for sure see 4A424A in may 11 2018 live exe
/*0x2874*/ int          Unknown0x2874;
/*0x2878*/ int          Unknown0x2878;
/*0x287c*/
/******************* PCClient End ************************/
/*0x287c*/ void*        CharacterBase_vftable;
/*0x2880*/ CProfileManager ProfileManager; //size 8
 /*0x288*/ BYTE         languages[0x20];//CharBaseBegin+14
/*0x28a8*/ FLOAT		X;
/*0x28ac*/ FLOAT		Y;
/*0x28b0*/ FLOAT		Z;
/*0x28b4*/ FLOAT		Heading;
 /*0x28b8*/ CHAR         Name[0x40];//CharBaseBegin+44
/*0x28f8*/ CHAR         Lastname[0x20];//CharBaseBegin+84
/*0x2918*/ TSafeString<0x80>	Title;
/*0x2998*/ TSafeString<0x40>	VehicleName;
/*0x29d8*/ BYTE         Stunned;//CharBaseBegin+104
/*0x29d9*/ BYTE         Unknown0x29d9[0x3];
/*0x29dc*/ WORD         zoneId;//CharBaseBegin+108 Zone_0
/*0x29de*/ WORD         instance;
/*0x29e0*/ BYTE         standstate;//CharBaseBegin+10c
/*0x29e4*/ RaidData     raidData;//size 0xdc
/*0x2ac0*/ DWORD        ExpansionFlags;//CharBaseBegin+464
/*0x2ac4*/ bool			bSuperPKILL;
/*0x2ac5*/ bool			bUnclone;
/*0x2ac6*/ bool			bDead;
/*0x2ac8*/ int			LD_Timer;
/*0x2acc*/ int			SpellInterruptCount;
/*0x2ad0*/ bool			bAutoSplit;
/*0x2ad1*/ bool			bTellsOff;
/*0x2ad2*/ bool			bGmInvis;
/*0x2ad4*/ int			KillMe;
/*0x2ad8*/ bool			CheaterLdFlag;//likely this is int SoulMarkCount instead.
/*0x2ad9*/ bool			NoRent;
/*0x2ada*/ bool			Corpse;
/*0x2adb*/ bool			ClientGmFlagSet;
/*0x2adc*/ DWORD        BankSharedPlat;//31e4 CharBaseBegin+488
/*0x2ae0*/ DWORD        BankSharedGold;//CharBaseBegin+48c
/*0x2ae4*/ DWORD        BankSharedSilver;//CharBaseBegin+490
/*0x2ae8*/ DWORD        BankSharedCopper;//CharBaseBegin+494
/*0x2aec*/ DWORD        BankPlat;//CharBaseBegin+498
/*0x2af0*/ DWORD        BankGold;//CharBaseBegin+49c
/*0x2af4*/ DWORD        BankSilver;//CharBaseBegin+4a0
/*0x2af8*/ DWORD        BankCopper;//CharBaseBegin+4a4
/*0x2afc*/ DWORD        STR;//CharBaseBegin+4a8
/*0x2b00*/ DWORD        STA;//CharBaseBegin+4ac
/*0x2b04*/ DWORD        CHA;//CharBaseBegin+4b0
/*0x2b08*/ DWORD        DEX;//CharBaseBegin+4b4
/*0x2b0c*/ DWORD        INT;//CharBaseBegin+4b8
/*0x2b10*/ DWORD        AGI;//CharBaseBegin+4bc
/*0x2b14*/ DWORD        WIS;//CharBaseBegin+4c0
/*0x2b18*/ DWORD        LCK;//CharBaseBegin+4c4
/*0x2b1c*/ DWORD        SavePoison;//CharBaseBegin+4c8
/*0x2b20*/ DWORD        SaveMagic;//CharBaseBegin+4cc
/*0x2b24*/ DWORD        SaveDisease;//CharBaseBegin+4d0
/*0x2b28*/ DWORD        SaveCorruption;//CharBaseBegin+4d4
/*0x2b2c*/ DWORD        SaveFire;//CharBaseBegin+4d8
/*0x2b30*/ DWORD        SaveCold;//CharBaseBegin+4dc
/*0x2b34*/ DWORD        SavePhysical;//CharBaseBegin+4e0
/*0x2b38*/ int			UncappedStr;
/*0x2b3c*/ int  		UncappedSta;
/*0x2b40*/ int			UncappedCha;
/*0x2b44*/ int			UncappedDex;
/*0x2b48*/ int			UncappedInt;
/*0x2b4c*/ int			UncappedAgi;
/*0x2b50*/ int			UncappedWis;
/*0x2b54*/ int			UncappedResistPoison;
/*0x2b58*/ int			UncappedResistMagic;
/*0x2b5c*/ int			UncappedResistDisease;
/*0x2b60*/ int			UncappedResistCorruption;
/*0x2b64*/ int			UncappedResistFire;
/*0x2b68*/ int			UncappedResistCold;
/*0x2b6c*/ int          UncappedResistPhysical;
/*0x2b70*/ int			NoBuffStr;
/*0x2b74*/ int			NoBuffSta;
/*0x2b78*/ int			NoBuffCha;
/*0x2b7c*/ int			NoBuffDex;
/*0x2b80*/ int			NoBuffInt;
/*0x2b84*/ int			NoBuffAgi;
/*0x2b88*/ int			NoBuffWis;
/*0x2b8c*/ int			NoBuffResistPoison;
/*0x2b90*/ int			NoBuffResistMagic;
/*0x2b94*/ int			NoBuffResistDisease;
/*0x2b98*/ int			NoBuffResistCorruption;
/*0x2b9c*/ int			NoBuffResistFire;
/*0x2ba0*/ int			NoBuffResistCold;
/*0x2ba4*/ int			NoBuffResistPhysical;
/*0x2ba8*/
#ifdef NEWCHARINFO
} CHARINFOOLD, *PCHARINFOOLD;
#else
} CHARINFO, *PCHARINFO;
#endif

typedef struct _CHARINFONEW {
/*********************** PcBase Begin ************************/
/*0x0000*/ void*        PcClient_PcBase_vfTable;//see 5B8B39 Jun 19 2017
/*0x0004*/ void*        punknown;
/*0x0008*/ struct _CI_INFO*     charinfo_info;
/*0x000c*/ void*        vftablealso;
/*0x0010*/ TSafeArrayStatic<int, 0xa>	RecentTasks;
/*0x0038*/ TSafeArrayStatic<PCTaskStatus, 1>	Tasks;
/*0x00A8*/ TSafeArrayStatic<PCTaskStatus, 0x1d>	Quests;
/*0x0D58*/ TSafeArrayStatic<BYTE, 0x320>	BitFlags;
/*0x1078*/ TSafeArrayStatic<BenefitSelection, 5> ActiveTributeBenefits;//size 0x28 8 * 5
/*0x10A0*/ TSafeArrayStatic<BenefitSelection, 0xa> ActiveTrophyTributeBenefits;
/*0x10f0*/ TSafeArrayStatic<BYTE, 0x320>	BitFlags2;
/*0x1410*/ ItemBaseContainer	BankItems;//size 0x1c pBankArray
/*0x142c*/ ItemBaseContainer	SharedBankItems;
/*0x1448*/ ItemBaseContainer	OverflowBufferItems;
/*0x1464*/ ItemBaseContainer	LimboBufferItems;
/*0x1480*/ ItemBaseContainer	MercenaryItems;
/*0x149c*/ ItemBaseContainer	MountKeyRingItems;
/*0x14b8*/ ItemBaseContainer	IllusionKeyRingItems;
/*0x14d4*/ ItemBaseContainer	FamiliarKeyRingItems;
/*0x14f0*/ ItemBaseContainer	HeroForgeKeyRingItems;
/*0x150c*/ ItemBaseContainer	AltStorageItems;
/*0x1528*/ ItemBaseContainer	ArchivedDeletedItems;
/*0x1544*/ ItemBaseContainer	MailItems;
/*0x1560*/ HashTable<MailItemData, EqItemGuid, ResizePolicyNoShrink> MailItemsData;//size 0x10
/*0x1570*/ TSafeArrayStatic<UINT, 1>	RecentMoves;
/*0x1574*/ HashTable<DynamicZoneData>	CurrentDynamicZones;
/*0x1584*/ HashTable<int>	LearnedRecipes;	
/*0x1594*/ EQList<TradeskillRecipeCount*>	QualifyingRecipeCounts;
/*0x15a4*/ HashTable<int>	NonrepeatableQuests;
/*0x15b4*/ HashTable<int>	CompletedTasks;
/*0x15c4*/ HashTable<int>	CompletedQuests;
/*0x15d4*/ UINT	        AlchemyTimestamp;
/*0x15d8*/ bool	        bGoHomeOverride;
/*0x15d9*/ bool	        bSomethingHome;
/*0x15dc*/ DWORD	    LoginTime;//next must start on 8 align
/*0x15e0*/ EqGuid      GuildID;//GuildID_0
/*0x15E8*/ EqGuid		FellowshipID;
/*0x15F0*/ PFELLOWSHIPINFO  pFellowship;
/*0x15F4*/ bool			GuildShowSprite;
/*0x15F8*/ UINT			CharCreationTime;
/*0x15FC*/ UINT			AccountCreationTime;
/*0x1600*/ UINT			LastPlayedTime;
/*0x1604*/ DWORD		MinutesPlayed;
/*0x1608*/ BYTE			Anonymous;
/*0x1609*/ bool			bGM;
/*0x160A*/ bool			bGMStealth;
/*0x160C*/ DWORD        AAExp;//Post60Exp
/*0x1610*/ BYTE         NobilityRank;
/*0x1611*/ BYTE         PercentEXPtoAA;//do_alt_exp
/*0x1614*/ int			AirSupply;
/*0x1618*/ int			SerialNum;
/*0x161C*/ bool			bNewCharacter;
/*0x1620*/ int			TasksAssigned;
/*0x1624*/ int			TasksCompleted;
/*0x1628*/ long			TaskRequestTimer;
/*0x162C*/ unsigned int UniquePlayerID;
/*0x1630*/ WorldLocation	DynamicZoneSafeReturnLocation;//size 0x14
/*0x1644*/ DynamicZoneTimerData* pDZTimerRoot;
/*0x1648*/ DWORD        TributeTimer;
/*0x164C*/ DWORD        BenefitTimer;
/*0x1650*/ __int64      CareerFavor;
/*0x1658*/ __int64      CurrFavor;
/*0x1660*/ bool			bBenefitsActive;
/*0x1661*/ bool			bTrophyBenefitsActive;
/*0x1662*/ bool			bHasResetStartingCity;
/*0x1663*/ bool			bIsHeadStartCharacter;
/*0x1664*/ int			PvPKills;
/*0x1668*/ int			PvPDeaths;
/*0x166C*/ int			PvPCurrentPoints;
/*0x1670*/ int			PvPTotalPointsEarned;
/*0x1674*/ int			PvPKillStreak;
/*0x1678*/ int			PvPDeathStreak;
/*0x167C*/ int			PvPCurrentStreak;
/*0x1680*/ PvPKill		LastKill;//size 0x60
/*0x16E0*/ PvPDeath		LastDeath;//size 0x58
/*0x1738*/ HashTable<PvPKill24HourData>	PvPLast24HoursKillHash;
/*0x1748*/ int			PvPInfamyLevel;//for sure see 5B6274 in apr 07 2020 test exe -eqmule
/*0x174C*/ int			PvPVitality;
/*0x1750*/ UINT			PvPLastInfamyTime;
/*0x1754*/ int			LastLastNameChange;
/*0x1758*/ int			LastNameChangePriv;
/*0x175c*/ UINT			PvPLastVitalityTime;
/*0x1760*/ bool			bKeepItemsOnDeath;
/*0x1761*/ bool			bResetSpecializationSkills;
/*0x1764*/ DWORD        RadiantCrystals;//GoodPointsAvailable
/*0x1768*/ int			GoodTotalPointsEarned;
/*0x176c*/ DWORD        EbonCrystals;//EvilPointsAvailable
/*0x1770*/ int			EvilTotalPointsEarned;
/*0x1774*/ bool			bCanRequestNameChange;
/*0x1775*/ bool			bCanRequestNameChange2;
/*0x1776*/ bool			bCanRequestServerTransfer;
/*0x1777*/ bool			bIsCopied;
/*0x1778*/ int			ServerTransferGrantTime;
/*0x177c*/ bool			bCanRequestRaceChange;
/*0x1780*/ UINT			LastAAResetTime;
/*0x1784*/ UINT			LastMercAAResetTime;
/*0x1788*/ DWORD	    NewZoneID;//EQZoneIndex
/*0x178c*/ int			NewAreaID;
/*0x1790*/ int          eNewAreaCorner;//EAreaCorner
/*0x1794*/ DWORD	    PreviousZoneID;//EQZoneIndex
/*0x1798*/ int			RealEstateZoneID;
/*0x179c*/ CHAR			ServerCreated[0x20];
/*0x17Bc*/ PCAdventureData	    AdventureData;//size 0x0d8
/*0x1894*/ PCSharedTaskData	    SharedTaskData;//size 0x8c
/*0x1920*/ TaskTimerData*	    pTaskTimerData;
/*0x1924*/ PCQuestHistoryData	QuestHistoryData;//size 0x258
/*0x1B7c*/ PCStatistics		    PcStatistics;//size 0x104 i think
/*0x1C80*/ GroupMemberStats		GroupStats;//size 0x150 i think
/*0x1Dd0*/ BYTE         Unknown0x1Db0[0x9c];
/*0x1E6c*/ bool			bIsLfg;
/*0x1E70*/ EqGuid		RaidId;//could be int
/*0x1E78*/ EqGuid		GroupID;
/*0x1E80*/ __int64      Exp;
/*0x1E88*/ int	        DaysEntitled;
/*0x1e8c*/ bool	        bAutoConsentGroup;
/*0x1e8d*/ bool	        bAutoConsentRaid;
/*0x1e8e*/ bool	        bAutoConsentGuild;
/*0x1e8f*/ bool	        bPrivateForEqPlayers;
/*0x1e90*/ long	        AchievementFilesModificationTime;
/*0x1e94*/ CHAR	        StationID[0x20];
/*0x1eb8*/ EqGuid       Guid;//size 8 so it MUST start at a int64 sized address.. i.e. 0 or 8
/*0x1ec0*/ bool	        bBetaBuffed;
/*0x1ec4*/ int	        Unknown0x1ec4;
/*0x1EC8*/ int	        StartingCity;
/*0x1ECC*/ int	        MainLevel;
/*0x1ED0*/ bool	        bShowHelm;
/*0x1ED8*/ __int64      LastTestCopyTime;
/*0x1EE0*/ CPlayerPointManager  PointManager;//size 0x14
/*0x1EF4*/ PointSystemBase      PointSystem;//size 0x14
/*0x1F08*/ UINT			LoyaltyVelocity;
/*0x1F0C*/ UINT			LoyaltyTokens;
/*0x1F10*/ bool			bHasLoyaltyInfo;
/*0x1F14*/ ArrayClass_RO<int>   OwnedRealEstates;
/*0x1F24*/ ArrayClass_RO<int>   OwnedItemRealEstates;
/*0x1F34*/ ArrayClass_RO<int>   ArchivedRealEstates;
/*0x1F44*/ CHAR			OverridePetName[0x40];
/*0x1F84*/ bool			bCanRequestPetNameChange;
/*0x1F85*/ CHAR			OverrideFamiliarName[0x40];
/*0x1FC5*/ bool			bCanRequestFamiliarNameChange;
/*0x1FC8*/ _CXSTR*		OverrideMercName[0xb];//size 0x2c
/*0x1FF4*/ bool			bCanRequestMercNameChange;
/*0x1FF8*/ PendingRewardList    PendingRewards;//size 0x2c
/*0x2024*/ UINT         DowntimeReductionTime;
/*0x2028*/ UINT         DowntimeTimerStart;
/*0x202C*/ FLOAT        ActivityValue;
/*0x2030*/ UINT         NextItemId;
/*0x2034*/ _CXSTR*      pSharedBank;
/*0x2038*/ _CXSTR*      pBankBuffer;
/*0x203C*/ _CXSTR*      pLimboBuffer;
/*0x2040*/ _CXSTR*      pMercenaryBuffer;
/*0x2044*/ _CXSTR*      pKeyRingBuffer[4];//size 0x10
/*0x2054*/ _CXSTR*      pAltStorageBuffer;
/*0x2058*/ _CXSTR*      ItemOverflow;
/*0x205C*/ UINT         AltStorageTimestamp;
/*0x2060*/ ELockoutCharacterReason LCR;
/*0x2064*/ HashTable<ProgressionExperience> ProgressionExp;//size 0x10
/*0x2074*/ PCXSTR       ArchivedStorageBuffer;
/*0x2078*/ PCXSTR       MailItemsBuffer;
/*0x207C*/ PCXSTR       MailItemsDataBuffer;
/*0x2080*/ int          MailItemsOverCapWarningCount;
/*0x2084*/ ItemIndex	StatKeyRingItemIndex[4];//size 0x18
/*0x209C*/ BYTE         UseAdvancedLooting;     //0x1ff2 confirmed jun 12 2017 test
/*0x209D*/ BYTE         MasterLootCandidate;                     //0=off 1=on
/*0x209E*/ bool			bIsCorrupted;
/*0x20A0*/ char*		pCorruptionReport;
/*0x20A4*/ TString<0x100>   InspectText;
/*0x21A4*/ HashTable<int>   BlockedSpellsHash;
/*0x21B4*/ int			BlockedSpell[0x28];
/*0x2254*/ HashTable<int>   BlockedPetSpellsHash;
/*0x2264*/ int			BlockedPetSpell[0x28];
/*0x2304*/ ClaimDataCollection  ConsumableFeatures;//size 0x10
/*0x2314*/ bool		    bGrantItemsRegistered;
/*0x2318*/ unsigned __int64	CreatedGuildID;
/*0x2320*/ UINT		    GuildCreateTime;
/*0x2324*/ PCXSTR	    GuildCreateCharacter;
/*0x2328*/ bool	        bInventoryUnserialized;
/*0x2329*/ bool	        bAltStorageUnserialized;
/*0x232A*/ bool	        bArchivedStorageUnserialized;
/*0x232B*/ bool	        bMailUnserialized;
/*0x232C*/ bool	        bPendingInventorySerialization;	
/*0x2330*/ PCXSTR	    BuyLines;
/*0x2334*/ ArrayClass_RO<PCXSTR>	OfflineTraderSoldItems;//size 0x10
/*0x2344*/ ArrayClass_RO<PCXSTR>	OfflineBuyerBoughtItems;//szie 0x10
/*0x2354*/ DWORD        Krono;//confirmed jun 12 2017 test
/*0x2358*/ DWORD        CursorKrono;
/*0x2360*/ __int64      MercAAExp;// divide this with 3.30f and you get the percent - eqmule
/*0x2368*/ DWORD        MercAAPoints;//number of unspent merc AA points
/*0x236C*/ DWORD        MercAAPointsSpent;//number of spent merc AA points
/*0x2370*/ ArrayClass_RO<MercenaryAbilityInfo*>	MercenaryAbilities;//size 0x10
/*0x2380*/ HashTable<CompletedAchievementData, int, ResizePolicyNoShrink> CompletedAchievements;//size 0x10
/*0x2390*/ HashTable<AchievementSubComponentCountData, int, ResizePolicyNoShrink> CompletedEventBasedSubComponents;//size 0x10
/*0x23A0*/ HashTable<AchievementSubComponentCountData, int, ResizePolicyNoShrink> OpenEventBasedSubComponents;//size 0x10
/*0x23B0*/ int		    LastFellowshipJoin;//next is 8 bit aligned
/*0x23B8*/ __int64      Vitality;
/*0x23C0*/ int		    AAVitality;
/*0x23C4*/ int		    Unknown0x23C4;
/*0x23C8*/ int          FPStuff[0x1e];
/*0x2440*/
/********************* PcBase End **********************/
/************ CharacterZoneClient Begin ****************/
/*0x2440*/ void*        PcClient_CharacterZoneClient_vfTable;//see 61FB6A Nov 02 2018 beta
/*0x2444*/ struct _EQC_INFO*    eqc_info;
/*0x2448*/ struct _SPAWNINFO*   pSpawn;//pSpawn_0
/*0x244C*/ bool         bUpdateStuff;
/*0x244D*/ bool         bZoningStatProcessing;
/*0x2450*/ DWORD        ArmorClassBonus;//vtable2+10
/*0x2454*/ DWORD        CurrWeight;//vtable2+14
/*0x2458*/ int			astHitPointSendPercent;
/*0x245C*/ int			LastManaPointSendPercent;
/*0x2460*/ int			LastEndurancePointSendPercent;
/*0x2464*/ DWORD        HPBonus;//vtable2+24
/*0x2468*/ DWORD        ManaBonus;//vtable2+28
/*0x246C*/ DWORD        EnduranceBonus;//vtable2+2c
/*0x2470*/ int          EnduranceCostPerSecond;
/*0x2474*/ DWORD        CombatEffectsBonus;//vtable2+34 Combat Effects in UI
/*0x2478*/ DWORD        ShieldingBonus;//vtable2+38 Melee Shielding in UI
/*0x247C*/ DWORD        SpellShieldBonus;//vtable2+3c Spell Shielding in UI
/*0x2480*/ DWORD        AvoidanceBonus;//vtable2+40 Avoidance in UI
/*0x2484*/ DWORD        AccuracyBonus;//vtable2+44 Accuracy in UI
/*0x2488*/ DWORD        StunResistBonus;//vtable2+48 Stun Resist in UI
/*0x248C*/ DWORD        StrikeThroughBonus;//vtable2+4c Strike Through in UI
/*0x2490*/ DWORD        DoTShieldBonus;//vtable2+50 Dot Shielding in UI
/*0x2494*/ DWORD        DamageShieldMitigationBonus;//vtable2+54 Damage Shield Mitig in UI
/*0x2498*/ DWORD        DamageShieldBonus;//vtable2+58 Damage Shielding in UI
/*0x249C*/ TSafeArrayStatic<int, 9> ItemSkillMinDamageMod;//size 0x24
/*0x24C0*/ TSafeArrayStatic<int, 9> SkillMinDamageModBonus;//size 0x24
/*0x24E4*/ DWORD        HeroicSTRBonus;//vtable2+a4
/*0x24E8*/ DWORD        HeroicINTBonus;//vtable2+a8
/*0x24EC*/ DWORD        HeroicWISBonus;//vtable2+ac
/*0x24F0*/ DWORD        HeroicAGIBonus;//vtable2+b0
/*0x24F4*/ DWORD        HeroicDEXBonus;//vtable2+b4
/*0x24F8*/ DWORD        HeroicSTABonus;//vtable2+b8
/*0x24FC*/ DWORD        HeroicCHABonus;//vtable2+bc
/*0x2500*/ DWORD        HealAmountBonus;//vtable2+d8
/*0x2504*/ DWORD        SpellDamageBonus;//vtable2+dc
/*0x2508*/ int			ItemHealAmountDotMod;
/*0x250C*/ int			ItemSpellDamageDotMod;
/*0x2510*/ DWORD        ClairvoyanceBonus;//vtable2+e8
/*0x2514*/ DWORD        AttackBonus;//vtable2+ec
/*0x2518*/ DWORD        HPRegenBonus;//vtable2+f0
/*0x251C*/ DWORD        ManaRegenBonus;//vtable2+f4
/*0x2520*/ DWORD        EnduranceRegenBonus;//vtable2+f8
/*0x2524*/ DWORD        AttackSpeed;//vtable2+fc
/*0x2528*/ int          NoBuffItemHitpointAdjustment;
/*0x252C*/ int          NoBuffItemManaAdjustment;
/*0x2530*/ int          NoBuffItemEnduranceAdjustment;
/*0x2534*/ int          NoBuffItemBaseChanceProc;
/*0x2538*/ int          NoBuffItemMinDamageMod;
/*0x253C*/ int          NoBuffItemInnateSpellRune;
/*0x2540*/ int          NoBuffItemAvoidance;
/*0x2544*/ int          NoBuffItemToHit;
/*0x2548*/ int          NoBuffItemResistStunChance;
/*0x254C*/ int          NoBuffItemDotShieldingEffect;
/*0x2550*/ int          NoBuffItemStrikeThroughChance;
/*0x2554*/ int          NoBuffItemAttack;
/*0x2558*/ int          NoBuffItemHitPointRegen;
/*0x255C*/ int          NoBuffItemManaRegen;
/*0x2560*/ int          NoBuffItemEnduranceRegen;
/*0x2564*/ int          NoBuffItemDamageShield;
/*0x2568*/ int          NoBuffItemDamageShieldMitigation;
/*0x256C*/ int          NoBuffItemHaste;
/*0x2570*/ TSafeArrayStatic<int, 9>   NoBuffItemSkillMinDamageMod;//size 0x24
/*0x2594*/ bool         bOutputHpRegen;
/*0x2595*/ bool         bInvulnerable;
/*0x2596*/ bool         bOnAVehicle;//0x2420 + 0x156 see 4D94E8 in jun 11 2018 test
/*0x2598*/ EQData::SpellCache     spellCache;//size 0x58
/*0x25F0*/ HashListSet<int, 0x80> DoomEffectsBySlot;//size 0x10 + (0x80 * 4)
/*0x2800*/ UINT         LastHitEval;
/*0x2804*/
/*********************** CharacterZoneClient End ***********************/
/******************* PcZoneClient Begin ******************/
/*0x2804*/ void*        PcZoneClient_vfTable; //see 61A04C jun 11 test 2018
/*0x2808*/ TSafeArrayStatic<unsigned long, 3> Flags;//size 0xc
/*0x2814*/ unsigned __int32 TransfersReceived;
/*0x2818*/ int          LastLanguageSpoken;
/*0x281C*/ int          CurPowerSourceDrain;
/*0x2820*/ EQList<ALCHEMYBONUSSKILLDATA*> AlchemyBaseSkillBonusList;
/*0x2830*/ UINT         MomentumBalance; 
/*0x2834*/ UINT         LoyaltyRewardBalance;
/*0x2838*/
/******************* PcZoneClient End ******************/
/******************* PCClient Begin ************************/
/*0x2838*/ ExtendedTargetList*  pXTargetMgr;
/*0x283C*/ DWORD        InCombat;
/*0x2840*/ DWORD        Downtime;
/*0x2844*/ DWORD        DowntimeStamp;
/*0x2848*/ bool         bOverrideAvatarProximity;
/*0x284C*/ struct _GROUPINFO*   pGroupInfo;
/*0x2850*/ bool         bIAmCreatingGroup;
/*0x2854*/ VeArray<VePointer<PCONTENTS>> ItemsPendingID;//size 0xc
/*0x2860*/ int          ParcelStatus;//eParcelStatus
/*0x2864*/ int          SubscriptionDays;//24BC for sure see 7A6C40 in may 11 2018 live exe
/*0x2868*/ short        BaseKeyRingSlots[4];
/*0x2870*/ bool         bPickZoneFewest;//for sure see 4A424A in may 11 2018 live exe
/*0x2874*/ int          Unknown0x2874;
/*0x2878*/ int          Unknown0x2878;
/*0x287C*/
/******************* PCClient End ************************/
/******************* CharacterBase Begin ************************/
/*0x287C*/ void*        CharacterBase_vftable;//61FB30 in Nov 02 2018 Beta
/*0x2880*/ CProfileManager ProfileManager;//size 0x8
/*0x2888*/ TSafeArrayStatic<BYTE, 0x20>	languages;
/*0x28A8*/ FLOAT		X;
/*0x28AC*/ FLOAT		Y;
/*0x28B0*/ FLOAT		Z;
/*0x28B4*/ FLOAT		Heading;
/*0x28B8*/ CHAR         Name[0x40];//CharBaseBegin+44
/*0x28F8*/ CHAR         Lastname[0x20];//CharBaseBegin+84
/*0x2918*/ TSafeString<0x80>	Title;
/*0x2998*/ TSafeString<0x40>	VehicleName;
/*0x29D8*/ BYTE         Stunned;//CharBaseBegin+104
/*0x29D9*/ BYTE         Unknown0x29D9[0x3];
/*0x29DC*/ WORD         zoneId;//CharBaseBegin+108 Zone_0
/*0x29DE*/ WORD         instance;
/*0x29E0*/ BYTE         standstate;//CharBaseBegin+10c
/*0x29E4*/ RaidData     raidData;//size 0xdc
/*0x2AC0*/ DWORD        ExpansionFlags;//CharBaseBegin+464
/*0x2AC4*/ bool			bSuperPKILL;
/*0x2AC5*/ bool			bUnclone;
/*0x2AC6*/ bool			bDead;
/*0x2AC8*/ int			LD_Timer;
/*0x2ACC*/ int			SpellInterruptCount;
/*0x2AD0*/ bool			bAutoSplit;
/*0x2AD1*/ bool			bTellsOff;
/*0x2AD2*/ bool			bGmInvis;
/*0x2AD4*/ int			KillMe;
/*0x2AD8*/ bool			CheaterLdFlag;//likely this is int SoulMarkCount instead.
/*0x2AD9*/ bool			NoRent;
/*0x2ADA*/ bool			Corpse;
/*0x2ADB*/ bool			ClientGmFlagSet;
/*0x2ADC*/ DWORD        BankSharedPlat;//31e4 CharBaseBegin+488
/*0x2AE0*/ DWORD        BankSharedGold;//CharBaseBegin+48c
/*0x2AE4*/ DWORD        BankSharedSilver;//CharBaseBegin+490
/*0x2AE8*/ DWORD        BankSharedCopper;//CharBaseBegin+494
/*0x2AEC*/ DWORD        BankPlat;//CharBaseBegin+498
/*0x2AF0*/ DWORD        BankGold;//CharBaseBegin+49c
/*0x2AF4*/ DWORD        BankSilver;//CharBaseBegin+4a0
/*0x2AF8*/ DWORD        BankCopper;//CharBaseBegin+4a4
/*0x2AFC*/ DWORD        STR;//CharBaseBegin+4a8
/*0x2B00*/ DWORD        STA;//CharBaseBegin+4ac
/*0x2B04*/ DWORD        CHA;//CharBaseBegin+4b0
/*0x2B08*/ DWORD        DEX;//CharBaseBegin+4b4
/*0x2B0C*/ DWORD        INT;//CharBaseBegin+4b8
/*0x2B10*/ DWORD        AGI;//CharBaseBegin+4bc
/*0x2B14*/ DWORD        WIS;//CharBaseBegin+4c0
/*0x2B18*/ DWORD        LCK;//CharBaseBegin+4c4
/*0x2B1C*/ DWORD        SavePoison;//CharBaseBegin+4c8
/*0x2B20*/ DWORD        SaveMagic;//CharBaseBegin+4cc
/*0x2B24*/ DWORD        SaveDisease;//CharBaseBegin+4d0
/*0x2B28*/ DWORD        SaveCorruption;//CharBaseBegin+4d4
/*0x2B2C*/ DWORD        SaveFire;//CharBaseBegin+4d8
/*0x2B30*/ DWORD        SaveCold;//CharBaseBegin+4dc
/*0x2B34*/ DWORD        SavePhysical;//CharBaseBegin+4e0
/*0x2B38*/ int			UncappedStr;
/*0x2B3C*/ int  		UncappedSta;
/*0x2B40*/ int			UncappedCha;
/*0x2B44*/ int			UncappedDex;
/*0x2B48*/ int			UncappedInt;
/*0x2B4C*/ int			UncappedAgi;
/*0x2B50*/ int			UncappedWis;
/*0x2B54*/ int			UncappedResistPoison;
/*0x2B58*/ int			UncappedResistMagic;
/*0x2B5C*/ int			UncappedResistDisease;
/*0x2B60*/ int			UncappedResistCorruption;
/*0x2B64*/ int			UncappedResistFire;
/*0x2B68*/ int			UncappedResistCold;
/*0x2B6C*/ int          UncappedResistPhysical;
/*0x2B70*/ int			NoBuffStr;
/*0x2B74*/ int			NoBuffSta;
/*0x2B78*/ int			NoBuffCha;
/*0x2B7C*/ int			NoBuffDex;
/*0x2B80*/ int			NoBuffInt;
/*0x2B84*/ int			NoBuffAgi;
/*0x2B88*/ int			NoBuffWis;
/*0x2B8C*/ int			NoBuffResistPoison;
/*0x2B90*/ int			NoBuffResistMagic;
/*0x2B94*/ int			NoBuffResistDisease;
/*0x2B98*/ int			NoBuffResistCorruption;
/*0x2B9C*/ int			NoBuffResistFire;
/*0x2BA0*/ int			NoBuffResistCold;
/*0x2BA4*/ int			NoBuffResistPhysical;
/*0x2BA8*/
#ifdef NEWCHARINFO
} CHARINFO, *PCHARINFO;
#else
} CHARINFONEW, *PCHARINFONEW;
#endif

typedef struct _INVENTORYARRAY {
union {
/*0x00*/ struct _INVENTORY Inventory;
/*0x00*/ struct _CONTENTS* InventoryArray[NUM_INV_SLOTS];
};
} INVENTORYARRAY, *PINVENTORYARRAY;

//aSdeityD CharInfo2__CharInfo2
#define CHARINFO2_Size 0xAE68 // Jul 08 2019 test (see 8A2EB9) - eqmule
typedef struct _CHARINFO2 {
/******************************** BaseProfile Start ********************************/
/*0x0000*/ BYTE    Unknown0x0000[0x10];
/*0x0010*/ DWORD        BaseProfile;
/*0x0014*/ BYTE    Unknown0x0014[0x8];
/*0x001C*/ struct _INVENTORYARRAY*    pInventoryArray;
/*0x0020*/ BYTE    Unknown0x0020[0x48];
/*0x0068*/ struct _SPELLBUFF    Buff[NUM_LONG_BUFFS];//EQ_Affect size is 0x68 * 0x2a = 0x1110
/*0x1178*/ struct _SPELLBUFF    ShortBuff[NUM_SHORT_BUFFS];//EQ_Affect size is 0x68 * 0x37 = 0x1658
//these IDs are gone (or moved?) from june 10 2019 test we never really used them so whatever... -eqmule
//*0x27d0*/ DWORD    CasterSpellIDs[NUM_BUFF_SLOTS]; // caster IDs for the Effects Window of whoever cast the buff on you in the same zone...
//*0x27D0*/ DWORD    DiseaseSpreadTimers[NUM_BUFF_SLOTS];
/*0x27D0*/ DWORD    SpellBook[NUM_BOOK_SLOTS];
/*0x36d0*/ DWORD    MemorizedSpells[0x12];
/*0x3718*/ DWORD    Skill[NUM_SKILLS];
/*0x38a8*/ DWORD    InnateSkill[0x19];
/*0x390C*/ TSafeArrayStatic<ArmorProperties, 9>    ArmorProps;//size 0xb4
/*0x39C0*/ TSafeArrayStatic<DWORD,9>    CharacterTint;//size 0x24
/*0x39e4*/ DWORD        Gender;
/*0x39e8*/ DWORD        Race;
/*0x39ec*/ DWORD        Class;
/*0x39f0*/ HashTable<int> properties;
/*0x3a00*/ DWORD        Level;
/*0x3a04*/ DWORD        Mana;
/*0x3a08*/ DWORD        Endurance;
/*0x3a10*/ __int64      BaseHP;
/*0x3a18*/ DWORD        BaseSTR;
/*0x3a1c*/ DWORD        BaseSTA;
/*0x3a20*/ DWORD        BaseCHA;
/*0x3a24*/ DWORD        BaseDEX;
/*0x3a28*/ DWORD        BaseINT;
/*0x3a2c*/ DWORD        BaseAGI;
/*0x3a30*/ DWORD        BaseWIS;
/*0x3a34*/ int          Face;
/*0x3a38*/ DWORD        Plat;
/*0x3a3c*/ DWORD        Gold;
/*0x3a40*/ DWORD        Silver;
/*0x3a44*/ DWORD        Copper;
/*0x3a48*/ DWORD        CursorPlat;
/*0x3a4c*/ DWORD        CursorGold;
/*0x3a50*/ DWORD        CursorSilver;
/*0x3a54*/ DWORD        CursorCopper;
/*0x3a58*/ int         _max_allowed_spell_slots;
/*0x3a5c*/ int         practices;
/*0x3a60*/ int         height;
/*0x3a64*/ int         width;
/*0x3a68*/ int         length;
/*0x3a6c*/ int         view_height;
/*0x3a70*/ char        texture_type;
/*0x3a71*/ char        m_armorMat;
/*0x3a72*/ char        m_armorVariation;
/*0x3a73*/ char        headType;
/*0x3a74*/ char        caneditface;
/*0x3a78*/ int         DisciplineTimer;
/*0x3a7c*/ UINT        MendTimer;
/*0x3a80*/ int         ForageTimer;
/*0x3a84*/ int         thirstlevel;
/*0x3a88*/ int         hungerlevel;
/*0x3a8c*/ int         PotionCount;
/*0x3a90*/ int         profileType;
/*0x3a94*/ int         Shrouded;
/*0x3a98*/ int         systemId;
/*0x3a9c*/ int         designId;
/*0x3aa0*/ int         InventorySlotBitmask;
/*0x3aa4*/ UINT        CurrentProgressionID;
/*0x3aa8*/ BYTE        Unknown0x3aa8[0x54];
/*0x3afc*/ int         ParentId;
/*0x3b00*/ int         TattooIndex;
/*0x3b04*/ int         FacialAttachmentIndex;
/******************************** BaseProfile End ********************************/
/******************************** PcProfile Start ********************************/
/*0x3b08*/ TSafeArrayStatic<WorldLocation,5>			BoundLocations;//size 0x64 home_zone
/*0x3B6C*/ TSafeArrayStatic<ArmorProperties, 0x16>		ArmorType;//size 0x1b8
/*0x3D24*/ TSafeArrayStatic<AALIST, AA_CHAR_MAX_REAL>	AAList;//AlternateAbilities 0xE10
/*0x4B34*/ TSafeArrayStatic<DWORD, 0x9>					BodyColor;//0x24
/*0x4b58*/ TSafeArrayStatic<int, 0x800>					FactionTable;//factiontable 0x2000
/*0x6b58*/ TSafeArrayStatic<int, NUM_COMBAT_ABILITIES>	CombatAbilities;//KnownCombatAbilities 0x4B0
/*0x7008*/ TSafeArrayStatic<UINT, 0xF>		SpellRecastTimer;  //spell_used 0x3C
/*0x7044*/ TSafeArrayStatic<UINT, 0x19>		CombatAbilityTimers; //fs 0x64
/*0x70A8*/ TList<CombatAbilityTimer>		CombatAbilityTimersList;//size 8 for sure CombatAbilityTimersAddl
/*0x70b0*/ TSafeArrayStatic<UINT, 0x19>		LinkedSpellTimers;// 0x64 for sure, we used to call thius CombatAbilityTimes...
/*0x7114*/ TSafeArrayStatic<UINT, 0x64>		ItemRecastTimers; //0x190 for sure
/*0x72A4*/ TSafeArrayStatic<UINT, 0x64>		AATimers;//for sure
/*0x7434*/ TSafeArrayStatic<BandolierSet, 0x14>		Bandolier;//size 0x1900 = 0x140 * 0x14 for sure see 8DE476 Jan 04 2019 test
//gone in test 2019-01-04 test /*0x903C*/ TSafeArrayStatic<BandolierItemInfo, 5>	PotionBelt;//size 0x168 = 0x48 * 5
/*0x8D34*/ TSafeArrayStatic<BenefitSelection, 5>	ActiveTributeBenefits;//size 0x28 = 8 * 5 for sure see 8DE437 Jan 04 2019 test
/*0x8D5C*/ TSafeArrayStatic<BenefitSelection, 0xa>	ActiveTrophyTributeBenefits;//size 0x50 = 8 * 0xa
/*0x8DAC*/ ItemBaseContainer		GuildTributeBenefitItems;//size 0x1c for sure see 8C9D9C in 21 Sep 2018
/*0x8DC8*/ ItemBaseContainer		GuildTrophyTributeBenefitItems;//size 0x1c
/*0x8DE4*/ ArrayClass_RO<PCXSTR>	MercenarySaveStrings;//size 0x10
/*0x8DF4*/ AssociatedNPCSaveStringNode *PetSaveString;//for sure
/*0x8DF8*/ DWORD	Deity;//fs see 8DE504 Jan 04 2019 test
/*0x8DFC*/ bool		bPVPFlag;
/*0x8DFD*/ BYTE		HighestLevel;
/*0x8E00*/ DWORD	Drunkenness;//inebriation
/*0x8E04*/ BYTE		HairColor;
/*0x8E05*/ BYTE		BeardColor;
/*0x8E08*/ int		NpcTintIndex;
/*0x8E0c*/ BYTE		LeftEye;
/*0x8E0d*/ BYTE		RightEye;
/*0x8E0e*/ BYTE		Hair;
/*0x8E0f*/ BYTE		Beard;
/*0x8E10*/ BYTE		OldFace;	
/*0x8E14*/ DWORD	AAPoints;
/*0x8E18*/ CHAR		PocketPetSaveString[0x2000];//0x1000 in older clients
/*0xAE18*/ PCXSTR	ItemBuffer;
/*0xAE1C*/ UINT		LastShield;
/*0xAE20*/ bool		bSneak;
/*0xAE21*/ bool		bHide;
/*0xAE24*/ DWORD	AAPointsSpent;
/*0xAE28*/ DWORD	AAPointsAssigned[6];//none, general, arch, class, special, focus, merc
/*0xAE40*/ void	*	pPetData;//PetObjectData todo fill in
/*0xAE44*/ DWORD    PrimActor;
/*0xAE48*/ DWORD    SecdActor;
/*0xAE4C*/ bool     bUseTemplateFaction;
/*0xAE50*/ DWORD    TitlePrefixID;
/*0xAE54*/ DWORD    TitleSuffixID;
/*0xAE58*/ bool     bAreHandsMagic;
/*0xAE5c*/ DWORD    SoleEnabledZoneID;
/*0xAE60*/ DWORD    NewBodyTint;
/*0xAE64*/ DWORD    CurrentMercenaryIndex;
/*0xAE68*/
/******************************** PcProfile End ********************************/

} CHARINFO2, *PCHARINFO2;

typedef struct _MODELINFONAME {
/*0x00*/    DWORD Unknown0000;
/*0x04*/    DWORD Unknown0004;
/*0x08*/    PCHAR Name;
/*0x0c*/
} MODELINFONAME, *PMODELINFONAME;

typedef struct _MODELINFO_GENERIC {
/*0x00*/    DWORD Type;
/*0x04*/    DWORD Unknown0x04;
/*0x08*/    DWORD Unknown0x08;
/*0x0c*/    DWORD Unknown0x0c;
/*0x10*/    DWORD Unknown0x10;
/*0x14*/
} MODELINFO_GENERIC, *PMODELINFO_GENERIC;

typedef struct _MODELINFO_48 {
/*0x00*/    struct _MODELINFO_GENERIC Header;
/*0x14*/    FLOAT Float1;
/*0x18*/    FLOAT Float2;
/*0x1c*/    FLOAT Float3;
/*0x20*/    struct _MODELINFONAME *pModelName;
/*0x24*/
} MODELINFO_48, *PMODELINFO_48;

typedef struct _MODELINFO_51 {
/*0x00*/    struct _MODELINFO_GENERIC Header;
/*0x14*/    struct _MODELINFONAME *pFontName;
/*0x18*/    PCHAR LabelText;
/*0x1c*/
} MODELINFO_51, *PMODELINFO_51;

// 10/09/2003 build      plazmic
// 12/24/2003 verified   Amadeus
typedef struct _MODELINFO {
/*0x00*/    DWORD   Unknown;
/*0x04*/    PCHAR NameDAG;
/*0x08*/    struct _MODELINFO_GENERIC *pModelInfo;
/*0x0c*/    struct _MODELINFO *pNextInChain;
/*0x10*/    PVOID pUnknown;
/*0x14*/    struct _MODELINFONAME *pTrack1;
/*0x18*/    struct _MODELINFONAME *pTrack2;
   //moredata
} MODELINFO, *PMODELINFO;

// 4/30/2003 build      eqmule
typedef struct _CAMERAINFO {
/*0x00*/   DWORD Unknown0x00;
/*0x04*/   DWORD Unknown0x04;
/*0x08*/   BYTE  Unknown0x08[0x8];
/*0x10*/   FLOAT Y;
/*0x14*/   FLOAT X;
/*0x18*/   FLOAT Z;
/*0x1c*/   FLOAT LightRadius;
/*0x20*/
} CAMERAINFO, *PCAMERAINFO;

//is this possibly my old CAMERAINFO struct? -eqmule
typedef struct _EQCAMERABASE {
/*0x000*/ void      *vftable;
/*0x004*/ float     Y;
/*0x008*/ float     X;
/*0x00c*/ float     Z;
/*0x010*/ float     Orientation_Y;	// old name Heading
/*0x014*/ float     Orientation_X;	// old name LookAngle
/*0x018*/ float     Orientation_Z;
/*0x01c*/ float     OldPosition_Y;
/*0x020*/ float     OldPosition_X;
/*0x024*/ float     OldPosition_Z;
/*0x028*/ float     Heading;
/*0x02C*/ float     Height;
/*0x030*/ float     Pitch;
/*0x034*/ float     Distance;
/*0x038*/ float     DirectionalHeading;
/*0x03c*/ float     SideMovement;
/*0x040*/ float     Zoom;          // old name: ViewAngle
/*0x044*/ bool      bAutoPitch;
/*0x045*/ bool      bAutoHeading;
/*0x046*/ bool      bSkipFrame;
/*0x048*/
} EQCAMERABASE, *PEQCAMERABASE;


#define MODEL_LABEL                     0 
#define MODEL_LABELINFO                 1
#define MODEL_NULL2                     2
#define MODEL_HELD_R                    3
#define MODEL_HELD_L                    4
#define MODEL_SHIELD                    5
#define MODEL_NULL6                     6

/*
//Work in progress...
#define MODEL_HEAD                      0x00
#define MODEL_HEAD_POINT                0x01
#define MODEL_NULL_1                    0x02
#define MODEL_HELD_R                    0x03
#define MODEL_HELD_L                    0x04
#define MODEL_SHIELD                    0x05
#define MODEL_NULL_2                    0x06
#define MODEL_TUNIC                     0x07
#define MODEL_HAIR                      0x08
#define MODEL_BEARD                     0x09
#define MODEL_CHEST                     0x0a
#define MODEL_GLOVES                    0x0b
#define MODEL_GLOVES2                   0x0c
*/

typedef struct _ARGBCOLOR {
    union {
        struct {
            BYTE B;
            BYTE G;
            BYTE R;
            BYTE A;
        };
        DWORD ARGB;
    };
} ARGBCOLOR, *PARGBCOLOR;

// actual size: 0x14 05-14-2013 - eqmule
typedef struct _ARMOR {
/*0x00*/ UINT  ID; //idfile on Lucy
/*0x04*/ UINT  Var;
/*0x08*/ UINT  Material;
/*0x0c*/ UINT  NewArmorID;
/*0x10*/ UINT  NewArmorType;
/*0x14*/
} ARMOR, *PARMOR;

// 10-22-2003 Lax
typedef struct _EQUIPMENT {
   union {
      struct// EQUIPARRAY
      {
         struct _ARMOR Item[9];
      };// Array;
      struct //EQUIPUNIQUE
      {
         struct _ARMOR Head;//0x14
         struct _ARMOR Chest;
         struct _ARMOR Arms;
         struct _ARMOR Wrists;
         struct _ARMOR Hands;
         struct _ARMOR Legs;
         struct _ARMOR Feet;
         struct _ARMOR Primary;
         struct _ARMOR Offhand;
      };// Unique;
   };
} EQUIPMENT, *PEQUIPMENT;

//found these at B0DD28 in eqgame.exe dated Aug 15 2016 -eqmule

// offsets are relative to their position in _LAUNCHSPELLDATA
typedef struct _ITEMLOCATION {
/*0x0c*/	ItemContainerInstance Location;
/*0x10*/	short InvSlot;
/*0x12*/	short BagSlot;
/*0x14*/	short AugSlot;
/*0x16*/
} ITEMLOCATION, *PITEMLOCATION;

//size 0x58 see 442783 in eqgame.exe 2017 04 11 test -eqmule
typedef struct _LAUNCHSPELLDATA {
/*0x00*/ UINT    SpellETA;           //Calculated TimeStamp when current spell being cast will land. 0 while not casting.
/*0x04*/ int     SpellID;            // -1 = not casting a spell
/*0x08*/ BYTE    SpellSlot;          // 0xFF if not casting, otherwise it's the spell gem number (0 - 8)
/*0x09*/ BYTE    SpellLevel;
/*0x0c*/ struct  _ITEMLOCATION ItemLocation;
/*0x18*/ ItemSpellTypes ItemCastType;
/*0x1c*/ int     ItemID;
/*0x20*/ FLOAT   CastingY;
/*0x24*/ FLOAT   CastingX;
/*0x28*/ int     DamageID;
/*0x2c*/ UINT    TargetID;
/*0x30*/ bool    bDetrimental;
/*0x31*/ bool    bResetMeleeTimers;
/*0x32*/ bool    bResetAAOnNotTakeHold;
/*0x33*/ bool    bFreeTarget;
/*0x34*/ FLOAT   TargetPosY;
/*0x38*/ FLOAT   TargetPosX;
/*0x3c*/ FLOAT   TargetPosZ;
/*0x40*/ bool    bTwinCast;
/*0x41*/ bool    bLanded;
/*0x42*/ bool    bNPCTarget;
/*0x43*/ bool    bHasHitRecourse;
/*0x44*/ FLOAT   AnchorPosY;
/*0x48*/ FLOAT   AnchorPosX;
/*0x4c*/ FLOAT   AnchorPosZ;
/*0x50*/ bool    bIgnoreRange;
/*0x51*/ bool    bResetAAOnNotTakeHoldSuccess;
/*0x54*/ int	 Unknown0x54;
/*0x58*/

bool IsCasting() const
{
	return (SpellID != -1);
}
} LAUNCHSPELLDATA, *PLAUNCHSPELLDATA;

enum EActorType
{
	Undefined,
	Player,
	Corpse,
	Switch,
	Missile,
	Object,
	Ladder,
	Tree,
	Wall,
	PlacedObject
};

class CPhysicsInfo
{
public:
	/*0x00*/ FLOAT	Y;
	/*0x04*/ FLOAT	X;
	/*0x08*/ FLOAT	Z;
	/*0x0c*/ FLOAT	SpeedY;
	/*0x10*/ FLOAT	SpeedX;
	/*0x14*/ FLOAT	SpeedZ;
	/*0x18*/ FLOAT	SpeedRun;
	/*0x1c*/ FLOAT	Heading;
	/*0x20*/ FLOAT	Angle;
	/*0x24*/ FLOAT	AccelAngle;
	/*0x28*/ FLOAT	SpeedHeading;
	/*0x2c*/ FLOAT	CameraAngle;
	/*0x30*/
};
#define SPAWNINFOHEADER \
/*0x0000*/ void*	vtable; \
/*0x0004*/ struct _SPAWNINFO *pPrev; \
/*0x0008*/ struct _SPAWNINFO *pNext; \
/*0x000c*/ void	*List; \
/*0x0010*/

#define InnateETA 0xc
//we dont need a fully implemented version
//this does the job just fine
template <typename TheType,UINT _Len> class TCircularBuffer
{
public:
	TheType Type[_Len];
	UINT	Len;
	UINT	Index;
};
struct SDoCollisionMovementStats
{
/*0x00*/	CPhysicsInfo Source; /*size 0x30 */
/*0x30*/	FLOAT DestY;
/*0x34*/	FLOAT DestX;
/*0x38*/	FLOAT DestZ;
/*0x3c*/	FLOAT SourceFloor;
/*0x40*/	FLOAT DestFloor;
/*0x44*/	CPhysicsInfo Dest;
/*0x74*/
};

#define PLAYERZONECLIENT \
	DWORD		LastCastTime; \
	bool		bBetaBuffed; \
	int		PetID; \
	UINT		LastRefresh; \
	UINT		TimeStamp; /* updates all the time including when on a mount */ \
	int		SomeData[0x2]; \
	void		*pRaceGenderInfo; /* todo this is not a void* so... map the CRaceGenderInfo class */ \
	struct _EQC_INFO*	spawneqc_info; \
	UINT		RespawnTimer; /* its actually TimeOfDeath...TimeStamp of when RespawnWnd will close - 0 when you're alive */ \
	FLOAT		GetMeleeRangeVar1; /* used by GetMeleeRange */ \
	bool		Sneak; \
	BYTE		TitleVisible; \
	BYTE		CharClass; /* Im pretty sure this isnt working */ \
	int		DontKnowYet; \
	CHAR		Title[0x80]; \
	bool		bBuffTimersOnHold; /* no you can't control this client side so unless you want to get banned leave it alone */ \
	bool		bStationary; \
	DWORD		Meditating; \
	BYTE		HmmWhat; /* todo: figure out */ \
	int		CurrIOState; \
	BYTE		FD; \
	UINT		NextIntimidateTime; \
	BYTE		HoldingAnimation; /* todo: create enum for this byte. Holding: Nothing=0 A RightHand Weapon=1 A Shield=2 Dual Wielding Two Weapons=3 A Spear=4 A LeftHand Weapon=5 A Two Handed Weapon=6 A bow=7 */ \
	int		EnduranceCurrent; \
	UINT		LastResendAddPlayerPacket; \
	int		NpcTintIndex; \
	DWORD		**ppUDP; /* UdpLibrary::UdpConnection? */ \
	struct _LAUNCHSPELLDATA	CastingData; /* size: 0x58 */ \
	UINT		FishingETA; \
	UINT		SpellGemETA[0xf]; /*InnateETA is now the last member in this array */ \
	bool		LFG; \
	DWORD		LoginSerial; \
	__int64	HPMax; \
	UINT		LastTrapDamageTime; \
	BYTE		Level; \
	bool		bShowHelm; \
	bool		bAttackRelated; \
	int		AltAttack; \
	int		Trader;	/* found in CEverQuest__RightClickedOnPlayer_x */ \
	int		WarCry; \
	CHAR		Suffix[0x80]; \
	int		IsAttacking; /* need to investigate */ \
	BYTE		GMRank; /* i think */ \
	FLOAT		BearingToTarget; \
	FLOAT		FallingStartZ; \
	int		Stuff; \
	UINT		LastSecondaryUseTime; \
	bool		bSwitchMoved; /* true when a door moves near the spawn */ \
	UINT		MinuteTimer; \
	CHAR		DraggingPlayer[0x40]; \
	FLOAT		MissileRangeToTarget; \
	UINT		EnduranceMax; \
	DWORD		Zone; \
	FLOAT		MerchantGreed; \
	DWORD		PotionTimer; \
	UINT		CombatSkillTicks[0x2]; \
	FLOAT		CameraOffset; \
	FLOAT		AnimationSpeedRelated; \
	int		Dontknowyet2; \
	int		ManaMax; \
	int		ManaCurrent; \
	UINT		CorpseDragCount; \
	CPhysicsInfo	LastCollision; \
	int		Anon; /* found in EQPlayer__SetNameSpriteTint_x */ \
	CHAR		Handle[0x20]; \
	BYTE		Light; \
	bool		bTempPet; \
	FLOAT		MyWalkSpeed; \
	__int64	GuildID; \
	int		Buyer; \
	BYTE		InPvPArea; /* are we in a PvP area? */ \
	BYTE		StandState; \
	int		berserker; \
	UINT		LastMealTime; /* last time we eat or drank */ \
	bool		bAlwaysShowAura; \
	FLOAT		RunSpeed; /*0.70 on runspeed 5... */ \
	bool		bOfflineMode; \
	BYTE		FishingEvent; \
	UINT		MasterID; \
	UINT		CombatSkillUsed[0x2]; \
	UINT		NextSwim; \
	CHAR		LoginRelated[0x20]; \
	BYTE		IsPassenger; /* if u are on a boat or airship or whatever */ \
	__int64	HPCurrent; \
	UINT		SpellCooldownETA; \
	struct _SPAWNINFO*	pViewPlayer; \
	UINT		LastPrimaryUseTime; \
	UINT		ACounter; /* not sure what this one is for*/ \
	int		RealEstateID; \
	BYTE		FindBits; \
	UINT		StunTimer; \
	CHAR		GM; \
	int		DoSpecialMelee; \
	int		SomethingElse; \
	int		LastCastNum; \
	int		Deity; \
	int		PrimaryTintIndex; \
	int		AFK; \
	int		AARank;/* this really is the title id */ \
	void		*pTouchingSwitch; /* need to get that in here : struct _EQSWITCH */ \
	EqItemGuid realEstateItemGuid; \
	bool		bSummoned; /* by a PC or by anyone? need to investigate */ \
	int		HideMode; \
	UINT		LastTimeStoodStill; \
	UINT		LastTick; \
	bool		PvPFlag; \
	bool		Linkdead; \
	BYTE		IntimidateCount; \
	BYTE		LastAttack; \
	UINT		SitStartTime; \
	UINT		LastRangedUsedTime; \
	CHAR		DragNames[0x2][0x40]; \
	FLOAT		ViewHeight; \
	int		SecondaryTintIndex; \
	BYTE		Blind; \
	bool		bAnimationOnPop; \
	BYTE		Type2; /* check */ \
	int		RealEstateItemId; \
	bool		Mercenary; \
/*0x0608*/


//END PLAYERZONECLIENT

class CParticlePointInterface
{
	//we dont actually need this for now.
};
class CLightInterface
{
	//we dont actually need this for now.
};
class ActorAnimation
{
public:
	ActorAnimation *pPrev;
	ActorAnimation *pNext;
	CHAR Name[30];
	void *pActordef;//CActorDefinitionInterface*
	void **Anim;//EQAnimation
	int NumBones;
	bool bUsesLuclinAnimations;
	bool bNewStyleModel;
	float ParticleEmitterScaleFactor;
	float TargetIndicatorScaleFactor;
	float FirstPersonCameraOffset;
	float ThirdPersonCameraOffset;
	float VerticalCameraOffset;
	float CollisionSphereScaleFactor;
	float ZoomCameraMinimumDistance;
	int NumAnimations;
	int NumAnimationSlots;
};

class CObjectGroupStageInstance : public TListNode<CObjectGroupStageInstance>
{
public:
	void* pActor1;//CActorInterface
	void* pActor2;//CActorInterface
	void* pStage;//CObjectGroupStage
};
class CActorApplicationData
{
public:
	enum EApplicationDataType
	{
		ePlayerBase,
		eMissileBase,
		eObject,
		eSwitch,
		eEnvEmitter,
		ePlacedItem
	};
	virtual EApplicationDataType GetActorApplicationDataType() const = 0;
	virtual const void* AsMissileBase() const = 0;
	virtual void* AsMissileBase() = 0;
	virtual const void* /*PlayerBase*/AsPlayerBase() const = 0;
	virtual void* /*PlayerBase*/ AsPlayerBase() = 0;
	virtual const void * /*EQObject*/ AsObject() const = 0;
	virtual void* /*EQObject*/ AsObject() = 0;
	virtual const void *AsSwitch() const = 0;
	virtual void *AsSwitch() = 0;
	virtual const void* AsPlacedItem() const = 0;
	virtual void* AsPlacedItem() = 0;
};
class ActorBase
{
public:
/*0x0f7C*/ void		*vfTableActorClient;
/*0x0f68*/ CHAR		TextureType;
/*0x0f69*/ CHAR		Material;
/*0x0f6a*/ CHAR		Variation;
/*0x0f6b*/ CHAR		HeadType;
/*0x0f6c*/ BYTE		FaceStyle;
/*0x0f6d*/ BYTE		HairColor;
/*0x0f6e*/ BYTE		FacialHairColor;
/*0x0f6f*/ BYTE		EyeColor1;
/*0x0f70*/ BYTE		EyeColor2;
/*0x0f71*/ BYTE		HairStyle;
/*0x0f72*/ BYTE		FacialHair;
/*0x0f74*/ signed int	Race;
/*0x0f78*/ signed int	Race2;
/*0x0f94*/ signed int	Class;
/*0x0f98*/ BYTE		Gender;
/*0x0f81*/ CHAR		ActorDef[0x40];
/*0x0fc4*/ UINT		ArmorColor[0x9];
/*0x0fe8*/ bool		bShowHelm;
/*0x0fec*/ int		Heritage;               //drakkin only face setting
/*0x0ff0*/ int		Tattoo;                 //drakkin only face setting
/*0x0ff4*/ int		Details;                //drakkin only face setting
/*0x0ff8*/ struct _EQUIPMENT	ActorEquipment;  //0x0ff8 is confirmed // size 0xb4
/*0x10ac*/
EQLIB_OBJECT float ActorBase::GetBoundingRadius();
};

//size 0x1140 see 63D777 in Sep 25 2018 Test - eqmule
//.text:0063D777                 mov     [edi+1B8h], eax so last member is at 1B8h which makes the struct size 0x1bc
//0x1bc + 0x0f84 is 0x1140
class ActorClient : public ActorBase
{
public:
//EQLIB_OBJECT class CVector3 const & ActorClient::GetPosition(void)const;
//EQLIB_OBJECT void ActorClient::GetPosition(class CVector3 *)const;
public:
/*0x0f7C*/ int		LeftEyeMaterialIndex;
/*0x0f80*/ int		RightEyeMaterialIndex;
/*0x0f84*/ CParticlePointInterface* pParticlePoints[0xa];
/*0x0fac*/ void* pLowerBones;
/*0x10e0*/ void* pUpperBones;
/*0x10fc*/ void*	pcactorex; // todo: move to ActorInterface*
/*0x10e8*/ CLightInterface	*pLight;
/*0x10ec*/ ActorAnimation	*pActorAnimation;
/*0x10f0*/ TList<CObjectGroupStageInstance> StageInstances;//size 0x8
/*0x10f8*/ bool		bActiveTransition;
/*0x10Fc*/ UINT		CurrentStage;
/*0x1100*/ FLOAT	ZOffset;
/*0x1104*/ FLOAT	TempY;//related to ZOffset adjustments I *think*
/*0x1108*/ FLOAT	TempX;
/*0x110c*/ FLOAT	TempZ;
/*0x1110*/ bool		bReplacedStaticObject;
/*0x1114*/ int		PartialFaceNumber;
/*0x1118*/ bool		bNewArmorDisabled;
/*0x111c*/ CActorApplicationData* pAppData;
/*0x1120*/
};

class PlayerAnimationBase
{
	//todo: add members and maybe a vftable
};
class CLineBase
{
public:
/*0x00*/	FLOAT OriginY;
/*0x04*/	FLOAT OriginX;
/*0x08*/	FLOAT OriginZ;
/*0x0c*/	FLOAT DirectionY;
/*0x10*/	FLOAT DirectionX;
/*0x14*/	FLOAT DirectionZ;
/*0x18*/
};
class CLineSegment : public CLineBase
{
	//no members here

};
class CCapsule : public CLineSegment
{
public:
/*0x18*/	FLOAT	Radius;
/*0x1c*/
};
struct PhysicsEffect
{
/*0x00*/ int SpellID;
/*0x04*/ int CasterID;
/*0x08*/ int EffectID;
/*0x0c*/ int BaseEffect;
/*0x10*/
};

enum InvisibleTypes
{
	eAll,
	eUndead,
	eAnimal
};

enum GravityBehavior
{
	Ground,
	Flying,
	Levitating,
	Water,
	Floating,//boat
	LevitateWhileRunning
};
class PhysicsBase
{
public:	
/*0x1fA4*/ void*	vtable2;
/*0x1FA8*/	bool bApplyGravity;
};
class PlayerPhysics : public PhysicsBase
{
public:
/*0x1FAC*/	struct _SPAWNINFO*	pSpawn;//PlayerBase*
/*0x1FB0*/	GravityBehavior Levitate;
//bobbing control
/*0x1Fb4*/	int UpDownIndex;
/*0x1Fb8*/	int LeftRightIndex;
/*0x1Fbc*/	int UpDownSpeed;
/*0x1Fc0*/	int LeftRightSpeed;
/*0x1Fc4*/	FLOAT LeftRightDist;
/*0x1Fc8*/	FLOAT UpDownDist;
/*0x1Fcc*/
};
class PlayerPhysicsClient : public PlayerPhysics
{
public:
/*0x1Fb8*/
};

//this is the size of EQPlayer__EQPlayer_x
//aka PlayerClient__PlayerClient_x
// SpawnInfoSize 0x1E98 in Apr 13 2020 Test (see 6748D0) - eqmule
typedef struct _SPAWNINFO {
	SPAWNINFOHEADER
/* ******************** PlayerBase Starts Here ***************** */
/*0x0010*/ FLOAT	JumpStrength;
/*0x0014*/ FLOAT	SwimStrength;
/*0x0018*/ FLOAT	SpeedMultiplier;
/*0x001c*/ FLOAT	AreaFriction;
/*0x0020*/ FLOAT	AccelerationFriction;
/*0x0024*/ EActorType CollidingType; /* ok finally had time to get this one right, when we collide with something this gets set. */
/*0x0028*/ FLOAT	FloorHeight;
/*0x002c*/ bool		bSinksInWater;
/*0x0030*/ UINT		PlayerTimeStamp; /* doesn't update when on a Vehicle (mounts/boats etc) */
/*0x0034*/ UINT		LastTimeIdle;
/*0x0038*/ CHAR		Lastname[0x20];
/*0x0058*/ FLOAT	AreaHPRegenMod; /*from guild hall pools etc. */
/*0x005c*/ FLOAT	AreaEndRegenMod;
/*0x0060*/ FLOAT	AreaManaRegenMod;
/*0x0064*/ FLOAT	Y;
/*0x0068*/ FLOAT	X;
/*0x006c*/ FLOAT	Z;
/*0x0070*/ FLOAT	SpeedY;
/*0x0074*/ FLOAT	SpeedX;
/*0x0078*/ FLOAT	SpeedZ;
/*0x007c*/ FLOAT	SpeedRun;
/*0x0080*/ FLOAT	Heading;
/*0x0084*/ FLOAT	Angle;
/*0x0088*/ FLOAT	AccelAngle;
/*0x008c*/ FLOAT	SpeedHeading;
/*0x0090*/ FLOAT	CameraAngle;
/*0x0094*/ UINT		UnderWater; /*LastHeadEnvironmentType */
/*0x0098*/ UINT		LastBodyEnvironmentType;
/*0x009c*/ UINT		LastFeetEnvironmentType;
/*0x00a0*/ BYTE		HeadWet; /*these really are environment related, like lava as well for example */
/*0x00a1*/ BYTE		FeetWet;
/*0x00a2*/ BYTE		BodyWet;
/*0x00a3*/ BYTE		LastBodyWet;
/*0x00a4*/ CHAR		Name[0x40];             /* ie priest_of_discord00 */
/*0x00e4*/ CHAR		DisplayedName[0x40];    /* ie Priest of Discord*/
/*0x0124*/ BYTE		PossiblyStuck;          /* never seen this be 1 so maybe it was used a a point but not now... */
/*0x0125*/ BYTE		Type;
/*0x0128*/ DWORD**	BodyType;	/* this really should be renamed to charprops or something its broken anyway*/
/*0x012c*/ BYTE		CharPropFiller[0xc]; /* well since the above is a CharacterPropertyHash we have to pad here...*/
/*0x0138*/ FLOAT	AvatarHeight;           /* height of avatar from groundwhen standing for sure see 5C06A0 in Jun 10 2019 test - eqmule*/
/*0x013c*/ FLOAT	Height;
/*0x0140*/ FLOAT	Width;
/*0x0144*/ FLOAT	Length;
/*0x0148*/ int		Unknown0x0148;
/*0x014c*/ int		Unknown0x014C;
/*0x0150*/ DWORD	SpawnID;
/*0x0154*/ DWORD	PlayerState;         /* 0=Idle 1=Open 2=WeaponSheathed 4=Aggressive 8=ForcedAggressive 0x10=InstrumentEquipped 0x20=Stunned 0x40=PrimaryWeaponEquipped 0x80=SecondaryWeaponEquipped */
/*0x0158*/ struct _SPAWNINFO*	Vehicle;    /* NULL until you collide with a vehicle (boat,airship etc) */
/*0x015c*/ struct _SPAWNINFO*	Mount;      /* NULL if no mount present */
/*0x0160*/ struct _SPAWNINFO*	Rider;      /* _SPAWNINFO of mount's rider */
/*0x0164*/ DWORD	Unknown0x0164;
/*0x0168*/ bool		Targetable;	/* true if mob is targetable */
/*0x0169*/ bool		bTargetCyclable;
/*0x016a*/ bool		bClickThrough;
/*0x016b*/ bool		bBeingFlung;
/*0x016c*/ UINT		FlingActiveTimer;
/*0x0170*/ UINT		FlingTimerStart;
/*0x0174*/ bool		bFlingSomething;
/*0x0178*/ FLOAT	FlingY;
/*0x017c*/ FLOAT	FlingX;
/*0x0180*/ FLOAT	FlingZ;
/*0x0184*/ bool		bFlingSnapToDest;
/*0x0188*/ int		SplineID;
/*0x018c*/ int		SplineRiderID;
/* *********************** PlayerBase Ends Here ********************** */
/* ******************** PlayerZoneClient Starts Here ***************** */
/*0x0190*/ UINT		LastIntimidateUse;
/*0x0194*/ PLAYERZONECLIENT
/*0x0608*/ //I wont finetune these comments every single patch cause they change since PLAYERZONECLIENT size change...
/*0x0608*/ TCircularBuffer<SDoCollisionMovementStats, 0x14>MovementStats; /* size (0x74 * 0x14) +8 = 0x918 */
/*0x0f20*/ struct _SPAWNINFO*   WhoFollowing; // NULL if autofollow off
/*0x0f24*/ DWORD	GroupAssistNPC[0x1];
/*0x0f28*/ DWORD	RaidAssistNPC[0x3];
/*0x0f34*/ DWORD	GroupMarkNPC[0x3];
/*0x0f40*/ DWORD	RaidMarkNPC[0x3];
/*0x0f4c*/ DWORD	TargetOfTarget;
/*0x0f50*/ BYTE		PhysStuff[0x20];
/*0x0f70*/ UINT		ParticleCastStartTime;
/*0x0f74*/ UINT		ParticleCastDuration;
/*0x0f78*/ int		ParticleVisualSpellNum;
/*0x0f7c*/ BYTE		Filler0x0f7c[0x4];
/*0x0f80*/ ActorClient	mActorClient;          // start of ActorClient struct  size 0x1BC?
/*0x113c*/ PlayerAnimationBase *pAnimation;
/*0x1140*/ FLOAT	MeleeRadius;      // used by GetMeleeRange
/*0x1144*/ UINT		CollisionCounter;
/*0x1148*/ FLOAT	CachedFloorLocationY;
/*0x114c*/ FLOAT	CachedFloorLocationX;
/*0x1150*/ FLOAT	CachedFloorLocationZ;
/*0x1154*/ FLOAT	CachedFloorHeight;
/*0x1158*/ FLOAT	CachedCeilingLocationY;
/*0x115c*/ FLOAT	CachedCeilingLocationX;
/*0x1160*/ FLOAT	CachedCeilingLocationZ;
/*0x1164*/ FLOAT	CachedCeilingHeight;
/*0x1168*/ CCapsule	StaticCollision;//size 0x1c
/*0x1184*/ ArrayClass_RO<PhysicsEffect> mPhysicsEffects;//size is 0x10
/*0x1194*/ ArrayClass_RO<bool> PhysicsEffectsUpdated;//size is 0x10
/* ********************* PlayerZoneClient Ends Here ******************* */
/* ********************** PlayerClient Starts Here ******************** */
/*0x11a4*/ BYTE		Filler0x11a4[0x4];
/*0x11a8*/ int		Animation; /* Current Animation Playing. see 5671F1 in feb 14 2019 test */
/*0x11ac*/ int		NextAnim;
/*0x11b0*/ int		CurrLowerBodyAnim;
/*0x11b4*/ int		NextLowerBodyAnim;
/*0x11b8*/ int		CurrLowerAnimVariation;
/*0x11bc*/ int		CurrAnimVariation;
/*0x11c0*/ int		CurrAnimRndVariation;
/* ********************sound ID's BEGIN ******************* */
/*0x11c4*/ int		Loop3d_SoundID;//see 567254 in feb 14 2019 test
/*0x11c8*/ int		Step_SoundID;;
/*0x11cc*/ int		CurLoop_SoundID;
/*0x11d0*/ int		Idle3d1_SoundID;
/*0x11d4*/ int		Idle3d2_SoundID;
/*0x11d8*/ int		Jump_SoundID;
/*0x11dc*/ int		Hit1_SoundID;
/*0x11e0*/ int		Hit2_SoundID;
/*0x11e4*/ int		Hit3_SoundID;
/*0x11e8*/ int		Hit4_SoundID;
/*0x11ec*/ int		Gasp1_SoundID;
/*0x11f0*/ int		Gasp2_SoundID;
/*0x11f4*/ int		Drown_SoundID;
/*0x11f8*/ int		Death_SoundID;
/*0x11fc*/ int		Attk1_SoundID;
/*0x1200*/ int		Attk2_SoundID;
/*0x1204*/ int		Attk3_SoundID;
/*0x1208*/ int		Walk_SoundID;
/*0x120c*/ int		Run_SoundID;
/*0x1210*/ int		Crouch_SoundID;
/*0x1214*/ int		Swim_SoundID;
/*0x1218*/ int		TreadWater_SoundID;
/*0x121c*/ int		Climb_SoundID;
/*0x1220*/ int		Sit_SoundID;
/*0x1224*/ int		Kick_SoundID;
/*0x1228*/ int		Bash_SoundID;
/*0x122c*/ int		FireBow_SoundID;
/*0x1230*/ int		MonkAttack1_SoundID;
/*0x1234*/ int		MonkAttack2_SoundID;
/*0x1238*/ int		MonkSpecial_SoundID;
/*0x123c*/ int		PrimaryBlunt_SoundID;
/*0x1240*/ int		PrimarySlash_SoundID;
/*0x1244*/ int		PrimaryStab_SoundID;
/*0x1248*/ int		Punch_SoundID;
/*0x124c*/ int		Roundhouse_SoundID;
/*0x1250*/ int		SecondaryBlunt_SoundID;
/*0x1254*/ int		SecondarySlash_SoundID;
/*0x1258*/ int		SecondaryStab_SoundID;
/*0x125c*/ int		SwimAttack_SoundID;
/*0x1260*/ int		TwoHandedBlunt_SoundID;
/*0x1264*/ int		TwoHandedSlash_SoundID;
/*0x1268*/ int		TwoHandedStab_SoundID;
/*0x126c*/ int		SecondaryPunch_SoundID;
/*0x1270*/ int		JumpAcross_SoundID;
/*0x1274*/ int		WalkBackwards_SoundID;
/*0x1278*/ int		CrouchWalk_SoundID;
/* ******************** sound ID's END ****************** */
/*0x127c*/ UINT		LastHurtSound;// see 5E96E0 in feb 14 2019 test
/*0x1280*/ UINT		LastWalkTime;//used for animations
/*0x1284*/ int		ShipRelated;//ID? look into.
/*0x1288*/ int		RightHolding;//Nothing=0 Other/Weapon=1 shield=2
/*0x128c*/ int		LeftHolding;//old Holding
/*0x1290*/ UINT		DeathAnimationFinishTime;
/*0x1294*/ bool		bRemoveCorpseAfterDeathAnim;//0x1274 for sure used by /hidecorpse
/*0x1298*/ UINT		LastBubblesTime;
/*0x129c*/ UINT		LastBubblesTime1;
/*0x12a0*/ UINT		LastColdBreathTime;
/*0x12a4*/ UINT		LastParticleUpdateTime;
/*0x12a8*/ UINT		MercID;    // IT IS 0x1288      //if the spawn is player and has a merc up this is it's spawn ID -eqmule 16 jul 2014
/*0x12ac*/ UINT		ContractorID;    //if the spawn is a merc this is its contractor's spawn ID -eqmule 16 jul 2014
/*0x12b0*/ FLOAT	CeilingHeightAtCurrLocation;
/*0x12b4*/ void		*MobileEmitter;//todo: change and map to EqMobileEmitter*
/*0x12b8*/ bool		bInstantHPGaugeChange;
/*0x12bc*/ UINT		LastUpdateReceivedTime;
/*0x12c0*/ FLOAT	MaxSpeakDistance;
/*0x12c4*/ FLOAT	WalkSpeed;//how much we will slow down while sneaking
/*0x12c8*/ bool		bHideCorpse;
/*0x12c9*/ CHAR		AssistName[0x40];
/*0x1309*/ bool		InvitedToGroup;
/*0x130c*/ int		GroupMemberTargeted;// 0xFFFFFFFF if no target, else 1 through 5
/*0x1310*/ bool		bRemovalPending;//see 5E0763 in feb 14 2019 test
/*0x1314*/ void		*pCorpse;
/*0x1318*/ FLOAT	EmitterScalingRadius;
/*0x131c*/ int		DefaultEmitterID;
/*0x1320*/ bool		bDisplayNameSprite;
/*0x1321*/ bool		bIdleAnimationOff;
/*0x1322*/ bool		bIsInteractiveObject;
/*0x1323*/ BYTE		InteractiveObjectModelName[0x80];
/*0x13a3*/ BYTE		InteractiveObjectOtherName[0x80];
/*0x1423*/ BYTE		InteractiveObjectName[0x40];
/*0x1464*/ CPhysicsInfo PhysicsBeforeLastPort;//size IS /*0x30*/ see 5E617B in feb 14 2019 test
/*0x1494*/ DWORD	Filler0x1494;
/*0x1498*/ struct _FELLOWSHIPINFO	Fellowship; // IT IS AT 0x1498 see 63BEDD in feb 14 2019 test // size 0x9e8
/*0x1CF8*/ FLOAT	CampfireY;
/*0x1CFC*/ FLOAT	CampfireX;
/*0x1D00*/ FLOAT	CampfireZ;
/*0x1D04*/ int		CampfireZoneID;         // zone ID where campfire is
/*0x1D08*/ int		CampfireTimestamp;      // CampfireTimestamp-FastTime()=time left on campfire
/*0x1D0C*/ int		CampfireTimestamp2;
/*0x1D10*/ int		FellowShipID;
/*0x1D14*/ int		FellowShipID2;
/*0x1D18*/ int		CampType;
/*0x1D1C*/ bool		Campfire;
/*0x1D20*/ TSafeArrayStatic<int,3> SeeInvis;//size 0xc for sure see 63E23F or 63BD35 in feb 14 2019 test
/*0x1D2C*/ struct _EQUIPMENT	Equipment;// size 0xb4 see 63BF44 in feb 14 2019 test
/*0x1DE0*/ bool		bIsPlacingItem;//for sure see 543626 in feb 14 2019 test
/*0x1DE1*/ bool		bGMCreatedNPC;
/*0x1DE4*/ int		ObjectAnimationID;
/*0x1DE8*/ bool		bInteractiveObjectCollidable;
/*0x1DEC*/ int		InteractiveObjectType;
/*0x1DF0*/ int		SoundIDs[0xa];//0x28 bytes for sure see 648AB2 in feb 14 2019 test
/*0x1E18*/ UINT		LastHistorySentTime;//for sure see 648E7E in feb 14 2019 test
/*0x1E1C*/ ArrayClass2_RO<UINT>	BardTwistSpells;//size 0x18
/*0x1E34*/ int		CurrentBardTwistIndex;
/*0x1E38*/ int		CurrentBardTwistIndex2;
/*0x1E3C*/ PlayerPhysicsClient mPlayerPhysicsClient;//size 0x28
/*0x1E64*/ int		SpawnStatus[6];//todo: look closer at these i think they can show like status of mobs slowed, mezzed etc, but not sure
/*0x1E7C*/ int		BannerIndex0;//guild banners
/*0x1E80*/ int		BannerIndex1;
/*0x1E84*/ ARGBCOLOR BannerTint0;
/*0x1E88*/ ARGBCOLOR BannerTint1;
/*0x1E8C*/ int		MountAnimationRelated;
/*0x1E90*/ bool		bGuildShowAnim;//or sprite? need to check
/*0x1E91*/ bool		bWaitingForPort;//for sure see 5C5445 in feb 14 2019 test
/*0x1E94*/ int		Unknown0x1E94;
/* ********************** PlayerClient Ends Here ******************** */
/*0x1E98*/ //see SpawnInfoSize
	inline signed int GetClass()
	{
		return mActorClient.Class;
	}
	inline BYTE GetCharacterType()
	{
		return Type;
	}
	inline unsigned int GetId() const
	{
		return SpawnID;
	}
	EQLIB_OBJECT void* GetCharacter() const;
	EQLIB_OBJECT int   GetZoneID() const;
	EQLIB_OBJECT int   GetCurrentMana() const;
	EQLIB_OBJECT int   GetMaxMana() const;
	EQLIB_OBJECT int   GetCurrentEndurance() const;
	EQLIB_OBJECT int   GetMaxEndurance() const;
	EQLIB_OBJECT int   GetSpellCooldownETA() const;
} SPAWNINFO, *PSPAWNINFO;

#define STANDSTATE_STAND                0x64
#define STANDSTATE_CASTING              0x66
#define STANDSTATE_BIND                 0x69
#define STANDSTATE_SIT                  0x6E
#define STANDSTATE_DUCK                 0x6F
#define STANDSTATE_FEIGN                0x73
#define STANDSTATE_DEAD                 0x78

#define MONITOR_SPAWN_X                 1
#define MONITOR_SPAWN_Y                 2
#define MONITOR_SPAWN_Z                 4
#define MONITOR_SPAWN_HEADING           8
#define MONITOR_SPAWN_SPEEDRUN          16
#define MONITOR_SPAWN_HPCURRENT         32

typedef struct _SPAWNMONITORINFO {
    WORD SpawnID;
    FLOAT Y;
    FLOAT X;
    FLOAT Z;
    FLOAT Heading;
    FLOAT SpeedRun;
    DWORD HPCurrent;
    DWORD MonitorMask;
} SPAWNMONITORINFO, *PSPAWNMONITORINFO;

typedef struct _HASHENTRY {
    SPAWNINFO   *spawn;
    DWORD       key;            // same as SpawnID for spawns
    struct      _HASHENTRY *next;
} HASHENTRY, *PHASHENTRY;

typedef struct _HASHTABLE {
    struct _HASHENTRY **table;
    int size;
} HASHTABLE, *PHASHTABLE;

typedef struct _SPAWNMANAGER {
/*0x000*/ void          *vftable;
/*0x004*/ DWORD         random; // rand()%20000
/*0x008*/ struct  _SPAWNINFO        *FirstSpawn;
/*0x00c*/ struct  _SPAWNINFO        *LastSpawn;
/*0x010*/ DWORD         unknown10;
/*0x014*/ struct        _HASHTABLE  *SPHash;
} SPAWNMANAGER, *PSPAWNMANAGER;


#if 0

void *gethashedentry(struct _HASHTABLE  *table, DWORD key)
{
    PHASHENTRY p = NULL;
    p = table->array[key%table->size];

    while(p) {
        if (p->key == key) return p;
        p = p->next;
    }
    return NULL;
}

#endif

// copy of D3DMATRIX by brainiac dec 16 2015
struct Matrix4x4
{
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

//eqmule oct 31 2013
typedef struct _SWITCHCLICK
{
	FLOAT Y;
	FLOAT X;
	FLOAT Z;
	FLOAT Y1;
	FLOAT X1;
	FLOAT Z1;
} SWITCHCLICK,*PSWITCHCLICK;

enum eMemPoolType
{
	eGlobal,
	eOnDemand,
	eClearOnZone,
};

// this is actually a CActor Class
// actual size: 0x120 3-3-2009
//Size is 0x190 dec 13 2016 live - eqmule
//see Cactor::CActor in EQGraphicsDX9.dll
typedef struct _EQSWITCH {
/*0x00*/    void*		vfTable;
/*0x04*/    eMemPoolType  MemType;
/*0x08*/    bool        bIsS3DCreated;
/*0x09*/    bool        bHasParentBone;
/*0x0a*/    bool        bUpdateScaledAmbient;
/*0x0c*/    float		ScaledAmbient;
/*0x10*/    float		ScaledAmbientTarget;
/*0x14*/    float		ParticleScaleFactor;
/*0x18*/    float		CollisionSphereScaleFactor;
/*0x1c*/    UINT        UpdateAmbientTick;
/*0x20*/    UINT        InterpolateAmbientTick;
/*0x24*/    void*		pParentActor;//its a  CActor*
/*0x28*/    void*       pDPVSObject;
/*0x2C*/    FLOAT		Y;
/*0x30*/    FLOAT		X;
/*0x34*/    FLOAT		Z;
/*0x38*/    FLOAT		SurfaceNormalY;
/*0x3c*/    FLOAT		SurfaceNormalX;
/*0x40*/    FLOAT		SurfaceNormalZ;
/*0x44*/    UINT        VisibleIndex;
/*0x48*/    FLOAT       Alpha;
/*0x4c*/    bool	    bCastShadow;
/*0x4d*/    bool	    bNeverClip;
/*0x4e*/    bool	    bClientCreated;
/*0x50*/    FLOAT       ZOffset;
/*0x54*/    FLOAT       EmitterScalingRadius;
/*0x58*/    void*		pDuplicateActor;//its a  CActor*
/*0x5c*/    bool	    bShowParticlesWhenInvisible;
/*0x60*/    void*       pAreaPortalVolumeList;//CAreaPortalVolumeList*
/*0x64*/    void*       CleanupList;//a TListNode<CActor*>? not sure
/*0x68*/    BYTE        CleanupListFiller[0xc];
/*0x74*/    void*       pActorApplicationData;//CActorApplicationData* 74 for sure see 1003AE70
/*0x78*/    EActorType  ActorType;
/*0x7c*/    void*       pTerrainObject;//CTerrainObject*
/*0x80*/    void*       HighlightData;//HighlightData*
/*0x84*/    float       yAdjustment1;//from this point on im not sure -eqmule 2013 dec 16
/*0x88*/    float       xAdjustment1;
/*0x8c*/    float       zAdjustment1;
/*0x90*/    float       headingAdjustment1;
/*0x94*/    float       yAdjustment2;
/*0x98*/    float       xAdjustment2;
/*0x9c*/    float       zAdjustment2;
/*0xa0*/    float       headingAdjustment2;
/*0xa4*/    float       yAdjustment3;
/*0xa8*/    float       xAdjustment3;
/*0xac*/    float       zAdjustment3;
/*0xb0*/    float       headingAdjustment3;
/*0xb4*/    float       adjustments4[3];
/*0xc0*/    float       adjustments5[4];
/*0xd0*/    bool        bbHasAttachSRT;
/*0xd1*/    bool        bDisableDesignOverride;
/*0xd4*/    int         Unknown0xd4[4];
/*0xe4*/    Matrix4x4   transformMatrix;//used for new armor
/*0x128*/   FLOAT       Heading;
/*0x12c*/   BYTE        Unknown0x12c[0x14];
/*0x140*/   float       HeightAdjustment;//this is most likely wrong dec 16 2013 eqmule
/*0x144*/   BYTE        Unknown0x144[0x4c];
/*0x190*/
} EQSWITCH, *PEQSWITCH;



//Size is 0xe0 see 54933E in dec 13 2016 live - eqmule
typedef struct _DOOR {
/*0x00*/ void  *vtable;
/*0x04*/ BYTE  ObjType;          // always 5
/*0x05*/ BYTE  ID;
/*0x06*/ CHAR  Name[0x20];
/*0x26*/ BYTE  Type;
/*0x27*/ BYTE  State;               // 0 = closed, 1 = open, 2 = opening, 3 = closing
/*0x28*/ FLOAT DefaultY;
/*0x2c*/ FLOAT DefaultX;
/*0x30*/ FLOAT DefaultZ;
/*0x34*/ FLOAT DefaultHeading;
/*0x38*/ FLOAT DefaultDoorAngle;
/*0x3c*/ FLOAT TopSpeed1;
/*0x40*/ FLOAT TopSpeed2;
/*0x44*/ FLOAT Y;
/*0x48*/ FLOAT X;
/*0x4c*/ FLOAT Z;
/*0x50*/ FLOAT Heading;
/*0x54*/ FLOAT DoorAngle;
/*0x58*/ BYTE  DefaultState;
/*0x59*/ BYTE  SelfActivated;
/*0x5a*/ BYTE  Dependent;
/*0x5b*/ bool  bTemplate;
/*0x5c*/ BYTE  Difficulty;//pick/disarm...
/*0x5d*/ BYTE  AffectSlots[5];
/*0x62*/ BYTE  CurrentCombination[5];
/*0x67*/ BYTE  ReqCombination[5];
/*0x6c*/ BYTE  RandomCombo;
/*0x70*/ int   Key;
/*0x74*/ SHORT ScaleFactor;         // divide by 100 to get scale multiplier
/*0x78*/ int SpellID;
/*0x7c*/ BYTE  TargetID[0x5];
/*0x81*/ CHAR  Script[0x20];
/*0xa4*/ PEQSWITCH pSwitch;         // (CActorInterface*)
/*0xa8*/ void  *particle;       // (CParticleCloudInterface*)
/*0xac*/ DWORD TimeStamp;//last time UseSwitch
/*0xb0*/ FLOAT Accel;
/*0xb4*/ BYTE  AlwaysActive;
/*0xb8*/ int   AdventureDoorID;
/*0xbc*/ FLOAT ReturnY;
/*0xc0*/ FLOAT ReturnX;
/*0xc4*/ FLOAT ReturnZ;
/*0xc8*/ int   DynDoorID;
/*0xcc*/ bool  bHasScript;
/*0xd0*/ int   SomeID;
/*0xd4*/ bool  bUsable;
/*0xd5*/ bool  bRemainOpen;
/*0xd6*/ bool  bVisible;
/*0xd7*/ bool  bHeadingChanged;
/*0xd8*/ bool  bAllowCorpseDrag;
/*0xdc*/ int   RealEstateDoorID;
/*0xe0*/
} DOOR, *PDOOR; 

// 7-21-2003    Stargazer
typedef struct _DOORTABLE {
/*0x000*/   DWORD NumEntries;
/*0x004*/   PDOOR pDoor[0x0FF];
/*0x400*/
} DOORTABLE, *PDOORTABLE;

// actual size 0x80 20101012 - ieatacid
typedef struct _GROUNDITEM {
/*0x00*/ struct _GROUNDITEM *pPrev;
/*0x04*/ struct _GROUNDITEM *pNext;
/*0x08*/ VePointer<CONTENTS> ID;//well its not an int but plugins use this as one so ill keep the name
/*0x0c*/ DWORD  DropID;//unique id
/*0x10*/ DWORD  ZoneID;
/*0x14*/ DWORD  DropSubID;//well zonefile id, but yeah...
/*0x18*/ PEQSWITCH pSwitch; // (class EQSwitch *)
/*0x1c*/ CHAR   Name[0x40];
/*0x5c*/ long	Expires;
/*0x60*/ FLOAT  Heading;
/*0x64*/ FLOAT	Pitch;
/*0x68*/ FLOAT	Roll;
/*0x6c*/ FLOAT	Scale;
/*0x70*/ FLOAT  Y;
/*0x74*/ FLOAT  X;
/*0x78*/ FLOAT  Z;
/*0x7c*/ int   Weight;//-1 means it can't be picked up
/*0x80*/
} GROUNDITEM, *PGROUNDITEM;

enum eGroundObject
{
	GO_None,
	GO_GroundType,
	GO_ObjectType
};
typedef struct _GROUNDOBJECT
{
	eGroundObject Type;
	GROUNDITEM	GroundItem;//for conversion between switch and gorunditems
	void *ObjPtr;// EQPlacedItem *
	PGROUNDITEM	pGroundItem;
} GROUNDOBJECT,*PGROUNDOBJECT;

#define   MAX_ZONES                     0x3e8
extern    PCHAR szZoneExpansionName[];     //defined in LibEQ_Utilities.cpp

//Size 0x1D8 see 867D39 in eqgame.exe live 21 apr 2016 - eqmule
typedef struct _ZONELIST { 
/*0x000*/   DWORD  vfTable;
/*0x004*/   int  Unknown0x004;
/*0x008*/	int  EQExpansion;
/*0x00c*/	int  Id;  //EQZoneIndex
/*0x010*/	CHAR ShortName[0x81];
/*0x091*/	CHAR LongName[0x101];
/*0x198*/	unsigned __int64  ZoneFlags;// 0x800000 = gmzone? 0x8000 water/mountainzone? 0x4 = ? 0x1 = MultiInstanceZone 0x10000000 bazaarzone 0x2000000 = barterzone 0x100000 = HasMinLevel, 0x1000000 = tutorialzone 0x4000 = no air, 0x2 newbie zone, 0x20 no bind, 0x400000 lostestingdisabled, 0x80000000 guildhallzone
/*0x1a0*/	int eqstrID;
/*0x1a4*/	int	AccessLevel;
/*0x1a8*/	int MinLevel;
/*0x1ac*/	int CurPlayerCount;
/*0x1B0*/	int MaxPlayerCount;
/*0x1b4*/	USHORT NextInstanceID;
/*0x1b8*/	int Cpu1;
/*0x1bc*/	int Cpu2;
/*0x1c0*/	int Memory;
/*0x1c4*/	int MemLoad;
/*0x1c8*/	int VirtMemLoad;
/*0x1cc*/	int ActiveMercenaries;
/*0x1D0*/	int SuspendedMercenaries;
/*0x1D4*/	int  Unknown0x1D4;
/*0x1D8     next zone in list*/ 
} ZONELIST, *PZONELIST;

//EQWorldData__EQWorldData_x
//Size 0xFC0 see 5721F1 in eqgame.exe live 21 apr 2016 - eqmule
typedef struct _WORLDDATA {
/*0x000*/ PVOID lpvTable;
/*0x004*/ BYTE Hour;
/*0x005*/ BYTE Minute;
/*0x006*/ BYTE Day;
/*0x007*/ BYTE Month;
/*0x008*/ int Year;
/*0x00C*/ BYTE LastHour;
/*0x00D*/ BYTE LastMinute;
/*0x00E*/ BYTE LastDay;
/*0x00F*/ BYTE LastMonth;
/*0x010*/ int LastYear;
/*0x014*/ UINT LastAdvance;
/*0x018*/ UINT LastTime;
/*0x01C*/ UINT Unknown0x01C;
/*0x020*/ PZONELIST ZoneArray[MAX_ZONES];// see 867D1B in eqgame.exe live 21 apr 2016
/*0xFC0*/
} WORLDDATA, *PWORLDDATA;

enum EOutDoor : BYTE
{
	IndoorDungeon,		// Zones without sky SolB for example.
	Outdoor,			// Zones with sky like Commonlands for example.
	OutdoorCity,		// A Player City with sky Plane of Knowledge for example.
	DungeonCity,		// A Player City without sky Ak'anon for example.
	IndoorCity,			// A Player City without sky Erudin for example.
	OutdoorDungeon,		// Dungeons with sky like Blackburrow for example.
};
enum EPlace
{
	CannotPlace,
	CanOnlyPlace,
	CanPlaceAndGoto,
};
//Size 0x3a8 see F17224-F16E7C in eqgame.exe live 17 Jan 2017 - eqmule
typedef struct _ZONEINFO {
/*0x000*/   CHAR    CharacterName[0x40];
/*0x040*/   CHAR    ShortName[0x80];
/*0x0c0*/   CHAR    LongName[0x80];
/*0x140*/   CHAR    ZoneDesc[0x5][0x1e];  //zone description strings
/*0x1d6*/   BYTE    FogOnOff; // (usually FF)
/*0x1d7*/   ARGBCOLOR FogRed;
/*0x1db*/   ARGBCOLOR FogGreen;
/*0x1df*/   ARGBCOLOR FogBlue;
/*0x1e4*/   FLOAT   FogStart[0x4]; //fog distance
/*0x1f4*/   FLOAT   FogEnd[0x4];
/*0x204*/   FLOAT   ZoneGravity;
/*0x208*/   EOutDoor    OutDoor;//this is what we want instead of ZoneType, see the enum
/*0x209*/   BYTE    RainChance[0x4];//no u cant change these to dwords cause then u screw up 4 byte padding
/*0x20d*/   BYTE    RainDuration[0x4];
/*0x211*/   BYTE    SnowChance[0x4];
/*0x215*/   BYTE    SnowDuration[0x4];
/*0x219*/   char    ZoneTimeZone;   //in hours from worldserver, can be negative
/*0x21a*/   BYTE    SkyType;   //1 means active
/*0x21c*/   int		WaterMidi;   //which midi to play while underwater
/*0x220*/   int		DayMidi;   
/*0x224*/   int		NightMidi;
/*0x228*/   FLOAT   ZoneExpModifier;    //This has been nerfed ..now reads 1.0 for all zones
/*0x22c*/   FLOAT   SafeXLoc;
/*0x230*/   FLOAT   SafeYLoc;
/*0x234*/   FLOAT   SafeZLoc;
/*0x238*/   FLOAT   SafeHeading;
/*0x23c*/   FLOAT   Ceiling;
/*0x240*/   FLOAT   Floor;
/*0x244*/   FLOAT   MinClip;
/*0x248*/   FLOAT   MaxClip;
/*0x24c*/	int		ForageLow; //Forage skill level needed to get stuff
/*0x250*/	int		ForageMedium;
/*0x254*/	int		ForageHigh;
/*0x258*/	int		FishingLow; //Fishing skill level needed to get stuff
/*0x25c*/	int		FishingMedium;
/*0x260*/	int		FishingHigh;
/*0x264*/	int		SkyRelated; //0-24 i think
/*0x268*/	UINT	GraveyardTimer; //minutes until corpse(s) pops to graveyard
/*0x26c*/	int		ScriptIDHour;
/*0x270*/	int		ScriptIDMinute;
/*0x274*/	int		ScriptIDTick;
/*0x278*/	int		ScriptIDOnPlayerDeath;
/*0x27c*/	int		ScriptIDOnNPCDeath;
/*0x280*/	int		ScriptIDPlayerEnteringZone;
/*0x284*/	int		ScriptIDOnZonePop;
/*0x288*/	int		ScriptIDNPCLoot;
/*0x28c*/	int		ScriptIDAdventureFailed;
/*0x290*/	int		CanExploreTasks;
/*0x294*/	int		UnknownFlag;
/*0x298*/	int		ScriptIDOnFishing;
/*0x29c*/	int		ScriptIDOnForage;
/*0x2a0*/	CHAR	SkyString[0x20]; //if empty no sky, ive only seen this as the zone name
/*0x2c0*/	CHAR	WeatherString[0x20]; //if empty no weather
/*0x2e0*/	CHAR	SkyString2[0x20]; //if SkyString is empty this is checked
/*0x310*/	int		SkyRelated2; //0-24
/*0x314*/	CHAR	WeatherString2[0x20]; //if empty no weather
/*0x334*/	FLOAT	WeatherChangeTime;
/*0x338*/	int		Climate;
/*0x33c*/	int		NPCAgroMaxDist; //the distance needed for an npc to lose agro after an attack
/*0x340*/	int		FilterID; //found in the teleport table
/*0x344*/	int		ZoneID;
/*0x348*/	int		ScriptNPCReceivedanItem;
/*0x34c*/	bool	bCheck;
/*0x350*/	int		ScriptIDSomething;
/*0x254*/	int		ScriptIDSomething2;
/*0x358*/	int		ScriptIDSomething3;
/*0x35c*/	bool	bNoBuffExpiration;//this is checked serverside so no, u cant and shouldn't set this if u value your account
/*0x360*/   int		LavaDamage; //before resists
/*0x364*/   int		MinLavaDamage; //after resists
/*0x368*/   bool	bDisallowManaStone; //can a manastone be used here?
/*0x369*/   bool	bNoBind;
/*0x36a*/   bool	bNoAttack;
/*0x36b*/   bool	bNoCallOfHero;
/*0x36c*/   bool	bNoFlux;
/*0x36d*/   bool	bNoFear;
/*0x36e*/   bool	bNoEncumber;
/*0x370*/   int		FastRegenHP;//not exactly sure how these work but ome zones have these set
/*0x374*/   int		FastRegenMana;
/*0x378*/   int		FastRegenEndurance;
/*0x37c*/   EPlace	CanPlaceCampsite;
/*0x380*/   EPlace	CanPlaceGuildBanner;
/*0x384*/   FLOAT	FogDensity;
/*0x388*/   bool	bAdjustGamma;
/*0x38c*/   int		TimeStringID;
/*0x390*/   bool	bNoMercenaries;
/*0x394*/   int		FishingRelated;
/*0x398*/   int		ForageRelated;
/*0x39c*/   bool	bNoLevitate;
/*0x3a0*/   FLOAT	Blooming;
/*0x3a4*/   bool	bNoPlayerLight;
/*0x3a8*/   int		GroupLvlExpRelated;
/*0x3ac*/   BYTE	PrecipitationType;
/*0x3ad*/   bool	bAllowPVP;
/*0x3b0*/
} ZONEINFO, *PZONEINFO;

typedef struct _SPELLCALCINFO
{
/*0x00*/	int Slot;
/*0x04*/	int Base;
/*0x08*/	int Base2;
/*0x0c*/	int Max;
/*0x10*/	int Calc;
/*0x14*/	int Attrib;
} SPELLCALCINFO,*PSPELLCALCINFO;

#define   TOTAL_SPELL_COUNT             0xF230     // # of spells allocated in memory (07/10/2019 test 4F1197) -eqmule
#define   CalcInfoSize                  0x324B0    // 67777A in eqgame 2019 10 Jul test
//this is actually the size of the struct thats populated from aSpells_S_txt
//SpellManager__SpellManager_x
// size: 0x1966A8 2017-04-11 test (see 55DC54) - eqmule
// size: 0x1AED40 2018-04-10 test (see 5D32E2) - eqmule
// size: 0x1BC800 2019-07-10 test (see 5E36C2) - eqmule
typedef struct _SPELLMGR {
/*0x000000*/ PVOID vfTable;//need this for some calls later
/*0x000004*/ BYTE Unknown0x00004[0x3DAE0];
/*0x03DAE4*/ struct _SPELL* Spells[TOTAL_SPELL_COUNT];//60000
/*0x07A3A4*/ struct _SPELL* PtrToUnknownSpell;//default bailout pointer...
/*0x07A3A8*/ struct _SPELLCALCINFO* CalcInfo[CalcInfoSize];//200000
/*0x143668*/ DWORD What1[0x6];
/*0x143680*/ DWORD What2[0x1E460];//124000
/*0x1BC800*/ //(1820672) 1.8 mill! large struct in memory for sure...
} SPELLMGR, *PSPELLMGR;

// actual size: 0x148 10-25-2006  ieatacid
// actual size: 0x148 04-11-2017 test confirmed see 5F7150 -eqmule
enum eSkillCombatType
{
	SCT_NonCombat,
	SCT_Combat,
	SCT_Special 
};
typedef struct _SKILL {
/*0x000*/  int    ImageNumber;
/*0x004*/  int	  ImageDep;
/*0x008*/  DWORD  nName;
/*0x00c*/  DWORD  ReuseTimer;
/*0x010*/  DWORD  BaseDamage;
/*0x014*/  eSkillCombatType  SkillCombatType;
/*0x018*/  int    EnduranceCost;
/*0x01c*/  FLOAT  Force;
/*0x020*/  bool   Activated;
/*0x021*/  bool   LevelCappedSkill;
/*0x024*/  DWORD  MinLevel[0x24];//the level each class gains this skill
/*0x0b4*/  DWORD  Available[0x24];   //FF=not available for that class (its actually how difficult it is to learn... low num easy, high hard...)
/*0x144*/  bool  bSkillupable;//thats not a real word...
/*0x148*/  
} SKILL, *PSKILL;

//see SkillManager__IsValidSkillIndex_x (5C87C0) in eqgame dated 20140611 -eqmule
//SkillManager__SkillManager
//Actual Size: 0x2C68AC see 5465F8 in eqgame dated 20140611 -eqmule
//Actual Size: 0x2E9B2C see 57FDB7 in eqgame dated 20170911 test -eqmule
//Actual Size: 0x3301CC see 5E747D in eqgame dated 20201219 -eqmule
typedef struct _SKILLMGR {
/*0x000000*/	struct _SKILL *pSkill[NUM_SKILLS];
/*0x000190*/	int SkillCaps[MAX_CLASSES+1][NUM_SKILLS][MAX_PC_LEVEL+1];
/*0x197E90*/	FLOAT SkillMods[MAX_CLASSES+1][NUM_SKILLS][MAX_PC_LEVEL+1];
/*0x32FB90*/	CHAR SkillCapsFilename[MAX_PATH];
/*0x32FC94*/	UINT Unknown0x32FC94[0x4];
/*0x32FCA4*/	struct _SKILL *pSkill2[NUM_SKILLS];//im absolutely not sure these are skills, but the struct fits here so...-eqmule
/*0x32FE34*/	UINT SkillLastUsed[NUM_SKILLS];
/*0x32FFC4*/	UINT SkillTimerDuration[NUM_SKILLS];
/*0x330154*/	UINT CombatSkillLastUsed[CONCURRENT_SKILLS];
/*0x33015C*/	UINT CombatSkillDuration[CONCURRENT_SKILLS];
/*0x330164*/	bool bSkillCanUse[NUM_SKILLS];
/*0x3301C8*/	bool bCombatSkillCanUse[CONCURRENT_SKILLS];
/*0x3301CC*/
} SKILLMGR, *PSKILLMGR;

typedef struct _AUTOSKILL {
	int Skill[CONCURRENT_SKILLS];
} AUTOSKILL, *PAUTOSKILL;

class SkillManager
{
public:
/*0x000000*/	TSafeArrayStatic<PSKILL, NUM_SKILLS> pSkill;
/*0x000190*/	int SkillCaps[MAX_CLASSES+1][NUM_SKILLS][MAX_PC_LEVEL+1];
/*0x197E90*/	FLOAT SkillMods[MAX_CLASSES+1][NUM_SKILLS][MAX_PC_LEVEL+1];
/*0x32FB90*/	CHAR SkillCapsFilename[MAX_PATH];
/*0x32FC94*/	UINT Unknown0x32FC94[0x4];
/*0x32FCA4*/	struct _SKILL *pSkill2[NUM_SKILLS];//im absolutely not sure these are skills, but the struct fits here so...-eqmule
/*0x32FE34*/	UINT SkillLastUsed[NUM_SKILLS];
/*0x32FFC4*/	UINT SkillTimerDuration[NUM_SKILLS];
/*0x330154*/	UINT CombatSkillLastUsed[CONCURRENT_SKILLS];
/*0x33015C*/	UINT CombatSkillDuration[CONCURRENT_SKILLS];
/*0x330164*/	bool bSkillCanUse[NUM_SKILLS];
/*0x3301C8*/	bool bCombatSkillCanUse[CONCURRENT_SKILLS];
/*0x3301CC*/
};

//actual size 0x3a8 11-15-11  ieatacid
//actual size ? last checked by rlane187 may 19 2015
typedef struct _GUILDMEMBERCLIENT {
	//Start of GuildMember
/*0x000*/ struct  _GUILDMEMBER *pNext;
/*0x004*/ bool    bOnline;
/*0x005*/ BYTE    Filler0x005[0x3];
/*0x008*/ WORD    ZoneID;
/*0x00a*/ WORD    Instance;
/*0x00C*/ DWORD	  PlayerSerial;
/*0x010*/ bool	  bMainProfile;
/*0x011*/ bool	  bOfflineMode;
/*0x012*/ CHAR	  Name[0x40];
/*0x052*/ BYTE	  Filler0x52[0x2];
/*0x054*/ int	  Level;
/*0x058*/ int	  Flags; //1=banker, 2=alt
/*0x05c*/ DWORD   Class;
/*0x060*/ DWORD   Rank; //0=member 1=officer 2=leader
/*0x064*/ CHAR	  PlayerHandle[0x20];
/*0x084*/ CHAR    PlayerComments[0x100];
/*0x184*/ DWORD   LastLoginTime;
/*0x188*/ EqGuid  PlayerGuild;//size is 8
/*0x190*/ bool    bGuildShowSprite;
/*0x191*/ bool    bTributeStatus;//active on/off
/*0x192*/ bool    bTrophyStatus;//active on/off
/*0x194*/ int     TributeDonations;
/*0x198*/ DWORD   LastDonation;//timestamp
/*0x19c*/ //end of GuildMember
//start of GuildMemberClient
/*0x1a0*/ CHAR    PublicNote[0x100];
/*0x2a0*/ CHAR    PersonalNote[0x100];
/*0x3a0*/ bool	  bTributeOptIn;
/*0x3a1*/ bool	  bTrophyTributeOptIn;
/*0x3a4*/
} GUILDMEMBERCLIENT,*PGUILDMEMBERCLIENT;

typedef struct _GUILDDATA
{
/*0x00*/ char   Name[0x40];
/*0x04*/ DWORD  ID;
/*0x08*/
} GUILDDATA, *PGUILDDATA;

typedef struct _GUILD
{
/*0x00*/ CHAR   Name[0x40];
/*0x04*/ DWORD  ID;//maybe this is just a int64 now, not sure needs more investigation.
/*0x08*/ DWORD  ID2;
/*0x0c*/ struct _GUILD *pNext;
/*0x10*/ struct _GUILD *pPrev;
/*0x14*/
} GUILD, *PGUILD;

// 11-15-11 - ieatacid
//aUnknownGuild the offset below is the guild vftable
// 2016 Oct 11 beta - eqmule (see AB50E4) not sure on size needs more investigation
typedef struct _GUILDS {
/*0x0000*/ PVOID    pOneEntryVTable;
/*0x0004*/ BYTE     Unknown0x4[0x4];
/*0x0008*/ DWORD    GuildMemberCount;
/*0x000c*/ struct   _GUILDMEMBER *pMember;
/*0x0010*/ BYTE     Unknown0x10[0x51];
/*0x0061*/ CHAR     GuildMotD[0x200];
/*0x0261*/ CHAR     GuildLeader[0x40];
/*0x02a1*/ BYTE     Unknown0x2a1[0x3];
/*0x02a4*/ DWORD    GuildTribute;
/*0x02a8*/ BYTE     Unknown0x2a8[0x8dc1];
/*0x9069*/ CHAR     GuildUrl[0x200];
/*0x9269*/ CHAR     GuildChannelName[0x80];
/*0x92e9*/ BYTE     Unknown0x9e9[0x2f];
/*0x9310*/ PGUILD pFirst;
/*0x9314*/ PGUILD pLast;
/*0x9318*/ UINT     GuildListCount;
/*0x931C*/ DWORD    Empty;
/*0x9320*/ struct _GUILD *GuildList;
/*0x9320*/ DWORD    HashValue;
/* more data */
} GUILDS, *PGUILDS;

typedef struct _INTERACTGROUNDITEM {
    DWORD DropID;
    DWORD SpawnID;
} INTERACTGROUNDITEM, *PINTERACTGROUNDITEM;

typedef struct _SPELLFAVORITE {
/*0x000*/   DWORD   SpellId[NUM_SPELL_GEMS];
/*0x030*/   CHAR    Name[0x19];
/*0x049*/   BYTE    inuse;
/*0x04a*/   BYTE    Byte_0x4a;
/*0x04b*/   BYTE    Byte_0x4b;
/*0x04c*/
} SPELLFAVORITE, *PSPELLFAVORITE;

typedef struct _CMDLIST {
    DWORD LocalizedStringID;
    PCHAR szName;
    PCHAR szLocalized;
    VOID  (__cdecl *fAddress)(PSPAWNINFO, PCHAR);
    DWORD Restriction;
    DWORD Category;
    DWORD Flags;
} CMDLIST, *PCMDLIST;

typedef struct _EQSOCIALCHANGED
{
	bool bChanged[10][12];
} EQSOCIALCHANGED, *PEQSOCIALCHANGED;

typedef struct _EQSOCIAL {
/*0x0000*/	CHAR	Name[0x10];
/*0x0010*/	CHAR	Line[0x5][0x100];
/*0x0510*/	BYTE	Color;
/*0x0514*/	UINT	TimerBegin;
/*0x0518*/	UINT	TimerDuration;
/*0x051C*/
} EQSOCIAL, *PEQSOCIAL;

typedef struct _EQFRIENDSLIST {
/*0x0000*/ CHAR Name[0x64][0x40];
/*0x1900*/
} EQFRIENDSLIST, *PEQFRIENDSLIST;

typedef struct _AAEFFECTDATA
{
/*0x00*/	int EffectType;
/*0x00*/	int BaseEffect1;
/*0x00*/	int BaseEffect2;
/*0x00*/	int Slot;
} AAEFFECTDATA,*PAAEFFECTDATA;

// Size 0xa4    11/15/2011 ieatacid in msg_send_alt_data
// Size 0xa8    06/11/2014 eqmule in msg_send_alt_data
// Size 0xa8    See 4EF12F (msg_send_alt_data) in 2015-09-24 -eqmule
typedef struct _ALTABILITY {
	/*0x00*/ DWORD Index;
	/*0x04*/ bool bShowInAbilityWindow;					//[0] = enabled flag? everything 1
	/*0x05*/ BYTE bShowInAbilityWindowdPadding[0x3];
	/*0x08*/ DWORD nShortName;
	/*0x0c*/ DWORD nShorterName;
	/*0x10*/ DWORD nName;					// now a database number
	/*0x14*/ DWORD nDesc;					// now a database number
	/*0x18*/ DWORD MinLevel;				//LevelNeeded
	/*0x1c*/ DWORD Cost;					//Initial Cost or cost the last time you bought a level of it
	/*0x20*/ DWORD ID;					//ID of the AA group (/alt activate id)
	/*0x24*/ DWORD CurrentRank;				// GroupLevel the current rank of this AA first rank is 1 etc
	/*0x28*/ DWORD *RequiredGroups;		    // array of required groups
	/*0x2c*/ DWORD *RequiredGroupLevels;	// array of required group ID;
	/*0x30*/ DWORD Unknown0x30[2];			// ArrayClass stuff
	/*0x38*/ DWORD prereq_count2;			// count of next array, which contains rank required
	/*0x3c*/ DWORD *RequiresAbilityPoints;	//this is part of their ArrayClass
	/*0x40*/ DWORD Unknown0x40;				// ArrayClass stuff
	/*0x44*/ DWORD pointer;					// ArrayClass stuff
	/*0x48*/ DWORD Type;					// 1 General 2 Archetype 3 Class 4 special 5 focus
	/*0x4c*/ int  SpellID;					// -1 for no Spell
	/*0x50*/ DWORD Unknown0x50;
	/*0x54*/ DWORD Unknown0x54;				// this uses the same class as prereqs, so count?
	/*0x58*/ DWORD *reuse_id;
	/*0x5c*/ bool  bRefund;
	/*0x5d*/ BYTE  bRefundPadding[0x3];
	/*0x60*/ DWORD *TimerIds;				//ArrayClass of timer ids starts here
	/*0x64*/ DWORD ReuseTimer;				// in seconds
	/*0x68*/ DWORD Classes;					// Classes/2 is the actual value we want.
	/*0x6c*/ DWORD MaxRank;					//so like x/25, this is the 25	
	/*0x70*/ DWORD TotalPoints;				
	/*0x74*/ DWORD PreviousGroupAbilityId;	// -1 if none, although sometimes it can be -1 when there is ...
	/*0x78*/ DWORD NextGroupAbilityId;		// ID of the next rank
	/*0x7C*/ bool QuestOnly;				// vet AA, quest AA
	/*0x7D*/ BYTE QuestOnlypadding[0x3];
	/*0x80*/ DWORD max_charges;				// charges on expendable AAs (limited use aa's)
	/*0x84*/ BOOL bIgnoreDeLevel;
	/*0x88*/ DWORD Expansion;
	/*0x8c*/ DWORD special_category;		// 7 is expendable, -1 none
	/*0x90*/ bool bShroud;					//shrouds are also called "templates"
	/*0x91*/ bool bBetaOnlyAbility;
	/*0x92*/ bool bResetOnDeath;			// true for lay on hands for example.
	/*0x93*/ bool bAutogrant;				// true if its an autogrant ability? or if auto grant is enabled? need to check cause this could be useful
	/*0x94*/ DWORD AutoGrantAssociationId;		// Usually the same as normal expansion if enabled
	//this is where a list of Ability Effect Data starts in the packet
	/*0x98*/ DWORD effects_count;			// Count of spell effects for AA
	/*0x9c*/ DWORD **effects;				// this is repeated a few times some times depending on list size
	/*0xA0*/ BYTE Unknown0xA0[0x8];			//part of their internal list class, I need to re that at some point
	/*0xa8*/
} ALTABILITY, *PALTABILITY;

typedef struct _ALTABILITIESLISTMGR {
/*0x00*/ struct _ALTABILITY* Ability;
/*0x04*/ DWORD Index;
} ALTABILITIESLISTMGR, *PALTABILITIESLISTMGR;

//NUM_ALT_ABILITIES is now defined before CHARINFO definition in this same header file.
typedef struct _ALTABILITIESLIST {
/*0x00*/ struct _ALTABILITIESLISTMGR* Abilities[NUM_ALT_ABILITIES_ARRAY];
} ALTABILITIESLIST, *PALTABILITIESLIST;

typedef struct _NEWALTADVMGR {
/*0x00*/ struct _ALTABILITIESLIST* AltAbilityList;
/*0x04*/ DWORD NumAltAbilities;  // NUM_ALT_ABILITIES
/*0x08*/ DWORD Unknown0x08; // data here
/*0x0c*/ DWORD Unknown0x0c; // data here
/*0x10*/ BYTE  Unknown0x10[0x8];
} NEWALTADVMGR, *PNEWALTADVMGR;

typedef struct _ALTADVMGR {
/*0x00*/ struct _NEWALTADVMGR* AltAbilities;
} ALTADVMGR, *PALTADVMGR;

typedef struct _MERCAADATA {
/*0x00*/ DWORD nName;//I would guess we can find aapoints spent on the ability in this struct as well
} MERCAADATA,*PMERCAADATA;//but I dont know yet, I dont have a mercenary with aa yet... -eqmule

typedef struct _MERCAA {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD Unknown0x04;
/*0x08*/ struct _MERCAADATA *Ptr;
/*0x0c*/ DWORD Unknown0x00c;
/*0x10*/ DWORD Max;//how many AA can be spent on this ability
} MERCAA, *PMERCAA;

//pinstMercAltAbilities_x
//MercAltAbilities__MercAltAbilities
//Actual Size: 0x478 in eqgame dated oct 04 2013 (see 4A96D4) - eqmule 
typedef struct _EQMERCALTABILITIES {
/*0x000*/ BYTE Unknown0x000[0x408];
/*0x408*/ PMERCAA MercAAInfo[0xc];//12 pointers since there are currently only 12 mercenary aa's
/*0x438*/ BYTE Unknown0x438[0x40];
/*0x478*/
} EQMERCALTABILITIES, *PEQMERCALTABILITIES;

// size 0x98 (3-12-2014) -eqmule
// size 0x9c 3-18-2015 test see (49A077) -eqmule
typedef struct _EQRAIDMEMBER { 
/*0x000*/ CHAR      Name[0x40]; 
/*0x040*/ CHAR      RaidNote[0x40]; 
/*0x080*/ DWORD     nLevel;
/*0x084*/ DWORD     nClass; 
/*0x088*/ BYTE      RaidLeader; 
/*0x089*/ BYTE      GroupLeader; 
/*0x08a*/ BYTE      RaidMainAssist;
/*0x08b*/ BYTE      RaidMarker;
/*0x08c*/ DWORD     MasterLooter;
/*0x090*/ DWORD     GroupNumber;
/*0x094*/ BYTE      Unknown0x94[0x8];//i guess new master looter is in here...
/*0x09c*/ 
} EQRAIDMEMBER, *PEQRAIDMEMBER;

// sizeof(_EQRAID) is 0x3668 (12-09-2009)
//is size calculated by doing instCGuild_x - 4 - instCRaid_x ? 366C
//0x3668 is locked so if its 4 byte aligned size should be /*0x366c*/ - eqmule Aug 10 2016
//instCRaid_x
// push    13C6h
//mar 18 2015 Test CRaid__ResetRaid eqgame.exe - eqmule
//as for the size... I have no idea...
//maybe 3544h? see 48055F                 mov     [esi+3544h], bl (jun 11 2014) -eqmule
//392C in mar 18 205 test? not sure...
typedef struct _EQRAID {
/*0x0000*/ BYTE     Unknown0x0000[0xe0];
/*0x00e0*/ CHAR     RaidMemberUsed[0x48];
/*0x0128*/ struct   _EQRAIDMEMBER RaidMember[0x48];
/*0x2d08*/ BYTE     Unknown0x2d08[0x4];
/*0x2d0c*/ DWORD    RaidMemberCount;
/*0x2d10*/ CHAR     RaidLeaderName[0x40];
/*0x2d50*/ CHAR     RaidMOTD[0x400];
/*0x3150*/ CHAR     Inviter[0x40];
/*0x3190*/ int      Invited; // this is an enum, 1 = not in raid, 2 = invited, 4 = in raid
/*0x3194*/ UINT		RaidID;//not sure
/*0x3198*/ bool		bCreateRaidInvite;
/*0x3199*/ bool     IsRaidLeader;
/*0x319a*/ BYTE     Filler0x319a[0x2];
/*0x319c*/ DWORD    RaidTarget;
/*0x31a0*/ DWORD    LootType;
/*0x31a4*/ CHAR     RaidLooters[0x13][0x40];
/*0x3664*/ DWORD    TotalRaidMemberLevels; // TotalRaidMemberLevels/RaidMemberCount=RaidAvgLevel
/*0x3668*/ BYTE     Locked;
/*0x3669*/ BYTE     Unknown0x3669[0x7];
/*0x3670*/ // <- im sure this is not right but whatever... we got what we came for...
} EQRAID, *PEQRAID;

// size 0x19C 3-23-2005
typedef struct _EQGROUP {
/*0x000*/ BYTE MemberExists[5];
/*0x005*/ CHAR MemberName[5][0x40];
/*0x145*/ BYTE Unused[3];
/*0x148*/ struct _SPAWNINFO* pMember[5];
/*0x15C*/ CHAR LeaderName[0x40];
/*0x19C*/
} EQGROUP, *PEQGROUP;

// size 0x08
typedef struct _EQSTRING {
/*0x00*/    DWORD ID;
/*0x04*/    PCHAR String;
} EQSTRING, *PEQSTRING;

// size 0x10 4-28-2004 lax
typedef struct _EQSTRINGTABLE {
/*0x00*/ struct _EQSTRING **StringItems;
/*0x04*/ DWORD Size;
/*0x08*/ DWORD Count;
/*0x0c*/ DWORD Unknown0x0c;
/*0x10*/
} EQSTRINGTABLE, *PEQSTRINGTABLE;

//updated by eqmule
//see 7B000C in eqgame.exe dated jul 16 2014
//not sure about size... oh and this is __gWorld_x
typedef struct connection_t {
/*0x000*/ void  *vtable;
/*0x004*/ BYTE  Unknown0x4[0x110];
/*0x114*/ DWORD Master;
/*0x118*/ DWORD Average;
/*0x11c*/ DWORD Low;
/*0x120*/ DWORD High;
/*0x124*/ DWORD Last;
/*0x128*/
} CONNECTION_T, *PCONNECTION_T;

//actual size 0x2dfc 3-19-09 - ieatacid 
typedef struct _CDISPLAY {
/*0x0000*/ BYTE   Unknown0x000[0x12c];
/*0x012c*/ void   *pActorTagManager;
/*0x0130*/ BYTE   Unknown0x130[0x24];
/*0x0154*/ DWORD  TimeStamp;
/*0x0158*/ BYTE   Unknown0x158[0x2c12];
/*0x2d6a*/ BYTE   NpcNames; // show npc names
} CDISPLAY, *PCDISPLAY;

typedef struct _DZTIMERINFO {
/*0x000*/ CHAR   ExpeditionName[0x80];
/*0x080*/ CHAR   EventName[0x100];
/*0x180*/ DWORD  TimeStamp;  // TimeStamp - Util__FastTime = time left
/*0x184*/ DWORD  TimerID;
/*0x188*/ struct _DZTIMERINFO *pNext;
/*0x18c*/
} DZTIMERINFO, *PDZTIMERINFO;

//Size 0x4c see 553F87 in Nov 19 2019 Beta -eqmule
typedef struct _DZMEMBER {
/*0x000*/ CHAR			Name[0x40];
/*0x040*/ DWORD			Status;  // 0="unknown", 1="Online", 2="Offline", 3="In Dynamic Zone", 4="Link Dead"
/*0x044*/ struct _DZMEMBER*		pNext;
/*0x048*/ bool bFlagged;//do we meet zonereqs?
/*0x049*/ bool bCheckedZoneReqs;//zone reqs serverside checked?
/*0x04c*/ 
} DZMEMBER, *PDZMEMBER;

//Shared Task Member Info
typedef struct _TASKMEMBER {
/*0x000*/ CHAR   Name[0x40];
/*0x040*/ DWORD  ShroudID;
/*0x044*/ DWORD  IsLeader;//Role, 0 none 1 leader it really should be an enum
/*0x048*/ struct _TASKMEMBER *pNext;
/*0x04c*/
} TASKMEMBER, *PTASKMEMBER;

typedef struct _DZSWITCHINFO
{
/*0x000*/ int	DZID;
/*0x004*/ int	Type;
/*0x008*/ int	DZSwitchID;
/*0x00c*/ float	SwitchX;
/*0x010*/ float	SwitchY;
/*0x014*/ float	SwitchZ;
/*0x018*/ 
} DZSWITCHINFO, *PDZSWITCHINFO;

typedef struct _DZCOMPASS
{
/*0x000*/ int	R;
/*0x004*/ int	G;
/*0x008*/ int	B;
/*0x00c*/ float	X;
/*0x010*/ float	Y;
/*0x014*/ float	Z;
/*0x018*/ bool	bVisible;
/*0x01c*/ int	PixelOffset;
/*0x020*/ bool	bInWindow;
/*0x024*/ 
} DZCOMPASS, *PDZCOMPASS;

typedef struct _DZSWITCH : _DZSWITCHINFO
{
/*0x000*/ struct _DZCOMPASS*	pCompass;
} DZSWITCH, *PDZSWITCH;

//CDynamicZone size: 0x128
typedef struct _DYNAMICZONE {
/*0x000*/ void*					vftable;
/*0x004*/ UINT					NewMemberDZID;
/*0x008*/ CHAR					NewMemberName[0x40];
/*0x048*/ bool					bNewSwap;
/*0x049*/ bool					bNewAssignedToDZ;
/*0x04a*/ CHAR					LeaderName[0x40];
/*0x08a*/ CHAR					DZName[0x80];
/*0x10C*/ int					MaxPlayers;
/*0x110*/ PDZMEMBER				pFirstMember;
/*0x114*/ PDZTIMERINFO			pFirstTimer;
/*0x118*/ HashTable<DZSWITCH>	Switches;
/*0x128*/

	//ALT_MEMBER_GETTER(CHAR, LeaderName, Name);
	//ALT_MEMBER_GETTER(CHAR, DZName, ExpeditionName);
	//ALT_MEMBER_GETTER(PDZMEMBER, pFirstMember, pMemberList);
} DYNAMICZONE, *PDYNAMICZONE;

typedef struct _CHATCHANNELS {
/*0x000*/ PCHAR  ChannelName[0xa];
/*0x004*/
} CHATCHANNELS, *PCHATCHANNELS;

enum eFriendStatus
{
	eFriendRemoved,
	eFriendOffline,
	eFriendOnline,
	eFriendOnlineAway,
	eFriendOnlineInvisible,
	eFriendInGame,
	eFriendInGameAway,
	eFriendInGameInvisible
};

struct FriendEntry
{
	CHAR Name[0x30];
	eFriendStatus Status;
	bool bName;//not sure.
};
typedef struct _CHATSERVICE {
/*0x000*/ PVOID vfTable;
/*0x004*/ PVOID pChatProxyHandler;
/*0x008*/ PVOID pUdpManager;
/*0x00c*/ struct _CHATCHANNELS *ChannelList;//really just a char**
/*0x010*/ DWORD  ActiveChannels;   // number of channels joined, aka channelcount
/*0x014*/ bool mAuthenticated;
/*0x015*/ bool bLoginSent;
/*0x016*/ bool bInvisible;
/*0x017*/ bool bFullNotifyMode;
/*0x018*/ void *UdpConnection;
/*0x01c*/ CHAR ChatID[0x30];     // "ServerName.CharName"
/*0x04c*/ CHAR ChatPass[0x30];
/*0x07c*/ CHAR ServerName[0x30]; // "ServerName."
/*0x0ac*/ int ServerNameLen;
/*0x0b0*/ CHAR Locale[0x10];
/*0x0c0*/ const char *ChatPrefix;
/*0x0c4*/ int LastDisconnectCheckTime;
/*0x0c8*/ FriendEntry **BuddyList;
/*0x0cc*/ int BuddyListCount;
/*0x0d0*/ ArrayClass_RO<PCXSTR> IgnoreList;
/*0x0e0*/
} CHATSERVICE, *PCHATSERVICE;

class PickZoneTimerHandler
{
public:
	struct PickZoneRecord {
		PCXSTR ZoneName;
		int Time;
	};
	EQArray<PickZoneRecord> Records;
};
typedef struct _PETITIONSTATUS{
/*0x00*/ int ID;
/*0x04*/ int Priority;//todo: check
/*0x08*/ int State;//todo: figure out.
/*0x0c*/ DWORD ArrivalTime;
/*0x10*/ CHAR User[0x20];
/*0x30*/ CHAR Player[0x40];
/*0x70*/ int NumActive;
/*0x74*/ CHAR Player2[0x40];
/*0xb4*/ DWORD TimeStamp;//not sure what its for
/*0xb8*/
} PETITIONSTATUS,*PPETITIONSTATUS;

//size is 0x170 see 4467A5 in Sep 18 2017 Live
typedef struct _CSINFO
{
/*0x000*/ CHAR Name[0x40]; 
/*0x040*/ int Class;
/*0x044*/ int Race;
/*0x048*/ BYTE Level; 
/*0x04c*/ int Class2;
/*0x050*/ int Race2;
/*0x054*/ int CurZoneID; 
/*0x058*/ BYTE Sex; 
/*0x059*/ BYTE Face; 
/*0x05c*/ ArmorProperties ArmProp[9]; //size /*0x14*/ * 9 = 0xB4
/*0x110*/ DWORD Tint[9]; //size 0x24
/*0x134*/ CHAR TextureType;
/*0x135*/ CHAR ArmorMaterial;
/*0x136*/ CHAR ArmorVariation;
/*0x137*/ CHAR HeadType;
/*0x138*/ int TattooIndex;
/*0x13c*/ int FacialAttachmentIndex;
/*0x140*/ int Deity; 
/*0x144*/ int PrimActor; 
/*0x148*/ int SecdActor; 
/*0x14c*/ BYTE HairColor;
/*0x14d*/ BYTE BeardColor;
/*0x14e*/ BYTE LeftEye;
/*0x14f*/ BYTE RightEye;
/*0x150*/ BYTE Hair;
/*0x151*/ BYTE Beard;
/*0x152*/ bool bCanGoHome;
/*0x153*/ bool bCanTutorial;
/*0x154*/ int ParentId;
/*0x158*/ bool bTooHighLevel;
/*0x159*/ bool bPreFTP;
/*0x15c*/ long SomethingLogin;
/*0x160*/ bool bUseable;
/*0x161*/ bool bHeroicCharacter;
/*0x162*/ bool bShrouded;
/*0x164*/ int Unknown0x164;
/*0x168*/ int Unknown0x168;
/*0x16c*/ int Unknown0x16c;
/*0x170*/ 
} CSINFO, *PCSINFO;

typedef struct _CharSelectPlayerArray
{
	//note that CharSelectPlayerCount determines how many are actully here
	CSINFO CharacterInfo[13];//is 13 chars the max u can have?
} CharSelectPlayerArray,*PCharSelectPlayerArray;

typedef struct _EVERQUEST {
/*0x000*/ BYTE   Unknown[0x2a4];
/*0x2a4*/ struct _CHATSERVICE *ChatService;
/*0x2a8*/ BYTE   Unknown0x2a8[0x8];
/*0x2b0*/ bool   bJoinedChannel;
/*0x2b1*/ CHAR   ChannelPlayerName[0x100];
/*0x3b1*/ CHAR   ChannelName[0xa][0x30];
/*0x591*/ BYTE   Unknown0x591[0x3];
/*0x594*/ DWORD  ChannelNumber[0xa];
/*0x5bc*/ int  ChannelQty;
/*0x5c0*/ void *pFreeTargetRing;//PTARGETRING
/*0x5c4*/ DWORD	 WorldState;//0 everything is fine, 1 we are getting disconnected 2 player not released from zone
/*0x5c8*/ DWORD  GameState;
/*0x5cc*/ bool	bStopAreaProcessing;
/*0x5cd*/ bool	bRAFEnabled;
/*0x5d0*/ __int64	ServerTimeSync;
/*0x5d8*/ __int64	ServerTimeBase;
/*0x5e0*/ __int64	ServerTimeLastReported;
/*0x5e8*/ bool	bServerTimeHasWrapped;
/*0x5ec*/ FLOAT	TargetCameraDistance;
/*0x5f0*/ bool	bUnknown0x5f0;
/*0x5f4*/ int	TotalCharacterSlots;
/*0x5f8*/ int	MarketplaceCharacterSlots;
/*0x5fc*/ int	Unknown0x5fc;
/*0x600*/ void*	CampDialog;//CPopDialogWnd
/*0x604*/ PickZoneTimerHandler pickZoneTimerHandler;//size 0x10?
/*0x614*/ USINGSKILL	UsingSkill;//size 0x8
/*0x61c*/ PETITIONSTATUS	PetitionStatus[0x200];// size 0xb8 * 0x200 = 0x17000
/*0x1761c*/ int	TotalQ;//see 760EE8 in Sep 18 2017
/*0x17620*/ int	TotalClientPetitions;
/*0x17624*/ CHAR	ChatText[0x840];
/*0x17e64*/ int	TrimIdx;//correct
/*0x17e68*/ CHAR ChatChanged;//1 or 0?
/*0x17e69*/ CHAR Trim[0x40][0x840];//correct. size 0x40*0x840= 0x21000
/*0x38E6c*/ BOOL bChat;
/*0x38E70*/ int Unknown0x38E70;
/*0x38E74*/ int	Red;//for sure see 564105 in spe 18 2017 exe
/*0x38E78*/ int	Green;
/*0x38E7c*/ int Blue;
/*0x38E80*/ ArrayClass_RO<CSINFO> pCharSelectPlayerArray;
/*0x38E88*/ // more data
} EVERQUEST, *PEVERQUEST;

typedef struct _AURAINFO {
/*0x000*/ CHAR    Name[0x40];
/*0x040*/ unsigned int     SpawnID;
/*0x044*/ int     Cost;
/*0x048*/ int     IconnID;
/*0x04c*/
} AURAINFO, *PAURAINFO;

typedef struct _AURAS {
/*0x000*/ _AURAINFO Aura[0x2];
} AURAS, *PAURAS;

typedef struct _AURAMGR {
/*0x000*/ DWORD   NumAuras;
/*0x004*/ BYTE    Unknown0x4[0xc];
/*0x010*/ _AURAS  **pAuraInfo;
/*0x014*/ BYTE    Unknown0x14[0x8];
/*0x01c*/
} AURAMGR, *PAURAMGR;

typedef struct _INTERACTSWITCH {
/*0x000*/ DWORD   switchID;
/*0x004*/ DWORD   dwzero;
/*0x008*/ DWORD   dwneg1;
/*0x00c*/ DWORD   spawnID;
} INTERACTSWITCH, *PINTERACTSWITCH;

typedef struct _MERCSTANCEDATA {
DWORD nStance;
DWORD nDbStance;
} MERCSTANCEDATA, *PMERCSTANCEDATA;

typedef struct _MERCSINFO {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD nMercCategory;
/*0x08*/ DWORD nMercDesc;
/*0x0c*/ DWORD Purchase; //in copper...
/*0x10*/ DWORD Upkeep; //in copper...
/*0x14*/ BYTE Unknown0x14[0x2c];
/*0x40*/ CHAR Name[0xC];
/*0x4c*/ BYTE Unknown0x4c[0x88];
/*0xD4*/
} MERCSINFO, *PMERCSINFO;
//Size 0xD4 in eqgame.exe dated 01 22 2015 -eqmule
typedef struct _MERCSLIST {
/*0x00*/ MERCSINFO mercinfo[7];//is 7 max, even with slots u can buy for sc?
} MERCSLIST, *PMERCSLIST;

//Actual Size: 0x2fc (See 57117F in eqgame dated dec 10 2013) - eqmule
//CMercenaryInfo__CMercenaryInfo
typedef struct _MERCENARYINFO {
/*0x000*/ BYTE Unknown0x0[0x110];
/*0x110*/ DWORD HaveMerc;
/*0x114*/ DWORD MercState; // 1 = suspended, 5 = active
/*0x118*/ BYTE  Unknown0x118[0x30];
/*0x148*/ DWORD ActiveStance;
/*0x14c*/ BYTE  Unknown0x14c[0x10];
/*0x15c*/ CHAR	MercName[0x18];
/*0x174*/ BYTE  Unknown0x174[0x7c];
/*0x1F0*/ DWORD MercenaryCount;//how many mercenaries we have
/*0x1F4*/ PMERCSLIST pMercsList; 
/*0x1F8*/ BYTE  Unknown0x1f8[0xc];
/*0x204*/ DWORD MaxMercsCount;//max you can have
/*0x208*/ BYTE  Unknown0x208[0x10];
/*0x218*/ DWORD CurrentMercIndex;
/*0x21c*/ BYTE  Unknown0x21c[0x8];
/*0x224*/ DWORD MercSpawnId;//yes its the spawnID of the mercenary
/*0x228*/ BYTE  Unknown0x228[0x30];
/*0x258*/ DWORD NumStances;
/*0x25c*/ _MERCSTANCEDATA **pMercStanceData;
/*0x260*/ BYTE  Unknown0x260[0x9c];
/*0x2Fc*/
} MERCENARYINFO, *PMERCENARYINFO;

typedef struct _MERCENARYSTATS {
/*0x000*/ DWORD MaxHP; 
/*0x004*/ DWORD CurrHP; 
/*0x008*/ DWORD MaxMana; 
/*0x00c*/ DWORD CurrMana; 
/*0x010*/ DWORD MaxEndurance; 
/*0x014*/ DWORD CurrEndurance; 
/*0x018*/ DWORD AC; 
/*0x01c*/ DWORD Attack; 
/*0x020*/ DWORD Haste; 
/*0x024*/ DWORD STR; 
/*0x028*/ DWORD STA; 
/*0x02c*/ DWORD INT; 
/*0x030*/ DWORD WIS; 
/*0x034*/ DWORD AGI; 
/*0x038*/ DWORD DEX; 
/*0x03c*/ DWORD CHA; 
/*0x040*/ DWORD CombatHPRegen; 
/*0x044*/ DWORD CombatManaRegen; 
/*0x048*/ DWORD CombatEnduranceRegen; 
/*0x04c*/ DWORD HealAmount; 
/*0x050*/ DWORD SpellDamage; 
/*0x054*/ 
} MERCENARYSTATS, *PMERCENARYSTATS;

#define MAX_XTARGETS 20

enum xTargetTypes
{
    XTARGET_EMPTY_TARGET,
    XTARGET_AUTO_HATER,
    XTARGET_SPECIFIC_PC,
    XTARGET_SPECIFIC_NPC,
    XTARGET_TARGETS_TARGET,
    XTARGET_GROUP_TANK,
    XTARGET_GROUP_TANKS_TARGET,
    XTARGET_GROUP_ASSIST,
    XTARGET_GROUP_ASSIST_TARGET,
    XTARGET_GROUP_PULLER,
    XTARGET_GROUP_PULLER_TARGET,
    XTARGET_GROUP_MARK1,
    XTARGET_GROUP_MARK2,
    XTARGET_GROUP_MARK3,
    XTARGET_RAID_ASSIST1,
    XTARGET_RAID_ASSIST2,
    XTARGET_RAID_ASSIST3,
    XTARGET_RAID_ASSIST1_TARGET,
    XTARGET_RAID_ASSIST2_TARGET,
    XTARGET_RAID_ASSIST3_TARGET,
    XTARGET_RAID_MARK1,
    XTARGET_RAID_MARK2,
    XTARGET_RAID_MARK3,
    XTARGET_MY_PET,
    XTARGET_MY_PET_TARGET,
    XTARGET_MY_MERCENARY,
    XTARGET_MY_MERCENTARY_TARGET
};

typedef struct _AGGRODATA {
/*0x00*/ DWORD Unknown0x0;
/*0x04*/ BYTE  AggroPct;
/*0x05*/ BYTE  padding[3];
/*0x08*/
} AGGRODATA, *PAGGRODATA;

// size 0xe4 11-28-12 - ieatacid (in GetAggroInfo)
// size 0xfc see 422F94 in 20 Aug 2015 -eqmule
typedef struct _AGGROINFO {
/*0x00*/ struct _AGGRODATA aggroData[0x1e];
/*0xf0*/ DWORD  AggroLockID;//this can be 0, I dont know what it is... -eqmule
/*0xf4*/ DWORD  AggroTargetID;//this is id of whoever we are fighting -eqmule
/*0xf8*/ DWORD  AggroSecondaryID;//this is id of whoever the npc is fighting -eqmule
/*0xfc*/
} AGGROINFO, *PAGGROINFO;

enum AggroDataTypes
{
    AD_Player,
    AD_Secondary,
    AD_Group1,
    AD_Group2,
    AD_Group3,
    AD_Group4,
    AD_Group5,
    AD_xTarget1,
    AD_xTarget2,
    AD_xTarget3,
    AD_xTarget4,
    AD_xTarget5,
    AD_xTarget6,
    AD_xTarget7,
    AD_xTarget8,
    AD_xTarget9,
    AD_xTarget10,
    AD_xTarget11,
    AD_xTarget12,
    AD_xTarget13,
    AD_xTarget14,
    AD_xTarget15,
    AD_xTarget16,
    AD_xTarget17,
    AD_xTarget18,
    AD_xTarget19,
    AD_xTarget20,
};
//eqmule 2013
typedef struct _GROUPAGGRO {
/*0x00*/ DWORD Unknown0x00;
/*0x04*/ DWORD Unknown0x04;
/*0x08*/ DWORD  GroupMemberAggro[6];//player is ALWAYS the 6th member...
} GROUPAGGRO, *PGROUPAGGRO;

#define EQ_ASSIST_CALC                  0x020c0f19
#define EQ_ASSIST_COMPLETE              0x4F2A   // aMsgTimeStampRe
#define EQ_ASSIST                       0x64BC   // do_assist(PlayerClient *,char const *)+399 20160212 live (see 52C319)
#define EQ_LoadingS__ArraySize          0x5a     // EQ_LoadingS__SetProgressBar_x+76 	(4C7396 yes it says 5b there, but we dont want to overwrite the NULL term...	2016 Apr 21
};
using namespace EQData;
#pragma pack(pop)

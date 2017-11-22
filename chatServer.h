#pragma once
#include "packet.h"
#include "ctlServer.h"

#define CHAT_SERVER_MAX_USER 5000
#define SERVER_NAME_LENGTH 10

// Login Amutios Lobby and Game Lobby
#define OPCODE_AMULTIOS_CHAT_LOGIN 13
// Login Group Lobby
#define OPCODE_AMULTIOS_CHAT_CONNECT_GAME 14
#define OPCODE_AMULTIOS_CHAT_CONNECT_GROUP 15
#define OPCODE_AMULTIOS_CHAT_DISCONNECT_GROUP 16
#define OPCODE_GAME_CHAT 17

//server name + group name to make virtual room
#define CHAT_GROUPNAME_LENGTH 18
typedef struct ChatGroupName {
	uint8_t data[CHAT_GROUPNAME_LENGTH];
} PACK ChatGroupName;


struct CTL_SERVER_INFO {
	int serverPort;
	char serverName[SERVER_NAME_LENGTH];
};

// C2S Chat Login Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetEtherAddr mac;
	SceNetAdhocctlNickname name;
	char server[SERVER_NAME_LENGTH];
	char pin[PIN_LENGTH];
	uint8_t enableGlobal;
	uint8_t enableGame;
} PACK ChatLoginPacketC2S;

typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetAdhocctlProductCode game;
}PACK ChatConnectGamePacketC2S;

// C2S Connect Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	ChatGroupName group;
} PACK ChatConnectPacketC2S;

// C2S Disconnect Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
} PACK ChatDisconnectPacketC2S;


typedef struct
{
	// PSP MAC Address
	SceNetEtherAddr mac;

	// PSP Hotspot IP Address
	uint32_t ip;
	uint16_t port;
	// PSP Player Name
	SceNetAdhocctlNickname name;

	uint8_t enableGlobal;
	uint8_t enableGame;

} ChatResolverInfo;
// Type Prototypes
typedef struct ChatGameNode ChatGameNode;
typedef struct ChatGroupNode ChatGroupNode;

// Double-Linked User List
typedef struct ChatUserNode {
	// Next Element
	struct ChatUserNode * next;

	// Previous Element
	struct ChatUserNode * prev;

	// Next Element (Group)
	struct ChatUserNode * group_next;

	// Previous Element
	struct ChatUserNode * group_prev;

	// Resolver Information
	ChatResolverInfo resolver;

	// Game Link
	ChatGameNode * game;

	// Group Link
	ChatGroupNode * group;

	// TCP Socket
	int stream;

	// Server Info
	char server[SERVER_NAME_LENGTH];
	uint8_t dbState;

	// Last Ping Update
	time_t last_recv;
	// RX Buffer
	uint8_t rx[1024];
	uint32_t rxpos;
	uint8_t role;

} ChatUserNode;

// Double-Linked Game List
struct ChatGameNode {
	// Next Element
	struct ChatGameNode * next;

	// Previous Element
	struct ChatGameNode * prev;

	// PSP Game Product Code
	SceNetAdhocctlProductCode game;

	// Number of Players
	uint32_t playercount;

	// Number of Groups
	uint32_t groupcount;

	// Double-Linked Group List
	ChatGroupNode * group;
};

// Double-Linked Group List
struct ChatGroupNode {
	// Next Element
	struct ChatGroupNode * next;

	// Previous Element
	struct ChatGroupNode * prev;

	// Game Link
	ChatGameNode * game;

	// virtual group name
	ChatGroupName group;

	// Number of Players
	uint32_t playercount;

	// Double-Linked Player List
	ChatUserNode * player;
};


class CHAT_SERVER {

	public:
		CTL_SERVER_INFO ctl_info[5];
		int Start_Thread(void);
		void Stop_Thread(void);
	private:
		int _port = 30000;

		bool _serverRunning = false;
		std::string _serverName = "Amultios";
		ChatUserNode * _DbUser = NULL;
		ChatGameNode * _DbGame = NULL;
		uint32_t _DbUserCount = 0;

		std::vector<db_crosslink> crosslinks;
		std::vector<db_productid> productids;
		std::vector<db_groupname> groupids;

		int MainLoop(int server);
		void PopulateGameDatabase(void);
		void ProcessWaitingUser(ChatUserNode * user);
		void ProcessLogedInUser(ChatUserNode * user);
		void ProcessCommand(ChatUserNode * user, SceNetAdhocctlCommandPacketC2S * command);
		// TCP Stream Handle
		void LoginTcpStream(int fd, uint32_t ip, uint16_t port);
		bool GetUniqueStream(ChatUserNode * user, uint32_t ip, uint16_t port);
		int GetUserState(ChatUserNode * user);
		void ClearRxBuf(ChatUserNode * user, int clear);
		void FreeDbUser(void);

		// User Database Manipulation
		//void LoginUser(ChatUserNode * user, SceNetAdhocctlLoginPacketC2S * data);
		void LoginChatUser(ChatUserNode * user, ChatLoginPacketC2S * data);
		void ConnectUserGame(ChatUserNode * user,ChatConnectGamePacketC2S * data);
		void SendUserMessage(int* fd, char * message);
		void SendGroupMessage(ChatUserNode * user, char * message);
		void SendGlobalMessage(ChatUserNode * user, char * message);
		bool SpamCheck(ChatUserNode * user);
		bool ValidMac(SceNetEtherAddr * mac);
		bool ValidLogin(SceNetAdhocctlLoginPacketC2S * data);
		bool ValidAmultiosLogin(ChatLoginPacketC2S * data, char * message, ChatUserNode * user);
		void LogoutUser(ChatUserNode * user);

		// User Adhoc Group Manipulation
		void ConnectUserGroup(ChatUserNode * user, ChatGroupName * group);
		void DisconnectUserGroup(ChatUserNode * user);
		bool ValidGroupName(ChatGroupName * group);

		// Game Database Manipulation
		void GameProductLink(SceNetAdhocctlProductCode * product);
		bool ValidGameProduct(SceNetAdhocctlProductCode * product);
};
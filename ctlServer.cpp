// Copyright (c) 2014- PPSSPP Project.
// Refactored by and used on Amultios Project https://amultios.net

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository for ppsspp and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

// This is a refactored code port of Coldbird's code from http://code.google.com/p/aemu/
// All credit goes to him!

#include "ctlServer.h"
#include "socket.h"
//Identified group name on the lobby
static const db_groupname default_groupname[] = {

	// Many games use empty group name to look for party
	{ "" , "Looking For Party" },

	// Monster Hunter Freedom group name
	{ "MHPSP000" , "Gathering Hall A" },
	{ "MHPSP001" , "Gathering Hall B" },
	{ "MHPSP002" , "Gathering Hall C" },
	{ "MHPSP003" , "Gathering Hall D" },
	{ "MHPSP004" , "Gathering Hall E" },
	{ "MHPSP005" , "Gathering Hall F" },
	{ "MHPSP006" , "Gathering Hall G" },
	{ "MHPSP007" , "Gathering Hall H" },
	{ "MHPSP008" , "Gathering Hall I" },
	{ "MHPSP009" , "Gathering Hall J" },

	// Monster Hunter Freedom Unite Room Name
	{ "MHP2Q000" , "Gathering Hall 01" },
	{ "MHP2Q001" , "Gathering Hall 02" },
	{ "MHP2Q002" , "Gathering Hall 03" },
	{ "MHP2Q003" , "Gathering Hall 04" },
	{ "MHP2Q004" , "Gathering Hall 05" },
	{ "MHP2Q005" , "Gathering Hall 06" },
	{ "MHP2Q006" , "Gathering Hall 07" },
	{ "MHP2Q007" , "Gathering Hall 08" },
	{ "MHP2Q008" , "Gathering Hall 09" },
	{ "MHP2Q009" , "Gathering Hall 10" },
	{ "MHP2Q010" , "Gathering Hall 11" },
	{ "MHP2Q011" , "Gathering Hall 12" },
	{ "MHP2Q012" , "Gathering Hall 13" },
	{ "MHP2Q013" , "Gathering Hall 14" },
	{ "MHP2Q014" , "Gathering Hall 15" },
	{ "MHP2Q015" , "Gathering Hall 16" },
	{ "MHP2Q016" , "Gathering Hall 17" },
	{ "MHP2Q017" , "Gathering Hall 18" },
	{ "MHP2Q018" , "Gathering Hall 19" },
	{ "MHP2Q019" , "Gathering Hall 20" },
	{ "MHP2Q020" , "Gathering Hall 21" },
	{ "MHP2Q021" , "Gathering Hall 22" },
	{ "MHP2Q022" , "Gathering Hall 23" },
	{ "MHP2Q023" , "Gathering Hall 24" },
	{ "MHP2A000" , "Training Area 01" },
	{ "MHP2A001" , "Training Area 02" },
	{ "MHP2A002" , "Training Area 03" },
	{ "MHP2A003" , "Training Area 04" },
	{ "MHP2A004" , "Training Area 05" },
	{ "MHP2A005" , "Training Area 06" },
	{ "MHP2A006" , "Training Area 07" },
	{ "MHP2A007" , "Training Area 08" },
	{ "MHP2A008" , "Training Area 09" },
	{ "MHP2A009" , "Training Area 10" },
	{ "MHP2A010" , "Training Area 11" },
	{ "MHP2A011" , "Training Area 12" },
	{ "MHP2A012" , "Training Area 13" },
	{ "MHP2A013" , "Training Area 14" },
	{ "MHP2A014" , "Training Area 15" },
	{ "MHP2A015" , "Training Area 16" },
	{ "MHP2A016" , "Training Area 17" },
	{ "MHP2A017" , "Training Area 18" },
	{ "MHP2A018" , "Training Area 19" },
	{ "MHP2A019" , "Training Area 20" },
	{ "MHP2A020" , "Training Area 21" },
	{ "MHP2A021" , "Training Area 22" },
	{ "MHP2A022" , "Training Area 23" },
	{ "MHP2A023" , "Training Area 24" },

	// Monster Hunter Portable 3rd Group Name
	{ "MHP3Q000" , "Guild Hall 01" },
	{ "MHP3Q001" , "Guild Hall 02" },
	{ "MHP3Q002" , "Guild Hall 03" },
	{ "MHP3Q003" , "Guild Hall 04" },
	{ "MHP3Q004" , "Guild Hall 05" },
	{ "MHP3Q005" , "Guild Hall 06" },
	{ "MHP3Q006" , "Guild Hall 07" },
	{ "MHP3Q007" , "Guild Hall 08" },
	{ "MHP3Q008" , "Guild Hall 09" },
	{ "MHP3Q009" , "Guild Hall 10" },
	{ "MHP3Q010" , "Guild Hall 11" },
	{ "MHP3Q011" , "Guild Hall 12" },
	{ "MHP3Q012" , "Guild Hall 13" },
	{ "MHP3Q013" , "Guild Hall 14" },
	{ "MHP3Q014" , "Guild Hall 15" },
	{ "MHP3Q015" , "Guild Hall 16" },
	{ "MHP3Q016" , "Guild Hall 17" },
	{ "MHP3Q017" , "Guild Hall 18" },
	{ "MHP3Q018" , "Guild Hall 19" },
	{ "MHP3Q019" , "Guild Hall 20" },
	{ "MHP3Q020" , "Guild Hall 21" },
	{ "MHP3Q021" , "Guild Hall 22" },
	{ "MHP3Q022" , "Guild Hall 23" },
	{ "MHP3Q023" , "Guild Hall 24" },
	{ "MHP3A000" , "Training Hall 01" },
	{ "MHP3A001" , "Training Hall 02" },
	{ "MHP3A002" , "Training Hall 03" },
	{ "MHP3A003" , "Training Hall 04" },
	{ "MHP3A004" , "Training Hall 05" },
	{ "MHP3A005" , "Training Hall 06" },
	{ "MHP3A006" , "Training Hall 07" },
	{ "MHP3A007" , "Training Hall 08" },
	{ "MHP3A008" , "Training Hall 09" },
	{ "MHP3A009" , "Training Hall 10" },
	{ "MHP3A010" , "Training Hall 11" },
	{ "MHP3A011" , "Training Hall 12" },
	{ "MHP3A012" , "Training Hall 13" },
	{ "MHP3A013" , "Training Hall 14" },
	{ "MHP3A014" , "Training Hall 15" },
	{ "MHP3A015" , "Training Hall 16" },
	{ "MHP3A016" , "Training Hall 17" },
	{ "MHP3A017" , "Training Hall 18" },
	{ "MHP3A018" , "Training Hall 19" },
	{ "MHP3A019" , "Training Hall 20" },
	{ "MHP3A020" , "Training Hall 21" },
	{ "MHP3A021" , "Training Hall 22" },
	{ "MHP3A022" , "Training Hall 23" },
	{ "MHP3A023" , "Training Hall 24" }

};

CTL_SERVER::CTL_SERVER(int port, std::string name,bool ppsspp) {
	CTL_SERVER::_port = port;
	CTL_SERVER::_serverName = name;
	CTL_SERVER::_DbUser = NULL;
	CTL_SERVER::_DbGame = NULL;
	CTL_SERVER::_DbUserCount = 0;
	CTL_SERVER::_enablePPSSPP = ppsspp;
}


CTL_SERVER::~CTL_SERVER()
{

}

int CTL_SERVER::Start_Thread(void) {

	int result = 0;
	printf("CTL_SERVER [%s] Begin Thread \n", _serverName.c_str());
	int server = createTcpListenSocket(_port, CTL_SERVER_BACKLOG);

	if (server != INVALID_SOCKET) {

		_serverRunning = true;
		printf("CTL_SERVER [%s] Listening on port %d \n", _serverName.c_str(), _port);
		PopulateGameDatabase();
		result = MainLoop(server);

		printf("CTL_SERVER [%s] Shutting down on port %d \n", _serverName.c_str(), _port);
	}
	
	printf("CTL_SERVER [%s] End of Thread \n", _serverName.c_str());
	_serverRunning = false;
	return result;
}

//populate database from mysql
void CTL_SERVER::PopulateGameDatabase(void) {

	CTL_SERVER::groupids = std::vector<db_groupname>(default_groupname, default_groupname + ARRAY_SIZE(default_groupname));
	std::unique_lock<std::mutex> lock(sql_lock);
	if (mysql_query(&_CON, "SELECT * from crosslinks")) {
		printf("CTL_SERVER [%s][ERROR] Failed to To Populate DB crosslinks %s\n", _serverName.c_str(), mysql_error(&_CON));
	}
	else {
		MYSQL_RES *result = mysql_store_result(&_CON);
		MYSQL_ROW row;
		//populate product ids
		while ((row = mysql_fetch_row(result)) != NULL) {
			db_crosslink cross;
			strncpy(cross.id_from, row[0], sizeof(cross.id_from));
			strncpy(cross.id_to, row[1], sizeof(cross.id_to));
			crosslinks.push_back(cross);
			printf("CTL_SERVER [%s] Added Crosslinks id_from [%s] to id_to [%s] \n", _serverName.c_str(), cross.id_from, cross.id_to);
		}
		mysql_free_result(result);
	}

	if (mysql_query(&_CON, "SELECT id,name from productids")) {
		printf("CTL_SERVER [%s][ERROR] Failed to To Populate DB productids %s\n", _serverName.c_str(), mysql_error(&_CON));
	}
	else {
		MYSQL_RES *result2 = mysql_store_result(&_CON);
		MYSQL_ROW row2;
		//populate product ids
		while ((row2 = mysql_fetch_row(result2)) != NULL) {
			db_productid product;
			strncpy(product.id, row2[0], sizeof(product.id));
			strncpy(product.name, row2[1], sizeof(product.name));
			productids.push_back(product);
			printf("CTL_SERVER [%s] Added Productids id %s to name %s\n", _serverName.c_str(), product.id, product.name);
		}
		mysql_free_result(result2);
	}
}


// main loop that handle incoming tcp connection
int CTL_SERVER::MainLoop(int server) {

	UpdateServerStatus();
	while (_serverRunning && g_amultios) {
		// Login Block
		{
			// Login Result
			int loginresult = 0;

			// Login Processing Loop
			do
			{
				// Prepare Address Structure
				struct sockaddr_in addr;
				socklen_t addrlen = sizeof(addr);
				memset(&addr, 0, sizeof(addr));

				// Accept Login Requests
				// loginresult = accept4(server, (struct sockaddr *)&addr, &addrlen, SOCK_NONBLOCK);

				// Alternative Accept Approach (some Linux Kernel don't support the accept4 Syscall... wtf?)
				loginresult = accept(server, (struct sockaddr *)&addr, &addrlen);
				if (loginresult != -1)
				{
					// Switch Socket into Non-Blocking Mode
					change_blocking_mode(loginresult, 1);
				}

				// Login User (Stream)
				if (loginresult != -1) {

					LoginTcpStream(loginresult, addr.sin_addr.s_addr, addr.sin_port);
				}
			} while (loginresult != -1);
		}

		// Receive Data from Users
		SceNetAdhocctlUserNode * user = _DbUser;

		while (user != NULL) {

			// Next User (for safe delete)
			SceNetAdhocctlUserNode * next = user->next;

			// Receive Data from User
			int recvresult = recv(user->stream, (char*)user->rx + user->rxpos, sizeof(user->rx) - user->rxpos, 0);

			// Connection Closed or Timed Out
			if (recvresult == 0 || (recvresult == -1 && errno != EAGAIN && errno != EWOULDBLOCK) || GetUserState(user) == CTL_USER_TIMED_OUT)
			{
				// Logout User
				LogoutUser(user);
			}


			// Received Data (or leftovers in RX-Buffer)
			else if (recvresult > 0 || user->rxpos > 0)
			{
				// New Incoming Data
				if (recvresult > 0)
				{
					// Move RX Pointer
					user->rxpos += recvresult;

					// Update Death Clock
					user->last_recv = time(NULL);
				}

				if (GetUserState(user) == CTL_USER_WAITING) {
					// validate and login user
					ProcessWaitingUser(user);
				}
				else if (GetUserState(user) == CTL_USER_LOGGED_IN) {
					// Process user requested packet
					ProcessLogedInUser(user);
				}
			}

			// Move Pointer
			user = next;
		}

		// Prevent needless CPU Overload (1ms Sleep)
		sleep_ms(1);
	}

	// Free User Database Memory
	FreeDbUser();

	// Close Server Socket
	closesocket(server);


	return 0;

}


void CTL_SERVER::ProcessWaitingUser(SceNetAdhocctlUserNode * user) {
	// Valid Opcode
	if (user->rx[0] == OPCODE_LOGIN)
	{
		// Enough Data available
		if (user->rxpos >= sizeof(SceNetAdhocctlLoginPacketC2S))
		{
			// Clone Packet
			SceNetAdhocctlLoginPacketC2S packet = *(SceNetAdhocctlLoginPacketC2S *)user->rx;

			// Remove Packet from RX Buffer
			ClearRxBuf(user, sizeof(SceNetAdhocctlLoginPacketC2S));

			// Login User (Data)
			LoginUser(user, &packet);
		}
	}

	// Valid Opcode
	else if (user->rx[0] == OPCODE_AMULTIOS_LOGIN)
	{
		// Enough Data available
		if (user->rxpos >= sizeof(SceNetAdhocctlLoginPacketAmultiosC2S))
		{
			// Clone Packet
			SceNetAdhocctlLoginPacketAmultiosC2S packet = *(SceNetAdhocctlLoginPacketAmultiosC2S *)user->rx;

			// Remove Packet from RX Buffer
			ClearRxBuf(user, sizeof(SceNetAdhocctlLoginPacketAmultiosC2S));

			// Login User (Data)
			LoginAmultiosUser(user, &packet);
		}
	}

	else if (user->rx[0] == OPCODE_AMULTIOS_COMMAND)
	{
		// Enough Data available
		if (user->rxpos >= sizeof(SceNetAdhocctlCommandPacketC2S))
		{
			// Clone Packet
			SceNetAdhocctlCommandPacketC2S packet = *(SceNetAdhocctlCommandPacketC2S *)user->rx;

			// Remove Packet from RX Buffer
			ClearRxBuf(user, sizeof(SceNetAdhocctlCommandPacketC2S));
			
			ProcessCommand(user, &packet);
			
		}
	}
	// Invalid Opcode
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		printf("CTL_SERVER [%s] Invalid Opcode 0x%02X in Waiting State from %u.%u.%u.%u", _serverName.c_str(),user->rx[0], ip[0], ip[1], ip[2], ip[3]);

		// Logout User
		LogoutUser(user);
	}
}

void CTL_SERVER::ProcessLogedInUser(SceNetAdhocctlUserNode * user) {
	// Ping Packet
	if (user->rx[0] == OPCODE_PING)
	{
		// Delete Packet from RX Buffer
		ClearRxBuf(user, 1);
	}

	// Group Connect Packet
	else if (user->rx[0] == OPCODE_CONNECT)
	{
		// Enough Data available
		if (user->rxpos >= sizeof(SceNetAdhocctlConnectPacketC2S))
		{
			// Cast Packet
			SceNetAdhocctlConnectPacketC2S * packet = (SceNetAdhocctlConnectPacketC2S *)user->rx;

			// Clone Group Name
			SceNetAdhocctlGroupName group = packet->group;

			// Remove Packet from RX Buffer
			ClearRxBuf(user, sizeof(SceNetAdhocctlConnectPacketC2S));

			// Change Game Group
			ConnectUserGroup(user, &group);
		}
	}

	// Group Disconnect Packet
	else if (user->rx[0] == OPCODE_DISCONNECT)
	{
		// Remove Packet from RX Buffer
		ClearRxBuf(user, 1);

		// Leave Game Group
		DisconnectUserGroup(user);
	}

	// Network Scan Packet
	else if (user->rx[0] == OPCODE_SCAN)
	{
		// Remove Packet from RX Buffer
		ClearRxBuf(user, 1);

		// Send Network List
		SendScanGroupResult(user);
	}

	// Chat Text Packet
	else if (user->rx[0] == OPCODE_CHAT)
	{
		// Enough Data available
		if (user->rxpos >= sizeof(SceNetAdhocctlChatPacketC2S))
		{
			// Cast Packet
			SceNetAdhocctlChatPacketC2S * packet = (SceNetAdhocctlChatPacketC2S *)user->rx;

			// Clone Buffer for Message
			char message[64];
			memset(message, 0, sizeof(message));
			strncpy(message, packet->message, sizeof(message) - 1);

			// Remove Packet from RX Buffer
			ClearRxBuf(user, sizeof(SceNetAdhocctlChatPacketC2S));

			// Spread Chat Message
			SendGroupMessage(user, message);
			//spread_message(user, message);
		}
	}

	// Invalid Opcode
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		printf("CTL_SERVER [%s] Invalid Opcode 0x%02X in Logged-In State from %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u)\n", _serverName.c_str(),user->rx[0], (char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3]);

		// Logout User
		LogoutUser(user);
	}
}


void CTL_SERVER::ProcessCommand(SceNetAdhocctlUserNode * user, SceNetAdhocctlCommandPacketC2S * command) {

	char safecommand[COMMAND_LENGTH +1];
	memset(safecommand, 0, sizeof(safecommand));
	strncpy(safecommand, command->command, COMMAND_LENGTH);

	char safeTarget[ADHOCCTL_NICKNAME_LEN + 1];
	memset(safeTarget, 0, sizeof(safeTarget));
	strncpy(safeTarget, command->target, ADHOCCTL_NICKNAME_LEN);
	
	// Kick user from external command
	if (strcmp(safecommand, "KICK") == 0) {
		//ban user
		SceNetAdhocctlUserNode * u = _DbUser;

		while (u != NULL) {
			if (u->group != NULL) {
				char userPlay[ADHOCCTL_NICKNAME_LEN + 1];
				memset(userPlay, 0, sizeof(userPlay));
				strncpy(userPlay, (char *)u->resolver.name.data, ADHOCCTL_NICKNAME_LEN);

				if (strcmp (userPlay,safeTarget) == 0) {
					LogoutUser(u);
					break;
				}
			}
			u = u->next;
		}
	}

	LogoutUser(user);
}
/** =====================================================================================
*									TCP STREAM HANDLE
*				This Function Below used to Handle TCP Stream on User Node
* =======================================================================================
*/


// Login Incoming Tcp Stream;
void CTL_SERVER::LoginTcpStream(int fd, uint32_t ip, uint16_t port) {

	// Maximum user reached
	if (_DbUserCount < CTL_SERVER_MAX_USER) {
		SceNetAdhocctlUserNode * u = _DbUser;

		// check duplicate user stream
		while (GetUniqueStream(u, ip, port)) u = u->next;

		// Unique TCP Stream
		if (u == NULL) {
			// Allocate User Node Memory
			SceNetAdhocctlUserNode * user = (SceNetAdhocctlUserNode *)malloc(sizeof(SceNetAdhocctlUserNode));

			// Allocated User Node Memory
			if (user != NULL)
			{
				// Clear Memory
				memset(user, 0, sizeof(SceNetAdhocctlUserNode));

				// Save Socket
				user->stream = fd;

				// Save IP
				user->resolver.ip = ip;

				// Save port 
				user->resolver.port = port;

				user->role = 1;
				// Link into User List
				user->next = _DbUser;
				if (_DbUser != NULL) _DbUser->prev = user;
				_DbUser = user;

				// Initialize Death Clock
				user->last_recv = time(NULL);

				// Notify User
				uint8_t * ipa = (uint8_t *)&user->resolver.ip;


				printf("CTL_SERVER [%s] New Connection from %u.%u.%u.%u\n", _serverName.c_str(),ipa[0], ipa[1], ipa[2], ipa[3]);

				// Fix User Counter
				_DbUserCount++;

				// Update Status Log
				UpdateServerStatus();
				// Exit Function
				return;
			}
		}
	}

	// Duplicate IP, Allocation Error or not enough space - Close Stream
	closesocket(fd);
}

// Get Unique ip address or port from double linked loop
bool CTL_SERVER::GetUniqueStream(SceNetAdhocctlUserNode * user, uint32_t ip, uint16_t port) {

	// next unique user node allocation
	bool next = false;

	// check existing user data
	if (user != NULL) {

		// different ip continue the loop
		if (user->resolver.ip != ip) {
			next = true;
			return next;
		}

		// same ip with different port continue the loop
		if (user->resolver.ip == ip && user->resolver.port != port) {
			next = true;
			return next;
		}

	}

	// get unique 
	return next;
}


/**
* Get Tcp Stream User State
* @param user SceNetAdhocctlUserNode
*/
int CTL_SERVER::GetUserState(SceNetAdhocctlUserNode * user) {
	// Timeout Status
	if ((time(NULL) - user->last_recv) >= CTL_SERVER_TIMEOUT) return CTL_USER_TIMED_OUT;

	// Waiting Status
	if (user->game == NULL) return CTL_USER_WAITING;

	// Logged-In Status
	return CTL_USER_LOGGED_IN;
}

/**
* Clear TCP Stream RX Buffer
* @param user SceNetAdhocctlUserNode
* @param clear Number of Bytes to clear (-1 for all)
*/
void CTL_SERVER::ClearRxBuf(SceNetAdhocctlUserNode * user, int clear) {
	if (clear == -1 || clear > user->rxpos) clear = user->rxpos;

	// Move Buffer
	memmove(user->rx, user->rx + clear, sizeof(user->rx) - clear);

	// Fix RX Buffer Pointer
	user->rxpos -= clear;
}


/**
* Free Database Memory
*/
void CTL_SERVER::FreeDbUser(void)
{

	// Iterate Users for Deletion
	SceNetAdhocctlUserNode * user = _DbUser;
	while (user != NULL)
	{
		// Next User (for safe delete)
		SceNetAdhocctlUserNode * next = user->next;

		// Logout User
		LogoutUser(user);

		// Move Pointer
		user = next;
	}
}

/** =====================================================================================
*									User Manipulation
*				This Function Below use to Manage User on User Node
* =======================================================================================
*/

void CTL_SERVER::LoginUser(SceNetAdhocctlUserNode * user, SceNetAdhocctlLoginPacketC2S * data) {


	if (ValidGameProduct(&data->game) && ValidMac(&data->mac) && ValidLogin(data)) {

		// Game Product Override
		GameProductLink(&data->game);

		// Find existing Game
		SceNetAdhocctlGameNode * game = _DbGame;
		while (game != NULL && strncmp(game->game.data, data->game.data, PRODUCT_CODE_LENGTH) != 0) game = game->next;

		// Game not found
		if (game == NULL)
		{
			// Allocate Game Node Memory
			game = (SceNetAdhocctlGameNode *)malloc(sizeof(SceNetAdhocctlGameNode));

			// Allocated Game Node Memory
			if (game != NULL)
			{
				// Clear Memory
				memset(game, 0, sizeof(SceNetAdhocctlGameNode));

				// Save Game Product ID
				game->game = data->game;

				// Link into Game List
				game->next = _DbGame;
				if (_DbGame != NULL) _DbGame->prev = game;
				_DbGame = game;
			}
		}

		// Game now available
		if (game != NULL)
		{
			// Save MAC
			user->resolver.mac = data->mac;

			// Save Nickname
			user->resolver.name = data->name;

			// Increase Player Count in Game Node
			game->playercount++;

			// Link Game to Player
			user->game = game;

			// Notify User
			uint8_t * ip = (uint8_t *)&user->resolver.ip;
			char safegamestr[10];
			memset(safegamestr, 0, sizeof(safegamestr));
			strncpy(safegamestr, game->game.data, PRODUCT_CODE_LENGTH);

			printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) started playing %s\n", _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr);
			// Update Status Log
			UpdateServerStatus();

			// Leave Function
			return;
		}
	}

	// Invalid Packet Data
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		printf("CTL_SERVER [%s] Invalid Login Packet Contents from %u.%u.%u.%u\n", _serverName.c_str(),ip[0], ip[1], ip[2], ip[3]);
	}

	// Logout User - Out of Memory or Invalid Arguments
	LogoutUser(user);
}

void CTL_SERVER::LoginAmultiosUser(SceNetAdhocctlUserNode * user, SceNetAdhocctlLoginPacketAmultiosC2S * data) {

	char message[64];
	if (ValidGameProduct(&data->game) && ValidMac(&data->mac) && ValidAmultiosLogin(data, message,user)) {

		// Game Product Override
		GameProductLink(&data->game);

		// Find existing Game
		SceNetAdhocctlGameNode * game = _DbGame;
		while (game != NULL && strncmp(game->game.data, data->game.data, PRODUCT_CODE_LENGTH) != 0) game = game->next;

		// Game not found
		if (game == NULL)
		{
			// Allocate Game Node Memory
			game = (SceNetAdhocctlGameNode *)malloc(sizeof(SceNetAdhocctlGameNode));

			// Allocated Game Node Memory
			if (game != NULL)
			{
				// Clear Memory
				memset(game, 0, sizeof(SceNetAdhocctlGameNode));

				// Save Game Product ID
				game->game = data->game;

				// Link into Game List
				game->next = _DbGame;
				if (_DbGame != NULL) _DbGame->prev = game;
				_DbGame = game;
			}
		}

		// Game now available
		if (game != NULL)
		{
			// Save MAC
			user->resolver.mac = data->mac;

			// Save Nickname
			user->resolver.name = data->name;

			// Increase Player Count in Game Node
			game->playercount++;

			// Link Game to Player
			user->game = game;

			//rejected packet
			SceNetAdhocctlNotifyPacketS2C packet;
			// Clear Memory
			memset(&packet, 0, sizeof(packet));
			packet.base.opcode = OPCODE_AMULTIOS_LOGIN_SUCCESS;
			// Set Chat Message
			strcpy(packet.reason, "Login Success");
			int iResult = send(user->stream, (const char*)&packet, sizeof(packet), 0);
			if (iResult < 0) printf("CTL_SERVER [%s][ERROR] send sucess packet  (Socket error %d) \n", _serverName.c_str(),errno);
			// Notify User
			uint8_t * ip = (uint8_t *)&user->resolver.ip;
			char safegamestr[10];
			memset(safegamestr, 0, sizeof(safegamestr));
			strncpy(safegamestr, game->game.data, PRODUCT_CODE_LENGTH);
			printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) started playing %s\n", _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr);

			// Update online status on mysql DB
			{
				std::unique_lock<std::mutex> lock(sql_lock);
				char update[100 + ADHOCCTL_NICKNAME_LEN];
				snprintf(update, sizeof(update), "UPDATE users SET online = '2', server='%s' WHERE nickname='%s';", _serverName.c_str(),(char *)user->resolver.name.data);
				if (mysql_query(&_CON, update)) {
					printf("CTL_SERVER [%s][ERROR] Failed To update online status nickname on database Query[%s] id  Error: %u\n", _serverName.c_str(), update, mysql_errno(&_CON));
					strcpy(message, "Login Failed Lost Connection to database report to admin");
				}
			}

			// Update Status Log
			UpdateServerStatus();

			// Leave Function
			return;
		}
	}

	// Invalid Packet Data
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		printf("CTL_SERVER [%s] Login Attempt failed reason [%s] \n", _serverName.c_str(),message);

		//rejected packet
		SceNetAdhocctlNotifyPacketS2C packet;
		// Clear Memory
		memset(&packet, 0, sizeof(packet));
		packet.base.opcode = OPCODE_AMULTIOS_LOGIN_FAILED;
		// Set Chat Message
		strcpy(packet.reason, message);
		int iResult = send(user->stream, (const char*)&packet, sizeof(packet), 0);
		if (iResult < 0) printf("CTL_SERVER [%s][ERROR] send rejected packet  (Socket error %d) \n", _serverName.c_str(),errno);
	}

	// Logout User - Out of Memory or Invalid Arguments
	LogoutUser(user);
}

void CTL_SERVER::SendUserMessage(int* fd, char * message) {

}

void CTL_SERVER::SendGroupMessage(SceNetAdhocctlUserNode * user,char * message) {
	// User is connected
	if (user->group != NULL)
	{
		// Broadcast Range Counter
		uint32_t counter = 0;

		// Iterate Group Players
		SceNetAdhocctlUserNode * peer = user->group->player;
		while (peer != NULL)
		{
			// Skip Self
			if (peer == user)
			{
				// Move Pointer
				peer = peer->group_next;

				// Continue Loop
				continue;
			}

			// Chat Packet
			SceNetAdhocctlChatPacketS2C packet;

			// Set Chat Opcode
			packet.base.base.opcode = OPCODE_CHAT;

			// Set Chat Message
			strcpy(packet.base.message, message);

			// Set Sender Nickname
			packet.name = user->resolver.name;

			// Send Data
			int iResult = send(peer->stream, (const char*)&packet, sizeof(packet), 0);
			if (iResult < 0) printf("CTL_SERVER [%s][ERROR] send group message [send peer chat] (Socket error %d) \n", _serverName.c_str(), errno);

			// Move Pointer
			peer = peer->group_next;

			// Increase Broadcast Range Counter
			counter++;
		}

		// Message Sent
		if (counter > 0)
		{
			// Notify User
			uint8_t * ip = (uint8_t *)&user->resolver.ip;
			char safegamestr[10];
			memset(safegamestr, 0, sizeof(safegamestr));
			strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
			char safegroupstr[9];
			memset(safegroupstr, 0, sizeof(safegroupstr));
			strncpy(safegroupstr, (char *)user->group->group.data, ADHOCCTL_GROUPNAME_LEN);
			printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) sent \"%s\" to %d players in %s group %s\n",_serverName.c_str(), (char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], message, counter, safegamestr, safegroupstr);
		}

		// Exit Function
		return;
	}

	// User not in a game group
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) attempted to send a text message without joining a %s group first\n", _serverName.c_str(), (char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr);
	}

}

void CTL_SERVER::LogoutUser(SceNetAdhocctlUserNode * user) {


	// Disconnect from Group
	if (user->group != NULL) DisconnectUserGroup(user);

	// Unlink Leftside (Beginning)
	if (user->prev == NULL) _DbUser = user->next;

	// Unlink Leftside (Other)
	else user->prev->next = user->next;

	// Unlink Rightside
	if (user->next != NULL) user->next->prev = user->prev;

	// Close Stream
	closesocket(user->stream);

	// Playing User
	if (user->game != NULL)
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) stopped playing %s\n",  _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr);

		// Disconnect on MYSQL DB
		
		{
			std::unique_lock<std::mutex> lock(sql_lock);
			char update[100 + ADHOCCTL_NICKNAME_LEN];
			snprintf(update, sizeof(update), "UPDATE users SET online = 1, server='Amultios' WHERE nickname='%s';", (char *)user->resolver.name.data);
			if (mysql_query(&_CON, update)) {
				printf("CTL_SERVER [%s][ERROR] Failed To update online status nickname on database Query[%s] id  Error: %u\n", _serverName.c_str(), update, mysql_errno(&_CON));
			}
		}

		// Fix Game Player Count
		user->game->playercount--;

		// Empty Game Node
		if (user->game->playercount == 0)
		{
			// Unlink Leftside (Beginning)
			if (user->game->prev == NULL) _DbGame = user->game->next;

			// Unlink Leftside (Other)
			else user->game->prev->next = user->game->next;

			// Unlink Rightside
			if (user->game->next != NULL) user->game->next->prev = user->game->prev;

			// Free Game Node Memory
			free(user->game);
		}
	}

	// Unidentified User
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		printf("CTL_SERVER [%s] Dropped Connection to %u.%u.%u.%u\n", _serverName.c_str(),ip[0], ip[1], ip[2], ip[3]);
	}

	// Free Memory
	free(user);

	// Fix User Counter
	_DbUserCount--;

	// Update Status Log
	UpdateServerStatus();
}

bool CTL_SERVER::ValidMac(SceNetEtherAddr * mac) {

	//Compare To Broadcast
	int cmp = memcmp(mac, "\xFF\xFF\xFF\xFF\xFF\xFF", sizeof(mac));
	int cmp2 = memcmp(mac, "\x00\x00\x00\x00\x00\x00", sizeof(mac));

	//TO DO check for duplicate mac
	//printf("CTL_SERVER [%s] cmp %d cmp2 %d, MAC: %02X:%02X:%02X:%02X:%02X:%02X \n",cmp,cmp2,mac->data[0], mac->data[1] ,mac->data[2], mac->data[3], mac->data[4], mac->data[5]);
	return cmp != 0 && cmp2 != 0;
}

bool CTL_SERVER::ValidLogin(SceNetAdhocctlLoginPacketC2S * data) {

	// amultios mode and ppsspp mode cannot be mixed this should allow only ppsspp build
	if (_enablePPSSPP) {
		if (data->name.data[0] == 0) return false;
		return true;
	}
	else {
		return false;
	}

}


bool CTL_SERVER::ValidAmultiosLogin(SceNetAdhocctlLoginPacketAmultiosC2S * data, char * message, SceNetAdhocctlUserNode * user) {

	char nameval[ADHOCCTL_NICKNAME_LEN + 1];
	memset(nameval, 0, sizeof(nameval));
	strncpy(nameval, (char *)data->name.data, ADHOCCTL_NICKNAME_LEN);

	if (_port == 27312) {
		strcpy(message, "Only Amultios Emulator can play on our server");
		return false;
	}

	if (data->name.data[0] == 0 || data->pin[0] == 0) {
		strcpy(message, "Login Failed NICKNAME or PIN is empty, did you set it on settings?");
		return false;
	}

	if (strcmp(nameval, "PPSSPP") == 0) {
		strcpy(message, "Login Failed using default PPSSPP name, did you set it on settings?");
		return false;
	}

	if (strcmp(nameval, "AMULTIOS") == 0) {
		strcpy(message, "Login Failed using default AMULTIOS name, did you set it on settings?");
		return false;
	}

	bool check = true;
	{
		std::unique_lock<std::mutex> lock(sql_lock);
		char nickname[ADHOCCTL_NICKNAME_LEN + 100];
		memset(nickname, 0, sizeof(nickname));
		snprintf(nickname, sizeof(nickname), "SELECT pin,online,role FROM users WHERE nickname='%s' LIMIT 1;", nameval);

		if (mysql_query(&_CON, nickname)) {
			printf("CTL_SERVER [%s][ERROR]Failed To select nickname on database Query[%s] id  Error: %u\n", _serverName.c_str(), nickname, mysql_errno(&_CON));
			strcpy(message, "Login Failed Invalid Input Character For Nickname");
			check = false;
		}
		else {
			MYSQL_RES *result = mysql_store_result(&_CON);
			MYSQL_ROW row = mysql_fetch_row(result);

			if (row == NULL) {
				printf("CTL_SERVER [%s] Failed login attemp nickname not found %s \n", _serverName.c_str(), nameval);
				strcpy(message, "Login Failed Nickname Not Found did you already register?");
				check = false;
			}
			else if(result!=NULL && row !=NULL) {

				char pinvalidaton[30];
				char onlinevalidation[30];
				char safepin[7];
				char safepindb[7];
				char onlineChar[sizeof(int) + 1];
				char roleChar[sizeof(int) + 1];

				memset(onlineChar, 0, sizeof(int));
				memset(roleChar, 0, sizeof(int));
				memset(safepin, 0, sizeof(safepin));
				memset(safepindb, 0, sizeof(safepindb));

				if (row[0] != NULL && row[0][0] != '\0') {
					strncpy(safepin, data->pin, PIN_LENGTH);
					strncpy(safepindb, row[0], PIN_LENGTH);
					if (IsMatch(safepin, safepindb)) {
						strcpy(pinvalidaton, "pin valid");
					}
					else {
						strcpy(pinvalidaton, "pin invalid");
						strcpy(message, "Invalid PIN , did you set your pin in network settings?");
						check = false;
					}
					printf("CHAT_SERVER [%s] Validate pin %s && db pin %s result [%s]\n", _serverName.c_str(), safepin, safepindb, pinvalidaton);
				}
				else {
					strcpy(message, "Server Still busy retry Login again later");
					check = false;
				}

				if (row[1] != NULL && row[1][0] != '\0') {
					strncpy(onlineChar, row[1], sizeof(int));
					if (atoi(onlineChar) == 2) {
						strcpy(onlinevalidation, "Login Failed");
						strcpy(message, "Login Failed Someone Already Joined with this nickname");
						check = false;
					}
					else {
						strcpy(onlinevalidation, "Login Success");
					}

					printf("CHAT_SERVER [%s] Validate online %d result [%s]\n", _serverName.c_str(), atoi(onlineChar), onlinevalidation);
				}
				else {
					strcpy(message, "Server Still busy retry Login again later");
					check = false;
				}

				if (user != NULL && row[2] != NULL && row[2][0] != '\0') {
					strncpy(roleChar, row[2], sizeof(int));
					user->role = atoi(roleChar);
					if (atoi(roleChar) > 2) {
						check = false;
						strcpy(message, "Your Account got Banned Stop Cheating Noob!");
					}
					printf("CTL_SERVER [%s] Validate role db=[%d] role=[%u]\n", _serverName.c_str(), atoi(roleChar), user->role);
				}
				else {
					strcpy(message, "Server Still busy retry Login again later");
					check = false;
				}

			}
			else {
				strcpy(message, "Server Still busy retry Login again later");
				check = false;
			}

			mysql_free_result(result);
		}
	}

	if (check) printf("CTL_SERVER [%s] Nickname %s Successfuly pass Amultios Login\n", _serverName.c_str(), nameval);

	return check;
}
/** =====================================================================================
*									User Group Manipulation
*	   This Function Below use to Manage UserGroup on User Node (Adhoc Game Room)
* =======================================================================================
*/
void CTL_SERVER::ConnectUserGroup(SceNetAdhocctlUserNode * user, SceNetAdhocctlGroupName * group) {

	if (ValidGroupName(group)) {

		//User is disconnected from group
		if (user->group == NULL) {
			// Find Group in Game Node
			SceNetAdhocctlGroupNode * g = user->game->group;
			while (g != NULL && strncmp((char *)g->group.data, (char *)group->data, ADHOCCTL_GROUPNAME_LEN) != 0) g = g->next;

			// BSSID Packet
			SceNetAdhocctlConnectBSSIDPacketS2C bssid;

			// Set BSSID Opcode
			bssid.base.opcode = OPCODE_CONNECT_BSSID;

			// Set Default BSSID
			bssid.mac = user->resolver.mac;

			// No Group found
			if (g == NULL)
			{
				// Allocate Group Memory
				g = (SceNetAdhocctlGroupNode *)malloc(sizeof(SceNetAdhocctlGroupNode));

				// Allocated Group Memory
				if (g != NULL)
				{
					// Clear Memory
					memset(g, 0, sizeof(SceNetAdhocctlGroupNode));

					// Link Game Node
					g->game = user->game;

					// Link Group Node
					g->next = g->game->group;
					if (g->game->group != NULL) g->game->group->prev = g;
					g->game->group = g;

					// Copy Group Name
					g->group = *group;

					// Increase Group Counter for Game
					g->game->groupcount++;
				}
			}

			// Group now available
			if (g != NULL)
			{
				// Iterate remaining Group Players
				SceNetAdhocctlUserNode * peer = g->player;
				while (peer != NULL)
				{
					// Connect Packet
					SceNetAdhocctlConnectPacketS2C packet;

					// Clear Memory
					// memset(&packet, 0, sizeof(packet));

					// Set Connect Opcode
					packet.base.opcode = OPCODE_CONNECT;

					// Set Player Name
					packet.name = user->resolver.name;

					// Set Player MAC
					packet.mac = user->resolver.mac;

					// Set Player IP
					packet.ip = user->resolver.ip;

					// Send Data
					int iResult = send(peer->stream, (const char*)&packet, sizeof(packet), 0);
					if (iResult < 0) printf("CTL_SERVER [%s][ERROR] connect_user[send peer] (Socket error %d)\n", _serverName.c_str(),errno);

					// Set Player Name
					packet.name = peer->resolver.name;

					// Set Player MAC
					packet.mac = peer->resolver.mac;

					// Set Player IP
					packet.ip = peer->resolver.ip;

					// Send Data
					iResult = send(user->stream, (const char*)&packet, sizeof(packet), 0);
					if (iResult < 0) printf("CTL_SERVER [%s][ERROR] connect_user[send user] (Socket error %d)\n", _serverName.c_str(), errno);

					// Set BSSID
					if (peer->group_next == NULL) bssid.mac = peer->resolver.mac;

					// Move Pointer
					peer = peer->group_next;
				}

				// Link User to Group
				user->group_next = g->player;
				if (g->player != NULL) g->player->group_prev = user;
				g->player = user;

				// Link Group to User
				user->group = g;

				// Increase Player Count
				g->playercount++;

				// Send Network BSSID to User
				int iResult = send(user->stream, (const char*)&bssid, sizeof(bssid), 0);
				if (iResult < 0) printf("CTL_SERVER [%s][ERROR] connect_user[send user bssid] (Socket error %d)\n", _serverName.c_str(),errno);

				// Notify User
				uint8_t * ip = (uint8_t *)&user->resolver.ip;
				char safegamestr[10];
				memset(safegamestr, 0, sizeof(safegamestr));
				strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
				char safegroupstr[9];
				memset(safegroupstr, 0, sizeof(safegroupstr));
				strncpy(safegroupstr, (char *)user->group->group.data, ADHOCCTL_GROUPNAME_LEN);
				printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) joined %s group %s\n", _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr, safegroupstr);

				// Update Status Log
				UpdateServerStatus();

				// Exit Function
				return;
			}

			else {
				// Log Invalid group
				uint8_t * ip = (uint8_t *)&user->resolver.ip;
				char safegamestr[10];
				memset(safegamestr, 0, sizeof(safegamestr));
				strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
				char safegroupstr[9];
				memset(safegroupstr, 0, sizeof(safegroupstr));
				strncpy(safegroupstr, (char *)group->data, ADHOCCTL_GROUPNAME_LEN);
				char safegroupstr2[9];
				memset(safegroupstr2, 0, sizeof(safegroupstr2));
				strncpy(safegroupstr2, (char *)user->group->group.data, ADHOCCTL_GROUPNAME_LEN);
				printf("CTL_Server[%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) attempted to join %s group %s without disconnecting from %s first\n", _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr, safegroupstr, safegroupstr2);
			}
		}
	}
	// Invalid Group Name
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		char safegroupstr[9];
		memset(safegroupstr, 0, sizeof(safegroupstr));
		strncpy(safegroupstr, (char *)group->data, ADHOCCTL_GROUPNAME_LEN);
		printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) attempted to join invalid %s group %s\n", _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr, safegroupstr);
	}

	// Invalid State, Out of Memory or Invalid Group Name
	LogoutUser(user);
}

void CTL_SERVER::DisconnectUserGroup(SceNetAdhocctlUserNode * user) {

	// User is connected to a group
	if (user->group != NULL)
	{
		// Unlink Leftside (Beginning)
		if (user->group_prev == NULL) user->group->player = user->group_next;

		// Unlink Leftside (Other)
		else user->group_prev->group_next = user->group_next;

		// Unlink Rightside
		if (user->group_next != NULL) user->group_next->group_prev = user->group_prev;

		// Fix Player Count
		user->group->playercount--;

		// Iterate remaining Group Players
		SceNetAdhocctlUserNode * peer = user->group->player;
		while (peer != NULL)
		{
			// Disconnect Packet
			SceNetAdhocctlDisconnectPacketS2C packet;

			// Clear Memory
			// memset(&packet, 0, sizeof(packet));

			// Set Disconnect Opcode
			packet.base.opcode = OPCODE_DISCONNECT;

			// Set User IP
			packet.ip = user->resolver.ip;

			// Send Data
			int iResult = send(peer->stream, (const char*)&packet, sizeof(packet), 0);
			if (iResult < 0) printf("CTL_SERVER [%s][ERROR] disconnect_user[send peer] (Socket error %d)\n", _serverName.c_str(), errno);

			// Move Pointer
			peer = peer->group_next;
		}

		// Log Leave Group
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		char safegroupstr[9];
		memset(safegroupstr, 0, sizeof(safegroupstr));
		strncpy(safegroupstr, (char *)user->group->group.data, ADHOCCTL_GROUPNAME_LEN);
		printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) left %s group %s\n", _serverName.c_str(),(char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr, safegroupstr);

		// Empty Group
		if (user->group->playercount == 0)
		{
			// Unlink Leftside (Beginning)
			if (user->group->prev == NULL) user->group->game->group = user->group->next;

			// Unlink Leftside (Other)
			else user->group->prev->next = user->group->next;

			// Unlink Rightside
			if (user->group->next != NULL) user->group->next->prev = user->group->prev;

			// Free Group Memory
			free(user->group);

			// Decrease Group Counter in Game Node
			user->game->groupcount--;
		}

		// Unlink from Group
		user->group = NULL;
		user->group_next = NULL;
		user->group_prev = NULL;

		// Update Status Log
		UpdateServerStatus();

		// Exit Function
		return;
	}

	// Not in a game group
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) attempted to leave %s group without joining one first\n", _serverName.c_str(), (char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr);
	}

	// Delete User
	LogoutUser(user);
}

void CTL_SERVER::SendScanGroupResult(SceNetAdhocctlUserNode * user) {
	// User is disconnected
	if (user->group == NULL)
	{
		// Iterate Groups
		SceNetAdhocctlGroupNode * group = user->game->group;
		for (; group != NULL; group = group->next)
		{
			// Scan Result Packet
			SceNetAdhocctlScanPacketS2C packet;

			// Clear Memory
			// memset(&packet, 0, sizeof(packet));

			// Set Opcode
			packet.base.opcode = OPCODE_SCAN;

			// Set Group Name
			packet.group = group->group;

			// Iterate Players in Network Group
			SceNetAdhocctlUserNode * peer = group->player;
			for (; peer != NULL; peer = peer->group_next)
			{
				// Found Network Founder
				if (peer->group_next == NULL)
				{
					// Set Group Host MAC
					packet.mac = peer->resolver.mac;
				}
			}

			// Send Group Packet
			int iResult = send(user->stream, (const char*)&packet, sizeof(packet), 0);
			if (iResult < 0) printf("CTL_SERVER [%s][ERROR] send_scan_result[send user] (Socket error %d)\n", _serverName.c_str(),errno);
		}

		// Notify Player of End of Scan
		uint8_t opcode = OPCODE_SCAN_COMPLETE;
		int iResult = send(user->stream, (const char*)&opcode, 1, 0);
		if (iResult < 0) printf("CTL_SERVER [%s][ERROR] send_scan_result[send peer complete] (Socket error %d)\n", _serverName.c_str(), errno);

		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		printf("CTL_SERVER [%s] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) requested information on %d %s groups\n", _serverName.c_str(), (char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], user->game->groupcount, safegamestr);

		// Exit Function
		return;
	}

	// User in a game group
	else
	{
		// Notify User
		uint8_t * ip = (uint8_t *)&user->resolver.ip;
		char safegamestr[10];
		memset(safegamestr, 0, sizeof(safegamestr));
		strncpy(safegamestr, user->game->game.data, PRODUCT_CODE_LENGTH);
		char safegroupstr[9];
		memset(safegroupstr, 0, sizeof(safegroupstr));
		strncpy(safegroupstr, (char *)user->group->group.data, ADHOCCTL_GROUPNAME_LEN);
		printf("CTL_SERVER [%s][ERROR] %s (MAC: %02X:%02X:%02X:%02X:%02X:%02X - IP: %u.%u.%u.%u) attempted to scan for %s groups without disconnecting from %s first\n", _serverName.c_str(), (char *)user->resolver.name.data, user->resolver.mac.data[0], user->resolver.mac.data[1], user->resolver.mac.data[2], user->resolver.mac.data[3], user->resolver.mac.data[4], user->resolver.mac.data[5], ip[0], ip[1], ip[2], ip[3], safegamestr, safegroupstr);
	}

	// Delete User
	LogoutUser(user);

}

bool CTL_SERVER::ValidGroupName(SceNetAdhocctlGroupName * group) {
	bool validName = true;

	for (int i = 0; i < ADHOCCTL_GROUPNAME_LEN && validName; i++) {

		// End of Name
		if (group->data[i] == 0) break;

		// A - Z
		if (group->data[i] >= 'A' && group->data[i] <= 'Z') continue;

		// a - z
		if (group->data[i] >= 'a' && group->data[i] <= 'z') continue;

		// 0 - 9
		if (group->data[i] >= '0' && group->data[i] <= '9') continue;

		// Invalid Symbol
		validName = false;
	}

	return validName;
}



/** =====================================================================================
*									Game Database Manipulation
*				This Function Below use to Link And Manage Game on User Node
* =======================================================================================
*/

/**
* Register Product or Crosslinks same game with different product Code (Mixin Adhoc Room)
* @params ctlProductCode
*/
void CTL_SERVER::GameProductLink(SceNetAdhocctlProductCode * product) {

	// Safe Product Code
	char productid[PRODUCT_CODE_LENGTH + 1];

	// Prepare Safe Product Code
	strncpy(productid, product->data, PRODUCT_CODE_LENGTH);
	productid[PRODUCT_CODE_LENGTH] = 0;

	// Crosslinked Flag
	int crosslinked = 0;

	// Exists Flag
	int exist = 0;

	for (std::vector<db_crosslink>::iterator it = crosslinks.begin(); it != crosslinks.end(); it++) {
		if (IsMatch(it->id_from, productid)) {
			// Grab Crosslink ID
			char crosslink[PRODUCT_CODE_LENGTH + 1];
			strncpy(crosslink, it->id_to, PRODUCT_CODE_LENGTH);
			crosslink[PRODUCT_CODE_LENGTH] = 0; // null terminated

												// Crosslink Product Code
			strncpy(product->data, it->id_to, PRODUCT_CODE_LENGTH);

			// Log Crosslink
			printf("CTL_SERVER [%s] Crosslinked [%s] to [%s] \n", _serverName.c_str(), productid, crosslink);

			// Set Crosslinked Flag
			crosslinked = 1;
			break;
		}
	}

	if (!crosslinked) {
		for (std::vector<db_productid>::iterator it = productids.begin(); it != productids.end(); it++) {
			if (IsMatch(it->id, productid)) {
				// Set Exists Flag
				exist = 1;
				break;
			}
		}

		if (!exist) {

			db_productid unkproduct;
			strncpy(unkproduct.id, productid, sizeof(unkproduct.id));
			strncpy(unkproduct.name, productid, sizeof(productid));
			productids.push_back(unkproduct);

			
			{
				std::unique_lock<std::mutex> lock(sql_lock);
				char query[100];

				snprintf(query, sizeof(query), "INSERT INTO PRODUCTIDS (id,name) VALUE('%s','%s')", unkproduct.id, unkproduct.name);

				if (mysql_query(&_CON, query)) {
					printf("CTL_SERVER [%s][ERROR] Failed to add Uknown Product ID [%s] to Database\n", _serverName.c_str(), productid);
				}
				else {
					printf("CTL_SERVER [%s] Added Unknown Product ID [%s] to Database\n", _serverName.c_str(), productid);
				}
			}
		}
	}
}

bool CTL_SERVER::ValidGameProduct(SceNetAdhocctlProductCode * product) {

	bool validGame = true;

	for (int i = 0; i < PRODUCT_CODE_LENGTH && validGame; i++) {

		if (product->data[i] >= 'A' && product->data[i] <= 'Z') continue;

		if (product->data[i] >= '0' && product->data[i] <= '9') continue;

		validGame = false;
	}

	return validGame;
}
/** =====================================================================================
*									CTL Server Manipulation
*		 This Function Below export CTL Server to be used by External Program
* =======================================================================================
*/
// update player status to external file
void CTL_SERVER::UpdateServerStatus(void) {
	//TO DO Create JSON Status
	FILE * log = OpenCFile(_serverName + ".json", "w");
	
	//opened log file
	if (log != NULL) {

		fprintf(log, "{\n");
		fprintf(log, "\t \"server\":\"%s\",\n", _serverName.c_str());
		fprintf(log, "\t \"totalplayer\":\"%u\",\n", _DbUserCount);
		fprintf(log, "\t \"game\":[");
		std::string gamecontent = "";
		SceNetAdhocctlGameNode * game = _DbGame; for (; game != NULL; game = game->next)
		{
			// Safe Product ID
			char productid[PRODUCT_CODE_LENGTH + 1];
			strncpy(productid, game->game.data, PRODUCT_CODE_LENGTH);
			productid[PRODUCT_CODE_LENGTH] = 0;

			std::string displayname;

			bool found = false;
			for (std::vector<db_productid>::iterator it = productids.begin(); it != productids.end(); it++) {
				if (IsMatch(it->id, productid)) {
					// Copy Game Name
					displayname = it->name;
					found = true;
					break;
				}
			}

			if (!found) {
				displayname = productid;
			}

			//open new game content child
			gamecontent += "\n\t\t{\n";

			//game content child write game name
			gamecontent += "\t\t\"name\":\"";
			gamecontent += displayname;
			gamecontent += "\",\n";

			//gamecontent child write total player on game
			gamecontent += "\t\t\"totalplayer\":\"";

			//convert into char 
			char gameplayercount[sizeof(game->playercount)];
			snprintf(gameplayercount, sizeof(gameplayercount), "%u", game->playercount);

			//write game product player count
			gamecontent += gameplayercount;
			gamecontent += "\",\n";

			// Activate Idle User Count
			uint32_t activecount = 0;

			// later user for game group array
			std::string groupContent = "";

			// Iterate Game Groups
			SceNetAdhocctlGroupNode * group = game->group; for (; group != NULL; group = group->next)
			{
				// Safe Group Name
				char groupname[ADHOCCTL_GROUPNAME_LEN + 1];
				strncpy(groupname, (const char *)group->group.data, ADHOCCTL_GROUPNAME_LEN);
				groupname[ADHOCCTL_GROUPNAME_LEN] = 0;

				std::string groupdisplayname = groupname;
				// pretty format group name
				for (std::vector<db_groupname>::iterator it = groupids.begin(); it != groupids.end(); it++) {
					if (IsMatch(it->groupid, groupname)) {
						// Copy Game Name
						groupdisplayname = it->name;
						break;
					}
				}

				//create group child
				groupContent += "\n\t\t\t{ ";

				//write group child name
				groupContent += "\"name\":\"";
				groupContent += groupdisplayname;
				groupContent += "\", ";

				//write totalplayer
				groupContent += "\"totalplayer\":\"";
				char groupcount[sizeof(group->playercount)];
				snprintf(groupcount, sizeof(groupcount), "%u", group->playercount);
				groupContent += groupcount;
				groupContent += "\", ";

				//for player username
				std::string username;

				SceNetAdhocctlUserNode * user = group->player; for (; user != NULL; user = user->group_next)
				{
					// Output User Tag + Username
					username += (const char *)user->resolver.name.data;
					username += ",";
				}

				//trim last comma on list of username
				username = username.substr(0, username.size() - 1);


				//write user
				groupContent += "\"user\":\"";
				groupContent += username;
				groupContent += "\"";

				// Output Closing Group Tag
				groupContent += "},";
				activecount += group->playercount;
			}

			// Output Idle Game Group
			if (game->playercount > activecount)
			{
				// Output Group Tag + Group Name + Idle User Count
				groupContent += "\n\t\t\t{ ";
				groupContent += "\"name\":\"Groupless\", ";
				groupContent += "\"totalplayer\":\"";

				// write total idle player on game
				char groupless[sizeof(game->playercount)];
				uint32_t grouplessvalue = game->playercount - activecount;
				snprintf(groupless, sizeof(groupless), "%u", grouplessvalue);

				groupContent += groupless;
				groupContent += "\"";
				groupContent += "},";
			}

			//trim last comma on group
			groupContent = groupContent.substr(0, groupContent.size() - 1);

			// add group content array
			gamecontent += "\t\t\"group\":[";
			gamecontent += groupContent;
			gamecontent += "\n\t\t\t]\n";


			// close game child
			gamecontent += "\t\t},";
		}

		//trim last comma on game
		gamecontent = gamecontent.substr(0, gamecontent.size() - 1);

		//print the game content loop content
		fprintf(log,"%s",gamecontent.c_str());

		//close game array
		fprintf(log, "\n\t  ]\n");
		// close json
		fprintf(log, "}\n");


		fclose(log);
	}
}

void CTL_SERVER::Stop_Thread(void) {
	CTL_SERVER:: _serverRunning = false;
}
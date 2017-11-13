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

#pragma once
#include "global.h"
#include <vector>
#include "sceNetAdhocCtlServer.h"
#include "sql.h"
FILE *OpenCFile(const std::string &filename, const char *mode);

class CTL_SERVER {
	public:
		CTL_SERVER(int, std::string,bool ppsspp);
		int Start_Thread(void);
		void Stop_Thread(void);
		virtual ~CTL_SERVER();
	private:
		int _port = 27312;
		bool _enablePPSSPP = false;
		bool _serverRunning = false;
		std::string _serverName;
		SceNetAdhocctlUserNode * _DbUser;
		SceNetAdhocctlGameNode * _DbGame;
		uint32_t _DbUserCount;

		std::vector<db_crosslink> crosslinks;
		std::vector<db_productid> productids;
		std::vector<db_groupname> groupids;

		int MainLoop(int server);
		void PopulateGameDatabase(void);
		void ProcessWaitingUser(SceNetAdhocctlUserNode * user);
		void ProcessLogedInUser(SceNetAdhocctlUserNode * user);
		void ProcessCommand(SceNetAdhocctlUserNode * user, SceNetAdhocctlCommandPacketC2S * command);
		// TCP Stream Handle
		void LoginTcpStream(int fd, uint32_t ip, uint16_t port);
		bool GetUniqueStream(SceNetAdhocctlUserNode * user, uint32_t ip, uint16_t port);
		int GetUserState(SceNetAdhocctlUserNode * user);
		void ClearRxBuf(SceNetAdhocctlUserNode * user, int clear);
		void FreeDbUser(void);

		// User Database Manipulation
		void LoginUser(SceNetAdhocctlUserNode * user, SceNetAdhocctlLoginPacketC2S * data);
		void LoginAmultiosUser(SceNetAdhocctlUserNode * user, SceNetAdhocctlLoginPacketAmultiosC2S * data);
		void SendUserMessage(int* fd, char * message);
		void SendGroupMessage(SceNetAdhocctlUserNode * user,char * message);
		bool ValidMac(SceNetEtherAddr * mac);
		bool ValidLogin(SceNetAdhocctlLoginPacketC2S * data);
		bool ValidAmultiosLogin(SceNetAdhocctlLoginPacketAmultiosC2S * data, char * message, SceNetAdhocctlUserNode * user);
		void LogoutUser(SceNetAdhocctlUserNode * user);

		// User Adhoc Group Manipulation
		void ConnectUserGroup(SceNetAdhocctlUserNode * user, SceNetAdhocctlGroupName * group);
		void DisconnectUserGroup(SceNetAdhocctlUserNode * user);
		void SendScanGroupResult(SceNetAdhocctlUserNode * user);
		bool ValidGroupName(SceNetAdhocctlGroupName * group);

		// Game Database Manipulation
		void GameProductLink(SceNetAdhocctlProductCode * product);
		bool ValidGameProduct(SceNetAdhocctlProductCode * product);

		// Server External File Status Manipulation
		void UpdateServerStatus(void);
		
};
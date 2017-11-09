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
#include <stdint.h>
#include <time.h>


#ifdef _MSC_VER
#define PACK  // on MSVC we use #pragma pack() instead so let's kill this.
#else
#define PACK __attribute__((packed))
#endif


// Pro Adhoc Server Packets Opcodes
#define OPCODE_PING 0
#define OPCODE_LOGIN 1
#define OPCODE_CONNECT 2
#define OPCODE_DISCONNECT 3
#define OPCODE_SCAN 4
#define OPCODE_SCAN_COMPLETE 5
#define OPCODE_CONNECT_BSSID 6
#define OPCODE_CHAT 7
#define OPCODE_GLOBAL_CHAT 8
#define OPCODE_AMULTIOS_LOGIN 9
#define OPCODE_AMULTIOS_LOGIN_SUCCESS 10
#define OPCODE_AMULTIOS_LOGIN_FAILED 11
#define OPCODE_AMULTIOS_COMMAND 12


// PSP Product Code
#define PRODUCT_CODE_LENGTH 9
#define PIN_LENGTH 6

#ifdef _MSC_VER 
#pragma pack(push,1) 
#endif

#define ETHER_ADDR_LEN 6
typedef struct SceNetEtherAddr {
	uint8_t data[ETHER_ADDR_LEN];
} PACK SceNetEtherAddr;

#define ADHOCCTL_NICKNAME_LEN 128
typedef struct SceNetAdhocctlNickname {
	uint8_t data[ADHOCCTL_NICKNAME_LEN];
} PACK SceNetAdhocctlNickname;

#define ADHOCCTL_GROUPNAME_LEN 8
typedef struct SceNetAdhocctlGroupName {
	uint8_t data[ADHOCCTL_GROUPNAME_LEN];
} PACK SceNetAdhocctlGroupName;

typedef struct {
	// Game Product Code (ex. ULUS12345)
	char data[PRODUCT_CODE_LENGTH];
} PACK SceNetAdhocctlProductCode;

// Basic Packet
typedef struct {
	uint8_t opcode;
} PACK SceNetAdhocctlPacketBase;

// C2S Login Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetEtherAddr mac;
	SceNetAdhocctlNickname name;
	SceNetAdhocctlProductCode game;
} PACK SceNetAdhocctlLoginPacketC2S;

// C2S Amultios Login Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetEtherAddr mac;
	SceNetAdhocctlNickname name;
	SceNetAdhocctlProductCode game;
	char pin[PIN_LENGTH];
} PACK SceNetAdhocctlLoginPacketAmultiosC2S;

// C2S Connect Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetAdhocctlGroupName group;
} PACK SceNetAdhocctlConnectPacketC2S;

// C2S Chat Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	char message[64];
} PACK SceNetAdhocctlChatPacketC2S;

// S2C Connect Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetAdhocctlNickname name;
	SceNetEtherAddr mac;
	uint32_t ip;
} PACK SceNetAdhocctlConnectPacketS2C;

// S2C Disconnect Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	uint32_t ip;
} PACK SceNetAdhocctlDisconnectPacketS2C;

// S2C Scan Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetAdhocctlGroupName group;
	SceNetEtherAddr mac;
} PACK SceNetAdhocctlScanPacketS2C;

// S2C Connect BSSID Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	SceNetEtherAddr mac;
} PACK SceNetAdhocctlConnectBSSIDPacketS2C;

// S2C Chat Packet
typedef struct {
	SceNetAdhocctlChatPacketC2S base;
	SceNetAdhocctlNickname name;
} PACK SceNetAdhocctlChatPacketS2C;

// S2C Notify Packet
typedef struct {
	SceNetAdhocctlPacketBase base;
	char reason[64];
} PACK SceNetAdhocctlNotifyPacketS2C;

// S2C Command Packet
#define COMMAND_LENGTH 10
typedef struct {
	SceNetAdhocctlPacketBase base;
	char command[COMMAND_LENGTH];
	char pin[PIN_LENGTH];
	char target[ADHOCCTL_NICKNAME_LEN];
} PACK SceNetAdhocctlCommandPacketC2S;


#ifdef _MSC_VER 
#pragma pack(pop)
#endif

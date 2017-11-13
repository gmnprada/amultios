#include <signal.h>
#include <stdlib.h>
#ifdef _WIN32
#include <WS2tcpip.h>
#endif
#include "chatServer.h"

std::thread sqltimer;
std::thread PPSSPP;
std::thread Midgard;
std::thread Asgard;
std::thread Vanaheim;
std::thread Alfheim;
std::thread Helheim;
std::thread ChatServer;

#ifdef _WIN32
BOOL WINAPI ConsoleHandler(DWORD dwType)
{
	switch (dwType) {
	case CTRL_C_EVENT:
		printf("Control + C\n");
		TerminateServer();
		if (connection) {
			std::unique_lock<std::mutex> lock(sql_lock);
			SQL::closeSQL();
		}
		break;
	case CTRL_BREAK_EVENT:
		printf("Control + Break\n");
		break;
	default:
		printf("Some Close Event");
	}
	return TRUE;
}
#else
void interrupt(int sig) {
	printf("Shutting down amultios server \n");
	TerminateServer();
	if (connection) {
		std::unique_lock<std::mutex> lock(sql_lock);
		SQL::closeSQL();
	}
}
#endif // _WIN32

int main(){

	InitLog();

	//create mysql connection
	{
		std::unique_lock<std::mutex> lock(sql_lock);
		SQL::initSQL();
		SQL::connectSQL();
	}

	// terminate program database not found
	if (!connection) {

#ifdef _WIN32
		system("pause");
#else
		system("read");
#endif
		return EXIT_SUCCESS;
	}

	RunServer();

	//start mysql timer
	sqltimer = std::thread(keepAliveThread);

#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE)) {
		//console->info("Unable to install handler");
		return EXIT_FAILURE;
	}
#else
	// Create Signal Receiver for CTRL + C
	signal(SIGINT, interrupt);

	// Create Signal Receiver for kill / killall
	signal(SIGTERM, interrupt);

#endif

	// CTL Server for PPSSPP Emulator Build
	PPSSPP = std::thread(&CTL_SERVER::Start_Thread, CTL_SERVER(27312, "PPSSPP",true));
	// CTL Server For Amultios Emulator Build
	Midgard = std::thread(&CTL_SERVER::Start_Thread, CTL_SERVER(27313, "Midgard",false));
	Asgard = std::thread(&CTL_SERVER::Start_Thread, CTL_SERVER(27314, "Asgard",false));
	//Vanaheim = std::thread(&CTL_SERVER::Start_Thread, CTL_SERVER(27315, "Vanaheim"));
	//Alfheim = std::thread(&CTL_SERVER::Start_Thread, CTL_SERVER(27316, "Alfheim"));
	//Helheim = std::thread(&CTL_SERVER::Start_Thread, CTL_SERVER(27317, "Helheim"));
	
	ChatServer = std::thread(&CHAT_SERVER::Start_Thread, CHAT_SERVER());
#ifdef _WIN32
	WSACleanup();
#endif //  _WIN32

	if (ChatServer.joinable()) {
		ChatServer.join();
	}

	if (Midgard.joinable()) {
		Midgard.join();
	}
	if (Asgard.joinable()) {
		Asgard.join();
	}

	if (Vanaheim.joinable()) {
		Vanaheim.join();
	}

	if (Alfheim.joinable()) {
		Alfheim.join();
	}

	if (Helheim.joinable()) {
		Helheim.join();
	}

	if (sqltimer.joinable()) {
		sqltimer.join();
	}

    return EXIT_SUCCESS;
}
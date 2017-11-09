#include "global.h"

std::mutex g_mutex;
bool g_amultios;
std::condition_variable g_cond;


//TO DO Integrate PPSSPP Log Manager
void InitLog() {

}

void RunServer() {
	std::unique_lock<std::mutex> lock(g_mutex);
	g_amultios = true;
}

void TerminateServer() {
	std::unique_lock<std::mutex> lock(g_mutex);
	g_amultios = false;
}
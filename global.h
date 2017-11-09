#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>


extern std::mutex g_mutex;
extern bool g_amultios;
//extern std::condition_variable g_cond;

extern void InitLog(void);
extern void RunServer();
extern void TerminateServer();
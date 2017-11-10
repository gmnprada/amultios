#pragma once

#include <my_global.h>
#include <mysql.h>
#include "global.h"

#define DB_HOST "localhost"
#define DB_USERNAME "root"
#define DB_PASSWORD ""
#define DB_DATABASE "m_amultios"

extern MYSQL _CON;
extern bool connection;
extern std::mutex sql_lock;


void keepAliveThread();
namespace SQL {

extern void initSQL();
extern void connectSQL();
extern void closeSQL();

}
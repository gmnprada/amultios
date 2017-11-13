#include <time.h>
#include <sceNetAdhocCtlServer.h>
#include "sql.h"

#ifdef _WIN32
#else
#include <unistd.h>
#endif

//Global Shared SQL Object Connection
MYSQL _CON;
bool connection = false;

// SQL object lock
std::mutex sql_lock;

// Keep ALive Global MYSQL Connection
clock_t begin_time;
bool keepAliveRunning = false;

namespace SQL {


void initSQL() {
	begin_time = clock();
	mysql_init(&_CON);
}

void connectSQL() {
	if (mysql_real_connect(&_CON, DB_HOST, DB_USERNAME, DB_PASSWORD, DB_DATABASE, 0, NULL, 0) == NULL) {
		printf("MYSQL_SERVER [%s]: Failed to connect to database [%s] username [%s] password [%s]\n",DB_HOST, mysql_error(&_CON), DB_USERNAME,DB_PASSWORD);
	}
	else {
		printf("MYSQL_SERVER [%s] : Connected to Database\n",DB_HOST);
		connection = true;
		mysql_query(&_CON, "update users set online = 0 , server = null where 1;");
	}
}


void closeSQL() {
	mysql_query(&_CON, "update users set online = 0 , server = null where 1;");
	mysql_close(&_CON);
	connection = false;
}

}

/*

	This Thread Job is to maintain MYSQL Connection

*/
void keepAliveThread() {

	float interval;
	int one_hour = 3600;
	printf("MYSQL_SERVER [%s] : Starting Keep Alive Thread\n", DB_HOST);
	while (g_amultios) {
		//printf("MYSQL_SERVER Keep Alive Counting");
		interval = float(clock() - begin_time) / CLOCKS_PER_SEC;

		if (interval > one_hour) {
			//reset the timer
			begin_time = clock();

			if (mysql_query(&_CON,"SELECT 1;") !=0) {
				if (g_amultios) {
					std::unique_lock<std::mutex> lock(sql_lock);
					SQL::closeSQL();
					SQL::initSQL();
					SQL::connectSQL();
				}
			}
			else {
				printf("MYSQL_SERVER [%s] : PING the database %.2f \n", DB_HOST, interval);
			}
		}
		// count every 10 second
#ifdef _WIN32
		Sleep(10 * 1000);
#else
		usleep(10 * 1000 * 1000);
#endif

	}


}
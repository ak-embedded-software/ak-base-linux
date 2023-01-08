#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "app_data.h"
#include "app_dbg.h"
#include "app_if.h"

if_app_t if_app_list[] = {
	/*	[id]				[socket_path]							[location_path]									[enable_laucher]*/
	{	IF_TYPE_APP_GMNG,	(char*)"/tmp/gateway_app_manager",		(char*)"/usr/local/bin/gateway_app_manager",	ENABLE_LAUNCHER		},
	{	IF_TYPE_APP_GW,		(char*)"/tmp/gateway",					(char*)"/usr/local/bin/gateway",				ENABLE_LAUNCHER		},
	{	IF_TYPE_APP_GI,		(char*)"/tmp/gateway_ui",				(char*)"/usr/local/bin/gateway_ui",				ENABLE_LAUNCHER		},
};

uint32_t if_app_list_size = sizeof(if_app_list)/sizeof(if_app_list[0]);

void show_app_table() {
	APP_DBG("\n[APPS TABLE]\n");
	APP_DBG("%-10s%-40s%-40s%-40s%-40s\n", "[id]", "[socket_path]", "[location_path]", "[enable_laucher]", "[pid]");
	for (uint32_t i = 0; i < if_app_list_size; i++) {
		APP_DBG("%-10d%-30s%-30s%-30s%-30d\n", if_app_list[i].id	\
				, if_app_list[i].socket_path	\
				, if_app_list[i].location_path	\
				, (const char*)((if_app_list[i].enable_launcher == ENABLE_LAUNCHER) ? "ENABLE_LAUNCHER" : "DISABLE_LAUNCHER")	\
				, if_app_list[i].pid);
	}
}

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>

#include "app.h"
#include "app_if.h"
#include "app_data.h"
#include "app_dbg.h"

#include "task_list.h"
#include "task_list_if.h"
#include "task_debug.h"

#include "link.h"
#include "link_sig.h"

#define UnitTest(fmt, ...)	__LOG__(fmt, "UnitTest", ##__VA_ARGS__)

q_msg_t gw_task_debug_mailbox;

using namespace std;

void fopen_s(FILE ** file_pointer, const char * fname, const char * mode) {
	*file_pointer = fopen(fname, mode);
}

void* gw_task_debug_entry(void*) {
	ak_msg_t* msg = AK_MSG_NULL;

	wait_all_tasks_started();

	APP_DBG("[STARTED] gw_task_debug_entry\n");

	while (1) {
		/* get messge */
		msg = ak_msg_rev(GW_TASK_DEBUG_ID);

		switch (msg->header->sig) {

		default:
			break;
		}

		/* free message */
		ak_msg_free(msg);
	}

	return (void*)0;
}

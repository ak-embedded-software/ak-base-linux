#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/stat.h>

#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "ak.h"
#include "timer.h"

#include "cmd_line.h"

#include "app.h"
#include "app_if.h"
#include "app_dbg.h"
#include "app_config.h"
#include "shell.h"

#include "link.h"
#include "link_sig.h"

#include "task_list.h"
#include "task_list_if.h"

static int32_t shell_ver(uint8_t* argv);
static int32_t shell_help(uint8_t* argv);
static int32_t shell_dbg(uint8_t* argv);
static int32_t shell_fw(uint8_t* argv);

uint8_t FW_Link_Request_Frame[] = { \
	/* header */\
	0xef, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x6a, 0x32, 0x6b, \
	/* data */ \
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1, 0x0, 0x6a, 0x1, 0x0, 0x12, 0x0, 0x38, 0xff, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x1, 0x0, 0x6, 0x0, 0x80, 0xff, 0x7, 0xb, 0x80, 0x79, 0x40, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
};

cmd_line_t lgn_cmd_table[] = {
	{(const int8_t*)"ver",		shell_ver,		(const int8_t*)"get kernel version"},
	{(const int8_t*)"help",		shell_help,		(const int8_t*)"help command info"},
	{(const int8_t*)"dbg",		shell_dbg,		(const int8_t*)"debug"},
	{(const int8_t*)"fw",		shell_fw,		(const int8_t*)"firmware update"},

	/* End Of Table */
	{(const int8_t*)0,(pf_cmd_func)0,(const int8_t*)0}
};

int32_t shell_ver(uint8_t* argv) {
	(void)argv;
	APP_PRINT("version: %s\n", AK_VERSION);
	return 0;
}

int32_t shell_help(uint8_t* argv) {
	uint32_t idx = 0;
	switch (*(argv + 4)) {
	default:
		APP_PRINT("\nCOMMANDS INFORMATION:\n\n");
		while(lgn_cmd_table[idx].cmd != (const int8_t*)0) {
			APP_PRINT("%s\n\t%s\n\n", lgn_cmd_table[idx].cmd, lgn_cmd_table[idx].info);
			idx++;
		}
		break;
	}
	return 0;
}

int32_t shell_dbg(uint8_t* argv) {
	switch (*(argv + 4)) {

	case 'f': {
		FATAL("Test Safe Exit", 0x01);
	}
		break;

	default:
		break;
	}

	return 0;
}

int32_t shell_fw(uint8_t* argv) {
	switch (*(argv + 3)) {
	case 'b': {
		APP_PRINT("[shell_fw] update slave boot request\n");
		gateway_fw_dev_update_req_t gateway_fw_dev_update_req;
		memset(&gateway_fw_dev_update_req, 0, sizeof(gateway_fw_dev_update_req_t));
		strcpy(gateway_fw_dev_update_req.dev_bin_path, "/home/lenovo/workspace/dev/GaoKong/ak-base-kit-stm32l151/boot/build_ak-base-kit-stm32l151-boot/ak-base-kit-stm32l151-boot.bin");
		gateway_fw_dev_update_req.type_update   = TYPE_UPDATE_TARTGET_BOOT;
		gateway_fw_dev_update_req.source_if_type = IF_TYPE_UART_GW;
		gateway_fw_dev_update_req.target_task_id = AC_TASK_FW_ID;
		gateway_fw_dev_update_req.target_if_type = IF_TYPE_UART_AC;

		ak_msg_t* s_msg = get_dynamic_msg();
		set_msg_sig(s_msg, GW_FW_OTA_REQ);
		set_data_dynamic_msg(s_msg, (uint8_t*)&gateway_fw_dev_update_req, sizeof(gateway_fw_dev_update_req_t));
		set_msg_src_task_id(s_msg, GW_TASK_CONSOLE_ID);
		task_post(GW_TASK_FW_ID, s_msg);
	}
		break;

	case 'a': {
		APP_PRINT("[shell_fw] update slave app request\n");
		gateway_fw_dev_update_req_t gateway_fw_dev_update_req;
		memset(&gateway_fw_dev_update_req, 0, sizeof(gateway_fw_dev_update_req_t));
		strcpy(gateway_fw_dev_update_req.dev_bin_path, "/home/lenovo/workspace/dev/GaoKong/ak-base-kit-stm32l151/application/build_ak-base-kit-stm32l151-application/ak-base-kit-stm32l151-application.bin");

		gateway_fw_dev_update_req.type_update   = TYPE_UPDATE_TARTGET_APP;
		gateway_fw_dev_update_req.source_if_type = IF_TYPE_UART_GW;
		gateway_fw_dev_update_req.target_task_id = AC_TASK_FW_ID;
		gateway_fw_dev_update_req.target_if_type = IF_TYPE_UART_AC;

		ak_msg_t* s_msg = get_dynamic_msg();
		set_msg_sig(s_msg, GW_FW_OTA_REQ);
		set_data_dynamic_msg(s_msg, (uint8_t*)&gateway_fw_dev_update_req, sizeof(gateway_fw_dev_update_req_t));
		set_msg_src_task_id(s_msg, GW_TASK_CONSOLE_ID);
		task_post(GW_TASK_FW_ID, s_msg);
	}
		break;

	case 'r': {
		APP_PRINT("[shell_fw] update slave app request via rf24\n");
		gateway_fw_dev_update_req_t gateway_fw_dev_update_req;
		memset(&gateway_fw_dev_update_req, 0, sizeof(gateway_fw_dev_update_req_t));
		strcpy(gateway_fw_dev_update_req.dev_bin_path, "/home/lenovo/workspace/dev/GaoKong/ak-base-kit-stm32l151/application/build_ak-base-kit-stm32l151-application/ak-base-kit-stm32l151-application.bin");
		gateway_fw_dev_update_req.type_update   = TYPE_UPDATE_TARTGET_APP;
		gateway_fw_dev_update_req.source_if_type = IF_TYPE_RF24_GW;
		gateway_fw_dev_update_req.target_task_id = AC_TASK_FW_ID;
		gateway_fw_dev_update_req.target_if_type = IF_TYPE_RF24_AC;

		ak_msg_t* s_msg = get_dynamic_msg();
		set_msg_sig(s_msg, GW_FW_OTA_REQ);
		set_data_dynamic_msg(s_msg, (uint8_t*)&gateway_fw_dev_update_req, sizeof(gateway_fw_dev_update_req_t));
		set_msg_src_task_id(s_msg, GW_TASK_CONSOLE_ID);
		task_post(GW_TASK_FW_ID, s_msg);
	}
		break;

	default:
		break;
	}

	return 0;
}

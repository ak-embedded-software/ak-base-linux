#include "timer.h"

#include "task_list.h"

ak_task_t task_list[] = {
	/* SYSTEM TASKS */
	{	AK_TASK_TIMER_ID,				TASK_PRI_LEVEL_1,	timer_entry						,	&timer_mailbox						,	"timer service"			},

	/* APP TASKS */
	{	GW_TASK_IF_CONSOLE_ID,			TASK_PRI_LEVEL_8,	gw_task_if_console_entry		,	&gw_task_if_console_mailbox			,	"terminal gate"			},
	{	GW_TASK_CONSOLE_ID,				TASK_PRI_LEVEL_8,	gw_task_console_entry			,	&gw_task_console_mailbox			,	"handle commands"		},
	{	GW_TASK_IF_ID,					TASK_PRI_LEVEL_1,	gw_task_if_entry				,	&gw_task_if_mailbox					,	"task if"				},
	{	GW_TASK_DEBUG_ID,				TASK_PRI_LEVEL_1,	gw_task_debug_entry				,	&gw_task_debug_mailbox				,	"task debug message"	},
	{	GW_TASK_IF_APP_ID,				TASK_PRI_LEVEL_1,	gw_task_if_app_entry			,	&gw_task_if_app_mailbox				,	"if app socket"			},
	{	GW_TASK_IF_CPU_SERIAL_ID,		TASK_PRI_LEVEL_1,	gw_task_if_cpu_serial_entry		,	&gw_task_if_cpu_serial_mailbox		,	"cpu serial interface"	},
	{	GW_TASK_FW_ID,					TASK_PRI_LEVEL_1,	gw_task_fw_entry				,	&gw_task_fw_mailbox					,	"firmware update"		},

	/* LINK TASKS */
	{	GW_LINK_PHY_ID,					TASK_PRI_LEVEL_3,	gw_task_link_phy_entry			,	&gw_task_link_phy_mailbox			,	"link phy"				},
	{	GW_LINK_MAC_ID,					TASK_PRI_LEVEL_2,	gw_task_link_mac_entry			,	&gw_task_link_mac_mailbox			,	"link mac"				},
	{	GW_LINK_ID,						TASK_PRI_LEVEL_1,	gw_task_link_entry				,	&gw_task_link_mailbox				,	"link"					},
};

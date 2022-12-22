include sources/app/interfaces/Makefile.mk

CXXFLAGS	+= -I./sources/app

VPATH += sources/app

OBJ += $(OBJ_DIR)/app.o
OBJ += $(OBJ_DIR)/app_config.o
OBJ += $(OBJ_DIR)/app_data.o
OBJ += $(OBJ_DIR)/shell.o

OBJ += $(OBJ_DIR)/task_console.o
OBJ += $(OBJ_DIR)/task_debug.o
OBJ += $(OBJ_DIR)/task_fw.o
OBJ += $(OBJ_DIR)/task_if.o
OBJ += $(OBJ_DIR)/task_list.o

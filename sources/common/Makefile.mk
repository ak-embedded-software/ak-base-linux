CXXFLAGS	+= -I./sources/common

VPATH += sources/common

OBJ += $(OBJ_DIR)/base64.o
OBJ += $(OBJ_DIR)/cmd_line.o
OBJ += $(OBJ_DIR)/fifo.o
OBJ += $(OBJ_DIR)/firmware.o

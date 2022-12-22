CXXFLAGS	+= -I./sources/app/interfaces

VPATH += sources/app/interfaces

OBJ += $(OBJ_DIR)/if_app.o
OBJ += $(OBJ_DIR)/if_console.o
OBJ += $(OBJ_DIR)/if_cpu_serial.o

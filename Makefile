SRC_DIR	 = src
INC_DIR	 = include

CC 	 = gcc
DEPFLAGS = -MP -MD
C_FLAGS  = -Wall -Wextra -Werror $(DEPFLAGS) -I $(INC_DIR)
C_DEP	 = -lcrypto
DEPFLAGS = -MP -MD

EXE	 = hashdog
CFILES	 = $(foreach D,$(SRC_DIR),$(wildcard $(D)/*.c))
OBJECTS	 = $(patsubst %.c,%.o,$(CFILES))
DEPFILES = $(patsubst %.c,%.d,$(CFILES))

DOCK_IMG = $(EXE)
DOCK_CON = $(DOCK_IMG)



all: compile

compile: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $^ -o $@ $(C_DEP)

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

docker_build:
	sudo docker build -t $(DOCK_IMG) .

docker_run:
	sudo docker run -t -d --name $(DOCK_CON) $(DOCK_IMG)

docker_exec:
	sudo docker exec -it $(DOCK_CON) bash

docker_stop:
	sudo docker stop $(DOCK_CON)

docker_rm:
	sudo docker rm $(DOCK_CON)

clean:
	rm -rf $(EXE) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)

.PHONY: all compile clean

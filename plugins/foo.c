#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <event/EventServices.h>
#include <event/PlayerChatEvent.h>
#include <event/PlayerConnectEvent.h>
#include <Console.h>

void onConnect(PlayerConnectEvent* evt) {
	printf("foo: %s has connected\n", evt->player.name);
}

void onChat(PlayerChatEvent* evt) {
		
	printf("foo: %s\n", evt->message);
	if (evt->message[0] == '/') {
		char* args;
		char* message = malloc(strlen(evt->message));
		
		strcpy(message, evt->message);
		args = strtok(message, " ");
		if (strcmp(message, "/foo") == 0) {
			char cmd[64];
			sprintf(cmd, "tellraw %s §6§lbar", evt->player.name);
			runCommand(cmd);
		}
		
		free(message);
	}
	
	
}

void onLoad() {
	subscribeToPicketEvent(PLAYER_CONNECT_EVENT, onConnect);
	subscribeToPicketEvent(PLAYER_CHAT_EVENT, onChat);
	printf("foo has been loaded\n");
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <event/EventServices.h>
#include <event/PlayerChatEvent.h>
#include <event/PlayerCommandEvent.h>
#include <event/PlayerConnectEvent.h>
#include <Console.h>

void onConnect(PlayerConnectEvent* evt) {
	printf("foo: %s has connected\n", evt->player.name);
}

void onChat(PlayerChatEvent* evt) {
	printf("foo: %s\n", evt->message);
}

void onCommand(PlayerCommandEvent* evt) {
	printf("foo: command: %s\n", evt->command);
	
	if (strcmp(evt->command, "foo") == 0) {
		char cmd[64];
		sprintf(cmd, "tellraw %s §6§lbar", evt->player.name);
		runCommand(cmd);
	}
}

void onLoad() {
	subscribeToPicketEvent(PLAYER_CONNECT_EVENT, onConnect);
	subscribeToPicketEvent(PLAYER_CHAT_EVENT, onChat);
	subscribeToPicketEvent(PLAYER_COMMAND_EVENT, onCommand);
	printf("foo has been loaded\n");
}

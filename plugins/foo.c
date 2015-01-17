#include <stdio.h>

#include <event/EventServices.h>
#include <event/PlayerConnectEvent.h>

void onConnect(PlayerConnectEvent evt) {
	printf("Foo: %s has connected\n", evt.player.name);
}

void onLoad() {
	subscribeToPicketEvent(PLAYER_CONNECT_EVENT, onConnect);
	printf("Foo has been loaded\n");
}

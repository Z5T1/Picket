#!/bin/bash

case "$1" in
"start")
	source picket.config

	screen -d -m -S $screen

	screen -p 0 -S $screen -X stuff "$server_command"$(printf \\r)

	./picket \
		--plugins $plugins \
		--max-players $max_players \
		--interface $interface \
		--port $port
	;;
"start-picket")
	source picket.config

	./picket \
		--plugins $plugins \
		--max-players $max_players \
		--interface $interface \
		--port $port
	;;
"stop")
	source picket.config

	screen -p 0 -S $screen -X stuff "stop"$(printf \\r)
	screen -p 0 -S $screen -X quit
	;;
"setup")
	if [ "$USER" != "root" ]; then
		echo "Picket must be setup as root"
		exit
	fi
	setcap cap_net_raw,cap_net_admin=eip ./picket
	;;
*)
	echo "Usage: $0 <start|stop|setup>"
	;;
esac

exit

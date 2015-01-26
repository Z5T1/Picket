#!/bin/bash

case "$1" in
"start")
	echo "Starting the Minecraft server and Picket"

	source picket.config

	screen -p 0 -S $screen -X quit > /dev/null
	screen -d -m -S $screen

	screen -p 0 -S $screen -X stuff "$server_command"$(printf \\r)

	./picket \
		--plugins $plugins \
		--max-players $max_players \
		--interface $interface \
		--port $port
	;;
"start-picket")
	echo "Starting Picket"
	echo "All players must rejoin the Minecraft server now"

	source picket.config

	./picket \
		--plugins $plugins \
		--max-players $max_players \
		--interface $interface \
		--port $port
	;;
"stop")
	echo "Stopping the Minecraft server"

	source picket.config

	screen -p 0 -S $screen -X stuff "stop"$(printf \\r) > /dev/null
	screen -p 0 -S $screen -X quit > /dev/null
	;;
"setup")
	if [ "$USER" != "root" ]; then
		echo "Picket must be setup as root"
		exit
	fi
	echo "Setting up Picket..."
	
	setcap cap_net_raw,cap_net_admin=eip ./picket
	
	echo "Done"
	;;
*)
	echo "Usage: $0 <start|start-picket|stop|setup>"
	;;
esac

exit

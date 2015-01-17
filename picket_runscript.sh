#!/bin/bash

source picket.config

./picket \
	--plugins $plugins \
	--max-players $max_players \
	--interface $interface \
	--port $port

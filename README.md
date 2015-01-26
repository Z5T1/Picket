# Picket

Picket is a server side plugin system for Minecraft multiplayer. It
works by sniffing the packets going to/from the server, allowing it to
work across different versions of Minecraft and with various mods.

## Dependencies

Picket requires the following dependencies to be installed:

* libpcap
* GNU screen

## Building

Building Picket is similar to building any other C program. It should
only require typing `make` at the root directory. Once this is complete,
run `./picket_runscript.sh setup` as root. This grants the Picket
executable permission to sniff network traffic.

## Running Picket

Once Picket is built, simply run `./picket_runscript.sh start` to start
Picket. To stop Picket, press ^C and then run
`./picket_runscript.sh stop`

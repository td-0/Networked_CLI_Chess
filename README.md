# Networked CLI Chess

This is a command line based chess game for Linux machines that supports local and remote two player games.

## Compilation/Installation
To install, clone or download the repo and use the **make** command. Then simply type **./cli-chess** to begin.
There is also a .deb file available for users running Debian or Ubuntu based linux distributions.

## Playing the Game
A game can be played by two players locally on one machine or over LAN. 
Online play is also available, but requires port-forwarding by the host for port 8025.

## Under the Hood
Networked play was created through direct C++ socket programming.

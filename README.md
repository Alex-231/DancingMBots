# DancingMBots
A script for Makeblock mBots and Arduino.

## Purpose
This script can be used to make mBots dance in unison.
The host bot randomly generates a string of letters and sends the string to other bots using the infrared transmitter.
When other bots recieve the string, they split the characters. Each character represents a different dance move. These are predefined and can be edited, new moves can be added too.

## Room For Improvement
The script was written an assignment project, and hardware was limited.
This could be improved using a wireless connection to control all of the bots from a host machine, which could allow a user to override the string, and send a custom string of dance moves. Additionally, there's no recovery code. If a bot hits an obsticle it's likely that their position/rotation will be offset for the rest of the sequence.

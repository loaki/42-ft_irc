#!/bin/bash

docker pull ghcr.io/ergochat/ergo:stable

docker volume create ergo-data

docker run -d --name ergo -v ergo-data:/ircd -p 6667:6667 -p 6697:6697 ghcr.io/ergochat/ergo:stable

python proxy-irc/proxy.py testnet.ergo.chat 6667 8888

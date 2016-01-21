#!/bin/bash
set -ev

sudo add-apt-repository --yes ppa:beineri/opt-qt551-trusty
sudo apt-get update -qq

sudo apt-get install qt55base qt55serialport qt55tools

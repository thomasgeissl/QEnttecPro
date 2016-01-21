#!/bin/bash
set -ev

sudo apt-get update -qq
sudo apt-add-repository -y ppa:beineri/opt-qt56-beta-trusty
sudo apt-get update -qq

sudo apt-get install -qq qt56base qt56serialport qt56tools

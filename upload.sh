#!/usr/bin/env bash

PROJECT=$1

./compile.sh "${PROJECT}"
arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:uno "${PROJECT}"

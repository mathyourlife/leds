#!/usr/bin/env bash

PROJECT=$1

arduino-cli compile --fqbn arduino:avr:uno "${PROJECT}"
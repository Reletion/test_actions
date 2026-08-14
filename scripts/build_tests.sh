#!/usr/bin/env bash

WORKING_DIRECTORY="${1:-../tests}"
BUILD_DIRECTORY="$WORKING_DIRECTORY/build"

CMAKE_ARGS=${@:2}

NC="\033[0m"
BOLD="\033[1m"

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"

set -e
echo -e "${BOLD}${YELLOW}Starting script...${NC}\n"

mkdir -p $BUILD_DIRECTORY

cmake ${CMAKE_ARGS[@]} -B $BUILD_DIRECTORY -S $WORKING_DIRECTORY 
cmake --build $BUILD_DIRECTORY

echo -e "\n\n${BOLD}${GREEN}Tests are built${NC}\n"

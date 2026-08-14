#!/usr/bin/env bash

#BASH SCRIPT FOR BUILDING LIBSIM PROJECT

#Versions
LIBRARY_VERSION="0.0.1"
SCRIPT_VERSION="0.5"

#Flags
BUILD_TESTS=${1:-"-b"}

#Directories

WORKING_DIRECTORY=${2:-".."}
BUILD_DIRECTORY="$WORKING_DIRECTORY/build"
TMP_DIR="$BUILD_DIRECTORY/output"
INSTALL_DIR="$TMP_DIR/libsim"
API_DIR="$TMP_DIR/.cmake/api/v1"
required_utilities=("cmake" "jq")

#Colors
BOLD="\033[1m"
NC="\033[0m"

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"

CMAKE_ARGS=${@:3}
set -e

#Show help

case "$1" in

	-h|--help)

	cat<<-EOF
	===========================================================
	build.sh is a script for building libsim library with cmake

	Usage:
	        build.sh [OPTIONS]
	        build.sh [-b|-p] [WORKING DIRECTORY=".."] [CMAKE ARGUMENTS]
	OPTIONS:
	        -h, --help 		print help
	        -v, --version		print version of script and library
	ARGUMENTS:
		[-b|-p]			flag of building tests
					-b build all tests
					-p pass building
					default: -b

		[WORKING DIRECTORY]	working directory (default: "..")

		[CMAKE ARGUMENTS]	arguments for cmake building the library
	===========================================================
	EOF
	exit 0
	;;

	-v|--version)

	cat<<-EOF
	==================================
	Library version: $LIBRARY_VERSION
	Script version: $SCRIPT_VERSION
	==================================
	EOF
	exit 0
	;;
esac


case "$BUILD_TESTS" in
	"-b"|"-p")
	;;
	*)
		echo -e "${BOLD}${RED}Cannot recognize $BUILD_TESTS"
		exit 1
	;;
esac

#Finding distro

echo -e "${BOLD}${YELLOW}Starting script...${NC}\n\n"

if command -v lsb_release &> /dev/null; then
	DISTRO=$(lsb_release -is | tr '[:upper:]' '[:lower:]')
else
	DISTRO=$(grep '^ID=' /etc/os-release | cut -d= -f2 | tr -d '"' | tr '[:upper:]' '[:lower:]')
fi

echo "Distro name: $DISTRO"

if command -v apt &> /dev/null; then
	PACKAGE_MANAGER=apt
	INSTALL_COMMAND=install
elif command -v dnf &> /dev/null; then
	PACKAGE_MANAGER=dnf
	INSTALL_COMMAND=install
elif command -v yum &> /dev/null; then
	PACKAGE_MANAGER=yum
	INSTALL_COMMAND=install
elif command -v pacman &> /dev/null; then
	PACKAGE_MANAGER=pacman
	INSTALL_COMMAND=-S
elif command -v zypper &> /dev/null; then
	PACKAGE_MANAGER=zypper
	INSTALL_COMMAND=install
else
	echo -e "${RED}${BOLD}Cannot specify package manager${NC}"
	exit 1
fi

echo "Package manager name: $PACKAGE_MANAGER"

echo -e "\n"


#Finding utilities

echo -e "${YELLOW}Checking utilities${NC}\n"

for utulity in "${required_utilities[@]}"; do
	echo "utulity: $utulity"
	if command -v $utulity  &> /dev/null; then
		echo -e "${GREEN}$utulity downloaded${NC}"
	else
		read -p "$(printf "${RED}${utulity} is not downloaded. Would you install ${utulity}?${NC} (Y/n): ")"  response

		case "$response" in
			[yY][eE][sS] | [yY])
				sudo $PACKAGE_MANAGER $INSTALL_COMMAND  $utulity
			;;
			*)
				exit 1
			;;
		esac
	fi

	echo -e "\n"
done

#Creating build directory

echo -e "${YELLOW}Creating temporary build directory in $TMP_DIR${NC}\n"

mkdir -p $TMP_DIR

#Configuring project
echo -e "${YELLOW}Configuring cmake${NC}\n"

mkdir -p "$API_DIR/query"
touch "$API_DIR/query/toolchains-v1"

cmake ${CMAKE_ARGS[@]} -B $TMP_DIR -S $WORKING_DIRECTORY

#Building project

echo -e "${YELLOW}\nBuilding project ...\n${NC}"

mkdir -p "${TMP_DIR}/libsim"

cmake --build $TMP_DIR

cmake --install $TMP_DIR --prefix "${TMP_DIR}/libsim" > /dev/null 2>&1

REPLY_DIR="$API_DIR/reply"
REPLY_FILE=$(ls $REPLY_DIR/toolchains-v1-*.json 2>/dev/null | head -n 1)

COMPILER_ID=$(jq -r '.toolchains[] | select(.language == "CXX") | .compiler.id' "$REPLY_FILE")
#COMPILER_ID=$(grep -E "^CMAKE_CXX_COMPILER:FILEPATH=" "$TMP_DIR/CMakeCache.txt" | cut -d = -f2)

echo -e "${YELLOW}\nProject is built with $COMPILER_ID compiler\n${NC}"

FINAL_DIRECTORY="$BUILD_DIRECTORY/$COMPILER_ID"

if [ -d $FINAL_DIRECTORY ]; then
	rm -rf $FINAL_DIRECTORY
fi

#Coping project
mkdir $FINAL_DIRECTORY

mv $INSTALL_DIR $FINAL_DIRECTORY
rm -r $TMP_DIR

echo -e "${BOLD}${GREEN}Project is built in $FINAL_DIRECTORY${NC}\n"

#Coping projects into tests
echo -e "${YELLOW}Coping library into tests directory${NC}\n"
cp -rf ${FINAL_DIRECTORY}/libsim "${WORKING_DIRECTORY}/tests/lib"
#cp ${FINAL_DIRECTORY}/libsim/*.a "${WORKING_DIRECTORY}/tests"

echo -e "${BOLD}${GREEN}Project is copied in ${WORKING_DIRECTORY}/tests${NC}\n"

#Building tests
case "$BUILD_TESTS" in
	"-b")
		echo -e "${YELLOW}Building tests${NC}\n\n"
		./build_tests.sh "../tests" "${CMAKE_ARGS[@]}"
	;;
esac

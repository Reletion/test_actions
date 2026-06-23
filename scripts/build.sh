#BASH SCRIPT FOR BUILDING LIBSIM PROJECT

#Versions
LIBRARY_VERSION="0.0.1"
SCRIPT_VERSION="0.1"

#Directories

WORKING_DIRECTORY=${1:-".."}
BUILD_DIRECTORY="$WORKING_DIRECTORY/build"
TMP_DIR="$BUILD_DIRECTORY/output"
API_DIR="$TMP_DIR/.cmake/api/v1"
required_utilities=("cmake" "jq")

#Colors
BOLD="\033[1m"
NC="\033[0m"

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"


CMAKE_ARGS=("$@")
set -e


#Show help

case "$1" in

	-h|--help)

	cat<<-EOF
	===========================================================
	build.sh is a script for building libsim library with cmake

	Usage:
	        bash build.sh [OPTIONS]
	        bash build.sh [WORKING DIRECTORY=".."] [CMAKE ARGUMENTS]
	OPTIONS:
	        -h, --help 	print help
	        -v, --version	print version of script and library
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

#Finding distro

echo -e "${BOLD}${YELLOW}Starting script...${NC}\n\n"

if command -v lsb_release &> /dev/null; then
	DISTRO=$(lsb_release -is | tr '[:upper:]' '[:lower:]')
else
	DISTRO=$(grep '^ID=' /etc/os-release | cut -d= -f2 | tr -d '"' | tr '[:upper:]' '[:lower:]')
fi

echo "Distro name: $DISTRO"

case "$DISTRO" in
	ubuntu|debian|linuxmint|kali|astra*)
		PACKAGE_MANAGER=apt
		INSTALL_COMMAND=install
	;;
#	fedora|centos|rhel|almalinux|rocky)
#		PACKAGE_MANAGER=dnf
#	;;
#	arch|manjaro|endeavouros)
#		PACKAGE_MANAGER=pacman
#	;;
#	opensuse*)
#		PACKAGE_MANAGER=zypper
#	;;
#	altlinux)
#		PACKAGE_MANAGER=apt
#	;;
	*)
		echo "Cannot specify package manager"
		exit 1
	;;
esac

echo "Package manager name: $PACKAGE_MANAGER"

echo -e "\n"


#Finding utilities

echo -e "${YELLOW}Checking utilities${NC}\n"

for utulity in "${required_utilities[@]}"; do
	echo "utulity: $utulity"
	if command -v $utulity  &> /dev/null; then
		echo "$utulity downloaded"
	else
		read -p "$utulity is not downloaded. Would you install $utulity? (Y/n): " response

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

cmake -S $WORKING_DIRECTORY -B $TMP_DIR "${CMAKE_ARGS[@]}"

#Building project

echo -e "${YELLOW}\nBuilding project ...\n${NC}"

cmake --build $TMP_DIR

REPLY_DIR="$API_DIR/reply"
REPLY_FILE=$(ls $REPLY_DIR/toolchains-v1-*.json 2>/dev/null | head -n 1)

COMPILER_ID=$(jq -r '.toolchains[] | select(.language == "CXX") | .compiler.id' "$REPLY_FILE")
#COMPILER_ID=$(grep -E "^CMAKE_CXX_COMPILER:FILEPATH=" "$TMP_DIR/CMakeCache.txt" | cut -d = -f2)

echo -e "${YELLOW}\nProject is built with $COMPILER_ID compiler\n${NC}"

FINAL_DIRECTORY="$BUILD_DIRECTORY/$COMPILER_ID"

if [ -d $FINAL_DIRECTORY ]; then
	rm -rf $FINAL_DIRECTORY
fi

mkdir $FINAL_DIRECTORY

mv $TMP_DIR $FINAL_DIRECTORY

echo -e "${BOLD}${GREEN}Project is built in $FINAL_DIRECTORY${NC}"

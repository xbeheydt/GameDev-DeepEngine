# Copyright Xavier Beheydt. All rights reserved.


# NOTES :
#	FIXME rm in windiws raise an error when the directory doesn't exist
#	      see about extern/pulseaudio-win
#	TODO test wsl is working


## Settings

OUT_DIR				= out
BUILD_DIR			= ${OUT_DIR}/build
CONFIGS_DIR			= configs
EXTERN_DIR			= extern
VCPKG_DIR			= ${EXTERN_DIR}/vcpkg

VCPKG				= ${VCPKG_DIR}/vcpkg
CMAKE				= cmake
CURL				= curl
PYTHON				= python3
WSL					= wsl

# PULSAUDIO_WIN_VER	= 1.1
# PULSEAUDIO_DIR		= ${EXTERN_DIR}/pulseaudio-win

PYTHON_DIR			= Python
PYTHON_ENV_DIR		= .env

ifeq ($(OS),Windows_NT)

PLATFORM			?= windows

VCPKG_BOOTSTRAP		= ${VCPKG_DIR}\bootstrap-vcpkg.bat
UNZIP				= Expand-Archive
RM					= -powershell -Command \
					  rm -Force -Confirm:$$false -Recurse -EA Ignore
CP					= powershell -Command cp
PYTHON_CACHE_DIR	= $$(ls -Recurse -Directory -Filter __pycache__).FullName

else # Others platforms

PLATFORM			?= linux

VCPKG_BOOTSTRAP		= ${VCPKG_DIR}/bootstrap-vcpkg.sh
UNZIP				= unzip
RM					= rm -rf
CP					= cp
PYTHON_CACHE_DIR	= $$(find . | grep -E "(/__pycache__$|\.pyc$|\.pyo$)")

endif #! OS

## CMAKE variables
BITS				?= x64
COMPILER	 		?= clang
TYPE				?= debug
PRESET				?= ${PLATFORM}-${BITS}-${COMPILER}-${TYPE}
TARGET				?= all
#! CMAKE variables

ifeq ($(OS),Windows_NT)
ifneq (,$(findstring linux,${PRESET}))
PRE_EXE				= $(WSL)
endif
endif
#! Settings


.PHONY: all
# all: configure python/env build ## Configure and build all targets
all: configure build ## Configure and build all targets


.PHONY: configure
# configure: extern/pulseaudio-win ## Configure CMake project
configure: ## Configure CMake project
	$(PRE_EXE) $(CMAKE) --preset ${PRESET}

.PHONY: re/configure
re/configure: clean/cache configure ## Re-configure CMake project


.PHONY: build
build: ## Build CMake project
	$(PRE_EXE) $(CMAKE) --build "${BUILD_DIR}/${PRESET}" --target ${TARGET}

.PHONY: re/build
re/build: clean/build build ## Clean builds and build


.PHONY: clean/cache
clean/cache: ## Clean CMake project cache
	$(RM) "${BUILD_DIR}/${PRESET}/CMakeFiles"
	$(RM) "${BUILD_DIR}/${PRESET}/CMakeCache.txt"

.PHONY: clean/build
clean/build: ## Clean builds
	$(PRE_EXE) $(CMAKE) --build "${BUILD_DIR}/${PRESET}" --target clean

.PHONY: clean/vcpkg
clean/vcpkg: ## Clean VCPKG folder
	$(RM) ${VCPKG_DIR}

# .PHONY: clean/pulseaudio-win
# clean/pulseaudio-win: ## Clean pulseaudio-win folder
# 	$(RM) ${EXTERN_DIR}/pulseaudio-win

.PHONY: clean/deps
# clean/deps: clean/vcpkg clean/pulseaudio-win ## Clean all dependencies
clean/deps: clean/vcpkg ## Clean all dependencies

.PHONY: clean/python/cache
clean/python/cache: ## Clean Python cache
	-$(RM) ${PYTHON_CACHE_DIR}

.PHONY: clean/python
clean/python: clean/python/cache ## Clean Python environment
	$(RM) ${PYTHON_ENV_DIR}

.PHONY: clean
clean: clean/cache clean/build clean/python/cache ## Clean CMake project configuration and builds


.PHONY: fclean
fclean: clean/deps clean/python ## Clean all
	$(RM) ${OUT_DIR}


.PHONY: re
re: fclean all ## Re-configure and build


.PHONY: help
help: ## Print helps
	@echo Usage: make [target]
	@$(PYTHON_EXE) ${PRINT_HELP_PYSCRIPT} "${CURDIR}/Makefile"


## Others ======================================================================
# $(PULSEAUDIO_DIR): ## TODO
# 	$(CURL) -L -o $(PULSEAUDIO_DIR).zip \
# 		http://bosmans.ch/pulseaudio/pulseaudio-${PULSAUDIO_WIN_VER}.zip
# 	powershell -Command $(UNZIP) -Path $(PULSEAUDIO_DIR).zip \
# 		-DestinationPath $(PULSEAUDIO_DIR)

# 	$(RM) $(PULSEAUDIO_DIR).zip
# 	-$(CP) "${CONFIGS_DIR}/pulseaudio-win/etc/pulse/default.pa" \
# 		"$(PULSEAUDIO_DIR)/etc/pulse/default.pa"
# 	-$(CP) "${CONFIGS_DIR}/pulseaudio-win/etc/pulse/daemon.conf" \
# 		"$(PULSEAUDIO_DIR)/etc/pulse/daemon.conf"

.PHONY: python/env
python/env: .env ## Create python virtual environment
.env: ## Configure python virtual environment
	$(PYTHON) -m venv .env
	$(PYTHON) -m pip install --upgrade pip
	$(PYTHON) -m pip install -r requirements.txt

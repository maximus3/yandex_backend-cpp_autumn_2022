ifeq ($(shell test -e '.env' && echo -n yes),yes)
	include .env
endif

args := $(wordlist 2, 100, $(MAKECMDGOALS))
ifndef args
MESSAGE = "No such command (or you pass two or many targets to ). List of possible commands: make help"
else
MESSAGE = "Done"
endif

HELP_FUN = \
	%help; while(<>){push@{$$help{$$2//'options'}},[$$1,$$3] \
	if/^([\w-_]+)\s*:.*\#\#(?:@(\w+))?\s(.*)$$/}; \
    print"$$_:\n", map"  $$_->[0]".(" "x(20-length($$_->[0])))."$$_->[1]\n",\
    @{$$help{$$_}},"\n" for keys %help; \

# Commands

.PHONY: help
help: ##@Help Show this help
	@echo -e "Usage: make [target] ...\n"
	@perl -e '$(HELP_FUN)' $(MAKEFILE_LIST)

.PHONY: env
env:  ##@Environment Create .env file with variables
	@$(eval SHELL:=/bin/bash)
	@cp .env.example .env
	@echo "SECRET_KEY=$$(openssl rand -hex 32)" >> .env

.PHONY: install
install: ##@Code Install dependencies
	cd src && mkdir .build || echo "Build directory already exists"
	conan -h || pip3 install conan
	cd src/.build && conan install .. --build=missing
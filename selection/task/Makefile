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

clean: ##@Build Clean build files
	@rm -f .build

.PHONY: install
install: ##@Code Install dependencies
	cd src && mkdir .build || echo "Build directory already exists"
	conan -h || pip3 install conan
	cd src/.build && conan install .. --build=missing

.PHONY: db
db: ##@Database Run database
	docker-compose up -d --remove-orphans postgres

.PHONY: docker-build
docker-build: ##@Application Docker build
	docker-compose build

.PHONY: docker-down
docker-down: ##@Application Docker down
	docker-compose down

.PHONY: docker-clean
docker-clean: ##@Application Docker prune -f
	docker image prune -f

.PHONY: docker-up
docker-up: ##@Application Docker up
	docker-compose up --remove-orphans

.PHONY: docker-up-d
docker-up-d: ##@Application Docker up detach
	docker-compose up -d --remove-orphans

.PHONY: docker
docker: docker-clean docker-build docker-up-d docker-clean ##@Application Docker prune, up, run and prune

.PHONY: docker-gcc
docker-gcc: ##@Build Create docker container with gcc
	docker build -t gcc_image -f Dockerfile-gcc .

.PHONE: docker-gcc-shell
docker-gcc-shell: ##@Build Open docker container for clion
	make docker-gcc
	docker run -it --rm --entrypoint /bin/bash --name gcc_container gcc_image

.PHONY: docker-gcc-copy
docker-gcc-copy: ##@Build Copy conan files from docker container to host
	docker cp gcc_container:/home/conan/app/.build .

.PHONY: test
test: ##@Testing  Runs online tests
	python -m online_tests
	pytest online_tests --verbosity=2 --showlocals --log-level=DEBUG
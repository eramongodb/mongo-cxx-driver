# DO NOT EDIT THIS FILE DIRECTLY
# This file was auto generated from the template file Makefile.j2 using the generate.py script

MONGOCXX_VERSION=3.10.1
DOCKER=docker

.PHONY: build
build:
	$(DOCKER) build . \
		-t mongodb/mongo-cxx-driver:$(MONGOCXX_VERSION)-noble

.PHONY: nocachebuild
nocachebuild:
	$(DOCKER) build . \
		--no-cache \
		-t mongodb/mongo-cxx-driver:$(MONGOCXX_VERSION)-noble

.PHONY: run
run: | $(filter nocachebuild build, $(MAKECMDGOALS))
	$(DOCKER) run --rm -it mongodb/mongo-cxx-driver:$(MONGOCXX_VERSION)-noble

.PHONY: test
test: | $(filter nocachebuild build, $(MAKECMDGOALS))
	$(DOCKER) build . --no-cache -f TestDockerfile -t test-mongocxx-driver-image:$(MONGOCXX_VERSION)-noble
	$(DOCKER) run test-mongocxx-driver-image:$(MONGOCXX_VERSION)-noble

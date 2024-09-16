NAME = inception

SHELL := /bin/bash

all:
	mkdir -p volumes/postgresql
	@$(eval export MY_IP=$(shell hostname -i))
	docker-compose -f docker-compose.yml up --build -d
	@echo "La IP es: $$MY_IP"

debug:
	mkdir -p volumes/postgresql
	@$(eval export MY_IP=$(shell hostname -i))
	docker-compose -f docker-compose.yml up --build
	@echo "La IP es: $$MY_IP"

stop:
	@$(eval export MY_IP=$(shell hostname -i))
	docker-compose -f docker-compose.yml down

clean:
	@$(eval export MY_IP=$(shell hostname -i))
	docker-compose -f docker-compose.yml down --rmi all --volumes --remove-orphans
	
.PHONY: all stop clean

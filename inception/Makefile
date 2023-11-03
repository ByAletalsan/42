NAME = inception

all: prune dir reload
	
stop:
	docker-compose -f srcs/docker-compose.yml down

prune: stop
	docker system prune -f

dir:
	rm -rf /home/atalaver/data
	mkdir -p /home/atalaver/data/mariadb
	mkdir -p /home/atalaver/data/website

reload:
	docker-compose -f srcs/docker-compose.yml up --build

.PHONY: all stop prune dir reload

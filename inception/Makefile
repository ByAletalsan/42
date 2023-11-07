NAME = inception

all:
	docker-compose -f srcs/docker-compose.yml up --build

clean:
	docker-compose -f srcs/docker-compose.yml down
	docker system prune -f

fclean: clean
	rm -rf /home/atalaver/data
	mkdir -p /home/atalaver/data/mariadb
	mkdir -p /home/atalaver/data/website

re: fclean all
	
.PHONY: all clean fclean re

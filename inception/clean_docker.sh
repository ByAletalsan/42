#!/bin/bash

dock=$(docker ps -qa);
docker stop $dock 2>/dev/null;
docker rm $dock 2>/dev/null;

docker rmi -f $(docker images -qa) 2>/dev/null;

docker volume rm $(docker volume ls -q) 2>/dev/null;

docker network rm $(docker network ls -q) 2>/dev/null;

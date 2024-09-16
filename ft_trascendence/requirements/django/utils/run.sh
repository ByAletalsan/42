#!/bin/sh

set -e

echo "Esperando a PostgreSQL..."
sleep 10

echo "SHOWMIGRATIONS"
python manage.py showmigrations
echo "MAKEMIGRATIONS"
python /var/www/html/back/manage.py makemigrations data_app
echo "MIGRATE"
python /var/www/html/back/manage.py migrate
echo "RUNSERVER"

python /var/www/html/back/manage.py runserver 0.0.0.0:5000
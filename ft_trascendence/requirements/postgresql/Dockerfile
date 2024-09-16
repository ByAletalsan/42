# Usa la imagen oficial de PostgreSQL
FROM postgres:alpine

# Copia el script de configuración adicional (si es necesario) a la carpeta de scripts de inicio
COPY ./init_postgres.sh /docker-entrypoint-initdb.d/init_user_and_db.sh

# Asegúrate de que el script es ejecutable
RUN chmod a+x /docker-entrypoint-initdb.d/init_user_and_db.sh

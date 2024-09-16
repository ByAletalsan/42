#!/bin/sh
# init_postgres.sh

# Configuración adicional de PostgreSQL
echo "Configurando pg_hba.conf"
echo 'host all all 172.28.0.0/16 md5' >> "$PGDATA/pg_hba.conf"

# Actualizaciones adicionales de configuración, por ejemplo:
echo "listen_addresses='*'" >> "$PGDATA/postgresql.conf"

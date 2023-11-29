#!/usr/bin/env python3
import cgi
import os
import cgitb

# Habilitar la traza de excepciones de CGI para ver posibles errores
cgitb.enable()

# Obtener las cookies
cookies = os.environ.get('HTTP_COOKIE', '')

# Separar las cookies en un diccionario
cookies_dict = {}
if cookies:
    cookies_list = cookies.split('; ')
    for cookie in cookies_list:
        cookie_parts = cookie.split('=')
        if len(cookie_parts) == 2:
            cookies_dict[cookie_parts[0]] = cookie_parts[1]

# Encabezado HTTP y HTML
print("Content-Type: text/html\r\n", end="")
print("\r\n", end="")  # Línea en blanco después del encabezado

print("""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Cookies</title>
</head>
<body>
    <h1>Cookie stocker:</h1>
""")

# Mostrar las cookies si existen
if 'nombre' in cookies_dict:
    print("Nombre : " + cookies_dict['nombre'] + "<br>")
if 'apellido' in cookies_dict:
    print("Apellido : " + cookies_dict['apellido'] + "<br>")
if 'dir' in cookies_dict:
    print("Dir : " + cookies_dict['dir'] + "<br>")

print("""
</body>
</html>
""")

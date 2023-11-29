#!/usr/bin/env python3
import cgi

# Obtener datos del formulario
form_data = cgi.FieldStorage()

# Procesar los datos del formulario
# Verificar si los campos requeridos existen en el formulario
if "nombre_post" in form_data and "apellido_post" in form_data and "dir_post" in form_data:
    # Obtener los valores de los campos
    nom = form_data.getvalue('nombre_post')
    apellido = form_data.getvalue('apellido_post')
    dirr = form_data.getvalue('dir_post')

    # Configurar cookies
    print("Set-Cookie: nombre=" + nom + "; Max-Age=3600\r\n", end="")
    print("Set-Cookie: apellido=" + apellido + "; Max-Age=3600\r\n", end="")
    print("Set-Cookie: dir=" + dirr + "; Max-Age=3600\r\n", end="")

# Encabezado HTTP y HTML
print("Content-Type: text/html\r\n", end="")
print("\r\n", end="")  # Línea en blanco después del encabezado Content-Type
print("""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>Ver cookies</h1>
    <p><a href="show_cookies.py">Ir</a></p>
</body>
</html>
""", end="")

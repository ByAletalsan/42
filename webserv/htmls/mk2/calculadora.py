import cgi
import os

form = cgi.FieldStorage()

def suma(n1, n2):
	return n1 + n2

def resta(n1, n2):
	return n1 - n2

def mult(n1, n2):
	return n1 * n2;

def div(n1, n2):
	if n2 == 0:
		print("JAJAJAJA BUEN INTENTO")
		return 0
	return n1 / n2;

operaciones = {"SUMA":suma, "RESTA":resta, "MULT":mult, "DIV":div}

print("BIENVENIDOS A CALCULEITOR 51%!!\n")
print("MODO DE USO: url/calculadora.py/OPERACION?N1=X&N2=Y")
print("	Operaciones aceptadas [SUMA, RESTA, MULT, DIV]\n")

try:
	path_info = os.environ.get('PATH_INFO', '')
	if (not path_info):
		print("FALTA OPERACION")
		exit(0)
	else:
		path_info = path_info[1:]
		if (path_info not in ["SUMA", "RESTA", "MULT", "DIV"]):
			print("OPERACION NO VALIDA")
			exit(0)
	if ("N1" not in form or "N2" not in form):
		print("Error con los numeros N1, N2")
		exit(0)
	n1 = int(form["N1"].value)
	n2 = int(form["N2"].value)
	result = operaciones[path_info](n1, n2)
	print(str(n1) + " " +  path_info + " " + str(n2) + " = " + str(result))
	
except Exception as e:
	print("UPS... ALGO FALLO!")


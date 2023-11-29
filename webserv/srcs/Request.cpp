/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:38:39 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/29 19:38:17 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"
#include <stdlib.h>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>

Request::Request() : method(NONE), fullPath(""), path(""), file(""), infoPath(""), query(""), version(""), port(80), body(""), code(200), boundary("")
{
}

static char fromHex(const std::string &input)
{
    std::stringstream str;
    str << std::hex << input;
    int value;
    str >> value;
    return (static_cast<char>(value));
}

static std::string decodeText(const std::string &input)
{
    std::string decodedString;
    std::string::size_type length = input.length();
    std::string::size_type i = 0;

    while (i < length)
	{
        if (input[i] == '+')
		{
            decodedString += ' ';
            ++i;
        } else if (input[i] == '%' && i + 2 < length && isxdigit(input[i + 1]) && isxdigit(input[i + 2]))
		{
            std::string hex = input.substr(i + 1, 2);
            decodedString += fromHex(hex);
            i += 3;
        } else
		{
            decodedString += input[i];
            ++i;
        }
    }
    return (decodedString);
}

void	Request::decodeParams()
{
	this->fullPath = decodeText(this->fullPath);
	this->path = decodeText(this->path);
	this->file = decodeText(this->file);
	this->infoPath = decodeText(this->infoPath);
	this->query = decodeText(this->query);
	this->version = decodeText(this->version);
	this->host = decodeText(this->host);
	this->body = decodeText(this->body);
	this->boundary = decodeText(this->boundary);
}


void	Request::getInfoPath()
{
	this->path = "";
	path = this->fullPath.substr(0, this->fullPath.find("?"));
	size_t	index = path.find_last_of(".");
	if (index == path.size() - 1)
	{
		this->code = 400;
		std::cerr << "Incorrect file" << std::endl;
		return ;
	}
	size_t i;
	if ((i = path.find_first_of("/", index)) != std::string::npos)
		this->infoPath = this->path.substr(i, std::string::npos);
	while (this->infoPath.size() > 1 && this->infoPath[this->infoPath.size() - 1] == '/')
		this->infoPath.erase(this->infoPath.end() - 1);
	this->path = this->path.substr(0, i);
	while (this->path.size() > 1 && this->path[this->path.size() - 1] == '/')
		this->path.erase(this->path.end() - 1);
	if ((i = this->path.find_last_of("/")) != std::string::npos)
	{
		if ((index = this->path.find(".", i)) != std::string::npos && index > i + 1)
		{
			this->file = this->path.substr(i + 1, std::string::npos);
			this->path = (this->path.size() - 1 == this->file.size())? this->path.substr(0, this->path.size() - this->file.size()) : this->path.substr(0, this->path.size() - this->file.size() - 1);
		}
	}
}

static std::string	strip( std::string &s, char c)
{
	std::string	res = "";
	unsigned i = 0; 
	while (i < s.length())
	{
		res += s[i];
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
		}
		else
			i++;
	}
	return (res);
}

void		Request::setFirstLine( const std::string &line )
{
	size_t							i;
	size_t							j;
	std::string						buffer;
    std::map<std::string, Methods>	mapMethods;
    mapMethods["POST"] =  POST;
	mapMethods["GET"] =  GET;
	mapMethods["DELETE"] =  DELETE;
	mapMethods["PUT"] =  PUT;
	mapMethods["HEAD"] =  HEAD;
	mapMethods["OPTIONS"] =  OPTIONS;
	mapMethods["TRACE"] =  TRACE;

	if (line == "")
	{
		this->code = 400;
		return ;
	}
	//Method
	i = line.find_first_of(" ");
	if (i == std::string::npos)
	{
		this->code = 400;
		return ;
	}
	buffer = line.substr(0, i);
	if (mapMethods.find(buffer) != mapMethods.end())
		this->method = mapMethods.find(buffer)->second;
	if (this->method == NONE)
	{
		this->code = 400;
		std::cerr << "Invalid METHOD" << std::endl;
		return ;
	}
	//Path
	if ((j = line.find_first_not_of(' ', i)) == std::string::npos)
	{
		this->code = 400;
		std::cerr << "No PATH / HTTP version" << std::endl;
		return ;
	}
	if ((i = line.find_first_of(' ', j)) == std::string::npos)
	{
		this->code = 400;
		std::cerr << "No HTTP version" << std::endl;
		return ;
	}
	this->fullPath.assign(line, j, i - j);
	this->fullPath = strip(this->fullPath, '/');
	getInfoPath();
	if (this->code == 400)
		return ;
	if (this->path == "")
	{
		this->code = 400;
		return ;
	}
	//Version
	if ((i = line.find_first_not_of(' ', i)) == std::string::npos)
	{
		this->code = 400;
		std::cerr << "No HTTP version" << std::endl;
		return ;
	}
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T' &&
			line[i + 3] == 'P' && line[i + 4] == '/')
		this->version.assign(line, i + 5, 3);
	if (this->version != "1.0" && this->version != "1.1")
	{
		this->code = 400;
		std::cerr << "BAD HTTP VERSION " << this->version << std::endl;
		return ;
	}
}

std::string			Request::nextLine( const std::string &http, size_t &i )
{
	std::string		result;
	size_t			j;

	if (i == std::string::npos)
		return ("");
	j = http.find_first_of('\n', i);
	result = http.substr(i, j - i);
	if (result[result.size() - 1] == '\r')
	{
		if (result.size())
			result.resize(result.size() - 1);
	}
	i = (j == std::string::npos ? j : j + 1);
	return (result);
}

static std::string	getKey( const std::string &line )
{
	std::string	result;

	size_t	i = line.find_first_of(':');
	result.append(line, 0 , i);
	//TO_UPPER
	for (int i = 0; i < (int)result.length(); i++)
		result[i] = (char)std::toupper(result[i]);
	//STRIP
	i = result.length();
	if (!i)
		return (result);
	while (i && result[i - 1] == ' ')
		i--;
	result.resize(i);
	for (i = 0; result[i] == ' '; i++)
		result = result.substr(i, std::string::npos);
	return (result);
}

static std::string	getValue( const std::string &line )
{
	std::string	result;

	size_t	i = line.find_first_of(':');
	i = line.find_first_not_of(' ', i + 1);
	if (i != std::string::npos)
		result.append(line, i, std::string::npos);
	//STRIP
	i = result.length();
	if (!i)
		return (result);
	while (i && result[i - 1] == ' ')
		i--;
	result.resize(i);
	for (i = 0; result[i] == ' '; i++)
		result = result.substr(i, std::string::npos);
	return (result);
}

int			Request::getInfoPort()
{
	std::string	host;
	size_t	i;

	if (this->headers.find("HOST") == this->headers.end())
	{
		this->code = 400;
		std::cerr << "No HOST Header in getInfoPort" << std::endl;
		return (80);
	}
	host = this->headers.find("HOST")->second;
	if ((i = host.find_first_of(':')) == std::string::npos || i == host.size() - 1)
		return (80);
	return (atoi((host.substr(i + 1, host.size() - i)).c_str()));
}

std::string			Request::getInfoHost()
{
	std::string	host;
	size_t	i;

	if (this->headers.find("HOST") == this->headers.end())
	{
		this->code = 400;
		std::cerr << "No HOST Header in getInfoHost" << std::endl;
		return ("127.0.0.1");
	}
	host = this->headers.find("HOST")->second;
	if ((i = host.find_first_of(':')) == std::string::npos)
		return (host);
	host = host.substr(0, i);
	host = (host == "localhost" || host == "::1" )? "127.0.0.1" : host;
	return (host);
}

std::string	Request::getInfoQuery()
{
	std::string	query = "";
	size_t	i;

	if (this->fullPath.empty())
	{
		this->code = 400;
		std::cerr << "No Path" << std::endl;
		return (query);
	}
	if ((i = this->fullPath.find_first_of('?')) == std::string::npos || i == this->fullPath.size() - 1)
		return (query);
	return (this->fullPath.substr(i + 1, this->fullPath.size()));
}

Request::Request( std::string http ) : method(NONE), fullPath(""), path(""), file(""), infoPath(""), query(""), version(""), port(80), body(""), code(200), boundary("")
{
	std::string	line;
	std::string	key;
	std::string	value;
	size_t		i = 0;
	char		strip[] = {'\n', '\r'};

	line = this->nextLine( http, i );
	this->setFirstLine( line );
	//Headers
	while ((line = this->nextLine( http, i )) != "" && line != "\r" && this->code != 400)
	{
		key = decodeText(getKey( line ));
		value = decodeText(getValue( line ));
		this->headers[key] = value;
	}
	if (this->code == 400)
		return ;
	//Get Some Info
	this->port = getInfoPort();
	if (this->code == 400)
		return ;
	this->host = getInfoHost();
	if (this->code == 400)
		return ;
	this->query = getInfoQuery();
	if (this->code == 400)
		return ;
	//Body
	if (i != std::string::npos)
		this->body = http.substr(i, std::string::npos);
	while (this->body.size() > 0 &&
			(this->body[this->body.size() - 1] == strip[0] || this->body[this->body.size() - 1] == strip[1]))
		this->body.resize(this->body.size() - 1);
	decodeParams();
}

Request::Request( const Request &r )
{
	this->method = r.getMethod();
	this->path = r.getPath();
	this->file = r.getFile();
	this->infoPath = r.getInfoPath();
	this->fullPath = r.getFullPath();
	this->query = r.getQuery();
	this->version = r.getVersion();
	this->headers = r.getHeaders();
	this->port = r.getPort();
	this->host = r.getHost();
	this->body = r.getBody();
	this->code = r.getCode();
	this->boundary = r.getBoundary();
}

Request::~Request()
{
}


Request &Request::operator=( const Request &r )
{
	if (this != &r)
	{
		this->method = r.getMethod();
		this->path = r.getPath();
		this->file = r.getFile();
		this->infoPath = r.getInfoPath();
		this->fullPath = r.getFullPath();
		this->query = r.getQuery();
		this->version = r.getVersion();
		this->headers = r.getHeaders();
		this->port = r.getPort();
		this->host = r.getHost();
		this->body = r.getBody();
		this->code = r.getCode();
		this->boundary = r.getBoundary();
	}
	return (*this);
}

bool		Request::isCGI( std::vector<Cgi> cgis ) const
{
	std::string	extension;

	if (this->file.empty() || (this->method != GET && this->method != POST))
		return (false);
	if (this->file.find(".") == std::string::npos)
		return (false);
	extension = this->file.substr(this->file.find_last_of("."), std::string::npos);
	for (unsigned i = 0; i < cgis.size(); i++)
	{
		if (cgis[i].get_extension() == extension)
			return (true);
	}
	return (false);
}

static std::string intToString(size_t number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::map<std::string,std::string> Request::initEnv( Client &client, Server &server, const std::string &fileName )
{
	std::map<std::string,std::string> env;

	env["AUTH_TYPE"] = "BASIC";
	env["CONTENT_LENGTH"] = intToString(this->body.size());
	env["GATEWAY_INTERFACE"] = "CGI/1.1";
	env["PATH_INFO"] = this->infoPath;
	if (!this->infoPath.empty())
		env["PATH_TRANSLATED"] = this->fullPath;
	env["QUERY_STRING"] = this->query;
	if (this->headers.find("CONTENT-TYPE") != this->headers.end())
		env["CONTENT_TYPE"] = this->headers.find("CONTENT-TYPE")->second;
	if (this->headers.find("COOKIE") != this->headers.end())
		env["HTTP_COOKIE"] = this->headers.find("COOKIE")->second;
	env["REMOTE_ADDR"] = client.getIp();
	env["REQUEST_METHOD"] = (this->method == GET)? "GET" : "POST";
	env["REQUEST_URI"] = this->fullPath;
	env["SCRIPT_NAME"] = fileName;
	env["SERVER_NAME"] = (!server.get_server_name().empty())? server.get_server_name() : "server_name";
	env["SERVER_PORT"] = intToString(server.get_listen());
	env["SERVER_PROTOCOL"] = "HTTP/" + this->version;
	env["SERVER_SOFTWARE"] = "WebServ/1.0";
	return (env);
}

char	**Request::initArgs( std::vector<Cgi> cgis, const std::string &fileName ) const
{
	char **args = new char*[4];
	if (this->file.find(".") == std::string::npos)
		return (args);
	std::string extension = this->file.substr(this->file.find_last_of("."), std::string::npos);
	std::string buf;
	for (unsigned int i = 0; i < cgis.size(); i++)
	{
		if (cgis[i].get_extension() == extension)
		{
			buf = cgis[i].get_exec_route();
			args[0] = new char[buf.length() + 1];
			memset(args[0], 0, buf.length() + 1);
			strcpy(args[0], buf.c_str());
			break ;
		}
	}
	buf = fileName;
	args[1] = new char[buf.length() + 1];
	memset(args[1], 0, buf.length() + 1);
	strcpy(args[1], buf.c_str());
	buf = "2>/dev/null";
	args[2] = new char[buf.length() + 1];
	memset(args[2], 0, buf.length() + 1);
	strcpy(args[2], buf.c_str());
	args[3] = NULL;
	return (args);
}

static char	**mapToArray( std::map<std::string,std::string> map )
{
	char	**array = new char*[map.size() + 1];
	unsigned i = 0;
	for (std::map<std::string,std::string>::iterator it = map.begin(); it != map.end(); it++)
	{
		std::string data = it->first + "=" + it->second;
		array[i] = new char[data.length() + 1];
		memset(array[i], 0, data.length() + 1);
		strcpy(array[i], data.c_str());
		i++;
	}
	array[i] = NULL;
	return (array);
}

static std::string rm_to_one(std::string s, char c)
{
    std::string resultado;
    bool consecutivo = false;

    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == c)
        {
            if (!consecutivo)
            {
                resultado += s[i];
                consecutivo = true;
            }
        }
        else
        {
            resultado += s[i];
            consecutivo = false;
        }
    }
    while (resultado.size() > 1 && resultado[resultado.size() - 1] == '/')
		resultado.erase(resultado.end() - 1);
    return resultado;
}

void Request::executeCGI( Response &res, Client &client, Server &server, Location &loc )
{
	std::string	new_body;
	int			status;
	
	res.not_found();

	std::string path_aux = rm_to_one(this->path.substr(loc.get_path().size(), std::string::npos), '/');
    while (path_aux.size() > 1 && path_aux[path_aux.size() - 1] == '/')
		path_aux.erase(path_aux.end() - 1);
	std::string fileName = rm_to_one(loc.get_root() + "/" +  path_aux + "/" + this->file, '/');
	if (access(fileName.c_str(), F_OK) < 0)
		return ;

	int fd[2];
	if (pipe(fd) < 0)
	{
		res.internal_error();
		return ;
	}

	char **env = mapToArray(this->initEnv(client, server, fileName));
	char **args = this->initArgs(loc.get_cgis(), fileName);

	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		alarm(5);
		execve(args[0], args, env);
		alarm(0);
		for (unsigned i = 0; env[i]; i++)
			delete[] env[i];
		delete[] env;
		for (unsigned i = 0; args[i]; i++)
			delete[] args[i];
		delete[] args;
		exit(1);
	}
	else if (pid > 0)
	{
		write(fd[1], this->body.c_str(), this->body.size());
		close(fd[1]);
		fd[1] = -1;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			if (!WEXITSTATUS(status))
			{
				char	buffer[65536];
				lseek(fd[0], 0, SEEK_SET);

				ssize_t ret = 1;
				while (ret > 0)
				{
					memset(buffer, 0, 65536);
					ret = read(fd[0], buffer, 65535);
					new_body += buffer;
				}
				res.clear_headers();
				std::string extension = this->file.substr(this->file.find_last_of("."), std::string::npos);
				if (extension == ".php")
					res.set_php_header();
				if (new_body.find("\r\n\r\n") != std::string::npos)
					res.setBodyWithHeaders(new_body);
				else
					res.setBody(new_body);
				res.setCode(200);
				res.setMessage("OK");
			}
			else
				res.internal_error();
		}
		else
			res.internal_error();
	}
	else
		res.internal_error();
	for (unsigned i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	for (unsigned i = 0; args[i]; i++)
		delete[] args[i];
	delete[] args;
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
}

std::ostream&	operator<<( std::ostream &o, const Request &r )
{
	std::map<std::string, std::string>::const_iterator	it;

	o << "Method: " << r.getMethod() << std::endl;
	o << "FullPath: " << r.getFullPath() << std::endl;
	o << "Path: " << r.getPath() << std::endl;
	o << "File: " << r.getFile() << std::endl;
	o << "InfoPath: " << r.getInfoPath() << std::endl;
	o << "Query: " << r.getQuery() << std::endl;
	o << "Version: " << r.getVersion() << std::endl;
	o << "Port: " << r.getPort() << std::endl;
	o << "Code: " << r.getCode() << std::endl;
	o << "Host: " << r.getHost() << std::endl;
	o << "Boundary" << r.getBoundary() << std::endl;

	for (it = r.getHeaders().begin(); it != r.getHeaders().end(); it++)
		o << it->first << ": " << it->second << std::endl;

	o << "Body: " << std::endl;
	o << r.getBody();

	return (o);
}

bool	Request::isFileUpload()
{
	if (this->method != POST)
		return (false);
	for (std::map<std::string, std::string>::const_iterator it = this->headers.begin(); it != this->headers.end(); it++)
	{
		if (it->second.find("multipart/form-data;") != std::string::npos)
		{
			this->boundary = it->second.substr((it->second.find_last_of("=") + 1), it->second.size());
			return (true);
		}
	}
	return (false);
}

void	Request::createFilesUpload( std::string route, Response &res ) const
{
	size_t		posi = 0;
	size_t		posf = 0;
	std::string	filename;
	int			fin = 0;
	std::string ext;

	while (!fin)
	{
		posi = (this->body.find("filename=", posf));
		posi += 10;
		posf = (this->body.find("\"", posi));
		if (posf == std::string::npos)
		{
			std::cout << "asda" << std::endl;
			break;
		}
		filename = route + "/" + "_" + this->body.substr(posi, posf - posi);

		//CHECK EXTENSION
		std::cout << filename << std::endl;
		res.unsupported();
		if (filename.find(".") == std::string::npos)
			return ;
		ext = filename.substr(filename.find_last_of("."), std::string::npos);
		if (ext.empty())
			return;

		if (res.getExt().find(ext) == res.getExt().end())
			return ;
				
		posi = (this->body.find("\r\n\r\n", posi));
		if (posi == std::string::npos)
		{
			std::cout << "a" << std::endl;
			break;
		}
		else
			posi += 4;
		posf = (this->body.find(this->boundary, posi));
		if (posf == std::string::npos)
		{
			std::cout << "ab" << std::endl;
			break;
		}
		
		std::ofstream fichero(filename.c_str(), std::ios::out | std::ios::trunc);
		if (fichero.is_open())
		{
			fichero << this->body.substr(posi, posf - posi - 4);
			fichero.close();
		}
		else
		{
			std::cerr << "No se pudo abrir el archivo." << std::endl;
			break;
    	}		
		if (this->body.substr(posf, this->boundary.length() + 2) == (this->boundary + "--") || posf <= posi)
		{
			res.good();
			return ;
		}
		else
			posf++;
	}
	res.internal_error();
}


//getters
Methods										Request::getMethod() const
{
	return (this->method);
}

const std::string							&Request::getPath() const
{
	return (this->path);
}

const std::string							&Request::getFile() const
{
	return (this->file);
}

const std::string							&Request::getInfoPath() const
{
	return (this->infoPath);
}

const std::string							&Request::getFullPath() const
{
	return (this->fullPath);
}


const std::string							&Request::getHost() const
{
	return (this->host);
}

const std::string							&Request::getQuery() const
{
	return (this->query);
}

const std::string							&Request::getVersion() const
{
	return (this->version);
}

const std::map<std::string, std::string>	&Request::getHeaders() const
{
	return (this->headers);
}

int											Request::getPort() const
{
	return (this->port);
}

const std::string							&Request::getBody() const
{
	return (this->body);
}

int											Request::getCode() const
{
	return (this->code);
}

const std::string							&Request::getBoundary() const
{
	return (this->boundary);
}

//Setters
void	Request::setBoundary( const std::string &boundary )
{
	this->boundary = boundary;
}

void	Request::setFile( const std::string &file )
{
	std::string res = rm_to_one(file, '/');
    while (res.size() > 1 && res[res.size() - 1] == '/')
		res.erase(res.end() - 1);
	while (res.size() > 1 && res[0] == '/')
		res.erase(res.begin());
	this->file = res;
}

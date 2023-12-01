/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:40:35 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/29 19:38:20 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static std::string getCurrentHttpDate()
{
    std::time_t currentTime = std::time(NULL);
    std::tm* timeInfo = std::gmtime(&currentTime);

    char buffer[80];
    std::strftime(buffer, 80, "%a, %d %b %Y %H:%M:%S GMT", timeInfo);

    std::ostringstream oss;
    oss << buffer;
    return oss.str();
}

Response::Response() : version("1.1"), code(200), message("OK"), body(""), route_error_pages("")
{
	this->headers["Connection"] = "Close";
	this->headers["Server"] = "WebServ";
	this->headers["Date"] = getCurrentHttpDate();
	this->ext[".html"] = std::pair<std::string, bool> ("text/html", false);
	this->ext[".txt"] = std::pair<std::string, bool> ("text/plain", false);
	this->ext[".json"] = std::pair<std::string, bool> ("application/json", false);
	this->ext[".xml"] = std::pair<std::string, bool> ("application/xml", false);
	this->ext[".js"] = std::pair<std::string, bool> ("application/javascript", false);
	this->ext[".css"] = std::pair<std::string, bool> ("text/css", false);
	this->ext[".jpeg"] = std::pair<std::string, bool> ("image/jpeg", true);
	this->ext[".jpg"] = std::pair<std::string, bool> ("image/jpeg", true);
	this->ext[".png"] = std::pair<std::string, bool> ("image/png", true);
	this->ext[".gif"] = std::pair<std::string, bool> ("image/gif", true);
	this->ext[".pdf"] = std::pair<std::string, bool> ("application/pdf", true);
	this->ext[".mp3"] = std::pair<std::string, bool> ("audio/mp3", true);
	this->ext[".mpeg"] = std::pair<std::string, bool> ("audio/mpeg", true);
	this->ext[".wav"] = std::pair<std::string, bool> ("audio/wav", true);
	this->ext[".mp4"] = std::pair<std::string, bool> ("video/mp4", true);
	this->ext[".mkv"] = std::pair<std::string, bool> ("video/mkv", true);
	this->ext[".avi"] = std::pair<std::string, bool> ("video/avi", true);
	this->ext[".zip"] = std::pair<std::string, bool> ("application/zip", true);
}

Response::Response( const Response &r )
{
	this->version = r.getVersion();
	this->code = r.getCode();
	this->message = r.getMessage();
	this->headers = r.getHeaders();
	this->body = r.getBody();
	this->ext = r.getExt();
}

Response::~Response()
{
}


Response	&Response::operator=( const Response &r )
{
	if (this != &r)
	{
		this->version = r.getVersion();
		this->code = r.getCode();
		this->message = r.getMessage();
		this->headers = r.getHeaders();
		this->body = r.getBody();
		this->ext = r.getExt();
	}
	return (*this);
}

static std::string intToString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
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

std::string	Response::generateResponse() const
{
	std::map<std::string, std::string>::const_iterator	it;
	std::string	res = "";

	res += rm_to_one("HTTP/" + this->version + " " + intToString(this->code) + " " + this->message + "\r\n", '/');
	for (it = this->headers.begin(); it != this->headers.end(); it++)
		res += it->first + ": " + it->second + "\r\n";
	res += "\r\n";
	res += this->body;
	return (res);
}

std::string	Response::generateHeaders() const
{
	std::map<std::string, std::string>::const_iterator	it;
	std::string	res = "";

	res += rm_to_one("HTTP/" + this->version + " " + intToString(this->code) + " " + this->message + "\r\n", '/');
	for (it = this->headers.begin(); it != this->headers.end(); it++)
		res += it->first + ": " + it->second + "\r\n";
	for (unsigned i = 0; i < this->cookies.size(); i++)
		res += "Set-Cookie: " + this->cookies[i] + "\r\n";
	res += "\r\n";

	return (res);
}

std::ostream&	operator<<( std::ostream& o, const Response &r )
{
	std::map<std::string, std::string>::const_iterator	it;

	o << "HTTP/" << r.getVersion() << " " << r.getCode() << " " << r.getMessage() << std::endl;
	for (it = r.getHeaders().begin(); it != r.getHeaders().end(); it++)
		o << it->first << ": " << it->second << std::endl;
	for (unsigned i = 0; i < r.getCookies().size(); i++)
		o << "Set-Cookie: " + r.getCookies()[i] << std::endl;
	o << std::endl;
	o << r.getBody();
	return (o);
}

//Loaders
void	Response::good()
{
	this->code = 200;
	this->message = "OK";
	this->clear_headers();
	this->body.clear();
}

void	Response::clear_headers()
{
	this->headers.clear();
	this->headers["Connection"] = "Close";
	this->headers["Content-Type"] = "text/plain";
	this->headers["Server"] = "WebServ";
	this->headers["Date"] = getCurrentHttpDate();
}

void	Response::forbidden()
{
	this->code = 403;
	this->message = "Forbidden";
	this->clear_headers();
	this->body.clear();
	this->headers["Content-Type"] = "text/plain";
	this->body = "403 The requested file is forbidden";
	this->headers["Content-Length"] = intToString(body.length());
	std::string file = this->route_error_pages + "/403.html";
	if (!this->route_error_pages.empty() && !access(file.c_str(), F_OK))
		this->load_html(file);
}

void	Response::not_found()
{
	this->code = 404;
	this->message = "Not Found";
	this->clear_headers();
	this->body.clear();
	this->headers["Content-Type"] = "text/plain";
	this->body = "404 The requested URL was not found on this server";
	this->headers["Content-Length"] = intToString(body.length());
	std::string file = this->route_error_pages + "/404.html";
	if (!this->route_error_pages.empty() && !access(file.c_str(), F_OK))
		this->load_html(file);
}

void	Response::invalidMethod()
{
	this->code = 405;
	this->message = "Method Not Allowed";
	this->clear_headers();
	this->body.clear();
	this->headers["Content-Type"] = "text/plain";
	this->body = "405 Method Not Allowed";
	this->headers["Content-Length"] = intToString(body.length());
	std::string file = this->route_error_pages + "/405.html";
	if (!this->route_error_pages.empty() && !access(file.c_str(), F_OK))
		this->load_html(file);
}

void	Response::load_html( const std::string &s )
{
	std::ifstream	file_html(s.c_str());
	if (file_html.good())
	{
		file_html.seekg(0, std::ios::end);
		unsigned long fileSize = file_html.tellg();
		file_html.seekg(0, std::ios::beg);
		char *buffer = new char[fileSize];
		if (!buffer)
		{
			file_html.close();
			return ;
		}
		file_html.read(buffer, fileSize);
		this->body.clear();
		this->body.append(buffer, fileSize);
		delete[] buffer;
		this->headers["Content-Type"] = "text/html";
		this->headers["Content-Length"] = intToString(fileSize);
		file_html.close();
	}
}

void	Response::unsupported()
{
	this->code = 415;
	this->message = "Unsupported Media Type";
	this->clear_headers();
	this->body.clear();
	this->headers["Content-Type"] = "text/plain";
	this->body = "415 Unsupported Media Type";
	this->headers["Content-Length"] = intToString(body.length());
	std::string file = this->route_error_pages + "/415.html";
	if (!this->route_error_pages.empty() && !access(file.c_str(), F_OK))
		this->load_html(file);
}

void	Response::too_large()
{
	this->code = 413;
	this->message = "Request Entity Too Large";
	this->clear_headers();
	this->body.clear();
	this->headers["Content-Type"] = "text/plain";
	this->body = "413 Request Entity Too Large";
	this->headers["Content-Length"] = intToString(body.length());
	std::string file = this->route_error_pages + "/413.html";
	if (!this->route_error_pages.empty() && !access(file.c_str(), F_OK))
		this->load_html(file);
}

void	Response::internal_error()
{
	this->code = 500;
	this->message = "Internal Server Error";
	this->clear_headers();
	this->body.clear();
	this->headers["Content-Type"] = "text/plain";
	this->body = "500 Internal Server Error";
	this->headers["Content-Length"] = intToString(body.length());
	std::string file = this->route_error_pages + "/500.html";
	if (!this->route_error_pages.empty() && !access(file.c_str(), F_OK))
	{
		std::cout << "a" << std::endl;
		this->load_html(file);
	}
}

void	Response::load_file( std::string s, int status_code, std::string message )
{
	std::ifstream		file;
	std::string			extension;
	const unsigned long	size_max = 50 * 1024 * 1024; //50Mb max

	this->not_found();
	if (s.empty() || s.find(".") == std::string::npos)
		return ;
	if (access(s.c_str(), F_OK) < 0)
		return ;
	struct stat		fileStat;
	stat(s.c_str(), &fileStat);
	if (S_ISDIR(fileStat.st_mode))
		return ;
	extension = s.substr(s.find_last_of("."), std::string::npos);
	if (this->ext.find(extension) == this->ext.end())
	{
		if (file.good())
			this->unsupported();
		return ;
	}
	if (this->ext.find(extension)->second.second)
		file.open(s.c_str(), std::ios::binary);
	else
		file.open(s.c_str());
	if (!file.good())
		return ;
	file.seekg(0, std::ios::end);
    unsigned long fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
	if (fileSize > size_max)
	{
		this->too_large();
		file.close();
		return ;
	}
	char *buffer = new char[fileSize];
	if (!buffer)
	{
		this->too_large();
		file.close();
		return ;
	}
    file.read(buffer, fileSize);
	this->body.clear();
	this->body.append(buffer, fileSize);
	delete[] buffer;
	this->clear_headers();
	this->headers["Content-Type"] = this->ext.find(extension)->second.first;
	this->headers["Content-Length"] = intToString(fileSize);
	this->code = status_code;
	this->message = message;
	file.close();
}

void	Response::autoindex( std::string ruta_act, std::string path, std::string root )
{
    DIR* 			dir;
    struct dirent* 	entrada;
	std::string		html = "";

	while (path[path.size() - 1] == '/')
		path.erase(path.end() - 1);
	while (ruta_act[ruta_act.size() - 1] == '/')
		ruta_act.erase(ruta_act.end() - 1);
	ruta_act = rm_to_one(ruta_act, '/');
    if ((dir = opendir(ruta_act.c_str())) != NULL)
	{
		(void)dir;
		html = "<html><head></head><body>";
		html += "<style>.custom-list {list-style-type: none;padding-left: 20px;}.custom-list li {position: relative;margin-bottom: 10px;}.custom-list li:before {content: \"->\";position: absolute;left: -20px;color: #4285F4;}a:active {color: #0000EE;}a:focus {outline: none;color: #0000EE;}a {color: #0000EE;text-decoration: none;}</style>";
		std::string ruta = path + "/" + ruta_act.substr(root.size(), std::string::npos);
		ruta = rm_to_one(ruta, '/');
		while (ruta[ruta.size() - 1] == '/')
			ruta.erase(ruta.end() - 1);
		html += "<h1>Index of " + ruta + "/</h1>";
		html += "<ul class=\"custom-list\">";
        while ((entrada = readdir(dir)) != NULL)
		{
			std::string n_f(entrada->d_name);
			if (n_f != "." && n_f != "..")
				ruta = path + "/" +  ruta_act.substr(root.size(), std::string::npos) + "/" + n_f;
			else
				ruta = n_f;
			struct stat		fileStat;
			//memset(&fileStat, 0, sizeof(fileStat));
			stat(ruta.c_str(), &fileStat);
			if (S_ISDIR(fileStat.st_mode) && entrada->d_type != DT_REG) // Es carpeta
			{
				std::string name_file(entrada->d_name);
				html += "<li>";
				ruta = path + "/" +  ruta_act.substr(root.size(), std::string::npos) + "/" + name_file;
				ruta = rm_to_one(ruta, '/');
				html += "<a href=\"" + ruta + "\">";
                html += "		" + std::string(entrada->d_name) + "/";
				html += "</a>";
				html += "</li>";
			}
            else if (entrada->d_type == DT_REG) //Es archivo
			{
				std::string name_file(entrada->d_name);
				std::string extension = "";
				if (name_file.find(".") != std::string::npos)
					extension = name_file.substr(name_file.find_last_of("."), std::string::npos);
				html += "<li>";
				if (this->ext.find(extension) != this->ext.end())
				{
					ruta = path + "/" +  ruta_act.substr(root.size(), std::string::npos) + "/" + name_file;
					ruta = rm_to_one(ruta, '/');
					html += "<a href=\"" + ruta + "\">";
				}
                html += "		" + std::string(entrada->d_name);
				if (this->ext.find(extension) != this->ext.end())
					html += "</a>";
				html += "</li>";
			}
		}
		html += "<ul></body></html>";
		this->body.clear();
		this->body.append(html);
		this->headers["Content-Type"] = "text/html";
		this->headers["Content-Length"] = intToString(this->body.size());
		this->code = 200;
		this->message = "OK";
		closedir(dir);
    }
	else
	{
		this->not_found();
        std::cerr << "No se pudo abrir el directorio." << std::endl;
	}
}

void	Response::redirect( std::string url )
{
	this->headers.clear();
	this->body.clear();
	this->headers["Location"] = url;
	this->code = 301;
	this->message = "Moved Permanently";
}

//getter
const std::string							&Response::getVersion() const
{
	return (this->version);
}

int											Response::getCode() const
{
	return (this->code);
}

const std::string							&Response::getMessage() const
{
	return (this->message);
}

const std::map<std::string, std::string>	&Response::getHeaders() const
{
	return (this->headers);
}

const std::string							&Response::getBody() const
{
	return (this->body);
}

const std::map<std::string, std::pair<std::string, bool> >	&Response::getExt() const
{
	return (this->ext);
}

const std::string	&Response::getRouteErrorPages() const
{
	return (this->route_error_pages);
}

//Setters
void	Response::setVersion( const std::string &s )
{
	this->version = s;
}

void	Response::setBody( const std::string &body )
{
	this->body = body;
}

static std::string			nextLine( const std::string &body, size_t &i )
{
	std::string		result;
	size_t			j;

	if (i == std::string::npos)
		return ("");
	j = body.find_first_of('\n', i);
	result = body.substr(i, j - i);
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

const std::vector<std::string>	&Response::getCookies() const
{
	return this->cookies;
}

void	Response::setBodyWithHeaders( const std::string &new_body )
{
	size_t	i, index = 0;
	std::string line;
	if ((i = new_body.find("\r\n\r\n")) != std::string::npos)
	{
		while ((line = nextLine( new_body, index )) != "" && line != "\r")
		{
			std::string key = getKey( line );
			std::string value = getValue( line );
			if (key == "Set-Cookie")
				this->cookies.push_back(value);
			else
				this->headers[key] = value;
		}
		this->body = new_body.substr(i + 4, std::string::npos);
	}
}

void	Response::setCode( int code )
{
	this->code = code;
}

void	Response::setMessage( const std::string &message )
{
	this->message = message;
}

void	Response::setRouteErrorPages( const std::string &route )
{
	std::string route_good = rm_to_one(route, '/');
	while (route_good[route_good.size() - 1] == '/')
		route_good.erase(route_good.end() - 1);
	this->route_error_pages = route_good;
}

void	Response::set_php_header()
{
	this->headers["Content-Type"] = "text/html";
}

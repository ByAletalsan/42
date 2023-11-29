/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:02:00 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/29 12:15:18 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "Cgi.hpp"
#include "Response.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Location.hpp"


# define BOLD   "\033[1m"
# define BLACK  "\033[30;1m"
# define RED    "\033[31;1m"
# define GREEN  "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE   "\033[34;1m"
# define MAGENTA    "\033[35;1m"
# define CYAN   "\033[36;1m"
# define WHITE  "\033[37;1m"
# define DEFAULT    "\033[0m"

class Response;

class Request
{
	private:
		Methods								method;		// POST, GET...
		std::string							fullPath;	// /algo/dsa.php?sd=dsa
		std::string							path;		// /algo/dsa.php -> (/algo)
		std::string							file;		// /algo/dsa.php -> (dsa.php)
		std::string							infoPath;	// /algo/dsa.php/mas/info?ds=sad -> (/mas/info)
		std::string							query;		// index?variable=2,x=2 -> (variable=2,x=2)
		std::string							version;	// HTML/1.1 -> (1.1)
		std::map<std::string, std::string>	headers;	// Host:webserv, Accept-Langiage:es-Es,es;q=0.9, ...
		int									port;		// Host: webser:80 -> (80)
		std::string							host;		// Host: webser:80 -> (webser)
		std::string							body;		// <html>, [{},{}], "Jejeje, texto", ...
		int									code;		//status code (200:good, 400:bad)
		std::string							boundary;	// key when uploading files

		Request();

		//methods
		std::string							nextLine( const std::string &str, size_t& i );
		void								setFirstLine( const std::string &line );
		int									getInfoPort();
		std::string							getInfoHost();
		std::string							getInfoQuery();
		void								getInfoPath();
		void								decodeParams();
		std::map<std::string,std::string>	initEnv( Client &client, Server &server, const std::string &fileName );
		char								**initArgs( std::vector<Cgi> cgis, const std::string &fileName ) const;

	public:
		Request( std::string http );
		Request( const Request &r );
		~Request();

		Request &operator=( const Request &r );

		bool		isCGI( std::vector<Cgi> cgis ) const; //chequea si el archivo corresponde a un cgi de la lista
		void		executeCGI( Response &res, Client &client, Server &server, Location &loc ); //devuelve un Response configurado con la salida del cgi

		bool	isFileUpload(); //Chequear si es POST y etiquetas con body para upload
		void	createFilesUpload( std::string route, Response &res ) const; //Creamos los archivos en la ruta pasada
	
		//getters
		Methods										getMethod() const;
		const std::string							&getPath() const;
		const std::string							&getFile() const;
		const std::string							&getInfoPath() const;
		const std::string							&getFullPath() const;
		const std::string							&getHost() const;
		const std::string							&getQuery() const;
		const std::string							&getVersion() const;
		const std::map<std::string, std::string>	&getHeaders() const;
		int											getPort() const;
		const std::string							&getBody() const;
		int											getCode() const;
		const std::string							&getBoundary() const;

		//Setters
		void	setBoundary( const std::string &boundary );
		void	setFile( const std::string &file );

};

std::ostream&	operator<<( std::ostream &o, const Request &r );

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:58:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/29 16:46:54 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "Request.hpp"

class Response
{
	private:
		std::string												version;			// HTML/1.1 -> (1.1)
		int														code;				// status code (200:good, 400:bad, ...)
		std::string												message;			// HTTP/1.1 200 OK (OK -> first line)
		std::map<std::string, std::string>						headers;			// Content-Type, Content-Length, Content-Encoding, Set-Cookie
		std::vector<std::string>								cookies;			// Set-Cookies
		std::string												body;				// <html>, [{},{}], "Jejeje, texto", ...
		std::map<std::string, std::pair<std::string, bool> >	ext;				// Extensiones que manejamos
																					// pair ("data/text", isBinary)
		std::string												route_error_pages;	// routes for error pages

	public:
		Response();
		Response( const Response &r );
		~Response();

		Response	&operator=( const Response &r );

		std::string	generateResponse() const;
		std::string	generateHeaders() const;

		//Loaders
		void	clear_headers();
		void	good(); //200 OK
		void	forbidden(); // 403 Forbidden
		void	not_found(); //404 content not found
		void	invalidMethod(); //405 Invalid method
		void	unsupported(); //415 extension not sopported
		void	too_large(); //413 Payload too large
		void	internal_error(); //500 Internal Server Error
		void	load_html( const std::string &s );
		void	load_file( std::string s, int status_code, std::string message ); //"ruta html", codigo error, mensaje
		void	autoindex( std::string ruta_act, std::string path, std::string root ); //"ruta" -> genera response con html del listado de archivos de la ruta
		void	redirect( std::string url ); //"url" -> se configura para hacer una redireccion

		//getters
		const std::string											&getVersion() const;
		int															getCode() const;
		const std::string											&getMessage() const;
		const std::map<std::string, std::string>					&getHeaders() const;
		const std::string											&getBody() const;
		const std::map<std::string, std::pair<std::string, bool> >	&getExt() const;
		const std::string											&getRouteErrorPages() const;
		const std::vector<std::string>								&getCookies() const;

		//setter
		void	setVersion( const std::string &s );
		void	setBody( const std::string &body );
		void	setBodyWithHeaders( const std::string &new_body );
		void	setCode( int code );
		void	setMessage( const std::string &message );
		void	setRouteErrorPages( const std::string &route );
		void	set_php_header();
		
};

std::ostream&	operator<<( std::ostream& o, const Response &r );

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:44:51 by delvira-          #+#    #+#             */
/*   Updated: 2023/11/29 20:12:01 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

extern std::vector<int> sockets;
extern std::vector<struct sockaddr_in> serversAddrs;
extern std::vector<Server> server_vector;
extern std::vector<Client> client_vector;

static void send_http(Response &res, Client &client)
{
	int	control = 0;
	
    std::string headers = res.generateHeaders();
    control = send(client.getFd(), headers.c_str(), static_cast<int>(headers.length()), 0);
	if (control <= 0)
	{
		std::cerr << RED << "Failure sending response charging headers." << DEFAULT << std::endl;
		return ;
	}
    std::string body = res.getBody();
    control = send(client.getFd(), body.c_str(), static_cast<int>(body.length()), 0);
	if (control <= 0)
	{
		std::cerr << RED << "Failure sending response charging body." << DEFAULT << std::endl;
		return ;
	}
    std::cout << YELLOW << res.getCode() << " " << res.getMessage() << " -> " << client.getIp() << " : " << client.getPort() << DEFAULT << std::endl;
}

static void  handle_get(Location &final_loc, Request &req, Response &res, Client &client, int i)
{
    // ------------- Si hay redirección se la ponemos y nos vamos ---------------- //
	    
    if (!final_loc.get_redirect().empty())
    {
        res.redirect(final_loc.get_redirect());
        return ;
    }
    
    // ------------- Buscamos archivo y si no lo tiene comprobamos location y la ruta de request para saber si añadimos index o autoindex si lo tiene ---------------- //
    
    if (req.getFile().empty())
    {
        if (req.getPath() == final_loc.get_path())
            req.setFile(final_loc.get_index());
        else
        {
            if (res.getCode() == 404 && final_loc.get_autoindex())
                res.autoindex(final_loc.get_root() + "/" + req.getPath().substr(final_loc.get_path().size(), std::string::npos), final_loc.get_path(), final_loc.get_root());
            return ;
        }
    }

    // ------------- Ya tenemos archivo, comprobamos si es CGI o no ---------------- //
    
    if (!req.isCGI(final_loc.get_cgis()))
    {
        std::string full_route = final_loc.get_root() + "/" + req.getPath().substr(final_loc.get_path().size(), std::string::npos) + "/" + req.getFile();
        res.load_file(full_route, 200, "OK");
        if (res.getCode() == 404 && final_loc.get_autoindex())
            res.autoindex(final_loc.get_root() + "/" + req.getPath().substr(final_loc.get_path().size(), std::string::npos), final_loc.get_path(), final_loc.get_root());
        return ;
    }
    
    // ------------- Ejecutamos CGI si lo fuera ---------------- //
    
    else
    {
        req.executeCGI(res, client, server_vector[i], final_loc);
        if (res.getCode() == 404 && final_loc.get_autoindex())
            res.autoindex(final_loc.get_root() + "/" + req.getPath().substr(final_loc.get_path().size(), std::string::npos), final_loc.get_path(), final_loc.get_root());
        return ;
    }
    
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

static void  handle_delete(Location &final_loc, Request &req, Response &res)
{
    // ------------- Buscamos si existe el archivo que queremos eliminar y tiene extensión adecuada ---------------- //
	res.internal_error();
	if (req.getFile().empty() || req.getFile().find(".") == std::string::npos)
		return ;
	std::string ext = req.getFile().substr(req.getFile().find_last_of("."), std::string::npos);
	if (res.getExt().find(ext) == res.getExt().end())
		return ;
	// ------------- Montamos la ruta donde esté el archivo ---------------- //
    std::string route;
	route = final_loc.get_root() + "/" + req.getPath().substr(final_loc.get_path().size(), std::string::npos) + "/" + req.getFile();
	route = rm_to_one(route, '/');
	
	//Check caprtea
	struct stat		fileStat;
	stat(route.c_str(), &fileStat);
	if (S_ISDIR(fileStat.st_mode))
		return ;
	if (access(route.c_str(), F_OK) < 0)
	{
		res.not_found();
		return ;
	}
	//Se puede abrir archivo? - permisos
	if (!std::ifstream(route.c_str()))
	{
		res.forbidden();
    	return ;
	}
	//Ok, intentamos borrar
	if (remove(route.c_str()) == 0)
       res.good();
}


void manage_client(Client &client)
{
    Response 	res;
    res.not_found();
    
    Request		req(client.getRequest());
    if (req.getCode() == 400)
    {
        send_http(res, client);
        return ;
    }
    
    std::map<Methods, std::string>	mapMethods;
    mapMethods[POST] =  "POST";
	mapMethods[GET] =  "GET";
	mapMethods[DELETE] =  "DELETE";
	mapMethods[PUT] =  "PUT";
	mapMethods[HEAD] =  "HEAD";
	mapMethods[OPTIONS] =  "OPTIONS";
	mapMethods[TRACE] =  "TRACE";
    std::cout << BLUE << client.getIp() << " : " << client.getPort() << " -> " << mapMethods[req.getMethod()] << " " << req.getFullPath() << DEFAULT << std::endl;

    
    // ------------- Buscamos el servidor correcto ---------------- //
    
    unsigned i;
    for (i = 0; i < server_vector.size(); i++)
    {
        // ------------- Comprobamos el puerto ---------------- //
        if (server_vector.at(i).get_listen() == req.getPort())
        {
            // ------------- Comprobamos que el server name exista y coincida ---------------- //
            if (!server_vector.at(i).get_server_name().empty() && (server_vector.at(i).get_server_name() != req.getHost()))
                continue ;
            // ------------- Comprobamos ip del cliente para que coincida con el host del archivo de configuración ---------------- //
            if (!server_vector.at(i).get_host().empty() && (server_vector.at(i).get_host() != "0.0.0.0") && (server_vector.at(i).get_host() != client.getIp()))
                continue ;
            break ;
        }
    }
    
    // ------------- Si no encuentra servidor ponemos el primero ---------------- //
    if (i >= server_vector.size())
        i = 0;

    // ------------- Encontrar la localización en la que se encuentra el cliente ---------------- //

    size_t coincidencias_max = 0;
    Location final_loc = server_vector[i].get_locations()[0];
    for (unsigned j = 1; j < server_vector[i].get_locations().size(); j++)
    {
        Location l = server_vector[i].get_locations()[j];
        size_t size = 0;

    // ------------- Busqueda de coincidencias de nivel de profundidad ---------------- //
        
        for (size_t w = 0; w < l.get_path().length(); w++)
        {
            if (l.get_path()[w] == '/' && l.get_path()[w + 1] != 0)
                size++;
        }
        size_t index;
        if ((index = req.getPath().find(l.get_path())) != std::string::npos && (req.getPath()[index + l.get_path().size()] == '\0'
            || req.getPath()[index + l.get_path().size()] == '/') && size > coincidencias_max)
        {
            coincidencias_max = size;
            final_loc = l;
        }
    }

    // ------------- Establecemos la ruta de las paginas de error ---------------- //


    res.setRouteErrorPages(server_vector[i].get_error_pages());
    res.not_found();


    // ------------- Comprobamos el tamaño del body ---------------- //

    if (req.getBody().size() > final_loc.get_body_size())
    {
        res.too_large();
        send_http(res, client);
        return ;
    }

    // ------------- Comprobamos el método de la petición del cliente con el que acepta el servidor ---------------- //
    

    bool        method = false;
    for (unsigned j = 0; j < final_loc.get_methods().size(); j++)
    {
        if (req.getMethod() == final_loc.get_methods()[j])
        {
            method = true;
            break;
        }
    }
    if (!method)
    {
        res.invalidMethod();
        send_http(res, client);
        return ;
    }
    
    switch (req.getMethod())
    {
        case GET:
            handle_get(final_loc, req, res, client, i);
            break;
        case POST:
            if (!req.isFileUpload())
                handle_get(final_loc, req, res, client, i);
            else
                req.createFilesUpload(final_loc.get_root(), res);
            break;
        case DELETE:
            handle_delete(final_loc, req, res);
            break;
        default:
			res.invalidMethod();
            break;
    }
    
    send_http(res, client);
}

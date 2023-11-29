/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:46:26 by delvira-          #+#    #+#             */
/*   Updated: 2023/11/29 19:38:25 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parse.hpp"
#include <fstream>
#include <stdlib.h>
#include <limits.h>

Parse::Parse()
{
}
Parse::~Parse()
{
}
Parse::Parse( Parse &copy)
{
    this->server_vector = copy.server_vector;
    this->splitted_conf = copy.splitted_conf;
}
Parse & Parse::operator=(Parse & copy)
{
    this->server_vector = copy.server_vector;
    this->splitted_conf = copy.splitted_conf;
    return *this;
}
Parse::Parse(char * filename)
{
    this->filename = std::string(filename);
}


const char * Parse::Excep::what() const throw()
{
    return ("An exception has been thrown!!");
}


std::vector<std::string> file_split(std::string str)
{
    std::vector<std::string> str_vector;

    int i = 0;
    int j = 0;
    std::string aux;

    while (str[i] != '\0')
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;

        j = i;
        while (str[i] != ' ' && str[i] != '\t' && str[i] != ';' && str[i] != '\0' && str[i] != '\t')
            i++;
        
        aux = str.substr(j, (i - j));
        str_vector.push_back(aux);
        if (str[i] == ';')
        {
            str_vector.push_back(";");
            i++;
        }
        i++;
    }
    return (str_vector);
}

void Parse::get_splitted_conf()
{
    std::ifstream file(this->filename.c_str());
    std::vector<std::string> conf_vector;

    if (!file)
    {
        std::cerr << "File not opened" << std::endl;
        throw Parse::Excep();
    }

    std::string line;
    std::string str_file;
    while (std::getline(file, line))
    {
        str_file += line;
        str_file += " ";
    }
        try
    {
        conf_vector = file_split(str_file);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Confif file syntax error" << std::endl;
        throw Parse::Excep();
    }
    this->splitted_conf = conf_vector;
}
void    Parse::print_splitted_conf()
{
    for (std::vector<std::string>::iterator it = this->splitted_conf.begin(); it != this->splitted_conf.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void    Parse::fill_server_name(std::vector<std::string>::iterator &it, Server &srv)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        if (srv.get_server_name() != "")
        {
            std::cout << "server_name entered more than once" << std::endl;
            throw Parse::Excep();
        }
        srv.set_server_name(*it);
        
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: server_name" << std::endl;
        throw Parse::Excep();    
    }
}




std::vector<std::string> split_host(std::string str)
{
    std::vector<std::string> str_vector;

    unsigned int i = 0;
    int j = 0;
    std::string aux;

    while (i < str.length())
    {
        while (str[i] == '.')
            i++;

        j = i;
        while (str[i] != '.' && str[i] != '\0')
            i++;
        
        aux = str.substr(j, (i - j));
        str_vector.push_back(aux);
        i++;
    }
    return (str_vector);

}


bool check_host_number(std::string host)
{
    if (host == "localhost")
        return true;

    for (unsigned i = 0; i < host.size(); i++)
    {
        if ((host[i] > '9' || host[i] < '0') && host[i] != '.')
            return false;
    }

    
    int x = 0;
    for (unsigned i = 0; i < host.size(); i++)
    {
        if (host[i] == '.')
            x++;
    }
    if (x != 3)
        return false;

    std::vector<std::string> splitted_host = split_host(host);

    if (splitted_host.size() != 4)
        return false;

    for (unsigned long i = 0; i < splitted_host.size(); i++)
    {
        long temp = atol(splitted_host[i].c_str());
        if (temp > 255 || temp < 0)
            return false;
    }
    return (true);
}

void     Parse::fill_host(std::vector<std::string>::iterator &it, Server &srv)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        if (srv.get_host() != "")
        {
            std::cout << "server host entered more than once" << std::endl;
            throw Parse::Excep();
        }
        if (check_host_number(*it) == false)
        {
            std::cout << "Conf file error: host not formatted" << std::endl;
            throw Parse::Excep();
        }

        std::string host = (*it == "localhost" || *it == "::1" )? "127.0.0.1" : *it;
        
        srv.set_host(host);
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: host" << std::endl;
                throw Parse::Excep();      
    }
}

bool is_number_formated(std::string num)
{
    for (unsigned long i = 0; i < num.length(); i++)
    {
        if (num[i] > '9' || num[i] < '0')
            return (false);
    }

    if (num.empty())
        return (false);
    long int n;
    n = atol(num.c_str());
    if (n > INT_MAX || n < INT_MIN)
        return (false);
    return (true);
    
}

void     Parse::fill_listen(std::vector<std::string>::iterator &it, Server &srv)
{
    it++;
    if (is_number_formated(*it) == true && *(it + 1) == ";")
    {
        if (srv.get_listen() >= 0)
        {
            std::cout << "server port entered more than once" << std::endl;
            throw Parse::Excep();
        }
        srv.set_listen(atoi((*it).c_str()));
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: listen" << std::endl;
        throw Parse::Excep();    
    }
}

void     Parse::fill_server_error_pages(std::vector<std::string>::iterator &it, Server &srv)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        if (srv.get_error_pages() != "")
        {
            std::cout << "server error_pages entered more than once" << std::endl;
            throw Parse::Excep();
        }
        srv.set_server_error_pages(*it);
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: error_pages" << std::endl;
        throw Parse::Excep();      
    }
}


void     Parse::fill_root(std::vector<std::string>::iterator &it, Location &loc)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        
        loc.set_root(*it);
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: root" << std::endl;
        throw Parse::Excep();      
    }
}

void     Parse::fill_redirect(std::vector<std::string>::iterator &it, Location &loc)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        loc.set_redirect(*it);
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: redirect" << std::endl;
        throw Parse::Excep();      
    }
}


void    Parse::fill_autoindex(std::vector<std::string>::iterator &it, Location &loc)
{
    it++;
    if (*it == "on")
        loc.set_autoindex(true);
    else if (*it == "off")
        loc.set_autoindex(false);
    else
    {
        std::cerr << "Error in Config file: autoindex" << std::endl;
        throw Parse::Excep();
    }
    it++;
}

void     Parse::fill_index(std::vector<std::string>::iterator &it, Location &loc)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        loc.set_index(*it);
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: index" << std::endl;
        throw Parse::Excep();      
    }
}

void    Parse::fill_allow_methods(std::vector<std::string>::iterator &it, Location &loc)
{
    std::vector<Methods> vec;

    it++;
    if (*it != "GET" && *it != "POST" && *it != "DELETE")
    {
        std::cerr << "Error in Config file: allow_methods" << std::endl;
        throw Parse::Excep();
    }
    while (*it == "GET" || *it == "POST" || *it == "DELETE")
    {
        if (*it == "GET")
            vec.push_back(GET);
        else if (*it == "POST")
            vec.push_back(POST);
        else if (*it == "DELETE")
            vec.push_back(DELETE);
        else
        {
        std::cerr << "Error in Config file: allow_methods" << std::endl;
            throw Parse::Excep();
        }
        it++;
    }
    if (*it != ";")
    {
        std::cerr << "Error in Config file: allow_methods" << std::endl;
        throw Parse::Excep();
    }
    loc.set_methods(vec);
}

void     Parse::fill_cgis(std::vector<std::string>::iterator &it, Location &loc)
{
    Cgi cgi;

    it++;
    if (!(*it).empty() && !(*(it + 1)).empty() && *(it + 2) == ";")
    {
        cgi.set_extension(*it);
        it++;
        cgi.set_exec_route(*it);
        it++;
        
    }
    else
    {
        std::cerr << "Error in Config file: cgis" << std::endl;
        throw Parse::Excep();      
    }
    loc.push_back_cgi(cgi);
}

void    Parse::fill_body_size(std::vector<std::string>::iterator &it, Location &loc)
{
    it++;
    if (is_number_formated(*it) == true && *(it + 1) == ";")
    {
        loc.set_body_size(atoi((*it).c_str()));
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: body_size" << std::endl;
        throw Parse::Excep();    
    }
}

void    Parse::fill_mk_saved(std::vector<std::string>::iterator &it, Location &loc)
{
    it++;
    if (!(*it).empty() && *(it + 1) == ";")
    {
        loc.set_mk_saved(*it);
        it++;
    }
    else
    {
        std::cerr << "Error in Config file: mk_saved" << std::endl;
        throw Parse::Excep();      
    }
}


void    Parse::handle_location(std::vector<std::string>::iterator &it, Server &srv)
{
    Location location;

    std::string name_array[8] = {"root", "redirect", "autoindex", "index", "allow_methods", "body_size", "cgi", "mk_saved"};
    void    (Parse::* ptr_array[8]) (std::vector<std::string>::iterator &it, Location &loc) = {&Parse::fill_root, &Parse::fill_redirect, &Parse::fill_autoindex,
                                                                                                &Parse::fill_index, &Parse::fill_allow_methods, &Parse::fill_body_size,
                                                                                                &Parse::fill_cgis, &Parse::fill_mk_saved};

    if ((*(it + 1)).empty() || *(it + 2) != "{")
    {
        std::cerr << "Error in Config file: location" << std::endl;
        throw Parse::Excep();
    }
    location.set_path(*(it + 1));
    it += 3;
    while (*it != "}" && it != this->splitted_conf.end())
    {
        for (int i = 0; i < 8; i++)
        {
            if (*it == name_array[i])
            {
                (this->*ptr_array[i])(it, location);
                break;
            }
        }
        it++;  
    }
    srv.push_location(location);
}



void    Parse::handle_server(std::vector<std::string>::iterator &it)
{
    Server server;

    std::string name_array[5] = {"server_name", "host", "listen", "error_pages", "location"};
    void    (Parse::* ptr_array[5]) (std::vector<std::string>::iterator &it, Server &srv) = {&Parse::fill_server_name, &Parse::fill_host, &Parse::fill_listen,
                                                                                                &Parse::fill_server_error_pages, &Parse::handle_location};

    while (*it != "}" && it != this->splitted_conf.end())
    {
        //std::cout << "aa: " << *it << std::endl;
        for (int i = 0; i < 5; i++)
        {
            if (*it == name_array[i])
            {
                (this->*ptr_array[i])(it, server);
                break;
            }
        }
        it++;
        
    }
    this->server_vector.push_back(server);
}

void    Parse::check_required_location(Location &location)
{
    if (location.get_root() == "")
    {
        std::cout << "Location root not set for location: "<< location.get_path() << std::endl;
        throw Parse::Excep();
    }
    if (location.get_index() == "")
    {
        std::cout << "Location index not set for location: "<< location.get_path() << std::endl;
        throw Parse::Excep();
    }
    if (location.get_methods().empty())
    {
        std::cout << "Location methods not set for location: "<< location.get_path() << std::endl;
        throw Parse::Excep();
    }
}


void    Parse::check_default_location(std::vector<Location> locations)
{
    bool check = false;
    for(unsigned long i = 0; i < locations.size(); i++)
    {
        if (locations.at(i).get_path() == "/")
            check = true;
    }
    if (check == false)
    {
        std::cout << "Default location not set in a server" << std::endl;
        throw Parse::Excep();
    }
}


void    Parse::check_required_server(Server &server)
{
    if (server.get_listen() < 0)
    {
        std::cout << "Port number not set or valid in server"  << std::endl;
        throw Parse::Excep();
    }
    if (server.get_host() == "")
    {
        std::cout << "Server host not set" << std::endl;
        throw Parse::Excep();
    }
    if (server.get_error_pages() == "")
    {
        std::cout << "Server error_pages not set" << std::endl;
        throw Parse::Excep();
    }

    this->check_default_location(server.get_locations());

    for (unsigned long i = 0; i < server.get_locations().size(); i++)
    {
        this->check_required_location(server.get_locations().at(i));
    }
}


void    Parse::check_required()
{
    for (unsigned long i = 0; i < this->server_vector.size(); i++)
    {
        this->check_required_server(this->server_vector.at(i));
    }
}

void    Parse::open_closed_brackets()
{
    int open = 0;
    int closed = 0;
    for (unsigned long i = 0; i < this->splitted_conf.size(); i++)
    {
        for (unsigned long j = 0; j < this->splitted_conf.at(i).length(); j++)
        {
            if (this->splitted_conf.at(i)[j] == '{')
                open++;
            else if (this->splitted_conf.at(i)[j] == '}')
                closed++;
            
        }
    }
    if (open != closed)
    {
        std::cout << "open and closed brackets don't mathc in .conf file" << std::endl;
        throw Parse::Excep();
    }
    
}

void    Parse::check_multiple_brackets()
{
    for (unsigned long i = 0; i < this->splitted_conf.size() ; i++)
    {
        if (!this->splitted_conf.at(i).find("{", 0))
        {
            if (this->splitted_conf.at(i) != "{")
            {
                std::cout << this->splitted_conf.at(i) << std::endl;
                std::cout << "brackets must be separated in conf file" << std::endl;
                throw Parse::Excep();
            }
        }
        if (!this->splitted_conf.at(i).find("}", 0))
        {
            if (this->splitted_conf.at(i) != "}")
            {
                std::cout << "brackets must be separated in conf file" << std::endl;
                throw Parse::Excep();
            }
        }
    }
}


void    Parse::error_checks()
{
    this->check_required();
    if (this->server_vector.empty())
    {
        std::cout << "No server found in conf file" << std::endl;
        throw Parse::Excep();
    }
}


std::vector<Server>    &Parse::parse_file()
{
    this->get_splitted_conf();
    this->open_closed_brackets();
    this->check_multiple_brackets();
    std::vector<std::string>::iterator it = this->splitted_conf.begin();
    while (it != this->splitted_conf.end())
    {
        if (*it == "server" && *(it + 1) == "{")
           this->handle_server(it);
        it++;
    }
    this->error_checks();
    return this->server_vector;
}


void    Parse::print_all_info()
{
    for (int i = 0; i < (int)this->server_vector.size(); i++)
    {
        this->server_vector.at(i).print_server_info();
    }
}

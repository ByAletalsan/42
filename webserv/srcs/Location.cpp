/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:06:39 by delvira-          #+#    #+#             */
/*   Updated: 2023/11/29 17:39:45 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"
#include "../includes/webserv.hpp"

Location::Location()
{
    this->root = "";
    this->path = "";
    this->redirect = "";
    this->autoindex = false;
    this->index = "";
    this->body_size = -1;
    this->mk_saved = "";
}

Location::~Location()
{
        
}

Location::Location( const Location &l )
{
    this->root = l.root;
    this->path = l.path;
    this->autoindex = l.autoindex;
    this->index = l.index;
    this->methods = l.methods;
    this->body_size = l.body_size;
    this->redirect = l.redirect;
    this->cgis = l.cgis;
    this->mk_saved = l.mk_saved;
}

Location & Location::operator=( const Location &l )
{
    this->root = l.root;
    this->path = l.path;
    this->autoindex = l.autoindex;
    this->index = l.index;
    this->methods = l.methods;
    this->body_size = l.body_size;
    this->cgis = l.cgis;
    this->redirect = l.redirect;
    this->mk_saved = l.mk_saved;
    return *this;
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

void	Location::set_path(std::string path)
{
    std::string res = rm_to_one(path, '/');
    while (res.size() > 1 && res[res.size() - 1] == '/')
		res.erase(res.end() - 1);
    this->path = res;
}

void	Location::set_root(std::string root)
{
    std::string res = rm_to_one(root, '/');
    while (res.size() > 1 && res[res.size() - 1] == '/')
		res.erase(res.end() - 1);
    this->root = res;
}
void	Location::set_redirect(std::string redir)
{
    this->redirect = redir;
}
void	Location::set_autoindex(bool autoin)
{
    this->autoindex = autoin;
}
void	Location::set_index(std::string in)
{
    std::string res = rm_to_one(in, '/');
    while (res.size() > 1 && res[res.size() - 1] == '/')
		res.erase(res.end() - 1);
    this->index = res;
}
void	Location::set_methods(std::vector<Methods> &methods)
{
    this->methods = methods;
}
void	Location::set_body_size(unsigned int body)
{
    this->body_size = body;
}
void	Location::set_cgis(std::vector<Cgi> cgi)
{
    this->cgis = cgi;
}

void	Location::set_mk_saved(std::string mk_saved)
{
    std::string res = rm_to_one(mk_saved, '/');
    while (res.size() > 1 && res[res.size() - 1] == '/')
		res.erase(res.end() - 1);
    this->mk_saved = res;
}
		
		//GETTERS

std::string				&Location::get_path()
{
    return (this->path);
}

std::string				&Location::get_root()
{
    return (this->root);
}
std::string				&Location::get_redirect()
{
    return (this->redirect);
}
bool					Location::get_autoindex()
{
    return (this->autoindex);
}
std::string				&Location::get_index()
{
    return(this->index);
}
std::vector<Methods>	&Location::get_methods()
{
    return (this->methods);
}
unsigned int			Location::get_body_size()
{
    return (this->body_size);
}
std::vector<Cgi> 		&Location::get_cgis()
{
    return (this->cgis);
}

std::string				&Location::get_mk_saved()
{
    return (this->mk_saved);
}


void					Location::push_back_method(Methods &method)
{
    this->methods.push_back(method);
}
void					Location::push_back_cgi(Cgi &cgi)
{
    this->cgis.push_back(cgi);
}

void					Location::print_location_info()
{
    std::cout <<  "\033[32;1m" << std::endl;
    std::cout << "----------NEW_LOCATION------------" << std::endl;
    std::cout << "path: " << this->get_path() << std::endl;
    std::cout << "root: " << this->get_root() << std::endl;
    std::cout << "redirect: " << this->get_redirect() << std::endl;
    std::cout << "autoindex: " << this->get_autoindex() << std::endl;
    std::cout << "index: " << this->get_index() << std::endl;
    std::cout << "mk_saved: " << this->get_mk_saved() << std::endl;
    std::cout << "methods: ";
    for (int i = 0; i < (int)this->get_methods().size(); i++)
    {
        std::cout << this->get_methods().at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "body_size: " << this->get_body_size() << std::endl;
    std::cout <<  "\033[0m" << std::endl;
    for (int i = 0; i < (int)this->get_cgis().size(); i++)
    {
        this->get_cgis().at(i).print_info();
    }
}

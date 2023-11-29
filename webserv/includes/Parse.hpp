/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:39:06 by delvira-          #+#    #+#             */
/*   Updated: 2023/11/19 15:57:27 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
#define PARSE_HPP

#include "Server.hpp"
#include <vector>
#include <iostream>
#include <exception>

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

class Parse
{
    private:
        std::vector<Server>      server_vector;
        std::string              filename;
        std::vector<std::string> splitted_conf;
        
        void                    get_splitted_conf();
        void                    print_splitted_conf();
        void                    handle_server(std::vector<std::string>::iterator &it);

        // SERVER FILLERS
        void                    fill_server_name(std::vector<std::string>::iterator &it, Server &srv);
        void                    fill_host(std::vector<std::string>::iterator &it, Server &srv);
        void                    fill_listen(std::vector<std::string>::iterator &it, Server &srv);
        void                    fill_server_error_pages(std::vector<std::string>::iterator &it, Server &srv);
        
        void                    handle_location(std::vector<std::string>::iterator &it, Server &srv);

        // LOCATION FILLERS
        void                    fill_root(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_redirect(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_autoindex(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_index(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_allow_methods(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_cgis(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_body_size(std::vector<std::string>::iterator &it, Location &loc);
        void                    fill_mk_saved(std::vector<std::string>::iterator &it, Location &loc);

        // ERROR CHECKS

        void                    check_required();
        void                    check_required_server(Server &server);
        void                    check_required_location(Location &location);
        void                    check_default_location(std::vector<Location> locations);
        void                    open_closed_brackets();
        void                    check_multiple_brackets();

        
    public:
        Parse();
        ~Parse();
        Parse( Parse &copy);
        Parse & operator=(Parse & copy);
        Parse(char * filename);

        std::vector<Server>     &parse_file();
        void                    error_checks();
        void                    print_all_info();
        
        class Excep : public std::exception
        {
            public:
                const char *what() const throw();
        };
};


#endif
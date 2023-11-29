/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:33:51 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/11/29 17:25:34 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WEBSERV_HPP__
#define __WEBSERV_HPP__

#include "Cgi.hpp"
#include "Parse.hpp" 
#include "Location.hpp"
#include "Server.hpp"
#include "Response.hpp"
#include "Client.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <algorithm>
#include <csignal>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <dirent.h>
#include <sys/stat.h>
#include <cstdio>

#define BUFFER_SIZE 60000




int	recv_data( Client &client );
void manage_client(Client &client);

#endif
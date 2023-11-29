/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:36:24 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/11/29 19:46:54 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

// -------------- VARIABLES GLOBALES ----------------------- //

std::vector<int> sockets;
std::vector<struct sockaddr_in> serversAddrs;
std::vector<Server> server_vector;
std::vector<Client> client_vector;

// ------------------ MANEJADORES -------------------------- //

void	controlC(int nsignal)
{
	for (unsigned int i = 0; i < sockets.size(); i++)
	{
		close(sockets[i]);
		std::cout << GREEN << "Server " << server_vector[i].get_server_name() << " closed." << DEFAULT << std::endl;
	}
	signal(nsignal, controlC);
	exit(1);
}

// --------------------------------------------------------- //
// --------------------- MAIN ------------------------------ //
// --------------------------------------------------------- //

int main(int nargs, char **args)
{
    if (nargs != 2)
    {
        std::cerr << RED << "Arguments error" << DEFAULT << std::endl;
        return (1);
    }
	
	signal(SIGINT, controlC);
	signal(SIGPIPE, SIG_IGN);
	
	Parse  parse_obj(args[1]);
	try
	{
		server_vector = parse_obj.parse_file();

	// --------------------------------------------------------- //
	// ---------------- CONFIGUAMOS SOCKETS -------------------- //
	// --------------------------------------------------------- //

		for (unsigned int i = 0; i < server_vector.size(); i++)
		{
			int s;
			if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            {
                std::cerr << RED << "Error creating sockets..." << DEFAULT << std::endl;
                kill(getpid(), SIGINT);
            }
            sockets.push_back(s);
		}

		// ------------ CONFIGURACIÓN DE SOCKETS --------------- //

		for (unsigned i = 0; i < sockets.size(); i++)
        {
            struct sockaddr_in s;
            s.sin_family = AF_INET;
            s.sin_port = htons(server_vector[i].get_listen());
            s.sin_addr.s_addr = INADDR_ANY;
            memset(s.sin_zero, '\0', sizeof(s.sin_zero));
            serversAddrs.push_back(s);

            // -------------- BINDEAMOS ------------------------ //

            if (bind(sockets.at(i), (struct sockaddr *)&serversAddrs.at(i), sizeof(struct sockaddr)) == -1)
            {
                std::cerr << RED << "Error binding sockets..." << DEFAULT << std::endl;
                kill(getpid(), SIGINT);
            }
        }

		for (unsigned x = 0; x < server_vector.size(); x++)
		{
			std::cout << GREEN << "Server " << server_vector[x].get_server_name() << " : " << server_vector[x].get_listen() << DEFAULT << std::endl;
		}

		// ---------- CONFIGURACIÓN DE LISTEN ------------------ //
	
		for (unsigned i = 0; i < sockets.size(); i++)
        {
            if (listen(sockets[i], 10) == -1)
            {
               	std::cerr << RED << "Error listen sockets..." << DEFAULT << std::endl;
            	kill(getpid(), SIGINT);
            }
        }
		
		// ---------------- CONFIGURAMOS SELECT ---------------- //
	
		fd_set readfds;
		
    	FD_ZERO(&readfds);
        for (unsigned i = 0; i < sockets.size(); i++)
		{
        	FD_SET(sockets.at(i), &readfds);
		}
		

		// ----------------------------------------------------- //
		// ---------------- WHILE LOOP PASON ------------------- //
		// ----------------------------------------------------- //

		while (51)
		{
			int max_fd = *std::max_element(sockets.begin(), sockets.end());
        	for (unsigned i = 0; i < client_vector.size(); i++)
			{
				if (client_vector[i].getFd() > max_fd)
					max_fd = client_vector[i].getFd();
			}

			fd_set tempfds = readfds;
            int sel = select(max_fd + 1, &tempfds, NULL, NULL, NULL);
			if (sel < 0)
			{
				std::cerr << RED << "Error select" << DEFAULT << std::endl;
				kill(getpid(), SIGINT);
			}

		// ---------------- MANAGE CLIENTS --------------------- //

			for (unsigned int i = 0; i < sockets.size(); i++)
			{
				if (FD_ISSET(sockets[i], &tempfds))
				{
					int client_fd;
					struct sockaddr_in clientAddr;
					socklen_t sin_size = sizeof(struct sockaddr_in);
					client_fd = accept(sockets[i], (struct sockaddr *)&clientAddr, &sin_size);
					if (client_fd < 0)
					{
						std::cerr << RED << "Error accepting client" << DEFAULT << std::endl;
						kill(getpid(), SIGINT);				
					}
					Client new_client(client_fd, clientAddr);
					std::cout << CYAN << "Server " << server_vector[i].get_server_name() << " : " << server_vector[i].get_listen() << " has accepted a client " << new_client.getIp() << " : " << new_client.getPort() << DEFAULT << std::endl;
					client_vector.push_back(new_client);
					FD_SET(client_fd, &readfds);
				}
			}

			for (unsigned int i = 0; i < client_vector.size(); i++)
			{
				if (FD_ISSET(client_vector[i].getFd(), &tempfds))
				{
					int	status = recv_data(client_vector[i]);
					if (status == 0)
					{
			// ------------ CHECKEO DE INFO CLIENTE -------------- //
						manage_client(client_vector[i]);
						close(client_vector[i].getFd());
						FD_CLR(client_vector[i].getFd(), &readfds);
						client_vector.erase(client_vector.begin() + i);
					}
					else if (status == -1)
					{
						//fallo
						FD_CLR(client_vector[i].getFd(), &readfds);
						client_vector.erase(client_vector.begin() + i);
					}
				}
			}
			
		}
	}
	catch (std::exception &e)
	{
		std::cerr << RED << e.what() << DEFAULT << std::endl;
	}
	return 0;
}
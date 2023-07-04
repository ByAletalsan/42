/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:45:16 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/03 12:55:08 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    int n = 20;
    std::string name = "PACO";

    std::cout << "Creamos una horda zombie de PACOS" << std::endl;
    Zombie *zombies = zombieHorde(n, name);
    for (int i = 0; i < n; i++)
        zombies[i].announce();
    delete [] zombies;
    return (0);
}

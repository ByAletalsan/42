/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:50:45 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 05:42:00 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap paco("PACO");
    ClapTrap pepe("pepe");
    ClapTrap paco2 = paco;

    for (int i = 0; i < 10; i++)
        paco.attack(pepe.getName());

    paco.takeDamage(50);
    paco.beRepaired(10);

    for (int i = 0; i < 11; i++)
        paco2.attack(pepe.getName());

    paco2.takeDamage(1);
    paco2.beRepaired(2);

    return (0);
}

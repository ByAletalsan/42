/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:50:45 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 07:14:44 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main(void)
{
    ScavTrap pepe("PEPE");
    pepe.print_stats();

    ScavTrap pepe2(pepe);
    pepe2.print_stats();

    ScavTrap def;
    def.print_stats();
    def = pepe2;
    def.print_stats();

    def.attack(pepe.getName());
    pepe.takeDamage(def.getAttackDamage());

    pepe.print_stats();

    pepe.guardGate();

    return (0);
}

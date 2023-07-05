/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:50:45 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 07:22:35 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main(void)
{
    FragTrap pepe("PEPE");
    pepe.print_stats();

    FragTrap pepe2(pepe);
    pepe2.print_stats();

    FragTrap def;
    def.print_stats();
    def = pepe2;
    def.print_stats();

    def.attack(pepe.getName());
    pepe.takeDamage(def.getAttackDamage());

    pepe.highFivesGuys();
    pepe.print_stats();

    return (0);
}

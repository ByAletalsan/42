/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:51:14 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 06:40:21 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>


class ClapTrap
{
    private:
        std::string name;
        int         hit_points;
        int         energy_points;
        int         attack_damage;

    public:
        ClapTrap();
        ClapTrap( const ClapTrap &c );
        ClapTrap( const std::string &name );
        ~ClapTrap();
        
        ClapTrap&   operator=( const ClapTrap &c );

        void attack( const std::string& target );
        void takeDamage( unsigned int amount );
        void beRepaired( unsigned int amount );

        void print_stats() const;

        //getters
        std::string      getName() const;
        int              getHitPoints() const;
        int              getEnergyPoints() const;
        int              getAttackDamage() const;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 05:48:28 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 14:56:18 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
    public:
        ScavTrap();
        ScavTrap( const ScavTrap &s );
        ScavTrap( const std::string &name );
        ~ScavTrap();

        ScavTrap&   operator=( const ScavTrap &s );

        void guardGate();
        void attack( const std::string& target );
};

#endif

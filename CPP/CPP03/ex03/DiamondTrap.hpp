/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 07:45:43 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 08:09:26 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{
    private:
        std::string _name;
    
    public:
        DiamondTrap();
        DiamondTrap( const DiamondTrap &d );
        DiamondTrap( const std::string &name);
        ~DiamondTrap();

        DiamondTrap& operator=( const DiamondTrap &d );

        using   ScavTrap::attack;
        void    whoAmI( void );
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:24:01 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 16:03:31 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

class AAnimal
{
    protected:
        std::string type;

    public:
        virtual ~AAnimal();

        virtual AAnimal& operator=( const AAnimal &a );

        const std::string &getType() const;
        virtual void makeSound() const = 0;
};

#endif

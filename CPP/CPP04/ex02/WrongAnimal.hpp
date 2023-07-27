/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:53:02 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/07 10:56:07 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal
{
    protected:
        std::string type;

    public:
        WrongAnimal();
        WrongAnimal( const WrongAnimal &w );
        ~WrongAnimal();

        WrongAnimal& operator=( const WrongAnimal &w );

        const std::string &getType() const;
        void makeSound() const;

};

#endif

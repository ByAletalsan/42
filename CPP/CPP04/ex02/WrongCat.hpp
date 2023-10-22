/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:57:55 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 15:58:33 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"
#include "Brain.hpp"

class WrongCat : public WrongAnimal
{
    private:
        Brain *brain;

    public:
        WrongCat();
        WrongCat( const WrongCat &c );
        ~WrongCat();

        WrongCat& operator=( const WrongCat &c );

        void makeSound() const;
};

#endif

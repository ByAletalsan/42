/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:53:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 15:05:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <deque>

template< typename T, class Container = std::deque< T > >  //Establecemos el contenedor que se usa internamente
class MutantStack : public std::stack<T,Container>
{
	public:
		MutantStack( void ) {};
		MutantStack( const MutantStack& rhs ) { *this = rhs; }
		MutantStack&    operator=( const MutantStack& rhs ) {
			std::stack< T, Container >::operator=( rhs );
			return *this;
		}
		~MutantStack( void ) {};

		typedef typename Container::iterator    iterator;

		//Vamos a utilizar el contenedor interno para sacar los iteradores
		iterator    begin() { return this->c.begin(); }
		iterator    end() { return this->c.end(); }
};

#endif
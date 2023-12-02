/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:34:21 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 22:07:06 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <stdlib.h>

template <typename T>
class Array
{
	private:
		T*				data;
		unsigned int	len;

	public:
		Array() : data(new T()), len(0) {}
		Array( unsigned int n ) : data(new T[n]), len(n) {}
		Array( const Array &a ) : data(new T[a.size()]), len(a.size())
		{
			for (unsigned int i = 0; i < a.size(); i++)
			{
				this->data[i] = a.data[i];
			}
		}

		const Array &operator=( const Array &a )
		{
			if (this != &a)
			{
				delete[] this->data;
				this->len = a.size();
				this->data = new T[this->len];
				for (unsigned int i = 0; i < a.size(); i++)
				{
					this->data[i] = a.data[i];
				}
			}
			return *this;
		}

		T	&operator[]( unsigned int index )
		{
			if (index >= this->len)
				throw ArrayException();
			return this->data[index];
		}

		~Array() { delete[] this->data; }

		unsigned int	size() const { return this->len; }
	
	class ArrayException : public std::exception
	{
		public:
			const char *what() const throw() { return "Error index array"; };
	};
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:01:12 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 18:22:16 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria	*materias[4];
	public:
		MateriaSource();
		MateriaSource( const MateriaSource &m );
		~MateriaSource();
		MateriaSource &operator=( const MateriaSource &m );

		void learnMateria( AMateria* m );
		AMateria* createMateria( std::string const &type );
};

#endif

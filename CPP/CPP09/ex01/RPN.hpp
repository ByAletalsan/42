/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:55:18 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 20:11:51 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>
#include <string>

typedef struct oper
{
	std::string	op;
	int (*func)(int, int);
} t_oper;

class RPN
{
	private:
		std::stack<int>	nums;
		t_oper _oper[4];
	public:
		RPN();
		RPN( const RPN &r );
		const RPN &operator=( const RPN &r );
		~RPN();

		void	run( const std::string &numbers );
};

#endif
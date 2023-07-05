/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:39:59 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/05 04:46:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

static Fixed    ft_abs(Fixed x)
{
    if (x < 0)
        x = x * -1;
    return (x);
}

static Fixed    ft_area( Point const a, Point const b, Point const c )
{
    Fixed op1 = a.getX() * (b.getY() - c.getY());
    Fixed op2 = b.getX() * (c.getY() - a.getY());
    Fixed op3 = c.getX() * (a.getY() - b.getY());
    return ( ft_abs((op1 + op2 + op3) / 2 ));
}

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
    Fixed   areaABC = ft_area( a, b, c );
    Fixed   areaPAB = ft_area( point, a, b );
    Fixed   areaPBC = ft_area( point, b, c );
    Fixed   areaPCA = ft_area( point, c, a );

    Fixed operation = areaPAB + areaPBC + areaPCA;

    if (operation == areaABC)
        return (true);
    return (false);
}

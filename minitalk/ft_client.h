/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:03:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/31 12:53:22 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLIENT_H
# define FT_CLIENT_H
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

int	ft_printf(char const *s, ...);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

#endif
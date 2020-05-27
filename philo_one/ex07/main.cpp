/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 00:06:22 by henri             #+#    #+#             */
/*   Updated: 2020/04/06 17:18:46 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Sed.hpp"

int	main(int ac, char **av) {
	if (ac != 4)
		return (1);
	try {
		Sed::substitute(av[1], av[2], av[3]);
	} catch (const char *error) {
		std::cerr << error << std::endl;
		return (1);
	}
	return (0);
}

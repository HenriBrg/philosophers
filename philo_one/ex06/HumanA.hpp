/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:44:41 by henri             #+#    #+#             */
/*   Updated: 2020/04/05 22:07:43 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Maintenant, créez deux classes, HumanA et HumanB, qui ont toutes les
deux un Weapon, un nom et une fonction attack() qui affiche quelque
chose comme : NAME attacks with his WEAPON_TYPE
*/
#ifndef HUMAN_A_HPP
# define HUMAN_A_HPP

# include <string>
# include <iostream>
# include "Weapon.hpp"

class HumanA {
public:
	HumanA(std::string const &name, const Weapon &weapon);
	void	attack(void);
private:
	std::string	name;
	const Weapon		&weapon;
};

#endif

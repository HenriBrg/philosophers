/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:44:42 by henri             #+#    #+#             */
/*   Updated: 2020/04/05 22:55:10 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Maintenant, créez deux classes, HumanA et HumanB, qui ont toutes les
deux un Weapon, un nom et une fonction attack() qui affiche quelque
chose comme : NAME attacks with his WEAPON_TYPE
*/
#ifndef HUMAN_B_HPP
# define HUMAN_B_HPP


# include <string>
# include <iostream>
# include "Weapon.hpp"

class HumanB {
public:
	HumanB(std::string const &name);
	void setWeapon(const Weapon &weapon);
	void attack(void) const; // const pour try

private:
	std::string	name;
	const Weapon	*weapon;
	// on le déclare en pointeur car la fonction setWeapon

};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 23:03:52 by henri             #+#    #+#             */
/*   Updated: 2020/05/23 16:10:21 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HumanB.hpp"

HumanB::HumanB(std::string const &name):
	name(name), weapon(NULL) {
}


void HumanB::attack(void) const
{
	if (this->weapon)
		std::cout << this->name << " attacks with his " << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " has no weaopon " << std::endl;
}

/*
** Le fait de passer l'arme via setWeapon et non via constructeur ni directement
** fait qu'on est contraint d'utiliser un pointeur *weapon dans la classe HumanB
** Détail exemple : https://openclassrooms.com/fr/courses/1894236-programmez-avec-le-langage-c/1898260-associez-les-classes-et-les-pointeurs#/id/r-1907950
*/

void HumanB::setWeapon(const Weapon &weapon)
{
	this->weapon = &weapon;
}

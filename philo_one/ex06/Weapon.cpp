/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 22:39:23 by henri             #+#    #+#             */
/*   Updated: 2020/05/23 16:09:57 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Weapon.hpp"

Weapon::Weapon(std::string const &type): type(type) {
}

void	Weapon::setType(std::string const &type) {
	this->type = type;
}

std::string const &Weapon::getType(void) const {
	return (this->type);
}

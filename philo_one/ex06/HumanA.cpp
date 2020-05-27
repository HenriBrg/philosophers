/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 23:03:52 by henri             #+#    #+#             */
/*   Updated: 2020/05/23 16:09:17 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "HumanA.hpp"

HumanA::HumanA(std::string const &name, const Weapon &weapon):
	name(name), weapon(weapon) {

}

void HumanA::attack(void) // const here ? I would say yes because this would then unmodifiable
{
	std::cout << this->name << " attacks with his " << this->weapon.getType() << std::endl;
}

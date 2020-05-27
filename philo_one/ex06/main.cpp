/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 23:05:09 by henri             #+#    #+#             */
/*   Updated: 2020/04/05 21:46:54 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Faites en sorte que le code suivant génère des attaques avec
"crude spiked club" PUIS "some othe type of club", dans les deux cas de test :
*/

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

/*
** Const après déclaration de fonction
** Writing inside of this function will generate a compiler error
** https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
*/

/*
** Remember :
** " Use references when you can, and pointers when you have to "
** References are usually preferred over pointers whenever you
** don't need "reseating". This usually means that references are most
** useful in a class's public interface.
**
** Toujours utiliser les const, sauf si besoin de modifier
*/

/*
** Agit comme deux parties de code indépendante si {}
*/

int main(void)
{
	{
		Weapon club = Weapon("Crude Spiked Club");
		HumanA bob("Bob", club);

		bob.attack();
		club.setType("Some other type of Club");
		bob.attack();
	}
	{
		Weapon club = Weapon("Crude Spiked Club");
		HumanB jim("Jim");

		jim.setWeapon(club);
		jim.attack();
		club.setType("Some other type of Club");
		jim.attack();
	}
	return (0);
}

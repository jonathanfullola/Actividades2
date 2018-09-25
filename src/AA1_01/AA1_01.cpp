#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <iostream>
#include <sstream>
#include <map>


class Enemy
{
public:
	int vitality;
	int damages;
	int defense;
	std::string rate;
	int exp;
	std::map<std::string, std::string> weapons;
};

int main() {
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	std::map<std::string, Enemy> enemyMap;
	Enemy enemic;
	std::string enemyName, weapon;
	int distance;

	//Imprimir la información de la raíz del documento
	//std::cout << "Nombre de la raíz: " << doc.first_node()->name() << "\n";
	//std::cout << "Value: " << doc.first_node()->value() << "\n";

	//Imprimir todos los nodos con su elemento
	rapidxml::xml_node<> *pRoot = doc.first_node();

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemy"); pNode; pNode = pNode->next_sibling())
	{
		enemyName = pNode->first_node("name")->value();
		enemic.vitality = std::stoi(pNode->first_node("vitality")->value());
		enemic.damages = std::stoi(pNode->first_node("damages")->value());
		enemic.defense = std::stoi(pNode->first_node("defense")->value());
		enemic.rate = pNode->first_node("attackRate")->value();
		enemic.exp = std::stoi(pNode->first_node("exp")->value());


		for (rapidxml::xml_node<> *pNodeI = pNode->first_node("weapons")->first_node("weapon"); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			enemic.weapons[pNodeI->first_node("type")->value()] = std::stoi(pNodeI->first_node("distance")->value());
		};
		//insert enemy to enemyMap
		enemyMap[enemyName] = enemic;

		std::cout << '\n';
	}

	std::cout << "\n\n\n\n\n\n\n\n\n";

	std::cout << enemic.weapons.find("knife")->first << '\n'; //mostrar el arma knife del contenedor stl 

	system("pause");
}
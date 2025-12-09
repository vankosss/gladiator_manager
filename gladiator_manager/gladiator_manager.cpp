
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Gladiator {
private:
	std::string name;
	int max_hp;
	int hp;
	int strength;
	int evasion;
	int price;
	int lvl;
public:

	Gladiator(std::string n) {
		name = n;
		max_hp = 100;
		hp = max_hp;
		strength = 2 + rand() % 5;
		evasion = 1 + rand() % 3;

		price = 25 + (strength * 10) + (evasion * 10);
	}

	void Status() {
		std::cout << "Your gladiator " << name << ", has " << hp << " hp, " << strength << " strength, and " << evasion << " evasion!" << std::endl;
	}

	void LevelUp() {
		lvl++;
		hp += 5;
		strength += 2;
		evasion += 1;
	}

	bool IsDead() {
		if (hp <= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void TakeDamage(int damage) {
		hp -= damage;
	}

	void Heal() {
		hp = max_hp;
	}

	int GetPrice() { return price; }
	int GetStrength() { return strength; }
	int GetEvasion() { return evasion; }
	int GetHP() { return hp; }
	std::string GetName() { return name; }

};

class Shop {
private: 
	std::vector<Gladiator> gladiators_in_shop;
	std::vector<std::string> names = {
		"Andrey" , "Egor" , "Vlad" , "Pasha" , "Ivan" , "Timyr" , "Rita" , "Masha" , "Liza" , "Lera"
	};
public:
	
	void Refresh() {
		gladiators_in_shop.clear();

		for (int i = 0; i < 3; i++) {
			int index = rand() % names.size();
			std::string random_name = names[index];

			Gladiator new_gladiator_for_shop(random_name);
			gladiators_in_shop.push_back(new_gladiator_for_shop);
		}
	}

	void Show() {
		for (int i = 0; i < gladiators_in_shop.size(); i++) {
			std::cout << i + 1 << ". ";
			gladiators_in_shop[i].Status();
		}
	}

	Gladiator GetGladiator(int index) {
		return gladiators_in_shop[index];
	}
};

class Inventory {
public:

	Inventory() {
		gold = 200;
	}

	int gold;
	std::vector<Gladiator> gladiators_in_inventory;

	void Buy(Gladiator g) {
		if (gold >= g.GetPrice()) {
			gold -= g.GetPrice();
			gladiators_in_inventory.push_back(g);
			std::cout << "\nYou buy gladiator!" << std::endl;
		}
		else {
			std::cout << "\nNo money - no gladiators!" << std::endl;
		}
	}

	void Heal(int index) {
		if (index >= 0 && index < gladiators_in_inventory.size()) {
			int cost_for_heal = rand() % 50;
			if (gold >= cost_for_heal) {
				gold -= cost_for_heal;
				gladiators_in_inventory[index].Heal();
			}
			else {
				std::cout << "\nNo money - no heal!" << std::endl;
			}
		}
	}

	bool DailyTax() {
		gold -= 10;
		if (gold < 10) return false;
		else return true;
	}

	int GladiatorStrength() {
		for (int i = 0; i < gladiators_in_inventory.size(); i++) {
			int max_strength = 0;
			if (gladiators_in_inventory[i].GetStrength() > max_strength) {
				max_strength = gladiators_in_inventory[i].GetStrength();
				return max_strength;
			}
		}
	}

	Gladiator& GetFighter(int index) {
		return gladiators_in_inventory[index];
	}


	void ShowGladiators() {
		for (int i = 0; i < gladiators_in_inventory.size(); i++) {
			if (gladiators_in_inventory.empty()) {
				std::cout << "\nYou dont have no one gladiators in inventory!" << std::endl;
			}
			else gladiators_in_inventory[i].Status();
		}
	}

	void Delete_Gladiator() {
		for (int i = 0; i < gladiators_in_inventory.size(); i++) {
			if (gladiators_in_inventory[i].IsDead()) {
				gladiators_in_inventory.erase(gladiators_in_inventory.begin() + i);
				i--;
			}
		}
	}

};

class Arena {
public:
	bool Fight(Gladiator& myFighter) {
		Gladiator enemy("Enemy");
		std::cout << myFighter.GetName() << " VS " << enemy.GetName() << std::endl;
		while (!enemy.IsDead() && !myFighter.IsDead()) {
			int damageEnemy = myFighter.GetStrength();
			if (damageEnemy <= 1) damageEnemy = 1;
			enemy.TakeDamage(damageEnemy);

			std::cout << "\nYou dealt" << damageEnemy << " damage to an enemy!" << std::endl;

			if (enemy.IsDead()) {
				std::cout << "\nYou kill enemy!" << std::endl;
				return true;
		}
			int damageMyFighter = enemy.GetStrength();
			if (damageMyFighter <= 1) damageMyFighter = 1;
			myFighter.TakeDamage(damageMyFighter);

			std::cout << "\nAn enemy hit you and dealt " << damageMyFighter << " damage!" << std::endl;

			if (myFighter.IsDead()) {
				std::cout << "\nYou die from enemy!";
				return false;
			}

		}
	}
};

int main()
{
	srand(time(0));
	Gladiator gladiator ("Kristian");
	Shop shop;
	Arena arena;
	Inventory player;

	int days_left = 1;
	shop.Refresh();

	while (days_left <= 10) {
		std::cout << "\nDay " << days_left << " of 10" << std::endl;
	
		player.ShowGladiators();

		if (player.GladiatorStrength() >= 20) {
			std::cout << "\nYou win, your gladiator has 20+ power!" << std::endl;
			break;
		}

		if (player.gold >= 1000) {
			std::cout << "\nYou win, because you have 1000+ gold!" << std::endl;
			break;
		}


		int choice;
		std::cout << "\n    MENU    " << std::endl;
		std::cout << "1.Shop" << std::endl;
		std::cout << "2.Arena" << std::endl;
		std::cout << "3.Heal Gladiator" << std::endl;
		std::cout << "4.Show All Gladiator" << std::endl;
		std::cout << "5.End the day" << std::endl;
		std::cout << "Please select an action: ";
		std::cin >> choice;

		if (choice == 1) {
			int buyInd;
			shop.Show();
			std::cout << "\nYou wanna buy someone? Just write his id: ";
			std::cin >> buyInd;
			if (buyInd > 0 && buyInd <= 3) {
				player.Buy(shop.GetGladiator(buyInd - 1));
			}
		}
		else if (choice == 2) {
			if (player.gladiators_in_inventory.empty()) {
				std::cout << "You dont have gladiators!" << std::endl;
				continue;
			}
			int FightIndex;
			std::cout << "Who do you want to send to the arena: ";
			std::cin >> FightIndex;

			if (FightIndex > 0 && FightIndex <= player.gladiators_in_inventory.size()) {
				Gladiator& fighter = player.GetFighter(FightIndex - 1);

				if (fighter.IsDead()) {
					std::cout << "Your gladiator is die!" << std::endl;
				}
				else {
					bool win = arena.Fight(fighter);
					if (win) {
						fighter.LevelUp();
						player.gold += 50;
					}
					else {
						player.Delete_Gladiator();
					}
				}
			}

			
		}
		else if (choice == 3) {
			int healInd;
			std::cout << "\nWho do you wanna heal: ";
			std::cin >> healInd;
			player.Heal(healInd - 1);
		}
		else if (choice == 4) {
			player.ShowGladiators();
		}
		else if (choice == 5) {
			if (!player.DailyTax()) {
				std::cout << "\nYou lose!" << std::endl;
				break;
			}
			shop.Refresh();
			days_left++;
		}
	}

	return 0;
}

// Симулятор школы гладиаторов, суть игры - ты ланиста (владелец школы гладиаторов). Товя цель - за 10 игровых дней заработать 1000 монет или же вырастить чемпиона (гладиатора с силой > 20)
// У игрока есть стартовый капитал 200 золотых, игра поделена на дни, каждый день ты платишь налог за каждого живого гладиатора, если золото уходит в минус, то ты проиграл.
// Есть магазина, каждый день в магазине появляются 3 случайных кандидата в гладиаторы, у каждого из них свои случайные статы (здоровье, сила, ловкость) и их цена. Таким образом игрок может купить гладиатора и он попадет в казарму
// Инвентарь, место где хранятся гладиаторы, можно просмотреть список своих бойцов и их состояние [Имя, Здоровье, Сила]. За деньги можно полностью вылечить гладиатора.
// Арена, раз в день можно отправить одного своего гладиатора на арену, противник генерируется случайно (с рандомными статами), бой происходит автоматический (текстовый лог), гладиаторы бьют по очереди, урон зависит от силы атакующего и ловкости защищаеющегося (пример урон у врага 100, но у тебя 20 на уклонения, если прокнет то весь урон прошел мимо)
// Итог боя, если победил наш гладиатор, то получаем золото и гладиатор получает повышение стат, если проиграл, то он умирает и удаляется из игры.
// Победа в игре или поражение, есил набираешь 1000 золота, или прокачиваешь гладиатора до 20 силы, поражение если золото < 0 или все твои гладиаторы умерли, и денег на покупку новых нет

//Классы: Gladiator, Shop, Inventory, Arena, Result.
 
//Переменные вне главной функции и классов, я бы создал переменные количества золота и счетчик дней, а точнее сколько дней прошло, вне классов или функций
 
//Переменные внутри классов: внутри класса Gladiator, я бы создал следующие переменные, std::string name, int hp, int strong, int evasion.
//Переменные внутри классов: внутри класса Shop, я бы создал вектор который хранит 3 бойцев.
//Переменные внутри классов: внутри класса Inventory, я бы создал вектор который хранит моих бойцев.
//Переменные внутри классов: внутри класса Arena, я бы создал вектор который создает рандомного бойца хранит его и забирает моего бойца дратся.
//Переменные внутри классов: внутри класса Result, я бы использовал этот класс чтобы сделать проверки на то сколько у игрока золота и бойцов, если их меньше чем нужно то он проиграл, если нет то игра продолжается.

//Методы внутри класса Gladiator, я думаю что, для гладиатора я бы создал методы удара, и проверки, если хп > 0, то он умер, и если допустим рандомные 5% прокнут на уклонение, то весь удар пройдет мимо.
//Методы внутри класса Shop, я думаю что, для магазина, я бы создал методы покупки, проверки прошел ли день.
//Методы внутри класса Inventory, я думаю что, для инвентаря, я бы создал метод просмотра своих бойцов, и соотвественно метод хила за конкретную сумму, которая условно рандомно бы генерировалась в диапазоне до 50 монет.
//Методы внутри класса Arena, я думаю что, для арены, я бы создал генерацию рандомного бойца, метод для нанесения ударов, и проверку если боец проиграл то он удаляется.
//Методы внутри класса Result, я думаю, что для результата, я бы создал проверки, которые проверяют количество золота, бойцов и колово дней, если же золото меньше 0 и нет бойцов - то проиграл, если есть золото нет бойцов то играем дальше, если есть золото условно 500 и есть бойцы но наступил 10 день, то ты проиграл.

//Главный цикл выглядел бы у меня в виде бесконечного цикла while (days_passed < 10)
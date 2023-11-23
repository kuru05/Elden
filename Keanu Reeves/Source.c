#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>    
#include <string.h>
#include <time.h>


struct Player {
	char Name[50];
	int Health;
	float Physical_Damages;
	float Position[3];
	bool Defeated;
};

struct Boss {
	char Name[50];
	int Health;
	float Physical_Damages;
	float Position[3];
	bool Defeated;
};

// Function to simulate a basic attack
void attack(struct Player* attacker, struct Boss* defender) {
	printf("%s attacks %s!\n", attacker->Name, defender->Name);

	// Simulate some randomness in the attack
	float damage = attacker->Physical_Damages + (rand() % 10);

	// Reduce defender's health
	defender->Health -= damage;

	printf("%s takes %.2f damage. %s's health: %d\n", defender->Name, damage, defender->Name, defender->Health);

	// Check if the defender is defeated
	if (defender->Health <= 0) {
		defender->Defeated = true;
		printf("%s has been defeated!\n", defender->Name);
	}

	// Update the attacker's health
	float self_damage = defender->Physical_Damages / 2;  // Simulating counter-attack
	attacker->Health -= self_damage;

	printf("%s takes %.2f damage. %s's health: %d\n", attacker->Name, self_damage, attacker->Name, attacker->Health);

	// Check if the attacker is defeated
	if (attacker->Health <= 0) {
		attacker->Defeated = true;
		printf("%s has been defeated!\n", attacker->Name);
	}
}

// Function to handle player actions
void playerAction(struct Player* player, struct Boss* boss) {
	char action;
	printf("Choose an action:\n");
	printf("1. Attack\n");
	printf("2. Flee\n");
	printf("3. Take a potion\n");
	printf("4. Dodge\n");

	scanf(" %c", &action);

	switch (action) {
	case '1':
		attack(player, boss);
		break;
	case '2':
		printf("You fled from the battle!\n");
		player->Defeated = true;
		break;
	case '3':
		printf("You took a potion and restored some health!\n");
		player->Health += 20;  // Adjust this value based on your game mechanics
		break;
	case '4':
		printf("You dodged the boss's attack!\n");
		break;
	default:
		printf("Invalid action. Please choose a valid action.\n");
	}

	// Clear the input buffer
	while (getchar() != '\n');
}
int main(void)
{
	struct Player Sans_Eclat; {
		strcpy(Sans_Eclat.Name, "Sans Eclat");
		Sans_Eclat.Health = 100;
		Sans_Eclat.Physical_Damages = 13;
		Sans_Eclat.Position[0] = -152.34;
		Sans_Eclat.Position[1] = 5.0;
		Sans_Eclat.Position[2] = 2.0;
	};


	struct Boss Malenia; {
		strcpy(Malenia.Name, "Malenia, Epee de Miquella");
		Malenia.Health = 10000;
		Malenia.Physical_Damages = 36;
		Malenia.Position[0] = 152.34;
		Malenia.Position[1] = 6.0;
		Malenia.Position[2] = 3.0;
		Malenia.Defeated = false;
	};


	struct Boss Godrick; {
		strcpy(Godrick.Name, "Godrick, Pourfendeur de Dragons");
		Godrick.Health = 1000;
		Godrick.Physical_Damages = 43;
		Godrick.Position[0] = 192.34;
		Godrick.Position[1] = 5.2;
		Godrick.Position[2] = -3.8;
		Godrick.Defeated = false;
	};

	struct Boss Morgott; {
		strcpy(Morgott.Name, "Morgott, Rempart d'Elden");
		Morgott.Health = 2;
		Morgott.Physical_Damages = 289;
		Morgott.Position[0] = 258;
		Morgott.Position[1] = 5.21;
		Morgott.Position[2] = 4.6;
		Morgott.Defeated = false;
	};


	while (!Sans_Eclat.Defeated && !Malenia.Defeated) {
		printf("Player's Health: %d\n", Sans_Eclat.Health);
		printf("Boss's Health: %d\n", Malenia.Health);

		playerAction(&Sans_Eclat, &Malenia);

		// Check if the boss is defeated
		if (Malenia.Defeated) {
			printf("Congratulations! You defeated %s!\n", Malenia.Name);
			break;
		}

		// Boss's turn to attack
		if (!Sans_Eclat.Defeated) {
			attack(&Malenia, &Sans_Eclat);

			// Check if the player is defeated
			if (Sans_Eclat.Defeated) {
				printf("Game Over! %s has defeated you.\n", Malenia.Name);
				break;
			}
		}
	}

	return 0;
}
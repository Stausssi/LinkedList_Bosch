#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// ----- Weitere Aufgaben -----

// 1. Implementieren Sie eine Funktion in der Sie alle Eintraege sortiert ausgeben koennen. 
//    Sowohl eine Sortierung nach dem Integer-Wert, als auch nach dem char-Array-Wert (alphabetisch) muss 
//    mindestens moeglich sein.
//    Ob die Sortierfunktion die Reihenfolge Ihrer Liste aendert oder nur sortiert ausgibt, bleibt Ihnen ueberlassen.

// 2. Ergaenzen Sie Ihre Anwendung um eine Funktion, die den kompletten Inhalt aller Elemente 
//    der verketteten Liste in einer Textdatei speichert.

// 3. Ergaenzen Sie die Speicherfunktion um eine Ladefunktion, so dass bei Programmstart entweder eine neue Liste 
//    erstellt wird oder die gespeicherte Liste geladen wird.


typedef struct Person{
	struct Person *previousElement;
	struct Person *nextElement;

	char name[100];
	char position[50];
	unsigned int staffNumber;
	unsigned int age : 7;
	unsigned int sex : 2;

}Person;

bool 
delete_last_element(),
add_element(unsigned int position), delete_element(unsigned int position),
hasNextElement(Person *element), hasPreviousElement(Person *element),
firstElementDeleted, firstElementCreated;

void
fill_element(Person* element),
print_all_elements(), print_element(Person* element),
scroll_through_elements(), search_for(char keyword[]),
save_to_File(), get_from_File(),
clear_input_buffer();

Person *firstElement, *previousElement;

unsigned int elementCount;

int main(void) {
	char input[25];

	do {
		system("cls");

		printf("----------[Menu]----------\n");
		printf("Enter 'add' if you want to add another person!\n");
		printf("Enter 'add -p' if you want to add another person using a position!\n");
		printf("Enter 'delete' if you want to delete the last entry!\n");
		printf("Enter 'delete -p' if you want to delete an entry using a position!\n");
		printf("Enter 'print' if you want to print all elements!\n");
		printf("Enter 'show' to start viewing the entries!\n");
		printf("Enter 'search' to search for a keyword in all entries!\n");
		printf("Enter 'save' to save all entries to a file!\n");
		printf("Enter 'get' to retrieved saved entries from a previously saved file!\n");
		printf("Enter 'quit' if you want to end the programm!\n");

		gets_s(input, 25);

		system("cls");

		if (strncmp(input, "add", 3) == 0) {
			if (strcmp(input, "add -p") == 0) {
				printf("Enter the position you want to add the element at: ");

				unsigned int pos;
				scanf_s("%u", &pos);

				clear_input_buffer();
				if (add_element(pos))
					printf("Successfully added element at position %u!", pos);
				else
					printf("Couldn't add element at position %u!", pos);
			}

			else if (add_element(elementCount))
				printf("\nSuccessfully created new element!");
			else
				printf("New element couldn't be created.");
		}

		else if (strncmp(input, "delete", 6) == 0 && firstElementCreated) {
			if (strcmp(input, "delete -p") == 0) {
				printf("Enter the number of the element you want to delete: ");

				unsigned int pos;
				scanf_s("%u", &pos);

				clear_input_buffer();

				if (delete_element(pos)) {
					if (!firstElementDeleted)
						printf("Successfully deleted element %u!\n", pos);
					else
						printf("All elements deleted successfully");

					elementCount--;
				}
				else
					printf("The number you entered (%u) isn't a valid element!", pos);
			}
			else if (strcmp(input, "delete") == 0) {
				if (delete_last_element()) {
					if (!firstElementDeleted)
						printf("Successfully deleted last element!");
					else
						printf("All elements deleted successfully!");
					elementCount--;
				}
			}
		}

		else if (strcmp(input, "print") == 0 && firstElementCreated)
			print_all_elements();

		else if (strcmp(input, "show") == 0 && firstElementCreated)
			scroll_through_elements();

		else if (strcmp(input, "search") == 0 && firstElementCreated) {
			system("cls");

			char keyword[25];

			printf("Enter the keyword you want to search for: ");
			gets_s(keyword, 25);

			search_for(keyword);
		}

		else if (strcmp(input, "save") == 0 && firstElementCreated)
			save_to_File();

		else if (!firstElementCreated && (strcmp(input, "print") == 0 || strcmp(input, "delete") == 0 || strcmp(input, "show") == 0 || strcmp(input, "search") == 0 || strcmp(input, "save") == 0))
			printf("You need to add an entry first!");

		else if (strcmp(input, "quit") == 0)
			return 0;
		else
			printf("Invalid input!");

		printf("\n");
		system("pause");

	} while (strcmp(input, "quit") != 0);
}

void fill_element(Person *element) {
	printf("Enter the name: ");
	gets_s(element->name, 100);

	printf("Enter the position: ");
	gets_s(element->position, 50);

	printf("Enter the staff number: ");
	scanf_s("%u", &element->staffNumber);

	unsigned int tmp;

	printf("Enter the age: ");
	scanf_s("%u", &tmp);

	if (tmp > 128) {
		tmp = 128;
	}
	element->age = tmp;

	printf("Enter the sex (0 = male, 1 = female): ");
	scanf_s("%u", &tmp);

	if (tmp > 1) {
		tmp = 3;
	}
	element->sex = tmp;

	clear_input_buffer();
}

void print_all_elements() {
	Person *helpElement = firstElement;
	int count = 0;

	do {
		printf("Person %d:\n", ++count);
		print_element(helpElement);

		printf("\n");
		helpElement = helpElement->nextElement;
	} while (helpElement != NULL);
}

void print_element(Person *element) {
	printf("Name: %s\n", element->name);
	printf("Position: %s\n", element->position);
	printf("Staff number: %u\n", element->staffNumber);
	printf("Age: %u\n", element->age);

	printf("Sex: ");
	switch (element->sex) {
	case 0:
		printf("Male");
		break;
	case 1:
		printf("Female");
		break;
	default:
		printf("Invalid Input! Assuming this person is an Alien");
		break;
	}

	printf("\n");
}

void scroll_through_elements() {
	Person * helpElement = firstElement;
	char input;
	int counter = 0;

	do {
		system("cls");

		printf("Person %d\n\n", counter + 1);
		print_element(helpElement);

		printf("\nUse [a/d/q] to cycle through pages or exit!\n");
		scanf_s(" %c", &input, 1);

		clear_input_buffer();

		if (input == 'a' || input == 'A') {
			if (hasPreviousElement(helpElement)) {
				helpElement = helpElement->previousElement;
				counter--;
			}
		}
		else if (input == 'd' || input == 'D') {
			if (hasNextElement(helpElement)) {
				helpElement = helpElement->nextElement;
				counter++;
			}
		}

	} while (input != 'q' && input != 'Q');
}

void search_for(char keyword[]) {
	Person *helpElement = firstElement;

	do{
		if (strcmp(keyword, helpElement->name) == 0)
			printf("Found %s in name %s!\n", keyword, helpElement->name);

		if (strcmp(keyword, helpElement->position) == 0)
			printf("Found %s in position %s!\n", keyword, helpElement->position);
		if (hasNextElement(helpElement))
			helpElement = helpElement->nextElement;
	} while (hasNextElement(helpElement));

	printf("\nSearch finished!");
}

void save_to_File()
{  
	FILE *file = fopen("savedEntries.txt", "w");
	Person* helpElement = firstElement;

	fprintf(file, "{");

	do {
		fprintf(file, "[");

		fprintf(file, "Name: %s,", helpElement->name);
		fprintf(file, "Position: %s,", helpElement->position);
		fprintf(file, "Staff Number: %u,", helpElement->staffNumber);
		fprintf(file, "Age: %u,", helpElement->age);
		fprintf(file, "Sex: %u", helpElement->sex);

		fprintf(file, "]");

		if (hasNextElement(helpElement)) 
			fprintf(file, ",");
			
		helpElement = helpElement->nextElement;
	} while (helpElement != NULL);

	fprintf(file, "};");
	fclose(file);

	printf("Successfully saved entries to file 'savedEntries.txt'!");
}

void get_from_file() {
	FILE *file = fopen("savedEntries.txt", "r");
	Person* helpElement = firstElement;
}

void clear_input_buffer() {
	while (getchar() != '\n');
}


bool add_element(unsigned int position) {
	if (position > elementCount) {
		return false;
	}

	Person *toBeAdded = malloc(sizeof(Person));
	Person *helpElementPrevious = NULL, *helpElementNext = NULL;

	if (toBeAdded == NULL) return false;

	if (position == 0) {
		if (firstElementCreated) {
			helpElementNext = firstElement;
			helpElementNext->previousElement = toBeAdded;
		}

		firstElement = toBeAdded;
		
		firstElementCreated = true;
		firstElementDeleted = false;
	}
	else {
		helpElementPrevious = firstElement;
		unsigned int count = 0;

		while (hasNextElement(helpElementPrevious) && count++ < (position - 1)) {
			helpElementPrevious = helpElementPrevious->nextElement;
		}

		helpElementNext = helpElementPrevious->nextElement;
		helpElementPrevious->nextElement = toBeAdded;

		if (helpElementNext != NULL) {
			helpElementNext->previousElement = toBeAdded;
		}	
	}

	fill_element(toBeAdded);

	toBeAdded->previousElement = helpElementPrevious;
	toBeAdded->nextElement = helpElementNext;

	previousElement = toBeAdded;
	
	elementCount++;
}


bool delete_last_element() {
	Person *helpElement = firstElement;

	while (hasNextElement(helpElement)) {
		helpElement = helpElement->nextElement;
	}

	if (hasPreviousElement(helpElement)) {
		previousElement = helpElement->previousElement;

		free(helpElement);

		previousElement->nextElement = NULL;
		return true;
	}
	else {
		firstElementDeleted = true;
		firstElementCreated = false;

		free(firstElement);

		return true;
	}
	
	return false;
	
}

bool delete_element(unsigned int position) {
	Person *toBeDeleted = firstElement;
	Person *helpElementPrevious, *helpElementNext;

	// Computer starts counting at 0, user at 1, therefore -1
	position--;

	for (unsigned int i = 0; i < position; i++) {
		if (hasNextElement(toBeDeleted))
			toBeDeleted = toBeDeleted->nextElement;
		else
			return false;
	}

	if (hasPreviousElement(toBeDeleted)) {
		if (hasNextElement(toBeDeleted)) {
			helpElementPrevious = toBeDeleted->previousElement;
			helpElementNext = toBeDeleted->nextElement;

			helpElementPrevious->nextElement = helpElementNext;
			helpElementNext->previousElement = helpElementPrevious;
		}
		else {
			helpElementPrevious = toBeDeleted->previousElement;
			helpElementPrevious->nextElement = NULL;
		}
	}
	else if(hasNextElement(toBeDeleted)) {
		firstElement = toBeDeleted->nextElement;
		firstElement->previousElement = NULL;

	}
	else {
		firstElement = NULL;
		firstElementCreated = false;
		firstElementDeleted = true;
	}
	
	free(toBeDeleted);

	return true;
}


bool hasNextElement(Person *element) {
	if (element != NULL)
		return element->nextElement != NULL;
	else
		return false;
}

bool hasPreviousElement(Person *element) {
	if (element != NULL)
		return element->previousElement != NULL;
	else
		return false;
}
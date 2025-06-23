#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structs
struct List
{
    char name[100];        // each list contains an array with name
    struct List *nextList; // pointer to next list
    struct Item *nextItem; // pointer to next item
};

struct Item
{
    char itemName[200];    // each item contains an array with the item name
    struct Item *nextItem; // pointer to next item
};

typedef struct List Person; // synonym for struct List
typedef Person *PersonPtr;  // synonym for Person*

// Function to display the menu and get user's choice
int getMenuChoice()
{
    int choice;
    printf("\nMenu:\n");
    printf("1. Display board\n");
    printf("2. Load board from a file\n");
    printf("3. Edit list\n");
    printf("4. Edit board\n");
    printf("5. Save board to a file\n");
    printf("6. Quit\n");
    printf("Enter your choice (1-6): ");
    scanf("%d", &choice);
    getchar(); // Consume newline character from input buffer
    return choice;
}

void editBoard(PersonPtr *startPtr)
{
    int option;
    char listName[100];
    // Variables to track whether the list is found and to store the new name
    char newName[100];
    bool found = false;

    do
    {
        printf("Options:\n"
               "1. Edit the name of a list\n"
               "2. Add a new list\n"
               "3. Delete a list\n"
               "4. Return to main menu\n"
               "Enter your option: ");
        scanf("%d", &option);
        getchar(); // Consume newline character from input buffer

        switch (option)
        {
        case 1:
            printf("Enter the name of the list to edit: ");
            fgets(listName, sizeof(listName), stdin);
            strtok(listName, "\n"); // Remove newline character from the input

            if (listName[strlen(listName) - 1] != ':')
                strcat(listName, ":"); // Add ':' if it's missing

            PersonPtr currentList = *startPtr;
            while (currentList != NULL)
            {
                if (strcmp(currentList->name, listName) == 0)
                {
                    printf("List found!\n");
                    found = true;
                    break;
                }
                else
                {
                    currentList = currentList->nextList; // Move to the next list
                }
            }

            if (!found)
            {
                printf("Can't find list.\n");
                break; // Exit the switch statement
            }

            printf("Enter new name for list '%s': ", listName);
            fgets(newName, sizeof(newName), stdin);
            strtok(newName, "\n"); // Remove newline character from the input

            // Append ':' to the new name if it's not already present
            if (newName[strlen(newName) - 1] != ':')
                strcat(newName, ":");

            // Update the name of the list with the new name
            strcpy(currentList->name, newName);
            printf("List name updated successfully.\n");
            break;

        case 2:
            printf("Enter the name of the new list: ");
            fgets(newName, sizeof(newName), stdin);
            strtok(newName, "\n"); // Remove newline character from the input

            // Append ':' to the new name if it's not already present
            if (newName[strlen(newName) - 1] != ':')
                strcat(newName, ":");

            // Create a new list
            PersonPtr newList = malloc(sizeof(struct List));
            if (newList == NULL)
            {
                printf("Memory allocation failed.\n");
                break;
            }
            strcpy(newList->name, newName);
            newList->nextList = NULL;
            newList->nextItem = NULL;

            // Add the new list to the end of the lists
            if (*startPtr == NULL)    
            // Checks whether the pointer *startPtr is pointing to NULL. If it is, it means that the list is currently empty.
                *startPtr = newList;
            else
            {
                PersonPtr temp = *startPtr;
                // The while loop iterates through the list by following the nextList pointers until it reaches the end of the list. 
                while (temp->nextList != NULL)
                    temp = temp->nextList;
                temp->nextList = newList;
            }
            printf("New list added successfully.\n");
            break;
        case 3:
            printf("Enter the name of the list to delete: ");
            fgets(listName, sizeof(listName), stdin);
            strtok(listName, "\n"); // Remove newline character from the input

            // Delete the list with the specified name
            PersonPtr previous = NULL, current = *startPtr;
            while (current != NULL && strcmp(current->name, listName) != 0)
            {
                previous = current; // Updates the previous pointer to point to the node before moving current to the next node.
                current = current->nextList; // Moves current to the next node in the list.
            }
            /* 
            After the loop exits, current will either be NULL (if the specified name was not found) or 
            it will point to the node with the specified name.
            */
            if (current != NULL) // Node found
            {
                if (previous == NULL) // Indicates that the node to delete is the first node in the list
                /*
                If the node to delete is the first node, it means that the start pointer (*startPtr) should now 
                point to the second node in the list.
                */
                    *startPtr = current->nextList;
                else
                    previous->nextList = current->nextList;
                free(current);
                printf("List '%s' deleted successfully.\n", listName);
            }
            else
                printf("Can't find list.\n");
            break;
        case 4:
            printf("Returning to main menu...\n");
            break; 
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 4);
}

void editItemInList(PersonPtr *startPtr)
{
    char listName[100]; // list name entered by user
    char itemName[200]; // item name entered by user

    // display program instructions to user
    printf("Enter the name of the list to edit: ");
    fgets(listName, sizeof(listName), stdin); // Read list name from user

    // Remove newline character if present
    listName[strlen(listName) - 1] = '\0';

    // Find the list with the specified name
    PersonPtr currentList = *startPtr;
    while (currentList != NULL)
    {
        // Check if user added :
        if (listName[strlen(listName) - 1] != ':')
        {

            listName[strlen(listName)] = ':';
            // Compare modified list names without considering case sensitivity
            if (strcasecmp(currentList->name, listName) == 0)
            {
                // List found
                printf("List found!\n");
                break;
            }
        }
        else
        {
            // Compare modified list names without considering case sensitivity
            if (strcasecmp(currentList->name, listName) == 0)
            {
                // List found
                printf("List found!\n");
                break;
            }
        }

        printf("Checking list: %s\n", currentList->name);
        // Move to the next list
        currentList = currentList->nextList;
    }

    // Check if list was not found
    if (currentList == NULL)
    {
        printf("List '%s' not found.\n", listName);
        return;
    }

    printf("Options\n"
           "  1 to edit an item.\n"
           "  2 to add a new item.\n"
           "  3 to delete an item.\n"
           "  4 to return to main menu.\n");

    printf("Enter your option: ");
    unsigned int choice; // user's choice
    scanf("%u", &choice);
    getchar(); // Consume the newline character left in the input buffer

    // Loop while user does not choose 4
    while (choice != 4)
    {
        switch (choice)
        {
        case 1:
            // Edit an item
            printf("Enter the name of the item to edit: ");
            fgets(itemName, sizeof(itemName), stdin);
            strtok(itemName, "\n"); // Remove newline character from the input
            {
                struct Item *currentItem = currentList->nextItem;
                // Loop to find the item to edit
                while (currentItem != NULL)
                {
                    if (strcmp(currentItem->itemName, itemName) == 0)
                    { // Item found
                        printf("Enter new name for item '%s': ", itemName);
                        fgets(currentItem->itemName, sizeof(currentItem->itemName), stdin);
                        strtok(currentItem->itemName, "\n"); // Remove newline character from the input
                        printf("Item '%s' updated to '%s'\n", itemName, currentItem->itemName);
                    }
                    currentItem = currentItem->nextItem; // Move to the next item
                }
                
            }
            break;

        case 2:
            // Add a new item
            printf("Enter the name of the new item: ");
            fgets(itemName, sizeof(itemName), stdin);
            strtok(itemName, "\n"); // Remove newline character from the input
            {
                struct Item *newItem = malloc(sizeof(struct Item)); // Create new item
                if (newItem != NULL) // Allocation of memory successful
                {
                    strcpy(newItem->itemName, itemName); // Place itemName in node
                    newItem->nextItem = NULL;            // Node does not link to another node

                    // Insert new node at the end of the list
                    if (currentList->nextItem == NULL) // Checks if the current list has any items
                    {
                        currentList->nextItem = newItem; // New item is added directly as the first item.
                    }
                    else
                    {
                        struct Item *tempItem = currentList->nextItem; // Temporary pointer to the first item in the list
                        while (tempItem->nextItem != NULL) // goes through list until it reaches the last item
                        {
                            tempItem = tempItem->nextItem;
                        }
                        tempItem->nextItem = newItem;
                    }
                    printf("New item added successfully.\n");
                }
                else
                {
                    printf("Item not inserted. No memory available.\n");
                }
            }
            break;

        case 3:
            // Delete an item
            printf("Enter the name of the item to delete: ");
            fgets(itemName, sizeof(itemName), stdin);
            strtok(itemName, "\n"); // Remove newline character from the input
            {
                struct Item *previousItem = NULL;
                struct Item *currentItem = currentList->nextItem;

                // Loop to find the correct location in the list
                while (currentItem != NULL && strcmp(currentItem->itemName, itemName) != 0)
                {
                    previousItem = currentItem;          // update to current
                    currentItem = currentItem->nextItem; // current moves to next
                }

                // Delete node at currentItem
                if (currentItem != NULL) // found item
                {
                    if (previousItem == NULL) // item is first in list
                    {
                        currentList->nextItem = currentItem->nextItem; // skip over item to be deleted
                    }
                    else // previous item is linked to next and skips over current item to be deleted
                    {
                        previousItem->nextItem = currentItem->nextItem;
                    }
                    free(currentItem);
                    printf("Item '%s' deleted.\n", itemName);
                }
                else
                {
                    printf("Item '%s' not found.\n", itemName);
                }
            }
            break;

        case 4:
            printf("Returning to main menu...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        // Prompt for next choice
        printf("Options\n"
               "  1 to edit an item.\n"
               "  2 to add a new item.\n"
               "  3 to delete an item.\n"
               "  4 to return to main menu.\n");
        printf("Enter your option: ");
        scanf("%u", &choice);
        getchar(); // Consume the newline character left in the input buffer
    }
}

// For file displaying, loading and saving:

/// Function to create a new list
struct List *createList(const char name[]) 
{
    struct List *newList = (struct List *)malloc(sizeof(struct List));
    if (newList == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newList->name, name);
    newList->nextList = NULL; // Initialize nextList to NULL
    newList->nextItem = NULL; // Initialize nextItem to NULL
    return newList;
}

// Function to create item to a list
struct Item *createItem(char itemName[])
{
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    if (newItem == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newItem->itemName, itemName);
    newItem->nextItem = NULL;
    return newItem;
}

// Function to load the board from a file
struct List *loadBoard(const char *filename)
{
    FILE *file;
    char line[300];
    struct List *headList = NULL;
    struct List *currentList = NULL;
    struct Item *currentItem = NULL;

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename); // Print the filename
        perror("fopen");                              // Print detailed error message
        return NULL;                                  // Return NULL if file opening fails
    }
    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\r\n")] = 0; // Remove newline characters

        // Check if the line ends with ":"
        if (line[strlen(line) - 1] == ':')
        {
            // Create a new list
            struct List *newList = createList(line);
            if (headList == NULL)
            {
                headList = newList;
            }
            else
            {
                currentList->nextList = newList;
            }
            currentList = newList;
        }
        else
        {
            // Create a new item
            struct Item *newItem = createItem(line);
            if (currentList->nextItem == NULL)
            {
                currentList->nextItem = newItem;
            }
            else
            {
                currentItem->nextItem = newItem;
            }
            currentItem = newItem;
        }
    }

    // Close the file
    fclose(file);

    // Return th head of the list
    return headList;
}

// Function to create a default board
struct List *createDefaultBoard()
{
    struct List *headList = NULL;
    struct List *currentList = NULL;

    // Create lists
    headList = createList("Nick:");
    currentList = headList;
    currentList->nextItem = createItem("3070 RTX");

    currentList->nextList = createList("Tim:");
    currentList = currentList->nextList;
    currentList->nextItem = createItem("Oculus Quest 2");

    currentList->nextList = createList("Dante:");
    currentList = currentList->nextList;
    currentList->nextItem = createItem("Oculus Quest 1");
    currentList->nextItem->nextItem = createItem("3070 RTX");

    currentList->nextList = createList("Abey:");
    currentList = currentList->nextList;
    currentList->nextItem = createItem("Oculus Pro");
    currentList->nextItem->nextItem = createItem("Oculus Quest 1");

    return headList;
}

// Function to display the default board
void displayBoard(struct List *headList)
{
    struct List *tempList = headList;
    while (tempList != NULL)
    {

        char *listName = tempList->name;
        if (listName[strlen(listName) - 2] == ':')
            listName[strlen(listName) - 1] = '\0'; // Remove ':' if there are two
        
        printf("%s\n", listName);

        struct Item *tempItem = tempList->nextItem;
        while (tempItem != NULL)
        {
            printf(" %s\n", tempItem->itemName);
            tempItem = tempItem->nextItem;
        }
        tempList = tempList->nextList;
    }
}

// Function to save the board to a file
void saveBoard(struct List *headList, const char *filename)
{
    FILE *file;
    struct List *tempList = headList;
    struct Item *tempItem = NULL;

    // Open the file
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        perror("fopen");
        return;
    }

    // Loop through each list and item and write to the file
    while (tempList != NULL)
    {
        fprintf(file, "%s:\n", tempList->name);
        tempItem = tempList->nextItem;
        while (tempItem != NULL)
        {
            fprintf(file, "%s\n", tempItem->itemName);
            tempItem = tempItem->nextItem;
        }
        tempList = tempList->nextList;
    }

    // Close the file
    fclose(file);
}

// Function to free memory allocated for the board
void freeBoard(struct List *headList)
{
    struct List *tempList;
    struct Item *tempItem;

    while (headList != NULL)
    {
        tempList = headList;
        headList = headList->nextList;

        // Free items in the current list
        while (tempList->nextItem != NULL)
        {
            tempItem = tempList->nextItem;
            tempList->nextItem = tempList->nextItem->nextItem;
            free(tempItem);
        }

        free(tempList);
    }
}

void ascii();
int main()
{
    PersonPtr headList = NULL; // pointer to the first list in the board
    int choice;                // user's choice
    char filename[1000];       // name of the file to save/load the board

    // Create default board
    headList = createDefaultBoard();

    // Display the menu and get the user's choice
    do
    {
        choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            // Display board
            displayBoard(headList);
            break;
        case 2:
            // Load board from a file
            printf("Enter filename: ");
            scanf("%s", filename);
            headList = loadBoard(filename);
            if (headList == NULL)
            {
                printf("Error: could not open file %s\n", filename);
            }
            else
            {
                printf("Board loaded successfully from file.\n");
            }
            break;
        case 3:
            // Edit list
            editItemInList(&headList);
            break;
        case 4:
            // Edit board
            editBoard(&headList);
            break;
        case 5:
            // Save board to a file
            printf("Enter filename: ");
            scanf("%s", filename);
            saveBoard(headList, filename);
            printf("Board saved successfully to file.\n");
            break;
        case 6:
            // Quit
            printf("Exiting program.\n");
            ascii();
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            break;
        }
    } while (choice != 6);

    // Free memory allocated for the board
    freeBoard(headList);

    return 0;
}

void ascii () {
    printf("                               ...:----======--:..\n");
    printf("                            .:-==--::-----------===-..\n");
    printf("                         .:+=-::::::---------------==+:.\n");
    printf("                      ..-+=:::::::--------------------==-.\n");
    printf("                     .:+=---:::------------==------=======:.\n");
    printf("                    .:+===----------------=--=+++-========+-.\n");
    printf("                    .:+==------------------#-...=#=========+-.\n");
    printf("                   .:+-=-----------------=#@=...=#*=========+:.\n");
    printf("                   .+##=-----------------#@@@@@%%#+==========*..\n");
    printf("                   -##*-----------------+#@@@@@##+=+=========+=.\n");
    printf("                   =+#+-----------------*@@@@@@+++-+==========#.\n");
    printf("                 ..#**------------------*#*%%*++=-============#.\n");
    printf("                .:+---------------------+*+++==+=-+===========#.\n");
    printf("                .+--=----=---------------------===============#.\n");
    printf("                .*+=--------=+===---------------=============++.\n");
    printf("                 -+=++===++*+==+++**##*+++++++++++++*+=======*:.\n");
    printf("                 .-*==+++====================+++++==========*-. \n");
    printf("                   :++=====================================+*:. \n");
    printf("                   ..-+==================================++=+:. \n");
    printf("                     ..=+===============================+*=:=*=. \n");
    printf("                       ..=*+==========================**=--+*==*=. \n");
    printf("                   .:===++++#+*+===================*#*++++=+*++=+=.\n");
    printf("              ..=++==----=+=---==++***+++++++***##+=======+*#++++=+:\n");
    printf("          ..-+==--------+=:::----------========*=------=====+#***+=+:.\n");
    printf("        .:+=-::--------=-::::::-----------====*-:::----======+#++**+=:.\n");
    printf("  ....:++=-::---------+*=:::::::::----------=*--:::-----======**+++**=.\n");
    printf(" -+--==--------------=-:::=+:::::::::------=*---:--------======#+++++#-.\n");
    printf(" .=+===++-----------==::::::::-=++=--:::::-*=------------=====++*++++=*:.\n");
    printf("  .=+=*=-----------=+:::::::::::::-+::::::*=------------======#-#++=====.\n");
    printf(".:*+===+*#+--------+-:::::::::::::=-:::::-=---=*+------======+=:#++====*.\n");
    printf(":+-================#::::::::::::::+-:::::++-=#-=++---=======+=-:#+=====+:\n");
    printf(".:=+++++++++++++++#=+:::::::::::::+:::::-+=-====++-========*+-::*+======-\n");
    printf("          ...... .*:==::::::::::::*-:::=+--========+=--#=+*=--:-++======:\n");
    printf("                 .*:-=-::::::::::--:::-#=++===========*++**--:.#+++====+:\n");
    printf("                 .*::-=::::::::::--::::::-=++++++++++++--=+--::*+++===+*:\n");
    printf("                  =::-++====--:::=-:::::::::::-=#++==----==--::*+++++++#:       ...:--===--:..\n");
    printf("                  :=:==::::::-===#========-----+---------+*--::*++++++*#.    ..--++=-------=+=-..\n");
    printf("                  .*-+:::::::::::+-::::::::::::-+--------=*---:*++++***-.  ..-+=------------==++-.\n");
    printf("                 :++*-:::::::::::+-::::::::::::-=+=--=====++--:+++***+*:...-+=------------======+-..\n");
    printf("               .-=--+=:::::::::::+-:::::::::::--===++=+====+=+-:#**++*-. .++----------===========+-.\n");
    printf("              .==----==::::::::::+-:::::::::--====+=----------+*+*++++:.:++=======================*.\n");
    printf("             .==-::---+=:::::::::=-::::::-------==-------------=*#+++-.++==========+**+++*+=======+-\n");
    printf("             :=:::::---++-----:::=-:-----------+=---------------=#++-=++=========+*+======++======+-\n");
    printf("            .==:::::----=*=----=*+++----------+=-----------------+#*++===========*================*:\n");
    printf("            :=::::------==+#+==-----=+#=-----=*------------------=*+============**================*.\n");
    printf("           .-+---------====++*---------===+#+#=------------------=+*============+*===============*-.\n");
    printf("           .-+-----==========++**=-----------=#-----:::---------==+*=============#==============+=..\n");
    printf("            -+================+=...-+*+=====+##*-----::---------==+#==============*#+==========*=.\n");
    printf("          ..+*===============+-           ..:-==*--------------===+*===============+*#*+++++++=..\n");
    printf("         .+=-===============++                 .-+---=-------=====*#**+++++===========+++*#+..\n");
    printf("         .:=*===========+++*+.                  .=+===============++.  ...-=+*++++++**+:...\n");
    printf("          .=*+==*==++++=:..                     .-++==============+=.\n");
    printf("               :+++-..                           .-+==============++.\n");
    printf("                                                 .=+================:.\n");
    printf("                                                  -+=++===--=+++===*=.\n");
    printf("                                                        ..-=+=..  ...\n");

}

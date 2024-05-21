#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Transition: (current_state, current_symbol)|---(new_state, new_symbol, action)
struct Transition {
    char current_state[10];
    char current_symbol;
    char new_state[10];
    char new_symbol;
    char action;
};

// Turing Machine "M = (K, Σ, Γ, S, δ)"
struct TuringMachine {
    int states_number;      
    int isymbols_number;    
    char states[100][100];  /*K: number of states*/    
    char symbols[100];      /*Γ: internal symbols*/
    struct Transition transition[100][100];
};

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters in the input buffer
    }
}

// Checking the numbers that user is inserting
int getValidatedIntegerInput(const char *prompt) {
    int value;
    int num_scanned;

    while (1) {
        printf("%s", prompt);
        num_scanned = scanf("%d", &value);
        if (num_scanned == 1) {
            clearInputBuffer(); // Clear remaining characters from buffer
            return value;
        } else {
            printf("Invalid input. Please enter a valid number.\n\n");
            clearInputBuffer(); // Clear invalid input
        }
    }
}

// Function to generate binary strings incrementally
void generateBinaryString(int index, char *binaryString) {
    for (int i = 0; i <= index; i++) {
        strcat(binaryString, "1");
    }
}

// Checking the state name if valid
int isValidStateName(const char *state) {
    // Check if state name is composed of valid characters
    int len = strlen(state);
    if (len == 0) return 0;

    for (int i = 0; i < len; i++) {
        if (!isalnum(state[i])) { // Allow only alphanumeric characters
            return 0;
        }
    }

    // Check if state name is not purely numeric
    int is_numeric = 1;
    for (int i = 0; i < len; i++) {
        if (!isdigit(state[i])) {
            is_numeric = 0;
            break;
        }
    }

    return !is_numeric;
}

// Validation to check if the state exists
bool elementExistsInStates(const char *target, const char array[][100], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(target, array[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Validation to check if the symbol exists
bool elementExistsInSymbols(char target, const char array[], int size) {
    for (int i = 0; i < size; i++) {
        if (target == array[i]) {
            return true;
        }
    }
    return false;
}

// Initialize Turing Machine
void initializeTuringMachine(struct TuringMachine *turingMachine) {

    turingMachine->states_number = getValidatedIntegerInput("Specify the number of states (size of K): ");
    
    if(turingMachine->states_number > 0)
    {
        printf("\nSpecify the name of each state (e.g: q0,q1,A,...):\n");
        for (int i = 0; i < turingMachine->states_number; i++) {
        while (1) {
            printf("State %d: ", i+1);
            scanf("%s", turingMachine->states[i]);
            if (isValidStateName(turingMachine->states[i])) {
                break;
            } else {
                printf("Invalid state name. Please enter a valid state name (e.g: q0 q1 q2 ...).\n");
            }
        }
        }
    }
    

    turingMachine->isymbols_number = getValidatedIntegerInput("\nSpecify the number of symbols (size of Σ): ");

    if(turingMachine->isymbols_number > 0)
    {
        printf("\nSpecify the name of each symbol (e.g: a,2,c,...):\n");
        for (int i = 0; i < turingMachine->isymbols_number; i++) 
        {
            while (1) {
                printf("Symbol %d: ", i+1);
                scanf(" %c", &turingMachine->symbols[i]);
                if (isalnum(turingMachine->symbols[i])) {
                    break;
                } else {
                    printf("Invalid symbol. Please enter a valid symbol.\n");
                }
            }
        }
    }

    turingMachine->symbols[turingMachine->isymbols_number++] = '#'; // Adding blank symbol '#' to the symbols

    if(turingMachine->states_number > 0 && turingMachine->isymbols_number > 0)
    {
        printf("\nSpecify the transition function using this format (new_state new_symbol action):\n");
        for (int i = 0; i < turingMachine->states_number; i++) {
            for (int j = 0; j < turingMachine->isymbols_number; j++) {
                struct Transition *transition = &turingMachine->transition[i][j];
                printf("Transition of (%s , %c): ", turingMachine->states[i], turingMachine->symbols[j]);
                while (1) {
                    scanf("%s %c %c", transition->new_state, &transition->new_symbol, &transition->action);

                    // Validations
                    if (!elementExistsInStates(transition->new_state, turingMachine->states, turingMachine->states_number)) {
                        printf("This %s does not exist in the states.\n", transition->new_state);
                        printf("Transition of (%s , %c): ", turingMachine->states[i], turingMachine->symbols[j]);
                    } else if (!elementExistsInSymbols(transition->new_symbol, turingMachine->symbols, turingMachine->isymbols_number)) {
                        printf("This %c does not exist in the symbols.\n", transition->new_symbol);
                        printf("Transition of (%s , %c): ", turingMachine->states[i], turingMachine->symbols[j]);
                    } else if (transition->action != 'Y' && transition->action != 'y' &&
                               transition->action != 'N' && transition->action != 'n' &&
                               transition->action != 'L' && transition->action != 'l' &&
                               transition->action != 'R' && transition->action != 'r') {
                        printf("Invalid action. Please enter one of the following actions: (Y or y, N or n, L or l, R or r)\n");
                        printf("Transition of (%s , %c): ", turingMachine->states[i], turingMachine->symbols[j]);
                    } else {
                        break; // Break the loop if all validations pass
                    }
                }
            }
        }
    }
}

// Display Turing Machine
void displayTuringMachine(const struct TuringMachine *turingMachine) {
    printf("\nTuring Machine Information:\n");
    printf("Number of states (K): %d\n", turingMachine->states_number);
    printf("Number of symbols (Σ): %d\n", turingMachine->isymbols_number);

    printf("States (K):\n");
    for (int i = 0; i < turingMachine->states_number; i++) {
        printf("%s ", turingMachine->states[i]);
    }
    printf("\n");

    printf("Symbols (Σ):\n");
    for (int i = 0; i < turingMachine->isymbols_number; i++) {
        printf("%c ", turingMachine->symbols[i]);
    }
    printf("\n");

    printf("Transition Function (δ):\n");
    for (int i = 0; i < turingMachine->states_number; i++) {
        for (int j = 0; j < turingMachine->isymbols_number; j++) {
            const struct Transition *transition = &turingMachine->transition[i][j];
            printf("(%s , %c)|---", turingMachine->states[i], turingMachine->symbols[j]);
            printf("(%s ,%c ,%c)\n", transition->new_state, transition->new_symbol, transition->action);
        }
    }
}

// Encoding states
void encodeStates(char states[][100], int num_states, char encoded_states[][100]) {
    char binaryString[100];
    for (int i = 0; i < num_states; i++) {
        memset(binaryString, 0, sizeof(binaryString)); // Clear the binary string
        generateBinaryString(i, binaryString);
        strcpy(encoded_states[i], binaryString);
    }
}

// Encoding symbols
void encodeSymbols(char symbols[], int num_symbols, char encoded_symbols[][100]) {
    char binaryString[100];
    for (int i = 0; i < num_symbols; i++) {
        memset(binaryString, 0, sizeof(binaryString)); // Clear the binary string
        generateBinaryString(i, binaryString);
        strcpy(encoded_symbols[i], binaryString);
    }
}

// Encoding actions
void encodeActions(char actions[][100], int num_actions, char encoded_actions[][100]) {
    char binaryString[100];
    for (int i = 0; i < num_actions; i++) {
        memset(binaryString, 0, sizeof(binaryString)); // Clear the binary string
        generateBinaryString(i, binaryString);
        strcpy(encoded_actions[i], binaryString);
    }
}

// Encoding Turing Machine
void encodingTuringMachine(struct TuringMachine *turingMachine) {
    // Encode states, symbols, and actions
    char encoded_states[100][100] = {0};
    char encoded_symbols[100][100] = {0};
    char encoded_actions[100][100] = {0};

    // Encode transition
    char encoded[1000] = "";

    encodeStates(turingMachine->states, turingMachine->states_number, encoded_states);
    encodeSymbols(turingMachine->symbols, turingMachine->isymbols_number, encoded_symbols);
    encodeActions((char[][100]){"r", "l", "y", "n"}, 4, encoded_actions);  // Actions are predefined as r, l, y, n

    printf("\nEncoded States:\n");
    for (int i = 0; i < turingMachine->states_number; i++) {
        printf("State %s: %s\n", turingMachine->states[i], encoded_states[i]);
    }

    printf("Encoded Symbols:\n");
    for (int i = 0; i < turingMachine->isymbols_number; i++) {
        printf("Symbol %c: %s\n", turingMachine->symbols[i], encoded_symbols[i]);
    }

    printf("Encoded Actions:\n");
    for (int i = 0; i < 4; i++) {
        printf("Action %s: %s\n", (char *[]){"r", "l", "y", "n"}[i], encoded_actions[i]);
    }

    // Encode transitions and fill the encoded array
    for (int i = 0; i < turingMachine->states_number; i++) {
        for (int j = 0; j < turingMachine->isymbols_number; j++) {
            const struct Transition *transition = &turingMachine->transition[i][j];

            // Find indices for the current state and new state
            int current_state_index = i;
            int new_state_index = -1;
            for (int k = 0; k < turingMachine->states_number; k++) {
                if (strcmp(turingMachine->states[k], transition->new_state) == 0) {
                    new_state_index = k;
                    break;
                }
            }

            // Find indices for the current symbol and new symbol
            int current_symbol_index = j;
            int new_symbol_index = -1;
            for (int k = 0; k < turingMachine->isymbols_number; k++) {
                if (turingMachine->symbols[k] == transition->new_symbol) {
                    new_symbol_index = k;
                    break;
                }
            }

            // Find index for the action
            int action_index = strchr("rlyn", transition->action) - "rlyn";

            // Add encoded transition to the result string
            strcat(encoded, encoded_states[current_state_index]);
            strcat(encoded, "0");
            strcat(encoded, encoded_symbols[current_symbol_index]);
            strcat(encoded, "0");
            strcat(encoded, encoded_states[new_state_index]);
            strcat(encoded, "0");
            strcat(encoded, encoded_symbols[new_symbol_index]);
            strcat(encoded, "0");
            strcat(encoded, encoded_actions[action_index]);
            strcat(encoded, "00");
        }
    }
    encoded[strlen(encoded) - 2] = '\0';  // Remove the trailing "00"

    // Print the encoded string after each transition is added
    printf("Encoded Turing Machine Transitions: %s\n", encoded);
}

// Operating Turing Machine
void operateTuringMachine(struct TuringMachine *turingMachine) {
    char input_sequence[1000];
    int head_index = 0;
    int current_state_index = 0;
    char tape[1000];
    char temp[1000];

    printf("\nPlease provide the input sequence: ");
    scanf("%s", input_sequence);

    printf("\nPlease indicate the index of the tape head (starting from 1): ");
    scanf("%d", &head_index);

    head_index--; // Adjust to zero-based indexing

    strcpy(tape, "<"); // '<' indicator of the start of the tape
    strcat(tape, input_sequence);
    printf("Input Tape: %s\n", tape); // Tape after adding '<' at the beginning then adding the input symbols

    printf("\nExecution Steps:\n\n");
    while (1) {
        // Construct the temp string with brackets around the current symbol
        strncpy(temp, tape + 1, head_index); // Copy the part before the head
        temp[head_index] = '\0'; // Null-terminate
        sprintf(temp + head_index, "(%c)%s", tape[head_index + 1], tape + head_index + 2);

        printf("Current state: %s  Tape: %s\n", turingMachine->states[current_state_index], temp);

        char current_symbol = tape[head_index + 1];
        int symbol_index = -1;
        for (int i = 0; i < turingMachine->isymbols_number; i++) {
            if (current_symbol == turingMachine->symbols[i]) {
                symbol_index = i;
                break;
            }
        }
        if (symbol_index == -1) {
            printf("This Symbol (%c) doesn't exist in the supported alphabets.\n", current_symbol);
            break;
        }

        struct Transition t = turingMachine->transition[current_state_index][symbol_index];
        tape[head_index + 1] = t.new_symbol;

        // Switch case for actions
        switch (t.action) {
            case 'l':
            case 'L':
                head_index--; // Repositioning to the left symbol
                break;
            case 'r':
            case 'R':
                head_index++; // Repositioning to the right symbol
                if (head_index + 1 == strlen(tape)) {
                    strcat(tape, "#"); // Adding blank if reached to the end of the sequence
                }
                break;
            case 'y':
            case 'Y':
                // Accepted
                strncpy(temp, tape + 1, head_index); // Copy the part before the head
                temp[head_index] = '\0'; // Null-terminate
                sprintf(temp + head_index, "(%c)%s", tape[head_index + 1], tape + head_index + 2);
                printf("This sequence is accepted.\n");
                printf("Final Tape: %s\n", temp);
                return; // Exit the function
            case 'n':
            case 'N':
                // Rejected
                strncpy(temp, tape + 1, head_index); // Copy the part before the head
                temp[head_index] = '\0'; // Null-terminate
                sprintf(temp + head_index, "(%c)%s", tape[head_index + 1], tape + head_index + 2);
                printf("This sequence is rejected.\n");
                printf("Final Tape: %s\n", temp);
                return; // Exit the function
            default:
                printf("Invalid action encountered: %c\n", t.action);
                return; // Exit the function
        }

        // Updating the current state index
        int found = 0;
        for (int i = 0; i < turingMachine->states_number; i++) {
            if (!strcmp(t.new_state, turingMachine->states[i])) {
                current_state_index = i;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Invalid state transition to state: %s\n", t.new_state);
            break;
        }

        // Handling the head range
        if (head_index >= 1000 || head_index < 0) {
            printf("Tape head has moved out of the valid range of the tape.\n");
            break;
        }

        // Handling the current state index range
        if (current_state_index >= turingMachine->states_number || current_state_index < 0) {
            printf("Invalid state index.\n");
            break;
        }
    }
    printf("Final Tape: %s\n", temp);
}

int main() {
    printf("***********Welcome to the Turing Machine***********\n");
    printf("Turing Machine Formula (M):\n");
    printf("    M = (K, Σ, Γ, S, δ)\n");
    printf("K: a finite set of states\n");
    printf("Σ: an alphabet(input symbols)\n");
    printf("Γ: an alphabet(store symbols, machine symbols, internal symbols)\n");
    printf("S: an initial state\n");
    printf("δ: the transition function\n");
    printf("**************************************************\n");

    struct TuringMachine turingMachine;         // Creating Turing Machine

    initializeTuringMachine(&turingMachine);    // Initializing Turing Machine

    displayTuringMachine(&turingMachine);       // Displaying Turing Machine

    encodingTuringMachine(&turingMachine);      // Encoding Turing Machine

    operateTuringMachine(&turingMachine);       // Operating Turing Machine

    return 0;
}
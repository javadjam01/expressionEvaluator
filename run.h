#pragma once

// ANSI codes
const string CLEAR = "\033[2J\033[1;1H";
const string RESET = "\033[0m"; // reset text format to default
const string GREEN = "\033[32m";
const string BRED = "\033[91m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[95m";
const string GRAY = "\033[90m";

void displayPostfix(string p) {
    cout << CYAN << "       =========================" << RESET << endl;
    cout << CYAN << "        PostFix = " << p << RESET << endl;
    cout << CYAN << "       =========================" << RESET << endl;
}

void displayResult(float result) {
    cout << CYAN << "       =========================" << RESET << endl;
    cout << CYAN << "        Result  = " << result << RESET << endl;
    cout << CYAN << "       =========================" << RESET << endl;
}

void Input() {
    cout << BRED << "       =========================" << RESET << endl;
    cout << BRED << "               Calculator" << RESET << endl;
    cout << BRED << "       =========================" << RESET << endl;
    cout << GRAY << "        (type \"exit\" for exit)\n" << RESET << endl;
    cout << "        Infix = " << RESET;
}

void run() {
    string expression;

    while (true) {
        cout << CLEAR;
        Input();
        cin >> expression;

        if (expression == "exit") {
            cout << BRED << CLEAR << "\n\n\n            Closing ..... \n\n\n" << RESET << endl;
            break;
        }
        else {
            string postfix = infixToPostfix(expression);
            displayPostfix(postfix);
            float result = calc(postfix);
            displayResult(result);
            cout << GRAY << "\n       Press any key to continue... " << RESET;
            cin.ignore(); // Clear input buffer
            cin.get();    // Wait for a char, including Enter
        }
    }
}
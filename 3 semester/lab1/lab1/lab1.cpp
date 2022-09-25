#include <iostream>
#include <fstream>
#include <istream>
#include <stdlib.h>
#include <string>

using namespace std;

struct rule {
    string Left;
    string Right;
    rule* next;
    void init_def() {
        Left = "";
        Right = "";
        next = NULL;
    }
    rule() { init_def(); }
};

struct expression {
    string name;
    string value;
    expression* next;
    void init_def() {
        name = "";
        value = "";
        next = NULL;
    }
    expression() { init_def(); }
};

struct File {
    string A;//Alphabet
    string X;//Alphabet of variables
    string line;//condition
    rule* RULE;//Header
    void initDefault() {
        RULE = NULL;
        A = "";
        X = "";
        line = "";
        ReadFromFile();
    }

    void    ReadFromFile();
    int     CheckCompability(char c);
    int     FindThePos(int from, char c);
    bool    Decide(expression* x_val1, expression* x_val2);
    void    MainLoop();
};




int main() {
    File Program;
    Program.MainLoop();
    system("pause");
    return 0;
}

void File::ReadFromFile() {
    ifstream file("post.txt");
    string contents;                                    //Header
    string field;                                       //Field of Header

    if (file.fail()) {
        cout << "Error open file...";
        exit(0);
    }
    do {
        getline(file, contents);
        if (contents == "A:") {                           //Alphabet of constants
            getline(file, field);
            for (int i = 0; i < static_cast<int>(field.length()); i++) {
                A.push_back(field[i]);
            }
        }
        else if (contents == "A1:") {                        //expression
            getline(file, field);
            line = field;
            cout << line << endl;

        }
        else if (contents == "X:") {                           //variables
            getline(file, field);
            for (int i = 0; i < static_cast<int>(field.length()); i++) {
                X.push_back(field[i]);
            }
        }
        else if (contents == "R:") {                             //Rule
            getline(file, field);
            if (RULE == NULL)
                RULE = new rule;
            else {
                rule* tRule = RULE;
                while (tRule->next != NULL)
                    tRule = tRule->next;
                tRule = new rule;
            }
            bool change = false;

            for (int i = 0; i < static_cast<int>(field.length()); i++)
            {
                if (field[i] == '>') {
                    change = true;
                    continue;
                }

                if (change == false)
                    RULE->Left.push_back(field[i]);
                else if (change == true)
                    RULE->Right.push_back(field[i]);
            }
            continue;

        }
    } while (!file.eof());
}

int File::CheckCompability(char c) {
    for (int i = 0; i < A.length(); i++)
        if (A[i] == c)
            return 0;
    for (int i = 0; i < X.length(); i++)
        if (X[i] == c)
            return 1;
    return -1;
}

int File::FindThePos(int from, char c) {
    for (int i = from; i < line.length(); i++)
        if (c == line[i])
            return i;
    return -1;
}

bool File::Decide(expression* x_val1, expression* x_val2) {
    bool isDefined = true;
    // xx/yy - xx/yy
    if (x_val1->name.length() == 2) {
        // xx -> x; yy -> y
        if (x_val1->name[0] == x_val1->name[1]) {
            x_val1->name = x_val1->name.erase(0);
            if (x_val1->value.length() % 2 == 0 && x_val1->value.length() > 0)
                x_val1->value = x_val1->value.substr(x_val1->value.length() / 2 - 1, x_val1->value.length() / 2);
            else
                isDefined = false;
        }
    }
    else if (x_val2->name.length() == 2) {
        if (x_val2->name[0] == x_val2->name[1]) {
            x_val2->name = x_val2->name.erase(0);
            if (x_val2->value.length() % 2 == 0 && x_val2->value.length() > 0)
                x_val2->value = x_val2->value.substr(x_val2->value.length() / 2 - 1, x_val2->value.length() / 2);
            else
                isDefined = false;
        }
    }

    // x/y - ??
    if (x_val1->name.length() == 1) {
        // x/y - x/y
        if (x_val1->name.length() == x_val2->name.length()) {
            if (x_val1->name == x_val2->name)
                if (x_val1->value != x_val2->value)
                    isDefined = false;
        }
        // x/y - xy/yx
        else {
            // x/y - xy
            if (x_val2->name[0] == x_val1->name[0]) {
                x_val2->name.erase(0);
                x_val2->value = x_val2->value.substr(0, x_val1->value.length() - 1);
            }
            // x/y - yx
            else {
                x_val2->name.erase(1);
                x_val2->value = x_val2->value.substr(x_val2->value.length() - x_val1->value.length() - 1, x_val2->value.length() - 1);
            }
        }
    }
    // xy/yx - ??
    else {
        if (x_val2->name.length() == 2) {
            if (x_val1->name[0] == x_val2->name[1] && x_val1->name[1] == x_val2->name[0] && x_val1->value != x_val2->value)
                isDefined = false;
        }
        // xy - x
        else if (x_val1->name[0] == x_val2->name[0]) {
            x_val1->name.erase(0);
            x_val1->value = x_val1->value.substr(x_val2->value.length(), x_val2->value.length() - 1);
        }
        // yx - x
        else if (x_val1->value >= x_val2->value) {

            string S = x_val1->value.substr(x_val1->value.length() - x_val2->value.length(), x_val2->value.length());
            if (S == x_val2->value) {
                x_val1->name.erase(1);
                x_val1->value = x_val1->value.substr(0, x_val1->value.length() - x_val2->value.length());
            }
            else
                isDefined = false;
        }
        else
            isDefined = false;
    }
    return isDefined;
}
void File::MainLoop() {
    rule ForInit;
    expression ForInitExp;
    ForInitExp.init_def();
    ForInit.init_def();
    initDefault();
    bool End = false;
    string lastL = "";
    while (!End) {
        rule* tempR = RULE;

        while (tempR != NULL) {
            int curPos = 0;
            expression* E = NULL;
            expression* tmpE = E;
            // Filling expression
            for (int i = 0; i < RULE->Left.length(); i++) {
                switch (CheckCompability(RULE->Left[i])) {
                    // A
                case 0:
                    if (i != 0 && CheckCompability(RULE->Left[i - 1]) == 1) {
                        int endPos = FindThePos(curPos, RULE->Left[i]);
                        if (endPos != -1) {
                            tmpE->value = line.substr(curPos, endPos - curPos);
                            curPos = endPos + 1;
                        }
                        else {
                            cerr << "Программа завершена." << endl;
                            exit(1);
                        }
                    }
                    else {
                        curPos = FindThePos(curPos, RULE->Left[i]);
                    }
                    break;
                    // X
                case 1:
                    if (i != 0 && CheckCompability(RULE->Left[i - 1]) == 1)
                        tmpE->name += RULE->Left[i];
                    else {
                        // Creating Structure
                        if (E == NULL) {
                            E = new expression;
                            tmpE = E;
                            E->name += RULE->Left[i];
                        }
                        else {
                            tmpE->next = new expression;
                            tmpE->next->name += RULE->Left[i];
                            tmpE = tmpE->next;
                        }
                    }
                    break;
                    // Error
                case -1:
                    cerr << "Unknown Error." << endl;
                    exit(-1);
                    break;
                default:
                    break;
                }
                if (curPos == -1) {
                    cout << "No rule." << endl;
                    exit(-1);
                    break;
                }
            }

            tmpE = E;

            while (tmpE != NULL) {
                expression* tmpE2 = E;
                while (tmpE2 != NULL) {
                    if (!Decide(tmpE, tmpE2)) {
                        cout << "Completed.";
                        End = true;
                        exit(0);
                    }
                    tmpE2 = tmpE2->next;
                }
                tmpE = tmpE->next;
            }

            cout << line << " -> ";

            string lRuleStr = "", rRuleStr = "";

            //lRuleStr
            for (int i = 0; i < RULE->Left.length(); i++) {
                tmpE = E;
                if (CheckCompability(RULE->Left[i]))
                    while (tmpE != NULL) {
                        if (tmpE->name[0] == RULE->Left[i])
                            lRuleStr += tmpE->value;
                        tmpE = tmpE->next;
                    }
                else
                    lRuleStr += RULE->Left[i];
            }
            //rRuleStr
            for (int i = 0; i < RULE->Right.length(); i++) {
                tmpE = E;
                if (CheckCompability(RULE->Right[i]))
                    while (tmpE != NULL) {
                        if (tmpE->name[0] == RULE->Right[i])
                            rRuleStr += tmpE->value;
                        tmpE = tmpE->next;
                    }
                else
                    rRuleStr += RULE->Right[i];
            }
            bool isFound = false;
            int insertPos = 0;
            for (int i = 0; i < (line.length() - lRuleStr.length()); i++) {
                for (int j = 0; j < lRuleStr.length(); j++) {
                    if (lRuleStr[j] != line[j]) {
                        isFound = false;
                        break;
                    }
                    else {
                        if (!isFound)
                            insertPos = i;
                        isFound = true;
                        continue;
                    }
                }
                if (isFound)
                    break;
            }

            line.replace(insertPos, lRuleStr.length(), rRuleStr);
            cout << line << endl;
            if (lastL == line) {
                cout << "Программа завершена т. к. рез-тат бесконечен." << endl;
                End = true;
                break;
            }
            lastL = line;
            // to the next rule
            tempR = tempR->next;
        }
    }
}
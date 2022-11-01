#include "postmachine.h"

int main()
{
    PostMachine postMachine;
    postMachine.readTape();
    postMachine.readInputFile("input.txt");

    string result = postMachine.start();
    cout << result;
    return 0;
}

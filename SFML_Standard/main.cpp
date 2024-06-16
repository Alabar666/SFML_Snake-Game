#include "snake.hpp"

int main()
{
    srand(time(NULL));
    Snake* snake = new Snake();
    snake->run_game();
    delete snake;
    snake = nullptr;
    return EXIT_SUCCESS;
}

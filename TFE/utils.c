void display_title(void){
    printf("$$\\      $$\\                     $$\\           $$$$$$$\\  $$$$$$$\\  \n");
    printf("$$$\\    $$$ |                    \\__|          $$  __$$\\ $$  __$$\\ \n");
    printf("$$$$\\  $$$$ | $$$$$$\\ $$\\    $$\\ $$\\  $$$$$$\\  $$ |  $$ |$$ |  $$ |\n");
    printf("$$\\$$\\$$ $$ |$$  __$$\\$$\\  $$  |$$ |$$  __$$\\ $$ |  $$ |$$$$$$$\\ |\n");
    printf("$$ \\$$$  $$ |$$ /  $$ |\\$$\\$$  / $$ |$$$$$$$$ |$$ |  $$ |$$  __$$\\ \n");
    printf("$$ |\\$  /$$ |$$ |  $$ | \\$$$  /  $$ |$$   ____|$$ |  $$ |$$ |  $$ |\n");
    printf("$$ | \\_/ $$ |\\$$$$$$  |  \\$  /   $$ |\\$$$$$$$\\ $$$$$$$  |$$$$$$$  |\n");
    printf("\\__|     \\__| \\______/    \\_/    \\__| \\_______|\\_______/ \\_______/ \n");
}

void display_description(void){
    printf("This program is a simple movie database that allows you to add, remove, and display movies.\n");
    printf("You can also add, remove, and display genres.\n");
    printf("The program will also allow you to search for movies by genre.\n");
}

void exit_program(void){
    system("clear");
    printf("Goodbye!\n");
    printf("Made by: %s\n", style_text("Augustin Mauroy", GREEN));
    exit(EXIT_SUCCESS);
}

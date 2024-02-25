/*
? Regular Colors

| Value    | Color  |
| -------- | ------ |
| \e[0;30m | Black  |
| \e[0;31m | Red    |
| \e[0;32m | Green  |
| \e[0;33m | Yellow |
| \e[0;34m | Blue   |
| \e[0;35m | Purple |
| \e[0;36m | Cyan   |
| \e[0;37m | White  |

? Bold

| Value    | Color  |
| -------- | ------ |
| \e[1;30m | Black  |
| \e[1;31m | Red    |
| \e[1;32m | Green  |
| \e[1;33m | Yellow |
| \e[1;34m | Blue   |
| \e[1;35m | Purple |
| \e[1;36m | Cyan   |
| \e[1;37m | White  |

? Underline

| Value    | Color  |
| -------- | ------ |
| \e[4;30m | Black  |
| \e[4;31m | Red    |
| \e[4;32m | Green  |
| \e[4;33m | Yellow |
| \e[4;34m | Blue   |
| \e[4;35m | Purple |
| \e[4;36m | Cyan   |
| \e[4;37m | White  |

? Background

| Value  | Color  |
| ------ | ------ |
| \e[40m | Black  |
| \e[41m | Red    |
| \e[42m | Green  |
| \e[43m | Yellow |
| \e[44m | Blue   |
| \e[45m | Purple |
| \e[46m | Cyan   |
| \e[47m | White  |

? High Intensty

| Value    | Color  |
| -------- | ------ |
| \e[0;90m | Black  |
| \e[0;91m | Red    |
| \e[0;92m | Green  |
| \e[0;93m | Yellow |
| \e[0;94m | Blue   |
| \e[0;95m | Purple |
| \e[0;96m | Cyan   |
| \e[0;97m | White  |

? Bold High Intensty

| Value    | Color  |
| -------- | ------ |
| \e[1;90m | Black  |
| \e[1;91m | Red    |
| \e[1;92m | Green  |
| \e[1;93m | Yellow |
| \e[1;94m | Blue   |
| \e[1;95m | Purple |
| \e[1;96m | Cyan   |
| \e[1;97m | White  |

? High Intensty backgrounds

| Value     | Color  |
| --------- | ------ |
| \e[0;100m | Black  |
| \e[0;101m | Red    |
| \e[0;102m | Green  |
| \e[0;103m | Yellow |
| \e[0;104m | Blue   |
| \e[0;105m | Purple |
| \e[0;106m | Cyan   |
| \e[0;107m | White  |

? Reset

| Value |    Color    |
| ----- | ----------- |
| \e[0m | Reset       |
| \e[0m | CRESET      |
| \e[0m | COLOR_RESET |
*/

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

/*
?   EXAMPLE CODE:-
*	printf(BRED "Hey this is the color red, and it's bold! \n" reset);
*	printf(RED "If" BLU "you" YEL "are" GRN "bored" CYN "do" MAG "this! \n" reset); 
*	printf(BRED "If" BBLU "you" BYEL "are" BGRN "bored" BCYN "do" BMAG "this! \n" reset); 
*	printf(URED "If" UBLU "you" UYEL "are" UGRN "bored" UCYN "do" UMAG "this! \n" reset);
*/

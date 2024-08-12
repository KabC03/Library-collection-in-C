#12 Aug

library="./polynomial map.c"


mkdir -p output
clear && clang "$library" ./main.c -Wall -Werror -fsanitize=address -o ./output/exec && ./output/exec












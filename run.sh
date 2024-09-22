#12 Aug

library="./lib/arbitrary length.c"


mkdir -p output
clear && clang "$library" ./lib/vector.c ./lib/main.c -Wall -Werror -fsanitize=address -o ./output/exec && ./output/exec












#12 Aug

library="./lib/bitmap.c"


mkdir -p output
clear && clang "$library" ./lib/vector.c ./lib/main.c -Wall -Werror -fsanitize=address -o ./output/exec && ./output/exec 

#xxd ./output/reconstructed.wav > ./data/reconstructed.txt
#xxd ./data/tone.wav > ./data/input.txt    
#diff ./data/input.txt ./data/reconstructed.txt > ./data/differences.txt








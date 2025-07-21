#27 Mar

library="./lib/*.c"


mkdir -p output
clear && clang $library -Wall -Werror -fsanitize=address -O0 -o ./output/exec
echo "Compiled"
./output/exec 

#xxd ./output/reconstructed.wav > ./data/reconstructed.txt
#xxd ./data/tone.wav > ./data/input.txt    
#diff ./data/input.txt ./data/reconstructed.txt > ./data/differences.txt








#
#	SLS Copyright (C) 2022 SolindekDev
#	GNU General Public License
#

COMPILER_CPP = clang++ # Deafult clang++ but you can set g++

all: c add_to_bin

c: # Compile file and create an executable of it
	mkdir -p ./dist
	clang++ -O3 -Wextra -std=c++20 -I./ sls.cpp -o ./dist/sls

add_to_bin: # Add file in to bin folder
	sudo cp ./dist/sls /bin

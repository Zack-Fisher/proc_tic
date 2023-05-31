#!/bin/env ruby
def compile
    command = "gcc -o tic " + " main.c -lSDL2"
    system(command)
end

`rm tic`
compile
sleep 0.1
system("./tic")

all:
	emcc -I src -c wrapper.c -o wrapper.o
	emcc -I src -c src/game_aux.c -o src/game_aux.o
	emcc -I src -c src/game.c -o src/game.o
	emcc -I src -c src/game_ext.c -o src/game_ext.o
	emcc -I src -c src/game_private.c -o src/game_private.o
	emcc -I src -c src/queue.c -o src/queue.o
	emcc -I src -c src/game_tools.c -o src/game_tools.o
	emar rcs libgame.a src/game_aux.o src/game.o src/game_ext.o src/game_private.o src/queue.o src/game_tools.o
	emcc wrapper.o libgame.a -o game.js -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap

clean:
	rm -f *.o src/*.o libgame.a game.js game.wasm
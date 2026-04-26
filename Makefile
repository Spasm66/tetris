all:
	emcc -I src -c wrapper.c -o wrapper.o
	emcc -I src -c src/piece.c -o src/piece.o
	emcc -I src -c src/tetris.c -o src/tetris.o
	emar rcs libgame.a src/piece.o src/tetris.o
	emcc wrapper.o libgame.a -o game.js \
		-s ALLOW_MEMORY_GROWTH=1 \
		-s EXPORTED_RUNTIME_METHODS=ccall,cwrap

clean:
	rm -f *.o src/*.o libgame.a game.js game.wasm
Module.onRuntimeInitialized = () => {
    ModuleReady = true;
    start();
}

function draw_tetris(canvas, g, width, height) {
    const ctx = canvas.getContext("2d");
    ctx.fillStyle = "#7DE886";
    ctx.fillRect(0, height*30, width*30, 50);
    ctx.clearRect(0, 0, width*30, height*30);
    for (let j = 0; j < height; j++) {
        for (let i = 0; i < width; i++) {
            switch (Module._get(g, i, j)) {
                case 2:
                    ctx.fillStyle = "#E87DDF";
                    ctx.fillRect(i*30, j*30, 30, 30); 
                    break;
                case 1:
                    ctx.fillStyle = "#7DAAE8";
                    ctx.fillRect(i*30, j*30, 30, 30); 
                    break;
                default:
                    break;
            }
        }
    }
}

function game_over(canvas) {
    const ctx = canvas.getContext("2d");
    ctx.fillStyle = "white";
    ctx.font = "30px Arial";
    ctx.textAlign = "center";
    ctx.fillText("Game Over", canvas.width / 2, canvas.height / 2);
    document.addEventListener("keydown", (e) => {
        if (e.code === "Space")
            start();
    });
}

function falling(speed, canvas, g, state, width, height) {
    var loop = setTimeout(() => {
        if (!Module._next(g, state.p)) {
            draw_tetris(canvas, g, width, height); 
            Module._destroy_piece(state.p)
            state.p = Module._new_random_piece(Math.floor(Math.random() * 7));
            Module._update_piece(g, state.p)
            if (Module._hitting_floor(g, state.p) || Module._collapse_floor_wall(g, state.p)) {
                console.log("stop");
                state.stop();
                game_over(canvas);
                return;
            }
            else {
                speed = Math.max(150, speed - 50);
                console.log(speed);
                falling(speed, canvas, g, state, width, height);
            }
        }
        else {
            Module._update_piece(g, state.p)
            draw_tetris(canvas, g, width, height);
            falling(speed, canvas, g, state, width, height);
        }
        
    }, speed);
}

function input_fetch(e, g, state) {
    switch (e.key) {
        case "ArrowUp":
            Module._turn(g, state.p);
            break;
        case "ArrowDown":
            if (Module._hitting_floor(g, state.p)) {
                state.p = Module._new_random_piece(Math.floor(Math.random() * 7));
                Module._update_piece(g, state.p);
            } else {
                Module._next(g, state.p);
            }
            break;
        case "ArrowRight":
            Module._right(g, state.p);
            break;
        case "ArrowLeft":
            Module._left(g, state.p);
            break;
        default:
            break;
    }
}

function start() {
    var width = 15;
    var height = 20;
    var canvas = document.getElementById("game");
    canvas.width = width*30;
    canvas.height = height*30 + 50;
    var g = Module._new_tetris(width, height);
    var state = {p: Module._new_random_piece(Math.floor(Math.random() * 7))};

    const keyHandler = (e) => {
        if (state.p != null) {
            input_fetch(e, g, state);
            draw_tetris(canvas, g, width, height);
        }
    };

    state.stop = () => {
        document.removeEventListener("keydown", keyHandler);
    };

    Module._update_piece(g, state.p);
    draw_tetris(canvas, g, width, height);
    document.addEventListener("keydown", keyHandler);
    falling(800, canvas, g, state, width, height);
}
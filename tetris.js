Module.onRuntimeInitialized = () => {
    ModuleReady = true;
    start();
}

function draw_tetris(canvas, g, width, height) {
    const ctx = canvas.getContext("2d");
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

function tetris_score(canvas, g, del_row, width, height) {
    var equ = [40, 100, 300, 1200];
    var level = Module._get_level(g);
    var pts = (level + 1) * equ[del_row - 1];

    const ctx = canvas.getContext("2d");
    ctx.fillStyle = "white";
    ctx.font = "20px Arial";
    ctx.textAlign = "left";
    ctx.fillText("+" + String(pts), 20, canvas.height - 20);
    setTimeout(() => {
        ctx.fillStyle = "#7DE886";
        ctx.fillRect(0, height*30, 100, 50);
    },1500);
    Module._set_score(g, Module._get_score(g) + pts);
}

function update_score(canvas, g, width, height) {
    const ctx = canvas.getContext("2d");
    ctx.fillStyle = "#7DE886";
    ctx.fillRect((width*30) / 2, height*30, 100, 50);
    ctx.fillStyle = "white";
    ctx.font = "20px Arial";
    ctx.textAlign = "left";
    ctx.fillText(String(Module._get_score(g)), (width/2) * 30, height*30 + 30);
}

function falling(speed, canvas, g, state, width, height) {
    var loop = setTimeout(() => {
        if (Module._hitting_floor(g, state.p)){
            Module._update_piece(g, state.p);   
            var del_row = Module._fossilize(g, state.p);
            if (del_row){
                console.log("score");
                tetris_score(canvas, g, del_row, width, height);
                update_score(canvas, g, width, height);
            }
            state.p = Module._new_random_piece(Math.floor(Math.random() * 7));
            Module._update_piece(g, state.p)
            draw_tetris(canvas, g, width, height);
            if (Module._hitting_floor(g, state.p)) {
                console.log("stopi");
                state.stop();
            }
            else {
                if (speed > 300)
                        speed -= 50
                else if (speed > 200) {
                    speed -= 5
                }
                else if (speed > 150){
                    speed -= 2;
                }
                console.log(speed);
                falling(speed, canvas, g, state, width, height);
            }
        }
        else {
            Module._next(state.p);
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
            if (!Module._hitting_floor(g, state.p))
                Module._next(state.p);
            break;
        case "ArrowRight":
            if (!Module._hitting_at_right(g, state.p)) {
                Module._right(state.p);
            }
            break;
        case "ArrowLeft":
            if (!Module._hitting_at_left(g, state.p))
                Module._left(state.p);
            break;
        default:
            break;
    }
}

function start() {
    var width = 10;
    var height = 20;
    var canvas = document.getElementById("game");
    canvas.width = width*30;
    canvas.height = height*30 + 50;
    const ctx = canvas.getContext("2d");
    ctx.fillStyle = "#7DE886";
    ctx.fillRect(0, height*30, width*30, 50);
    var g = Module._new_tetris(width, height);
    update_score(canvas, g, width, height);
    var state = {p: Module._new_random_piece(Math.floor(Math.random() * 7))};
    Module._update_piece(g, state.p);
    draw_tetris(canvas, g, width, height);
    const keyHandler = (e) => {
        if (state.p != null) {
            input_fetch(e, g, state);
            Module._update_piece(g, state.p);
            draw_tetris(canvas, g, width, height);
        }
    };
    state.stop = () => {
        document.removeEventListener("keydown", keyHandler);
        game_over(canvas);
    };
    document.addEventListener("keydown", keyHandler);
    falling(800, canvas, g, state, width, height);
}
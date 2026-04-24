Module.onRuntimeInitialized = () => {
    ModuleReady = true;
    start();
}
function draw_tetris(canvas, g, width, height) {
    const ctx = canvas.getContext("2d");
    for (let j = 0; j < height; j++) {
        for (let i = 0; i < width; i++) {
            console.log(Module._get(g, i, j));
            switch (Module._get(g, i, j)) {
                case 2:
                    ctx.fillStyle = "red";
                    ctx.fillRect(i*30, j*30, 30, 30); 
                    break;
                case 1:
                    ctx.fillStyle = "black";
                    ctx.fillRect(i*30, j*30, 30, 30); 
                    break;
                case 0:
                    ctx.fillStyle = "green";
                    ctx.fillRect(i*30, j*30, 30, 30); 
                    break;
                default:
                    break;
            }
        }
    }
}


function start() {
    var width = 10;
    var height = 20;
    var canvas = document.getElementById("game");
    var g = Module._new_tetris(width, height);
    var p = Module._new_random_piece();
    Module._update_piece(g, p)
    draw_tetris(canvas, g, width, height);    
    setInterval(() => {
        if (!Module._next(g, p)) { 
            p = Module._new_random_piece();
        }
        Module._update_piece(g, p)
        draw_tetris(canvas, g, width, height);
    }, 1000);
        
    //Module._delete(g);
}

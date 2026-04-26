// demo.js

Module.onRuntimeInitialized = () => { 
    ModuleReady = true;
    if (loadedImage ==3) start(); }

const EMPTY = 0;    // empty square 
const TREE = 1;     // tree square 
const TENT = 2;     // tent square 
const GRASS = 3;    // grass square 
const BIGTREE = 4;  // big tree square 

let _square2str = [" ", "x", "*", "-", "#"];

function square2str(s) {
    return _square2str[s];
}

/*function printGame(g) {
    var text = "";
    var nb_rows = Module._nb_rows(g);
    var nb_cols = Module._nb_cols(g);
    for (var row = 0; row < nb_rows; row++) {
        for (var col = 0; col < nb_cols; col++) {
            var s = Module._get_square(g, row, col);
            text += square2str(s);
        }
        text += "\n";
    }

    // put this text in <div> element with ID 'result'
    var elm = document.getElementById('result');
    elm.innerHTML = text;
}*/

// load  image
var Tree = new Image() ;
var Tent = new Image() ;
var Tent_win = new Image() ;
var Grass = new Image() ;

Tree.onload = onAssertloaded;
Tent.onload = onAssertloaded;
Tent_win.onload = onAssertloaded;
Grass.onload = onAssertloaded;
   
Tree.src = "images/tree.png";
Tent.src = "images/tent.png";
Tent_win.src = "images/tent_win.png";
Grass.src = "images/grass.png";

var loadedImage = 0;
var ModuleReady = false;

function onAssertloaded(){
    loadedImage++;
    if (loadedImage == 4 && ModuleReady)  start();
}

function windowLoad() {
    console.log("image load");
    start();
}

function drawGame(g){
    var canvas = document.getElementById("mycanvas");
    var ctx = canvas.getContext("2d");

    var rows = Module._nb_rows(g);
    var cols = Module._nb_cols(g);

    var margin = 30;
    var cellSize =Math.min((canvas.width - margin)/cols, (canvas.height - margin)/rows) ;


    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    ctx.font = " 14px Arial";
    ctx.textAlign = "centre";
    ctx.textBaseline = "middle";


    for (var i= 0; i< rows; i++) {
        for (var j = 0; j < cols; j++) {
            var s = Module._get_square(g,i, j);

            var x = j*cellSize;
            var y = i *cellSize;
            
            if (s==1) {
                ctx.drawImage(Tree,x,y,cellSize,cellSize);
            }
            else if (s==2){
                if (!Module._won(g))
                    ctx.drawImage(Tent,x,y,cellSize,cellSize);
                else
                    ctx.drawImage(Tent_win,x,y,cellSize,cellSize);
            }
            else if (s==3) {
                ctx.drawImage(Grass,x,y,cellSize,cellSize);
            
            }
            //grille
            ctx.strokeRect(x,y,cellSize,cellSize)
        }
    }

    ctx.fillStyle = "black";
    for (var i = 0 ; i<rows; i++){
        var nb = Module._get_expected_nb_tents_row(g,i);
        var y = i*cellSize + cellSize /2 ;
        ctx.fillText(nb,cols*cellSize+ margin/2,y);
    }
    for (var j = 0 ; j<cols; j++){
        var nb = Module._get_expected_nb_tents_col(g,j);
        var x = j*cellSize + cellSize /2 ;
        ctx.fillText(nb,x,rows*cellSize+margin/2);
    }

}


function play(g, e) {
    const canvas = document.getElementById("mycanvas");
    const margin = 30;
    const rows = Module._nb_rows(g);
    const cols = Module._nb_cols(g);
    const cellSize = Math.min((canvas.width - margin) / cols, (canvas.height - margin) / rows);

    const col = Math.floor(e.offsetX / cellSize);
    const row = Math.floor(e.offsetY / cellSize);

    if (col >= cols || row >= rows) return; // clic hors grille

    if (Module._get_square(g, row, col) == EMPTY || Module._get_square(g, row, col) == GRASS)
        Module._play_move(g, row, col, TENT);
    else if (Module._get_square(g, row, col) == TENT)
        Module._play_move(g, row, col, EMPTY);
}

function solveGame() {
    var canvas = document.getElementById("mycanvas");
    var g = parseInt(canvas.dataset.game);
    Module._restart(g);
    Module._solve_web(g);
    drawGame(g);
}

function redoMove() {
    var canvas = document.getElementById("mycanvas");
    var g = parseInt(canvas.dataset.game);
    Module._redo(g);
    drawGame(g);
}

function toggleGameMenu() {
    document.getElementById("gameMenu").classList.toggle("open");
}

function toggleTypeMenu() {
    document.getElementById("typeMenu").classList.toggle("open");
}

function loadType(x, y) {
    var canvas = document.getElementById("mycanvas");
    var g = Module._new_random(x, y, false, 12, 0, false);
    canvas.dataset.game = g;
    drawGame(g);
}

function undoMove() {
    var canvas = document.getElementById("mycanvas");
    var g = parseInt(canvas.dataset.game);
    Module._undo(g);
    drawGame(g);
}



function restartGame(g) {
    var canvas = document.getElementById("mycanvas");
    var g = parseInt(canvas.dataset.game);
    Module._restart(g);
    drawGame(g);

}

function Resize() {
    const canvas = document.getElementById("mycanvas");
    const handle = document.getElementById("resizeHandle");

    let resizing = false;
    let startX, startY, startWidth, startHeight;

    handle.addEventListener('mousedown', (e) => {
        resizing = true;
        startX = e.clientX;
        startY = e.clientY;
        startWidth = canvas.width;
        startHeight = canvas.height;
    });

    document.addEventListener('mousemove', (e) => {
        if (!resizing) return;
        canvas.width = startWidth + (e.clientX - startX);
        canvas.height = startHeight + (e.clientY - startY);
        var g = parseInt(canvas.dataset.game);
        drawGame(g);
    });

    document.addEventListener('mouseup', () => {
        resizing = false;
    });
}

function start() {
    Resize();
    var canvas = document.getElementById("mycanvas");
    var g = Module._new_default();
    canvas.dataset.game = g;
    drawGame(g);
    canvas.addEventListener('click', (e) => {
        g = parseInt(canvas.dataset.game);
        play(g, e);
        drawGame(g);
    });
    //Module._delete(g);
}

/*function start() {
    console.log("call start routine");
    var g = Module._new_default();
    Module._play_move(g, 1, 0, TENT);
    printGame(g);
    Module._delete(g);
}

function start() {
    console.log("call start routine");
    var g = Module._new_random(5,5,0,5,0,1);
    Module._solve(g);
    printGame(g);
    Module._delete(g);
}*/



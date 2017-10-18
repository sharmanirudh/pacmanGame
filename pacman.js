MAT_MAX = 10;
function findPath(matrix, visited, currentpos, pacmanpos, pathToPacman, size) {
    var flag = 0;
    var i, j;
    // console.log(visited);
    // console.log(currentpos);
    visited[currentpos.x][currentpos.y] = 1;
    // console.log(visited);
    pathToPacman[size] = currentpos;
    size++;

    if(matrix[currentpos.x][currentpos.y] === 0 || currentpos.x < 0 || currentpos.x >= MAT_MAX || currentpos.y < 0 || currentpos.y >= MAT_MAX)
        return 0;

    if(currentpos.x === pacmanpos.x && currentpos.y ===  pacmanpos.y)
        return 1;

    var l = 0, r = 0, d = 0, u = 0;
    if(flag === 0 && currentpos.x >= 0 && currentpos.x < MAT_MAX && currentpos.y + 1 >= 0 && currentpos.y + 1 < MAT_MAX && matrix[currentpos.x][currentpos.y + 1] === 1 && visited[currentpos.x][currentpos.y + 1] === 0)
    {
        var newpos1 = {x: currentpos.x, y: currentpos.y + 1};
        if((r = findPath(matrix, visited, newpos1, pacmanpos, pathToPacman, size)) === 0)
            size--;
    }
    if(flag === 0 && currentpos.x + 1 >= 0 && currentpos.x + 1 < MAT_MAX && currentpos.y >= 0 && currentpos.y < MAT_MAX && matrix[currentpos.x + 1][currentpos.y] === 1 && visited[currentpos.x + 1][currentpos.y] === 0)
    {
        var newpos2 = {x: currentpos.x + 1, y: currentpos.y};
        if((d = findPath(matrix, visited, newpos2, pacmanpos, pathToPacman, size)) === 0)
            size--;
    }
    if(flag === 0 && currentpos.x - 1 >= 0 && currentpos.x - 1 < MAT_MAX && currentpos.y >= 0 && currentpos.y < MAT_MAX && matrix[currentpos.x - 1][currentpos.y] === 1 && visited[currentpos.x - 1][currentpos.y] === 0)
    {
        var newpos3 = {x: currentpos.x - 1, y: currentpos.y};
        if((u = findPath(matrix, visited, newpos3, pacmanpos, pathToPacman, size)) === 0)
            size--;
    }
    if(flag === 0 && currentpos.x >= 0 && currentpos.x < MAT_MAX && currentpos.y - 1 >= 0 && currentpos.y - 1 < MAT_MAX && matrix[currentpos.x][currentpos.y - 1] === 1 && visited[currentpos.x][currentpos.y - 1] === 0)
    {
        var newpos4 = {x: currentpos.x, y: currentpos.y - 1};
        if((l = findPath(matrix, visited, newpos4, pacmanpos, pathToPacman, size)) === 0)
            size--;
    }
    return(l || r || d || u);
}

function moveGhost(matrix, matrixOriginal, currentpos, pacmanpos) {
    var visited=[[0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0]];
    var pathToPacman = [];
    var size = 0;
    findPath(matrixOriginal, visited, currentpos, pacmanpos, pathToPacman, size);

    matrix[pathToPacman[0].x][pathToPacman[0].y] = 0;
    matrix[pathToPacman[1].x][pathToPacman[1].y] = 5;
    currentpos.x = pathToPacman[1].x;
    currentpos.y = pathToPacman[1].y;
    return currentpos;
}

function movePacman(matrixOriginal, pacmanpos, ghostCurrentpos) {
    var matrix=[[0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0]], i, j;
    var str = "";
    var b = document.getElementsByTagName("body")[0];
    number = setInterval(function() {
        ghostCurrentpos = moveGhost(matrix, matrixOriginal, ghostCurrentpos, pacmanpos);
        var map = {}; // You could also use an array
        onkeydown = onkeyup = function(event) {
            event = event || event; // to deal with IE
            map[event.keyCode] = event.type == 'keydown';
            /* insert conditional here */
            if (map[37] == true || map[38] == true || map[39] == true || map[40] == true) {
                if (map[38] == true) {
                    if (pacmanpos.x - 1 >= 0 && pacmanpos.x - 1 < MAT_MAX && pacmanpos.y >= 0 && pacmanpos.y < MAT_MAX) {
                        matrix[pacmanpos.x][pacmanpos.y] = 0;
                        matrix[--pacmanpos.x][pacmanpos.y] = 1;
                    }
                }
                if (map[37] == true) {
                    if (pacmanpos.x >= 0 && pacmanpos.x < MAT_MAX && pacmanpos.y - 1 >= 0 && pacmanpos.y - 1 < MAT_MAX) {
                        matrix[pacmanpos.x][pacmanpos.y] = 0;
                        matrix[pacmanpos.x][--pacmanpos.y] = 1;
                    }
                }
                if (map[40] == true) {
                    if (pacmanpos.x + 1 >= 0 && pacmanpos.x + 1 < MAT_MAX && pacmanpos.y >= 0 && pacmanpos.y < MAT_MAX) {
                        matrix[pacmanpos.x][pacmanpos.y] = 0;
                        matrix[++pacmanpos.x][pacmanpos.y] = 1;
                    }
                }
                if (map[39] == true) {
                    if (pacmanpos.x >= 0 && pacmanpos.x < MAT_MAX && pacmanpos.y + 1 >= 0 && pacmanpos.y + 1 < MAT_MAX) {
                        matrix[pacmanpos.x][pacmanpos.y] = 0;
                        matrix[pacmanpos.x][++pacmanpos.y] = 1;
                    }
                }
            }
        };
        b.innerHTML = "";
        str = "";
        for(var i = 0; i < MAT_MAX; i++)
        {
            for(var j = 0; j < MAT_MAX; j++) {
                str = str + matrix[i][j].toString() + " ";
            }
            // str = str + "\n";
            str = str + "<br>";
        }
        b.innerHTML = str;
        // console.log(str);
        // console.log("\n\n");
    }, 100);
}

function main() {
    console.log("\n\n");
    var matrix=[[1,1,1,1,1,0,0,1,0,0],
                [0,1,0,0,1,1,1,1,0,0],
                [0,1,0,0,0,0,0,0,0,0],
                [0,1,0,0,0,0,0,0,0,0],
                [0,1,0,0,1,1,1,0,0,0],
                [0,1,1,1,1,1,1,0,0,0],
                [0,0,1,1,1,0,0,0,0,0],
                [0,0,0,0,1,1,1,1,0,0],
                [0,0,0,0,0,0,1,1,0,0],
                [0,0,0,0,0,0,1,1,1,1]], i, j;

    var visited=[[0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0]];
    var pathToPacman = [];

    /*for(i = 0; i < MAT_MAX; i++)
    {
        for(j = 0; j < MAT_MAX; j++)
            console.log(matrix[i][j], " ");
        console.log("\n");
    }*/
    var ghostCurrentpos = {x: 0, y: 0};
    var pacmanpos = {x: 9, y: 9};
    var size = 0;
    //findPath(matrix, visited, ghostCurrentpos, pacmanpos, pathToPacman, size);
    // console.log(size, "\n");
    // for(i = 0; i < size; i++)
    //     console.log("(", pathToPacman[i].x, ", ", pathToPacman[i].y, "), ");

    movePacman(matrix, pacmanpos, ghostCurrentpos);
    return 0;
}
main();
document.addEventListener("DOMContentLoaded", function () {
  const gridSize = 9;
  const solveButton = document.getElementById("solve-btn");
  solveButton.addEventListener("click", solveSudoku);

  const sudokuGrid = document.getElementById("sudoku-grid");
  // create the sudoku grid and input cells

  for (let row = 0; row < gridSize; ++row) {
    const newRow = document.createElement("tr");
    for (let col = 0; col < gridSize; ++col) {
      const cell = document.createElement("td");
      const input = document.createElement("input");
      input.type = "number";
      input.className = "cell";
      input.id = `cell-${row}-${col}`;
      cell.appendChild(input);
      newRow.appendChild(cell);
    }
    sudokuGrid.appendChild(newRow);
  }
});

async function solveSudoku() {
  const gridSize = 9;
  const sudokuArr = [];

  // fill sudokuArr with input values from grid
  for (let row = 0; row < gridSize; ++row) {
    sudokuArr[row] = [];
    for (let col = 0; col < gridSize; ++col) {
      const cellId = `cell-${row}-${col}`;
      const cellValue = document.getElementById(cellId).value;
      sudokuArr[row][col] = cellValue !== "" ? parseInt(cellValue) : 0;
    }
  }

  // mark user-input cells
  for (let row = 0; row < gridSize; ++row) {
    for (let col = 0; col < gridSize; col++) {
      const cellId = `cell-${row}-${col}`;
      const cell = document.getElementById(cellId);

      if (sudokuArr[row][col] !== 0) {
        cell.classList.add("user-input");
      }
    }
  }

  // solve the puzzle and display solution
  if (solveSudokuHelper(sudokuArr)) {
    for (let row = 0; row < gridSize; ++row) {
      for (let col = 0; col < gridSize; col++) {
        const cellId = `cell-${row}-${col}`;
        const cell = document.getElementById(cellId);

        // fill in solved values -- show animation
        if (!cell.classList.contains("user-input")) {
          cell.value = sudokuArr[row][col];
          cell.classList.add("solved");
          await sleep(20);
        }
      }
    }
  } else {
    alert("No solution exists for the given Sudoku puzzle.");
  }
}

function solveSudokuHelper(board) {
  const gridSize = 9;
  for (let row = 0; row < gridSize; ++row) {
    for (let col = 0; col < gridSize; col++) {
      if (board[row][col] === 0) {
        for (let num = 1; num <= 9; ++num) {
          if (isValidMove(board, row, col, num)) {
            board[row][col] = num;

            // use recursion to solve the rest
            if (solveSudokuHelper(board)) {
              return true;
            }

            board[row][col] = 0;
          }
        }

        return false;
      }
    }
  }

  // all cells filled
  return true;
}

function isValidMove(board, row, col, num) {
  const gridSize = 9;
  // check conflicts
  for (let i = 0; i < gridSize; ++i) {
    if (board[row][i] === num || board[i][col] === num) {
      return false;
    }
  }

  // check 3x3 subgrid for conflicts
  const startRow = Math.floor(row / 3) * 3;
  const startCol = Math.floor(col / 3) * 3;

  for (let i = startRow; i < startRow + 3; ++i) {
    for (let j = startCol; j < startCol + 3; ++j) {
      if (board[i][j] === num) {
        return false;
      }
    }
  }

  // no conflicts
  return true;
}

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

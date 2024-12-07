#include <stdio.h>
#include <string.h>

#define MAX_SIZE 150


int main() {
    char grid[MAX_SIZE][MAX_SIZE+1];
    int i = 0;
    char line[MAX_SIZE+2];

    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        strcpy(grid[i++], line);
    }
    int rows = i;
    int cols = strlen(grid[0]);

    int start_row = -1, start_col = -1, start_dir = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '^') {
                start_col = i;
                start_row = j;
                break;
            }
        }
        if (start_col >= 0) break;
    }

    int count = 0;

    // Iterate over each cell to place a temporary obstruction
    for (int obstruct_y = 0; obstruct_y < rows; obstruct_y++) {
        for (int obstruct_x = 0; obstruct_x < cols; obstruct_x++) {
            if (grid[obstruct_y][obstruct_x] != '.' || 
                (obstruct_x == start_row && obstruct_y == start_col)) {
                continue;
            }

            grid[obstruct_y][obstruct_x] = '#';

            int pos_x = start_row;
            int pos_y = start_col;
            int dir = start_dir;
            unsigned char visited[MAX_SIZE][MAX_SIZE];
            memset(visited, 0, sizeof(visited));
            int loop_detected = 0;

            while (1) {
                if (visited[pos_y][pos_x] & (1 << dir)) {
                    loop_detected = 1;
                    break;
                }
                visited[pos_y][pos_x] |= (1 << dir);

                int front_x = pos_x;
                int front_y = pos_y;
                switch(dir) {
                    case 0: front_y = pos_y - 1; break; // up
                    case 1: front_x = pos_x + 1; break; // right
                    case 2: front_y = pos_y + 1; break; // down
                    case 3: front_x = pos_x - 1; break; // left
                }
                if (front_x < 0 || front_x >= cols || front_y < 0 || front_y >= rows) {
                    break;
                }
                if (grid[front_y][front_x] == '#') {
                    dir = (dir + 1) % 4;
                } else {
                    pos_x = front_x;
                    pos_y = front_y;
                }
            }

            if (loop_detected) {
                count++;
            }
            grid[obstruct_y][obstruct_x] = '.';
        }
    }
    
    printf("%d\n", count);

    return 0;
}
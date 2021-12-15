#include <stdio.h>
#include <stdlib.h>
#define FILEB "board.txt"
#define FILET "tiles.txt"

typedef struct{
    char row, column;
    int rowValue, columnValue;
    int inserted;
} tile_s;

typedef struct 
{
    int r,c;
    tile_s ***tiles;
} board_s;


void handleFileInputs(char *fileBoard, char *fileTiles, board_s *board, board_s *solution, board_s *temp, tile_s **tilesVec, int *dim);

int calculatePoints(board_s *board, tile_s *tiles, int *dim);

void rotateTile(tile_s *tile);

void printBoard(board_s *board);

int findSolution(board_s *board, board_s *solution, board_s *temp, tile_s *tiles, int dim);

int findSolutionRec(board_s *board, board_s *solution, int max, board_s *temp, tile_s *tiles, int dim);

int main(){
    board_s board, solution, temp;
    tile_s *tiles;
    int dim, max;

    handleFileInputs(FILEB, FILET, &board, &solution, &temp, &tiles, &dim);
    printBoard(&board);
    max=findSolution(&board, &solution, &temp, tiles, dim);
    printf("\n %d \n", max);
    printBoard(&solution);
}

void rotateTile(tile_s *tile){
    char tempChar;
    int tempInt;

    tempChar=tile->column;
    tile->column=tile->row;
    tile->row=tempChar;

    tempInt=tile->columnValue;
    tile->columnValue=tile->rowValue;
    tile->rowValue=tempInt;
}

int findSolutionRec(board_s *board, board_s *solution, int max, board_s *temp, tile_s *tiles, int dim){
    int i,j, tileInsertedIndex, end, result, r, c, valid;

    end=1;
    valid=0;
    result=0;

    for(i=0; i<board->r ; i++)
        for(j=0; j<board->c; j++)
            if(temp->tiles[i][j]==NULL){
                r=i;
                c=j;
                valid=1;
            }



    for(i=0; i<dim;i++){
        if(tiles[i].inserted==0 && valid){
            tiles[i].inserted=1;

            temp->tiles[r][c]=&(tiles[i]);
            result=findSolutionRec(board, solution, max, temp, tiles, dim);
            temp->tiles[r][c]=NULL;
            if(result>max)
                max=result;
            tiles[i].inserted=0;
            end=0;
        }
        if(tiles[i].inserted==0 && valid){
            tiles[i].inserted=1;
            rotateTile(&tiles[i]);
            temp->tiles[r][c]=&(tiles[i]);
            result=findSolutionRec(board, solution, max, temp, tiles, dim);
            temp->tiles[r][c]=NULL;
            if(result>max)
                max=result;
            tiles[i].inserted=0;
            end=0;
            rotateTile(&tiles[i]);
        }
    }

    if(end==1)
        result=calculatePoints(temp, tiles, &dim);
    if(end==1 && result>max){
        max=result;
        for(i=0; i<board->r; i++){
            for(j=0; j<board->c; j++){
                solution->tiles[i][j]=temp->tiles[i][j];
            }
        }
    }

    return(max);
}

int findSolution(board_s *board, board_s *solution, board_s *temp, tile_s *tiles, int dim){
    int max, i, j;

    for(i=0; i<board->r; i++){
        for(j=0; j<board->c; j++){
            temp->tiles[i][j]=board->tiles[i][j];
        }
    }
    
    max=0;
    return (findSolutionRec(board, solution, max, temp, tiles, dim));
}

void printBoard(board_s *board){
    int i, j;

    for(i=0; i<board->r; i++){
        for(j=0; j<board->c; j++){
            if(board->tiles[i][j]!=NULL)
            printf("%c%d/%c%d ", board->tiles[i][j]->row, board->tiles[i][j]->rowValue, board->tiles[i][j]->column, board->tiles[i][j]->columnValue);
            else
            printf(" -1/-1  ");
        }
        printf("\n");
    }

}

int calculatePoints(board_s *board, tile_s *tiles, int *dim){
    int i,j, sumParz, tot, valid;
    char temp;

    tot=0;

    for(i=0; i<board->r; i++){
        sumParz=0;
        valid=1;
        temp=board->tiles[i][0]->row;
        for(j=0; j<board->c; j++){
            sumParz+=board->tiles[i][j]->rowValue;
            if(board->tiles[i][j]->row!=temp)
                valid=0;
        }
        if(valid)
            tot+=sumParz;
    }

    for(i=0; i<board->c; i++){
        sumParz=0;
        valid=1;
        temp=board->tiles[0][i]->column;
        for(j=0; j<board->r; j++){
            sumParz+=board->tiles[j][i]->columnValue;
            if(board->tiles[j][i]->column!=temp)
                valid=0;
        }
        if(valid)
            tot+=sumParz;
    }

    return tot;
}

void handleFileInputs(char *fileBoard, char *fileTiles, board_s *board, board_s *solution, board_s *temp, tile_s **tilesVec, int *dim){
    FILE *fp_board, *fp_tiles;
    int i, j, indexTile, rotate;
    tile_s *tiles;


    fp_board=fopen(fileBoard, "r");
    fp_tiles=fopen(fileTiles, "r");

    if(fp_board!=NULL)
    fscanf(fp_board, "%d%d", &(board->r), &(board->c));
    if(fp_tiles!=NULL)
    fscanf(fp_tiles, "%d ", dim);

    *tilesVec=malloc(sizeof(tile_s)*(*dim));
    tiles=*tilesVec;
    temp->r=board->r;
    temp->c=board->c;
    solution->r=board->r;
    solution->c=board->c;
    board->tiles=malloc(board->r*sizeof(tile_s**));
    temp->tiles=malloc(board->r*sizeof(tile_s**));
    solution->tiles=malloc(board->r*sizeof(tile_s**));

    for(i=0; i<board->r; i++){
        board->tiles[i]=malloc(board->c*sizeof(tile_s*));
        temp->tiles[i]=malloc(board->c*sizeof(tile_s*));
        solution->tiles[i]=malloc(board->c*sizeof(tile_s*));
    }

    for(i=0; i<*dim; i++){
        fscanf(fp_tiles, "%c %d %c %d ", &(tiles[i].row), &tiles[i].rowValue, &tiles[i].column, &tiles[i].columnValue);
        tiles[i].inserted=0;
    }

    for(i=0; i<board->r; i++){
        for(j=0; j<board->c; j++){
            board->tiles[i][j]=NULL;
            fscanf(fp_board, "%d/%d", &indexTile, &rotate);

            if(indexTile!=-1 && rotate==0){
                board->tiles[i][j]=&tiles[indexTile];
                tiles[indexTile].inserted=1;
            }
            if(indexTile!=-1 && rotate==1){
                rotateTile(&tiles[indexTile]);
                board->tiles[i][j]=&tiles[indexTile];
                tiles[indexTile].inserted=1;
            }
        }
    }
}
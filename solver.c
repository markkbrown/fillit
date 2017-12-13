/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:06:39 by mbrown            #+#    #+#             */
/*   Updated: 2017/12/13 00:59:51 by mbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int		tet_count = 8;
int		pos = 0;

char	*boardgen(int size, char *board)
{
	int		iter;
	int		line;
	char	*newboard;
	
	if (board)
		free(board);
	newboard = malloc(sizeof(newboard) * (size * size) + (size));
	iter = 0;
	line = 0;
	while (iter < (size * size) + size)
	{
		if (iter == size || iter == (line * size) + size + line)
		{
			line++;
			newboard[iter++] = '\n';
		}
		else
			newboard[iter++] = '.';
	}
	newboard[iter] = '\0';
	return (newboard);
}

int		check(int *tet, int startpos, char *board, int tetnum)
{
	int i;
	int	*temp;

	temp = malloc(sizeof(temp) * 4);
	for (int k = 0; k < 4; k++)
		temp[k] = tet[k];
	i = -1;
	while (++i < strlen(board))
	{
		if (board[i] == tetnum + 'A')
			return (0);
	}
	i = -1;
	while (++i < 4)
	{
		if (temp[i] >= 4)
			temp[i] = temp[i] + temp[i] / 4;
	}
	i = 0;
	if (board[temp[0] + startpos] == '.' && board[temp[1] + startpos] == '.')
	{
		if (board[temp[2] + startpos] == '.' && board[temp[3] + startpos] == '.')
		{
			while (i < 4)
				board[temp[i++] + startpos] = tetnum + 'A';
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}
//
//int		combination(int *pieces, int tet_count)
//{
//	int 	iter1;
//	int		iter2;
//	int		temp;
//
//	iter1 = 0;
//	iter2 = 0;
//	while (iter1 <= tet_count)
//	{
//		iter2 = 0;
//		while (iter2 < tet_count - 1)
//		{
//			temp = pieces[iter2];
//			pieces[iter2] = pieces[iter2 + 1];
//			pieces[iter2 + 1] = temp;
//			iter2++;
//			if (check())
//		}
//		iter1++;
//	}
//	return (0);
//}

void	boardreset(char *board, int size)
{
	int iter;
	int line;

	line = 0;
	iter = 0;
	while (iter < (size * size) + size)
	{
		if (iter == size || iter == (line * size) + size + line)
		{
			line++;
			board[iter++] = '\n';
		}
		else
			board[iter++] = '.';
	}
	board[iter] = '\0';
}

int		backtrack(int pieces[4][4], int startpos, char *board, int tetnum, int placed, int size)
{
	if (placed == 4)
		return (1);
	if (!board[startpos + 1])
	{
		boardreset(board, 4);
		return(backtrack(pieces, 0, board, 4, 0, 4));
	}
	if (tetnum == 4)
		backtrack(pieces, startpos + 1, board, 0, placed, 4);
	if (tetnum < 4)
	{
		if (check(pieces[tetnum], startpos, board, tetnum))
			return (backtrack(pieces, 0, board, tetnum, placed + 1, 4));
		else
			return (backtrack(pieces, startpos, board, tetnum + 1, placed, 4));
	}
	return (0);
}

int main(void)
{
	int		i;
	int		j;
	int		numpieces;
	char	*board;
	int		tetnums[tet_count];
//	int		pieces[8][4] = {{0,4,8,12},
//							{0,1,2,3},
//							{0,1,2,6},
//							{2,3,6,5},
//							{0,1,4,5},
//							{0,1,5,6},
//							{0,1,5,9},
//							{0,1,2,5}};
	int		pieces[4][4] = {{0,1,5,9},
							{0,1,5,6},
							{0,4,5,6},
							{0,1,2,3}};
	//int		pieces[2][4] = {{0,4,8,12},
	//							{0,1,4,5}};
	//i = 0;
	//j = 0;
	//while (++j <= tet_count)
	//	tetnums[i++] = j;
	//combination(tetnums, tet_count);
	board = boardgen(4, NULL);
 	backtrack(pieces, 0, board, 0, 0, 4);
	printf("%s\n", board);
	return (0);
}

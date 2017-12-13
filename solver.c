/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:06:39 by mbrown            #+#    #+#             */
/*   Updated: 2017/12/12 23:32:53 by mbrown           ###   ########.fr       */
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

	temp = tet;
	i = -1;
	while (++i < strlen(board))
	{
		if (board[i] == tetnum + 'A')
			return (0);
	}
	i = -1;
	while (++i < 4)
	{
		if (temp[i] > 4)
			temp[i] = temp[i] + temp[i] / 4;
	}
	i = 0;
	if (board[temp[i] + startpos] == '.' && board[temp[i + 1] + startpos] == '.')
	{
		if (board[temp[i + 2] + startpos] == '.' && board[temp[i + 3] + startpos] == '.')
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

int		backtrack(int pieces[4][4], int startpos, char *board, int tetnum)
{
	if (board[startpos] == '\0')
		return (1);
	while (tetnum < 4)
	{
		if (check(pieces[tetnum], startpos, board, tetnum))
			return (backtrack(pieces, 0, board, 0));
		tetnum++;
	}
	backtrack(pieces, startpos + 1, board, 0);
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
	int		pieces[4][4] = {{0,1,5,6},
							{0,4,5,6},
							{0,1,5,9},
							{0,1,2,3}};
	//int		pieces[2][4] = {{0,4,8,12},
	//							{0,1,4,5}};
	//i = 0;
	//j = 0;
	//while (++j <= tet_count)
	//	tetnums[i++] = j;
	//combination(tetnums, tet_count);
	board = boardgen(4, NULL);
	backtrack(pieces, 0, board, 0);
	printf("%s", board);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:06:39 by mbrown            #+#    #+#             */
/*   Updated: 2017/12/13 21:13:53 by mbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char		*g_boardcopy;

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

int		check(int *tet, int startpos, char *board, int tetnum, int size)
{
	int i;
	int	*temp;

	temp = malloc(sizeof(temp) * 4);
	for (int k = 0; k < 4; k++)
		temp[k] = tet[k];
	i = -1;
	while (++i < (int)strlen(board))
	{
		if (board[i] == tetnum + 'A')
		{
			free(temp);
			return (0);
		}
	}
	i = -1;
	while (++i < 4)
	{
		if (temp[i] >= 4)
			temp[i] = temp[i] + (temp[i] / 4) * (size - 3);
	}
	i = 0;
	if (board[temp[0] + startpos] == '.' && board[temp[1] + startpos] == '.')
	{
		if (board[temp[2] + startpos] == '.' && board[temp[3] + startpos] == '.')
		{
			while (i < 4)
				board[temp[i++] + startpos] = tetnum + 'A';
			free(temp);
			return (1);
		}
		else
		{
			free(temp);
			return (0);
		}
	}
	free(temp);
	return (0);
}

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

int		boardfull(char *board, int size)
{
	int	i;
	
	i = 0;
	g_boardcopy = malloc(sizeof(int *) * (size * size) + (size));
	g_boardcopy = board;
	while (i < (size * size) + size)
	{
		if (g_boardcopy[i] == '.')
			return (0);
		i++;
	}
	return (1);
}

int		backtrack(int pieces[4][4], int startpos, char *board, int tetnum, int placed)
{
	//if (boardfull(board, 4) != 1)
	//	return (1);
	if (placed == 4)
		return (1);
	if (board[startpos + 1] == '\0')
		return (-1);
	if (board[startpos] != '.')
		return (backtrack(pieces, startpos + 1, board, tetnum, placed));
	if (tetnum == 4)
		return (backtrack(pieces, startpos + 1, board, 0, placed));
	while (tetnum < 4)
	{
		if (check(pieces[tetnum], startpos, board, tetnum, 4) != 0)
		{
			if (backtrack(pieces, 0, board, 0, placed + 1) < 0)
				return (0);
		}
		tetnum++;
	}
	boardreset(board, 4);
	return (0);
}

//int		backtrack(int pieces[4][4], int startpos, char *board, int tetnum, int placed, int size)
//{
//	if (placed == 4)
//		return (1);
//	if (!board[startpos + 1])
//	{
//		boardreset(board, 4);
//		return(backtrack(pieces, 0, board, tetnum + 1, 0, 4));
//	}
//	if (tetnum == 4)
//		backtrack(pieces, startpos + 1, board, 0, placed, 4);
//	if (tetnum < 4)
//	{
//		if (check(pieces[tetnum], startpos, board, tetnum))
//			return (backtrack(pieces, 0, board, 0, placed + 1, 4));
//		else
//			return (backtrack(pieces, startpos, board, tetnum + 1, placed, 4));
//	}
//	return (0);
//}
//
int main(void)
{
	char	*board;
//	int		pieces[8][4] = {{0,4,8,12},
//							{0,1,2,3},
//							{0,1,2,6},
//							{2,3,6,5},
//							{0,1,4,5},
//							{0,1,5,6},
//							{0,1,5,9},
//							{0,1,2,5}};
	int		pieces[4][4] = {{0,1,5,9},
							{0,4,5,6},
							{0,1,5,6},
							{0,1,2,3}};
//	int		pieces[2][4] = {{0,4,8,12},
//								{0,1,4,5}};
	board = boardgen(4, NULL);
	backtrack(pieces, 0, board, 0, 0);
	printf("%s",  board);
	return (0);
}

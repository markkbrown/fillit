/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrown <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:06:39 by mbrown            #+#    #+#             */
/*   Updated: 2017/12/16 16:23:39 by mbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int		g_tet_num = 8;
char	*g_board;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

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
			return (0);
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
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	removetet(int *tet, char *board, int pos, int size)
{
	int	i;

	int *temp;
	temp = malloc(sizeof(temp) * 4);
	for (int j = 0; j < 4; j++)
		temp[j] = tet[j];
	i = -1;
	while (++i < 4)
	{
		if (temp[i] >= 4)
			temp[i] = temp[i] + (temp[i] / 4) * (size - 3);
	}
	i = -1;
	while (++i < 4)
		board[pos + temp[i]] = '.';

}

int		backtrack(int pieces[8][4], char *board, int tetnum, int size)
{
	//printf("%s", board);
	int pos;

	if (tetnum == g_tet_num)
	{
		g_board = board;
		return (0);
	}
	pos = 0;
	while (board[pos] != '\0')
	{
			if (check(pieces[tetnum], pos, board, tetnum, size) != 0)
			{
				if (!backtrack(pieces, board, tetnum + 1, size))
					return (0);
				removetet(pieces[tetnum], board, pos, size);
			}
		pos++;
	}
	return (1);
}

int main(void)
{
	char	*board;
	int		pieces[8][4] = {{0,4,8,12},
							{0,1,2,3},
							{0,1,2,6},
							{2,3,6,5},
							{0,1,4,5},
							{0,1,5,6},
							{0,1,5,9},
							{0,1,2,5}};
//	int		pieces[4][4] = {{0,1,5,9},
//							{0,4,5,6},
//							{0,1,5,6},
//							{0,1,2,3}};
//	int		pieces[2][4] = {{0,4,8,12},
//								{0,1,4,5}};
	board = boardgen(6, NULL);
	g_board = 0;
	backtrack(pieces, board, 0, 6);
	printf("%s", g_board);
	return (0);
}

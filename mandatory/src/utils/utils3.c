/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:58:27 by aguinea           #+#    #+#             */
/*   Updated: 2025/07/21 20:41:22 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minirt.h"

static int	safe_malloc(char **token_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	token_v[position] = malloc(buffer);
	if (!token_v[position])
	{
		while (i < position)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

static size_t	count_tokens(char const *s, char delimiter)
{
	size_t	tokens;
	int		new_token;

	tokens = 0;
	while (*s && *s != '#')
	{
		while (*s == delimiter && *s && *s != '#')
			s++;
		new_token = 0;
		while (*s != delimiter && *s && *s != '#')
		{
			if (new_token == 0)
			{
				tokens++;
				new_token = 1;
			}
			s++;
		}
	}
	return (tokens);
}

static int	fill(char **token_v, char const *s, char delimiter)
{
	size_t	len;
	int		position;

	position = 0;
	while (*s && *s != '#')
	{
		while (*s == delimiter && *s && *s != '#')
			s++;
		if (*s == '\0' || *s == '#')
			break ;
		len = 0;
		while (s[len] != delimiter && s[len] && s[len] != '#')
			len++;
		if (safe_malloc(token_v, position, len + 1))
			return (1);
		ft_strlcpy(token_v[position], s, len + 1);
		s += len;
		position++;
	}
	return (0);
}

char	**ft_split1(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (s == NULL)
		return (NULL);
	tokens = 0;
	tokens = count_tokens(s, c);
	token_v = malloc((tokens + 1) * sizeof(char *));
	if (!token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill (token_v, s, c))
		return (NULL);
	return (token_v);
}

void	evaluate_token(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	if (i > 0 && !ft_isalnum(tokens[i - 1][0]))
	{
		free(tokens[i - 1]);
		tokens[i - 1] = NULL;
	}
}

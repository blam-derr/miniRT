#include <stdlib.h>

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_charset(str[i], charset))
		{
			count++;
			while (str[i] && !is_charset(str[i], charset))
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*strlendup(char *str, int start, int end)
{
	char	*string;
	int		i;

	i = 0;
	string = (char *)malloc(sizeof(char) * (end - start) + 1);
	if (string == NULL)
		return (0);
	while (start < end)
	{
		string[i++] = str[start++];
	}
	string[i] = '\0';
	return (string);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**arr;
	int		pos;
	int		start;
	int		i;

	pos = 0;
	start = 0;
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (count_words(str, charset) + 1));
	while (str[i])
	{
		if (!is_charset(str[i], charset))
		{
			start = i;
			while (!is_charset(str[i], charset) && str[i])
				i++;
			arr[pos++] = strlendup(str, start, i);
		}
		else
			i++;
	}
	arr[pos] = NULL;
	return (arr);
}

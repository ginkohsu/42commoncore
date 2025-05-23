/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:57:40 by jinxu             #+#    #+#             */
/*   Updated: 2025/05/23 13:34:10 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen_z(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen_z(s);
	dup = (char *)malloc(sizeof(char) *(len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	actl_len;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen_z(s) < start)
		return (ft_strdup(""));
	actl_len = ft_strlen_z(s) - start;
	if (actl_len > len)
		actl_len = len;
	subs = malloc (actl_len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < actl_len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

char	*ft_strjoin_safe(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen_z(s1);
	len2 = ft_strlen_z(s2);
	if ((len1 > SIZE_MAX - len2 - 1) || (len1 == 0 && len2 == 0))
		return (NULL);
	str = malloc (len1 + len2 + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && (i < len1))
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && (j < len2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

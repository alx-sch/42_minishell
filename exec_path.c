#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
MVP for executing a path
*/

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*char_dest;
	const char	*char_src;

	char_dest = (char *) dest;
	char_src = (const char *) src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (len1 + len2 +1));
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, len1);
	ft_memcpy(strjoin + len1, s2, len2 + 1);
	return (strjoin);
}

int main(int argc, char *argv[], char *envp[])
{
    char    *err_msg;
    char    *err_msg_2;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <path_to_executable> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Path to the executable
    char *path = argv[1];

    // Arguments for execve: the first argument should be the executable itself
    // We pass argv[1] (path to executable) as argv[0] to the new program
    char **exec_argv = &argv[1];

    // Execute the program
    if (execve(path, exec_argv, envp) == -1) {
        // If execve returns, it means there was an error
        err_msg = ft_strjoin("minishell: ", argv[1]);
        perror(err_msg);
        free(err_msg);
        return EXIT_FAILURE;
    }

    // This point will not be reached if execve is successful
    return EXIT_SUCCESS;
}
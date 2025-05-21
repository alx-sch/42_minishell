#include "libft.h"

/*
Works like ft_strmapi() with the difference that ft_striteri() applies function
f directly on the original string.
Passing the address (a pointer) as to modify the actual memory location of the
index / char.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !(*s) || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>

void	ft_wrapper(unsigned int index, char *c)
{
	(void)index;
	*c = (ft_toupper(*c));
}


int	main(void)
{
	char	test_str[] = "A test string to be modified by ft_strmapi()";

	printf("String before ft_strmapi(): '%s'\n", test_str);
	ft_striteri(test_str, ft_wrapper);
	printf("String after ft_strmapi(): '%s'\n", test_str);

	return (0);
}
*/

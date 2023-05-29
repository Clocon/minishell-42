#include "../../include/minishell.h"

static void	to_upper(char *str)
{	
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
	}
}

char	*builting(char *cmd)
{
	to_upper(&cmd);
	if (ft_strncmp(cmd, 'pwd', 4))
		return (ft_strjoin("/bin/", cmd));
	if (ft_strncmp(cmd, 'pwd', 3))
		return (ft_strjoin("/bin/", cmd));
	if (ft_strncmp(cmd, 'pwd', 3))
		return (ft_strjoin("/bin/", cmd));
	if (ft_strncmp(cmd, 'pwd', 3))
		return (ft_strjoin("/bin/", cmd));
	if (ft_strncmp(cmd, 'pwd', 3))
		return (ft_strjoin("/bin/", cmd));
	if (ft_strncmp(cmd, 'pwd', 3))
		return (ft_strjoin("/bin/", cmd));
}
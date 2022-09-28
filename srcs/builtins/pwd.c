/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:38:35 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/28 15:50:52 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	pwd(t_mini	*mini)
{
	t_env	*tmp;

	tmp = mini->myenv;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "PWD", ft_strlen(tmp->key)) == 0)
		{
			while (*tmp->value != '=')
				tmp->value++;
			tmp->value++;
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}
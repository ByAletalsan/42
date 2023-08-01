/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:23:54 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/27 15:53:28 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

static int	ft_tree_type(char *cmd, int op_idx)
{
	if (op_idx == -1)
		return (T_LEAF);
	else if (cmd[op_idx] == '|')
		return (T_OR);
	else if (cmd[op_idx] == '&')
		return (T_AND);
	else
	{
		printf("%c%c is not a valid operator!\n", cmd[op_idx], cmd[op_idx + 1]);
		return (T_ERROR);
	}
}

static int	ft_build_left_right(t_cmdtree *tree, int op_idx)
{
	char		*left_cmd;
	char		*right_cmd;

	left_cmd = ft_strcpy_range(tree->cmd, 0, op_idx);
	if (!ft_strlen(left_cmd))
		return (free(left_cmd), printf("Invalid operator\n"),
			ft_free_cmdtree(tree), 1);
	tree->left = ft_build_cmdtree(left_cmd);
	if (!tree->left)
		return (ft_free_cmdtree(tree), 1);
	right_cmd = ft_strcpy_range(tree->cmd, op_idx + 2, ft_strlen(tree->cmd));
	if (!ft_strlen(right_cmd))
		return (free(right_cmd), printf("Invalid operator\n"),
			ft_free_cmdtree(tree), 1);
	tree->right = ft_build_cmdtree(right_cmd);
	if (!tree->right)
		return (ft_free_cmdtree(tree), 1);
	return (0);
}

t_cmdtree	*ft_build_cmdtree(char *cmd_ln)
{
	t_cmdtree	*tree;
	int			op_idx;

	tree = malloc(sizeof(t_cmdtree));
	if (!tree)
		return (NULL);
	tree->cmd = ft_cpy_cmd_clean(cmd_ln, 0, NULL);
	if (!tree->cmd)
		return (free(tree), NULL);
	op_idx = ft_find_op_idx(tree->cmd);
	tree->type = ft_tree_type(tree->cmd, op_idx);
	if (tree->type != T_LEAF)
	{
		if (ft_build_left_right(tree, op_idx))
			return (NULL);
	}
	return (tree);
}

void	ft_exec_cmdtree(t_cmdtree *tree)
{
	if (tree->type == T_LEAF)
		tree->rc = ejecutor_i(tree->cmd, 0);
	else
	{
		if (tree->type == T_AND)
		{
			ft_exec_cmdtree(tree->left);
			if (tree->left->rc == 0)
				ft_exec_cmdtree(tree->right);
		}
		else if (tree->type == T_OR)
		{
			ft_exec_cmdtree(tree->left);
			if (tree->left->rc != 0)
				ft_exec_cmdtree(tree->right);
		}
		if (!tree->left->rc || !tree->right->rc)
			tree->rc = 0;
		else
			tree->rc = 1;
	}
}

void	ft_free_cmdtree(t_cmdtree *tree)
{
	if (tree->type != T_LEAF)
	{
		if (tree->left)
			ft_free_cmdtree(tree->left);
		if (tree->right)
			ft_free_cmdtree(tree->right);
	}
	if (tree->cmd)
		free(tree->cmd);
	free(tree);
}

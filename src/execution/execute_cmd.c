/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylr <ylr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:47:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/23 19:02:28 by ylr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../minishell.h"

char    *ft_path(t_parser *parse, t_env *env)
{
    char    *path;
    char    *paths;
    char    **splited;
    int        i;

    i = 0;
    paths = search_in_env(env, "PATH")->value;
    if (!paths)
    {
        write (2, "No such file or directory\n", 27);
        exit (127);
    }
    splited = ft_split(paths, ':');
    while (splited[i])
    {
        path = ft_strjoin(ft_strjoin(splited[i], "/"), parse->command->cmds[0]);
        if (access(path, X_OK | F_OK) == 0)
            return (path);
        i++;
    }
    write(2, "command not found\n", 19);
    exit(127);
    return (NULL);
}

// void open_pipes(t_parser *parse)
// {
//     t_parser *courant;
//     int        T[2];
    
//     courant = parse;
//     while (courant->next)
//     {
//         if (courant->command->pipe == 1)
//         {
//             pipe(T);
//             courant->command->pipe_fd->write = T[0];
//             courant->next->command->pipe_fd->read = T[1];
//         }
//     }
// }

void    ft_dup(t_parser *parse)
{

    if (parse->command->pipe)
        dup2(parse->command->pipe_fd.write, STDOUT_FILENO);
    if(parse->command->red_out != -1)
        dup2(parse->command->red_out, STDOUT_FILENO);
    if(parse->command->red_in != -1 || parse->command->red_in != -1)
        dup2(parse->command->red_in, STDIN_FILENO);
    if (parse->command->pipe_fd.to_close && parse->command->pipe_fd.to_close != 1)
        close(parse->command->pipe_fd.to_close);
}

char **env_in_tab(t_env *env)
{
    char    **envp;
    int     count;
    t_env   *cur;
    int     i;
    
    i = 0;
    count = 0;
    cur = env;
    while (cur)
    {
        count++;
        cur = cur->next;
    }
    // exit(100);
    envp = (char **) malloc((count+1)*sizeof(char *));
    while (env)
    {
        envp[i] = ft_strjoin(env->key,"=");
        envp[i] = ft_strjoin(envp[i],env->value);
        env=env->next;
        i++;
    }
    envp[count] = NULL;
    return(envp);
}
void set_pipes(t_parser *parse)
{
    t_parser     *courant;
    int            T[2];

    
    courant = parse;
    while (courant->next)
    {
        if (courant->command->pipe == 1)
        {
            pipe(T);
            courant->command->pipe_fd.write = T[1];
            courant->next->command->pipe_fd.to_close = T[1];
            courant->next->command->pipe_fd.read = T[0];
        }
        courant = courant->next;
    }
}

void   execute_cmd(t_parser *parse, t_env *env, char **envp)
{
    int id;
    char *path;
    
    id = fork();
    if(!id)
    {
        path = ft_path(parse, env);
        if (!path)
            exit(127);
        if (execve(path, parse->command->cmds, envp) == -1)
        {
            write(2, "could not execve", 17);
            exit(127);
        }
        exit(1);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:39:03 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/13 16:42:27 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_rlst
{
	char			*content;
	struct s_rlst	*next;
}	t_rlst;

typedef struct s_typed_ptr
{
	int		type;
	void	**ptr_storage;
	void	*ptr_malloc;
}	t_typed_ptr;

int		ft_printf(const char *format, ...);
int		ft_eprintf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);

char	*get_next_line(int fd);
char	*join_list_to_str(t_rlst *start);

void	ft_cancel_newline_at_end(char *line);
int		ft_isspace(char c);
int		ft_is_int_str(char *s);
int		ft_is_hex_str(char *s);
long	ft_atol(const char *nptr);
long	ft_htol(const char *nptr);

void	*set(void *vtarget, void *void_new);

int		ft_isalpha(char c);
int		ft_isdigit(char c);
int		ft_isalnum(char c);
int		ft_isascii(int c);
int		ft_isprint(char c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_stpcpy(char *dst, const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	**ft_split(char const *s, char c);
size_t	ft_count_splits(char **split);
void	*ft_free_splits(void *vtable);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **begin_list, t_list *new);
int		ft_lstsize(t_list *begin_list);
t_list	*ft_lstlast(t_list *begin_list);
void	ft_lstadd_back(t_list **begin_list, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *begin_list, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
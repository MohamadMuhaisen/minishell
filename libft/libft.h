/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:41:44 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/08/22 15:28:37 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_format
{
	int	left_justify;
	int	zero_pad;
	int	field_width;
	int	precision;
	int	alternate_form;
	int	space;
	int	plus;
}	t_format;

long	ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *string, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *str, const char *target, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*get_next_line(int fd);
char	*fill_stash(char *str);
char	*extract_line(int fd, char *stash, char *buffer);
int		ft_printf(const char *str, ...);
int		ft_putnbr_hex(unsigned long nbr, char *base,
			t_format *format, int l);
int		ft_putptr_fd(void *ptr, t_format *format, int l);
int		ft_putnbr_unsigned(unsigned long int n, int fd, t_format *format);
int		ft_putnbr_unsigned_recursive(unsigned int n, int fd);
int		ft_putnbr_hex_lower(unsigned int nbr, t_format *format);
int		ft_putnbr_hex_upper(unsigned int nbr, t_format *format);
void	left_justify(t_format *format, int *count, int limit);
int		parse_s(va_list ap, t_format *format);
int		parse_int(va_list ap, t_format *format);
void	init_format(t_format *format);
void	fill_format(const char **str, t_format *format);
int		parse_c(va_list ap, t_format *format);
int		parse_arg(const char **str, va_list ap);
int		ft_putnbr_hex_recursive(unsigned long nbr, char *base);
void	add_zeros(t_format *format, int *n, int *count);
int		handle_output(va_list ap, t_format *format);
void	add_zeros_unsigned(t_format *format, unsigned long int *n,
			int *count, int base);

#endif
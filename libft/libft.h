/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:34:17 by jbrosio           #+#    #+#             */
/*   Updated: 2025/11/19 21:50:13 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include "../minishel.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ========================================================================== */
/*                              STRUCTURES                                    */
/* ========================================================================== */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ========================================================================== */
/*                        CHARACTER VALIDATION                                */
/* ========================================================================== */

/**
 * @brief Checks if character is alphabetic (a-z, A-Z).
 * @param c Character to check (as int).
 * @return 1 if alphabetic, 0 otherwise.
 */
int			ft_isalpha(int c);

/**
 * @brief Checks if character is a digit (0-9).
 * @param c Character to check (as int).
 * @return 1 if digit, 0 otherwise.
 */
int			ft_isdigit(int c);

/**
 * @brief Checks if character is alphanumeric.
 * @param c Character to check (as int).
 * @return 1 if alphanumeric, 0 otherwise.
 */
int			ft_isalnum(int c);

/**
 * @brief Checks if character is in ASCII table (0-127).
 * @param c Character to check (as int).
 * @return 1 if ASCII, 0 otherwise.
 */
int			ft_isascii(int c);

/**
 * @brief Checks if character is printable (32-126).
 * @param c Character to check (as int).
 * @return 1 if printable, 0 otherwise.
 */
int			ft_isprint(int c);

/**
 * @brief Converts lowercase letter to uppercase.
 * @param c Character to convert.
 * @return Uppercase character or unchanged if not lowercase.
 */
int			ft_toupper(int c);

/**
 * @brief Converts uppercase letter to lowercase.
 * @param c Character to convert.
 * @return Lowercase character or unchanged if not uppercase.
 */
int			ft_tolower(int c);

/* ========================================================================== */
/*                          STRING OPERATIONS                                 */
/* ========================================================================== */

/**
 * @brief Calculates the length of a string.
 * @param s String to measure.
 * @return Number of characters before null terminator.
 */
size_t		ft_strlen(const char *s);

/**
 * @brief Locates first occurrence of character in string.
 * @param s String to search in.
 * @param c Character to find.
 * @return Pointer to character or NULL if not found.
 */
char		*ft_strchr(const char *s, int c);

/**
 * @brief Locates last occurrence of character in string.
 * @param s String to search in.
 * @param c Character to find.
 * @return Pointer to character or NULL if not found.
 */
char		*ft_strrchr(const char *s, int c);

/**
 * @brief Compares two strings up to n bytes.
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Maximum bytes to compare.
 * @return Difference between first differing bytes, 0 if equal.
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Locates substring within string, searching up to len bytes.
 * @param big String to search in.
 * @param little Substring to find.
 * @param len Maximum bytes to search.
 * @return Pointer to substring or NULL if not found.
 */
char		*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Copies string to destination with size limit.
 * @param dst Destination buffer.
 * @param src Source string.
 * @param size Size of destination buffer.
 * @return Length of source string.
 * @note Always null-terminates unless size is 0.
 */
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Concatenates strings with size limit.
 * @param dst Destination buffer.
 * @param src Source string to append.
 * @param size Total size of destination buffer.
 * @return Total length of string it tried to create.
 * @note Always null-terminates unless size is 0.
 */
size_t		ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Duplicates a string with malloc.
 * @param s String to duplicate.
 * @return Pointer to new string or NULL if allocation fails.
 */
char		*ft_strdup(const char *s);

/**
 * @brief Concatenates two strings into new allocated string.
 * @param s1 First string (prefix).
 * @param s2 Second string (suffix).
 * @return New string or NULL if allocation fails.
 */
char		*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Extracts substring from string.
 * @param s Source string.
 * @param start Starting index.
 * @param len Maximum length of substring.
 * @return New substring or NULL if allocation fails.
 */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Trims characters from beginning and end of string.
 * @param s1 String to trim.
 * @param set Set of characters to remove.
 * @return New trimmed string or NULL if allocation fails.
 */
char		*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Splits string into array of strings using delimiter.
 * @param s String to split.
 * @param c Delimiter character.
 * @return Array of strings or NULL if allocation fails.
 * @note Last element is NULL. Free with ft_free_double_array().
 */
char		**ft_split(char const *s, char c);

/**
 * @brief Applies function to each character creating new string.
 * @param s String to iterate.
 * @param f Function to apply (index, character).
 * @return New string or NULL if allocation fails.
 */
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies function to each character of string in place.
 * @param s String to iterate.
 * @param f Function to apply (index, character pointer).
 */
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

/* ========================================================================== */
/*                          MEMORY OPERATIONS                                 */
/* ========================================================================== */

/**
 * @brief Sets block of memory to zero.
 * @param s Pointer to memory block.
 * @param n Number of bytes to zero out.
 */
void		ft_bzero(void *s, size_t n);

/**
 * @brief Fills memory with a constant byte.
 * @param s Pointer to memory block.
 * @param c Byte value to set.
 * @param n Number of bytes to set.
 * @return Pointer to memory area s.
 */
void		*ft_memset(void *s, int c, size_t n);

/**
 * @brief Copies n bytes from src to dest.
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to dest.
 * @note Memory areas must not overlap. Use ft_memmove for overlapping.
 */
void		*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copies n bytes handling overlapping memory areas.
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to dest.
 * @note Safe for overlapping memory areas.
 */
void		*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Scans memory for first occurrence of byte.
 * @param s Memory area to search.
 * @param c Byte to find (as int).
 * @param n Number of bytes to scan.
 * @return Pointer to byte or NULL if not found.
 */
void		*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares two memory areas.
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Number of bytes to compare.
 * @return Difference between first differing bytes, 0 if equal.
 */
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Allocates and zeroes memory for array.
 * @param nmemb Number of elements.
 * @param size Size of each element.
 * @return Pointer to allocated memory or NULL if fails.
 */
void		*ft_calloc(size_t nmemb, size_t size);

/* ========================================================================== */
/*                          CONVERSION FUNCTIONS                              */
/* ========================================================================== */

/**
 * @brief Converts string to integer.
 * @param nptr String to convert.
 * @return Converted integer value.
 * @note Handles leading whitespace and +/- signs.
 */
int			ft_atoi(const char *nptr);

/**
 * @brief Converts string to long integer.
 * @param nptr String to convert.
 * @return Converted long integer value.
 * @note Handles leading whitespace and +/- signs.
 */
long int	ft_atol(const char *nptr);

/**
 * @brief Converts string to float (with decimal point).
 * @param nptr String to convert.
 * @return Converted float value.
 * @note Handles leading whitespace, +/- signs and decimal point.
 */
float		ft_atod(char *nptr);

/**
 * @brief Converts integer to string.
 * @param n Integer to convert.
 * @return String representation or NULL if allocation fails.
 * @note Handles negative numbers.
 */
char		*ft_itoa(int n);

/* ========================================================================== */
/*                          FILE DESCRIPTOR I/O                               */
/* ========================================================================== */

/**
 * @brief Writes character to file descriptor.
 * @param c Character to write.
 * @param fd File descriptor.
 * @return Number of bytes written (1).
 */
int			ft_putchar_fd(char c, int fd);

/**
 * @brief Writes string to file descriptor.
 * @param s String to write.
 * @param fd File descriptor.
 * @return Number of bytes written.
 */
int			ft_putstr_fd(char *s, int fd);

/**
 * @brief Writes string followed by newline to file descriptor.
 * @param s String to write.
 * @param fd File descriptor.
 */
void		ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes integer to file descriptor.
 * @param n Integer to write.
 * @param fd File descriptor.
 * @return Number of bytes written.
 * @note Handles negative numbers.
 */
int			ft_putnbr_fd(int n, int fd);

/**
 * @brief Writes unsigned integer to file descriptor.
 * @param n Unsigned integer to write.
 * @param fd File descriptor.
 * @return Number of bytes written.
 */
int			ft_putnbr_u(long int n);

/* ========================================================================== */
/*                          LINKED LIST OPERATIONS                            */
/* ========================================================================== */

/**
 * @brief Creates new list node.
 * @param content Content to store in node.
 * @return Pointer to new node or NULL if allocation fails.
 */
t_list		*ft_lstnew(void *content);

/**
 * @brief Adds node at beginning of list.
 * @param lst Address of pointer to first node.
 * @param new Node to add.
 */
void		ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Adds node at end of list.
 * @param lst Address of pointer to first node.
 * @param new Node to add.
 */
void		ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Returns last node of list.
 * @param lst First node of list.
 * @return Last node or NULL if list is empty.
 */
t_list		*ft_lstlast(t_list *lst);

/**
 * @brief Counts number of nodes in list.
 * @param lst First node of list.
 * @return Number of nodes.
 */
int			ft_lstsize(t_list *lst);

/**
 * @brief Deletes single node using given function.
 * @param lst Node to delete.
 * @param del Function to delete content.
 */
void		ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Deletes and frees entire list.
 * @param lst Address of pointer to first node.
 * @param del Function to delete content.
 */
void		ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief Iterates list applying function to each node's content.
 * @param lst First node of list.
 * @param f Function to apply to each content.
 */
void		ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Creates new list applying function to each node.
 * @param lst First node of list.
 * @param f Function to apply to content.
 * @param del Function to delete content if needed.
 * @return New list or NULL if allocation fails.
 */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief Frees circular linked list nodes.
 * @param head Address of pointer to head node.
 * @note Specific for circular lists.
 */
void		ft_free_nodes(void **head);

/* ========================================================================== */
/*                         FPRINTF FUNCTIONS                                  */
/* ========================================================================== */

int			ft_fprintf(int fd, char const *s, ...);
int			ft_searchtype_fd(va_list vargs, char c, int fd);
int			ft_putnbr_u_fd(long int n, int fd);
int			puthex_p_fd(unsigned long long num, int fd);
int			puthex_x_fd(unsigned long long num, int fd);
int			puthex_X_fd(unsigned long long num, int fd);

/* ========================================================================== */
/*                          PRINTF FUNCTIONS                                  */
/* ========================================================================== */

/**
 * @brief Formatted output to stdout (similar to printf).
 * @param s Format string with specifiers.
 * @param ... Variable arguments.
 * @return Number of characters printed.
 * @note Supports: [%c] [%s] [%d] [%i] [%u] [%x] [%X] [%p] [%%].
 */
int			ft_printf(char const *s, ...);

/**
 * @brief Helper to process printf format specifiers.
 * @param vargs Variable argument list.
 * @param c Format specifier character.
 * @return Number of characters printed.
 */
int			ft_searchtype(va_list vargs, char c);

/**
 * @brief Prints hexadecimal in uppercase.
 * @param num Number to print.
 * @return Number of characters printed.
 */
int			ft_puthex_mayus(unsigned long long num);

/**
 * @brief Prints hexadecimal in lowercase.
 * @param num Number to print.
 * @return Number of characters printed.
 */
int			ft_puthex_x(unsigned long long num);

/**
 * @brief Prints pointer address in hexadecimal.
 * @param num Pointer address.
 * @return Number of characters printed.
 * @note Prints "(nil)" for NULL pointers.
 */
int			ft_puthex_p(unsigned long long num);

/* ========================================================================== */
/*                          GET_NEXT_LINE FUNCTIONS                           */
/* ========================================================================== */

/**
 * @brief Reads line from file descriptor.
 * @param fd File descriptor to read from.
 * @return Line read including newline, or NULL at EOF/error.
 * @note Uses static buffer. BUFFER_SIZE must be defined.
 */
char		*get_next_line(int fd);

/**
 * @brief GNL helper: calculates string length.
 * @param str String to measure.
 * @return Length of string.
 */
size_t		ft_strlen_gnl(char *str);

/**
 * @brief GNL helper: finds character in string.
 * @param s String to search.
 * @param c Character to find.
 * @return Pointer to character or NULL.
 */
char		*ft_strchr_gnl(const char *s, int c);

/**
 * @brief GNL helper: duplicates string.
 * @param s String to duplicate.
 * @return New string or NULL.
 */
char		*ft_strdup_gnl(const char *s);

/**
 * @brief GNL helper: joins two strings, freeing first.
 * @param s1 First string (will be freed).
 * @param s2 Second string.
 * @return New joined string or NULL.
 */
char		*ft_strjoin_gnl(char *s1, char *s2);

/**
 * @brief GNL helper: extracts substring.
 * @param s Source string.
 * @param start Starting index.
 * @param len Maximum length.
 * @param i Iterator (pass 0).
 * @return New substring or NULL.
 */
char		*gnl_substr(char *s, unsigned int start, size_t len, size_t i);

/* ========================================================================== */
/*                          UTILITY FUNCTIONS                                 */
/* ========================================================================== */

/**
 * @brief Sorts integer array in ascending order.
 * @param tab Array to sort.
 * @param size Number of elements.
 * @note Uses bubble sort algorithm.
 */
void		ft_sort_int_tab(int *list, int size);

/**
 * @brief Prints double pointer array to file descriptor.
 * @param s Array of strings.
 * @param fd File descriptor.
 * @note Prints each string on new line.
 */
void		ft_double_putstr_fd(char **s, int fd);

/**
 * @brief Joins array of strings with spaces.
 * @param str Array of strings.
 * @return Single joined string or NULL.
 */
char		*ft_dblstr_join(char **str);


int			ft_is_metachar(char c);
void		*ft_free_all_array(char **big);

#endif
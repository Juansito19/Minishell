/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrosio <jbrosio@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:04:52 by jbrosio           #+#    #+#             */
/*   Updated: 2026/01/15 19:04:53 by jbrosio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* ============================ */
/* ========== signals ========= */
/* ============================ */

/**
 * @brief Sets up signal handlers for interactive mode.
 * @return 0 on success, 1 on error.
 * @note SIGINT displays prompt on new line. SIGQUIT ignored.
 */
int		ft_hugin_signal(void);

/**
 * @brief Signal handler for interactive mode (Hugin).
 * @param sig Signal number received.
 * @note Handles SIGINT: prints newline, resets prompt, sets
 *       g_status to 130.
 */
void	ft_hugin_handler(int sig);

/**
 * @brief Sets up signal handlers for heredoc input mode.
 * @return 0 on success, 1 on error.
 * @note SIGINT closes STDIN and sets g_status. SIGQUIT ignored.
 */
int		ft_munin_signal(void);

/* ============================ */

/* ============================ */
/* ===== heimdall_signals ===== */
/* ============================ */

/**
 * @brief Sets up signal handlers to ignore signals during execution.
 * @return 0 on success, 1 on error.
 * @note Ignores SIGINT and SIGQUIT. Used in parent process.
 */
int		ft_odin_signal(void);

/**
 * @brief Restores default signal handlers for child processes.
 * @return 0 on success, 1 on error.
 * @note Sets SIGINT and SIGQUIT to SIG_DFL.
 */
int		ft_odinson_signal(void);

/* ============================ */

#endif
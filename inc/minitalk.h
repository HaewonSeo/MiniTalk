/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:28:08 by haseo             #+#    #+#             */
/*   Updated: 2021/10/12 17:39:38 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// # include <sys/siginfo.h>
# include <sys/types.h>
# include <signal.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/ft_printf.h"

# if defined(__linux__)
	# define PID_MAX 32768
# elif defined(__APPLE__) && defined(__MACH__)
	# define PID_MAX 99998
# endif

#endif

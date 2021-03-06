/*
 * Copyright (c) 2005-2014 Rich Felker, et al.
 * Copyright (c) 2015-2016 Álvaro Jurado et al.
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE.mit file.
 */

#include <locale.h>
#include <limits.h>

static const struct lconv posix_lconv = {
	.decimal_point = ".",
	.thousands_sep = "",
	.grouping = "",
	.int_curr_symbol = "",
	.currency_symbol = "",
	.mon_decimal_point = "",
	.mon_thousands_sep = "",
	.mon_grouping = "",
	.positive_sign = "",
	.negative_sign = "",
	.int_frac_digits = CHAR_MAX,
	.frac_digits = CHAR_MAX,
	.p_cs_precedes = CHAR_MAX,
	.p_sep_by_space = CHAR_MAX,
	.n_cs_precedes = CHAR_MAX,
	.n_sep_by_space = CHAR_MAX,
	.p_sign_posn = CHAR_MAX,
	.n_sign_posn = CHAR_MAX,
	.int_p_cs_precedes = CHAR_MAX,
	.int_p_sep_by_space = CHAR_MAX,
	.int_n_cs_precedes = CHAR_MAX,
	.int_n_sep_by_space = CHAR_MAX,
	.int_p_sign_posn = CHAR_MAX,
	.int_n_sign_posn = CHAR_MAX,
};

struct lconv *localeconv(void)
{
	return (void *)&posix_lconv;
}

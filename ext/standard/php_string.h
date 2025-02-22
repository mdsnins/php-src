/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | https://www.php.net/license/3_01.txt                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Stig Sæther Bakken <ssb@php.net>                            |
   +----------------------------------------------------------------------+
*/

#ifndef PHP_STRING_H
#define PHP_STRING_H

#if defined(ZTS)
PHP_MINIT_FUNCTION(localeconv);
PHP_MSHUTDOWN_FUNCTION(localeconv);
#endif
#if HAVE_NL_LANGINFO
PHP_MINIT_FUNCTION(nl_langinfo);
#endif
#if ZEND_INTRIN_SSE4_2_FUNC_PTR
PHP_MINIT_FUNCTION(string_intrin);
#endif

#define strnatcmp(a, b) \
	strnatcmp_ex(a, strlen(a), b, strlen(b), 0)
#define strnatcasecmp(a, b) \
	strnatcmp_ex(a, strlen(a), b, strlen(b), 1)
PHPAPI int strnatcmp_ex(char const *a, size_t a_len, char const *b, size_t b_len, int fold_case);
PHPAPI struct lconv *localeconv_r(struct lconv *out);
PHPAPI char *php_strtoupper(char *s, size_t len);
PHPAPI char *php_strtolower(char *s, size_t len);
PHPAPI zend_string *php_string_toupper(zend_string *s);
PHPAPI zend_string *php_string_tolower(zend_string *s);
PHPAPI char *php_strtr(char *str, size_t len, const char *str_from, const char *str_to, size_t trlen);
PHPAPI zend_string *php_addslashes(zend_string *str);
PHPAPI void php_stripslashes(zend_string *str);
PHPAPI zend_string *php_addcslashes_str(const char *str, size_t len, const char *what, size_t what_len);
PHPAPI zend_string *php_addcslashes(zend_string *str, const char *what, size_t what_len);
PHPAPI void php_stripcslashes(zend_string *str);
PHPAPI zend_string *php_basename(const char *s, size_t len, const char *suffix, size_t sufflen);
PHPAPI size_t php_dirname(char *str, size_t len);
PHPAPI char *php_stristr(char *s, char *t, size_t s_len, size_t t_len);
PHPAPI zend_string *php_str_to_str(const char *haystack, size_t length, const char *needle,
		size_t needle_len, const char *str, size_t str_len);
PHPAPI zend_string *php_trim(zend_string *str, const char *what, size_t what_len, int mode);
PHPAPI size_t php_strip_tags(char *rbuf, size_t len, const char *allow, size_t allow_len);
PHPAPI size_t php_strip_tags_ex(char *rbuf, size_t len, const char *allow, size_t allow_len, bool allow_tag_spaces);
PHPAPI void php_implode(const zend_string *delim, HashTable *arr, zval *return_value);
PHPAPI void php_explode(const zend_string *delim, zend_string *str, zval *return_value, zend_long limit);

PHPAPI size_t php_strspn(const char *s1, const char *s2, const char *s1_end, const char *s2_end);
PHPAPI size_t php_strcspn(const char *s1, const char *s2, const char *s1_end, const char *s2_end);

#if defined(_REENTRANT)
# ifdef PHP_WIN32
#  include <wchar.h>
# endif
# define php_mblen(ptr, len) ((int) mbrlen(ptr, len, &BG(mblen_state)))
# define php_mb_reset() memset(&BG(mblen_state), 0, sizeof(BG(mblen_state)))
#else
# define php_mblen(ptr, len) mblen(ptr, len)
# define php_mb_reset() php_ignore_value(mblen(NULL, 0))
#endif

void register_string_constants(INIT_FUNC_ARGS);

#endif /* PHP_STRING_H */

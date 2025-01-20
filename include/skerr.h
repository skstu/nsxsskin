#if !defined(__B8AC9007_F3B5_4B51_8DF9_C41392FFB505__)
#define __B8AC9007_F3B5_4B51_8DF9_C41392FFB505__

#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define SK__OK (-0)
#define SK__NO (-1)
#define SK__DONE (1)
//! system [ -1000 ~ -1999]
//! component [ -2000 ~ -2999 ]
//! plugin [ -3000 ~ -3999 ]
#define SK__EUNKN (-50000)
#define SK__EOF (-65533)

#define SK_ERRNO_MAP(XX)                                                       \
  XX(OK, "ok ")                                                               \
  XX(NO, "no ")                                                             \
		XX(DONE,"done ")					\
  XX(EUNKN, "unknown error")

typedef enum {
#define XX(code, _) SK_##code = SK__##code,
	SK_ERRNO_MAP(XX)
#undef XX
	SK_ERRNO_MAX = SK__EOF - 1
} sk_errno_t;


static const char* sk__unknown_err_code(int err) {
	char buf[256];
	char* copy = NULL;

	// snprintf(buf, sizeof(buf), "Unknown system error %d", err);
	sprintf_s(buf, "Unknown system error %d", err);
	do {
		size_t len = strlen(buf) + 1;
		char* m = (char*)malloc(len);
		if (m == NULL)
			break;
		copy = (char*)memcpy(m, buf, len);
	} while (0);

	return copy != NULL ? copy : "Unknown system error";
}

#define SK_ERR_NAME_GEN(name, _)                                               \
  case SK_##name:                                                              \
    return #name;
static const char* sk_err_name(int err) {
	switch (err) { SK_ERRNO_MAP(SK_ERR_NAME_GEN) }
	return sk__unknown_err_code(err);
}
#undef SK_ERR_NAME_GEN

#define SK_STRERROR_GEN(name, msg)                                             \
  case SK_##name:                                                              \
    return msg;
static const char* sk_strerror(int err) {
	switch (err) { SK_ERRNO_MAP(SK_STRERROR_GEN) }
	return sk__unknown_err_code(err);
}
#undef SK_STRERROR_GEN

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 07 Aug 2024 01:29:53 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__B8AC9007_F3B5_4B51_8DF9_C41392FFB505__

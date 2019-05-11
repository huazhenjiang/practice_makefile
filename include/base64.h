#ifndef _BASE64_
#define _BASE64_

int base64_encode( unsigned char *dst, size_t *dlen, const unsigned char *src, size_t slen );
int base64_decode( unsigned char *dst, size_t *dlen, const unsigned char *src, size_t slen );
char *urlDecode(const char *str);

#endif

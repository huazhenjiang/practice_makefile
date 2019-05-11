#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL               -0x002A  /**< Output buffer too small. */
#define POLARSSL_ERR_BASE64_INVALID_CHARACTER              -0x002C  /**< Invalid character in input. */
//typedef UINT32 uint32_t;

static const unsigned char base64_enc_map[64] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/'
};

static const unsigned char base64_dec_map[128] =
{
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127,  62, 127, 127, 127,  63,  52,  53,
     54,  55,  56,  57,  58,  59,  60,  61, 127, 127,
    127,  64, 127, 127, 127,   0,   1,   2,   3,   4,
      5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
     25, 127, 127, 127, 127, 127, 127,  26,  27,  28,
     29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
     39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
     49,  50,  51, 127, 127, 127, 127, 127
};

/*
 * Encode a buffer into base64 format
 */
int base64_encode( unsigned char *dst, size_t *dlen,
                   const unsigned char *src, size_t slen )
{
    size_t i, n;
    int C1, C2, C3;
    unsigned char *p;

    if( slen == 0 )
        return( 0 );

    n = ( slen << 3 ) / 6;

    switch( ( slen << 3 ) - ( n * 6 ) )
    {
        case  2: n += 3; break;
        case  4: n += 2; break;
        default: break;
    }

    if( *dlen < n + 1 )
    {
        *dlen = n + 1;
        return( POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL );
    }

    n = ( slen / 3 ) * 3;

    for( i = 0, p = dst; i < n; i += 3 )
    {
        C1 = *src++;
        C2 = *src++;
        C3 = *src++;

        *p++ = base64_enc_map[(C1 >> 2) & 0x3F];
        *p++ = base64_enc_map[(((C1 &  3) << 4) + (C2 >> 4)) & 0x3F];
        *p++ = base64_enc_map[(((C2 & 15) << 2) + (C3 >> 6)) & 0x3F];
        *p++ = base64_enc_map[C3 & 0x3F];
    }

    if( i < slen )
    {
        C1 = *src++;
        C2 = ( ( i + 1 ) < slen ) ? *src++ : 0;

        *p++ = base64_enc_map[(C1 >> 2) & 0x3F];
        *p++ = base64_enc_map[(((C1 & 3) << 4) + (C2 >> 4)) & 0x3F];

        if( ( i + 1 ) < slen )
             *p++ = base64_enc_map[((C2 & 15) << 2) & 0x3F];
        else *p++ = '=';

        *p++ = '=';
    }

    *dlen = p - dst;
    *p = 0;

    return( 0 );
}

/*
 * Decode a base64-formatted buffer
 */
int base64_decode( unsigned char *dst, size_t *dlen,
                   const unsigned char *src, size_t slen )
{
    size_t i, n;
    uint32_t j, x;
    unsigned char *p;

    for( i = n = j = 0; i < slen; i++ )
    {
        if( ( slen - i ) >= 2 &&
            src[i] == '\r' && src[i + 1] == '\n' )
            continue;

        if( src[i] == '\n' )
            continue;

        if( src[i] == '=' && ++j > 2 )
            return( POLARSSL_ERR_BASE64_INVALID_CHARACTER );

        if( src[i] > 127 || base64_dec_map[src[i]] == 127 )
            return( POLARSSL_ERR_BASE64_INVALID_CHARACTER );

        if( base64_dec_map[src[i]] < 64 && j != 0 )
            return( POLARSSL_ERR_BASE64_INVALID_CHARACTER );

        n++;
    }

    if( n == 0 )
        return( 0 );

    n = ( ( n * 6 ) + 7 ) >> 3;
    n -= j;

    if( dst == NULL || *dlen < n )
    {
        *dlen = n;
        return( POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL );
    }

   for( j = 3, n = x = 0, p = dst; i > 0; i--, src++ )
   {
        if( *src == '\r' || *src == '\n' )
            continue;

        j -= ( base64_dec_map[*src] == 64 );
        x  = ( x << 6 ) | ( base64_dec_map[*src] & 0x3F );

        if( ++n == 4 )
        {
            n = 0;
            if( j > 0 ) *p++ = (unsigned char)( x >> 16 );
            if( j > 1 ) *p++ = (unsigned char)( x >>  8 );
            if( j > 2 ) *p++ = (unsigned char)( x       );
        }
    }

    *dlen = p - dst;

    return( 0 );
}

/*

static const unsigned char base64_test_dec[64] =
{
    0x24, 0x48, 0x6E, 0x56, 0x87, 0x62, 0x5A, 0xBD,
    0xBF, 0x17, 0xD9, 0xA2, 0xC4, 0x17, 0x1A, 0x01,
    0x94, 0xED, 0x8F, 0x1E, 0x11, 0xB3, 0xD7, 0x09,
    0x0C, 0xB6, 0xE9, 0x10, 0x6F, 0x22, 0xEE, 0x13,
    0xCA, 0xB3, 0x07, 0x05, 0x76, 0xC9, 0xFA, 0x31,
    0x6C, 0x08, 0x34, 0xFF, 0x8D, 0xC2, 0x6C, 0x38,
    0x00, 0x43, 0xE9, 0x54, 0x97, 0xAF, 0x50, 0x4B,
    0xD1, 0x41, 0xBA, 0x95, 0x31, 0x5A, 0x0B, 0x97
};

static const unsigned char base64_test_enc[] =
    "JEhuVodiWr2/F9mixBcaAZTtjx4Rs9cJDLbpEG8i7hPK"
    "swcFdsn6MWwINP+Nwmw4AEPpVJevUEvRQbqVMVoLlw==";

// Checkup routine 
int base64_self_test( int verbose )
{
    size_t len;
    const unsigned char *src;
    unsigned char buffer[128];

    if( verbose != 0 )
        polarssl_printf( "  Base64 encoding test: " );

    len = sizeof( buffer );
    src = base64_test_dec;

    if( base64_encode( buffer, &len, src, 64 ) != 0 ||
         memcmp( base64_test_enc, buffer, 88 ) != 0 )
    {
        if( verbose != 0 )
            polarssl_printf( "failed\n" );

        return( 1 );
    }

    if( verbose != 0 )
        polarssl_printf( "passed\n  Base64 decoding test: " );

    len = sizeof( buffer );
    src = base64_test_enc;

    if( base64_decode( buffer, &len, src, 88 ) != 0 ||
         memcmp( base64_test_dec, buffer, 64 ) != 0 )
    {
        if( verbose != 0 )
            polarssl_printf( "failed\n" );

        return( 1 );
    }

    if( verbose != 0 )
        polarssl_printf( "passed\n\n" );

    return( 0 );
}
*/

//#include <ctype.h>

/* Function: urlDecode */
char *urlDecode(const char *str) {
  int d = 0; /* whether or not the string is decoded */

  char *dStr = malloc(strlen(str) + 1);
  char eStr[] = "00"; /* for a hex code */

  strcpy(dStr, str);

  while(!d) {
    d = 1;
    int i; /* the counter for the string */

    for(i=0;i<strlen(dStr);++i) {

      if(dStr[i] == '%') {
        if(dStr[i+1] == 0)
          return dStr;

        if(isxdigit(dStr[i+1]) && isxdigit(dStr[i+2])) {

          d = 0;

          /* combine the next to numbers into one */
          eStr[0] = dStr[i+1];
          eStr[1] = dStr[i+2];

          /* convert it to decimal */
          long int x = strtol(eStr, NULL, 16);

          /* remove the hex */
          memmove(&dStr[i+1], &dStr[i+3], strlen(&dStr[i+3])+1);

          dStr[i] = x;
        }
      }
    }
  }

  return dStr;
}


/*
void main(){
	unsigned char input[64]="huazhenjiang@gmail.com;12345678";//{0,10,2,23,22,35,12,8,9,1};//
	unsigned char decode[64]="aHVhemhlbmppYW5nQGdtYWlsLmNvbTsxMjM0NTY3OA==";
	unsigned char url_test[64]="id=huazhenjiang%40gmail.com&pwd=12345678";
	char buf[256];
	char temp_id[64],temp_pwd[64];
	size_t len=0;
	int ret=0;
	char *head, *tail;
	FILE *fp;
	char file_buf[256];
	const char *header="Basic 123312441sfdsff";
	char *code;
	
	//memcpy(buf, header,strlen(header));
	//printf("\r\n%s", buf);
	//code = strstr(buf,"Basic ");
	code = strstr(header,"Basic ");
	printf("\r\ncode:%s", (char *)(code+ strlen("Basic ")));
	
	fp=fopen("D:\\Code_example\\base64_encode_decode\\authfile.txt","r");
	if(fp == NULL){
		printf("\r\nOpen file error.");
	}
	memset(file_buf,0,sizeof(file_buf));
	
	fread(file_buf,sizeof(char),256,fp);
	fclose(fp);
	printf("\r\nfile_buff:%s",file_buf); 
	
	len=sizeof(buf);
	ret=base64_encode(buf, &len,file_buf,strlen(file_buf));
	printf("\r\nret:%d",ret);
	if(buf[0]!='\0')
	   printf("\r\n(len:%d)%s",len,buf);	
	
	len=0;
		
	memset(buf,0,sizeof(buf));
	memset(temp_id,0,sizeof(temp_id));
	memset(temp_pwd,0,sizeof(temp_pwd));
	len=sizeof(buf);
	ret=base64_encode(buf, &len,input,strlen(input));
	printf("\r\nret:%d",ret);
	if(buf[0]!='\0')
	   printf("\r\n(len:%d)%s",len,buf);
	   
	memset(buf,0,sizeof(buf));
	len=sizeof(buf);
	ret=base64_decode(buf, &len,decode,strlen(decode));
	printf("\r\nret:%d",ret);
	if(buf[0]!='\0')
	   printf("\r\n(len:%d)%s",len,buf);	   
	
	printf("\r\n%s",urlDecode(url_test));
	memset(buf,0,sizeof(buf));
	strcpy(buf, url_test);
	if(buf[0]!='\0'){
		len=strlen(buf);
		printf("\r\n(len:%d)%s",len,buf);
		head=strstr(buf,"id=");
		tail=strstr(buf,"&pwd");
		strncpy(temp_id,&buf[strlen("id=")],tail-head-strlen("id="));
		printf("\r\ntemp_id:%s",temp_id);
		strncpy(temp_pwd, (tail+strlen("&pwd=")), &(buf[len])-tail-strlen("&pwd="));
		printf("\r\ntemp_pwd:%s",temp_pwd);		
		strcat(temp_id,";");
		strcat(temp_id,temp_pwd);
		
		printf("\r\ntemp_id:%s",temp_id);
	} 
	
}
*/

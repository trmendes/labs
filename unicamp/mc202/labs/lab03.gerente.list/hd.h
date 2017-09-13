#ifndef __HD_H__
#define __HD_H__

#define NAMELEN          10
#define FMAXSIZE         127875000000
#define HDBLOCKSIZE      8

#define PRINTBLOCK       8

#define ERR_NO_HD       -1
#define ERR_FILE_EXIST  -2
#define ERR_HD_EXIST    -3
#define ERR_FILE_NAME   -4
#define ERR_FILE_MALLOC -5
#define ERR_NO_SPACE    -6
#define ERR_FILE_TO_BIG -7
#define SUCCESS          0
#define EMPTY_HD         1
#define FILE_NOT_FOUND   2
#define HD_OPTMIZED      3

typedef struct sfile {
    char           name[NAMELEN];
    long           addr;
    long           size;
    struct sfile  *next;
} file;

typedef struct shd {
    long       size;
    long       free;
    file      *ftable;
} hd;

hd   * hd_create_part (long _psize);
int    hd_insert_file (hd *_hd, char *_name, long _fsize);
int    hd_remove_file (hd *_hd, char *_name);
int    hd_optimize    (hd *_hd);
int    hd_destroy     (hd **_hd);
file * hd_find_file   (hd *_hd, char *_name);
void   hd_free        (hd *_hd);
void   hd_ls          (hd *_hd);
void   hd_print_out   (hd *_hd);

#endif

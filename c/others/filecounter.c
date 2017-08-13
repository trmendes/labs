#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

/* We are going to suppose that there is no more than 30 different words in the text
   To do a better version of this software we should user a list instead of an array */
#define DICSIZE 30

/* We are assuming that a single word is no longer than 100 chars */
#define WORDSIZE 20
#define USED 1
#define NUSED 0

#define SPACE ' '
#define NLINE '\n'
#define EOS   '\0'

typedef struct {
    char word[WORDSIZE];
    uint freq;
    uint used; /* If is markes as not used it means
		  there is no words further */
} sword;

int add_dic();
void upd_freq();

int main(int argc, char **argv) {
    uint i = 0, iw = 0, jw = 0, bcounter = 0;
    int search_res = 0;
    FILE *fd = NULL;
    char *fname = "file.txt", c, wordn[WORDSIZE], nextw[WORDSIZE];
    sword dic[DICSIZE];
    memset(dic, 0x00, sizeof(dic));
    memset(nextw, 0x00, sizeof(nextw));

    printf("Max # of different words this software will analyze: %d\n",DICSIZE);
    printf("Max size of a word is: %d\n",WORDSIZE);

    fd = fopen(fname, "r");
    if (fd == NULL) {
	fprintf(stderr, "Can't open input file\n");
	exit(1);
    }

    while ( (c = fgetc(fd)) != EOF) {
	bcounter++;
	if (c == SPACE || c == NLINE) {
	    wordn[iw] = EOS;
	    if (add_dic(dic, wordn) == 1) {
		while ( (c = fgetc(fd)) != EOF) {
		    if (c == SPACE || c == NLINE) {
			nextw[jw] = EOS;
			if (add_dic(dic,nextw) == 0) {
			    upd_freq(dic, nextw);
			}
			jw=0;
		    } else {
			if (jw > WORDSIZE) {
			    printf("There is a word bigger than %d in this file so we can't handle it.\n",WORDSIZE);
			    printf("-- word: %s\n",nextw);
			    exit(1);
			} else {
			    nextw[jw++] = c;
			}
		    }
		}
		if (fseek(fd, bcounter, SEEK_SET) == -1) {
		    fprintf(stderr, "Error setting the file position\n");
		    exit(1);
		}
	    }
	    iw=jw=0;
	} else {
	    if (iw > WORDSIZE) {
		printf("There is a word bigger than %d in this file so we can't handle it.\n", WORDSIZE);
		printf("- word: %s\n", wordn);
		exit(1);
	    } else {
		wordn[iw++] = c;
	    }
	}
    }

    printf("\n---- List ----\n");
    for (i = 0; i < DICSIZE; i++) {
	if (dic[i].used == USED) {
	    printf("* %s \t\t %d\n",dic[i].word,dic[i].freq);
	} else {
	    break;
	}
    }
    printf("---- List ----\n");
    printf("%d different words found.\n",i);
    return 0;
}

/* pdic = dictonary
   word = word to add
   */
int add_dic(sword * pdic, char *word) {
    int i;
    for (i = 0 ; i < DICSIZE ; i++) {
	if (pdic[i].used == USED) {
	    if (strcmp(pdic[i].word, word) == 0) {
		return 0;
	    }
	} else {
	    strcpy(pdic[i].word, word);
	    pdic[i].freq = 1;
	    pdic[i].used = USED;
	    return 1;
	}
    }
    return 0;
}

void upd_freq(sword *pdic, char *wnew) {
    int i;
    for (i = 0; i < DICSIZE; i++) {
	if (pdic[i].used == USED) {
	    if (strcmp(pdic[i].word, wnew) == 0) {
		pdic[i].freq++;
		break;
	    }
	} else {
	    break;
	}
    }
}

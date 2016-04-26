/*
 * split_path.c
 *
 *  Created on: Apr 22, 2015
 *  Author: Nick Pershin
 *
 *  Last edited on: Apr 22, 2015
 *  Editor: Nick Pershin
 *
 * 
 * BUILD DEBUG:
 *      gcc -std=c99 -I../.. -Wall -g -o split_path split_path.c
 * BUILD RELEASE:
 *      gcc -std=c99 -I../.. -Wall -O3 -o split_path split_path.c
 *
 * RUN: 
 *      ./split_path
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void split_path_file(char** p, char** f, char *pf) 
{
    // If pf == slash, then there is no directory component
    char *slash = pf, *next;
    while ((next = strpbrk(slash + 1, "\\/"))) slash = next;
    if (pf != slash) slash++;
    *p = strndup(pf, slash - pf);
    *f = strdup(slash);
}
*/

void split_path_file(char **p, char **f, char *pf) 
{
    // find the last delimiter
    char *z;
    for (z = pf+strlen(pf); z >= pf; z--) {
        if (*z == '/' || *z == '\\')
            break;
    }

    if (z >= pf) {
        // there is a delimiter: construct separate fragments for path and filename
        //printf("\t--> %li\n", z-pf);
        *p = malloc(z-pf+1);
        strncpy(*p, pf, z-pf);
        (*p)[z-pf] = '\0';
        *f = malloc(strlen(z));
        strcpy(*f, z+1);
    } else {
        // there is no delimiter: the entire string must be a filename
        *p = NULL;
        *f = malloc(strlen(pf)+1);
        strcpy(*f, pf);
    }
}


int main(int argc, char **argv)
{
    //char *path = "/bin/dubin/mkdir";
    //char *path = "output_data/TEST/Unzipped_Content/Организ.\\ пр-ва\\ на\\ предпр.\\ ЖКХ\\ РП.docx";
    char *path = "output_data/TEST/Unzipped_Content/Организ. пр-ва на предпр. ЖКХ РП.docx";
    //char *path = "Организ. пр-ва на предпр. ЖКХ РП.docx";
    char *p, *f;

    int len = strlen(path);
    printf("\n\tINPUT: [%s] (length: %d)\n\n", path, len);

    split_path_file(&p, &f, path);

    if(p != NULL) {
        len = strlen(p);
        printf("\tPATH: [%s] (length: %d)\n\n", p, len);
    } else {
        printf("\tPATH: NULL\n\n");
    }
    len = strlen(f);
    printf("\tFILE: [%s] (length: %d)\n\n", f, len);

    return 0;
}


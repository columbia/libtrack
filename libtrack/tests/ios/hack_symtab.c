/* hack_dysyms.c
 * 
 * Copyright (C) 2014 Vaggelis Atlidakis <vatlidak@cs.columbia.edu>
 *
 * Hide (obfuscate) selected exported symbols of a dynamic library so that they
 * are not visible to the dynamic linker / loader. The dynamic linker ignores
 * visibility of exported symbols and can link even to local symbols. We
 * manuever this by locating each symbol in the lazy binding info section and
 * modifying its name to a non-existing value. In that way, selected symbols
 * are invisible to dynamic linker / loader
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mach-o/loader.h>

#define MAXLEN 128
#define MAXSYMS 8192

int main(int argc, char **argv)
{
    int i, j, n_syms, n_found;
    long fsize;

    struct dyld_info_command *dyld_info;
    struct load_command *lc;
    struct mach_header_64 *header;

    void *obj, *p_obj;
    char *fname_bin, *fname_syms;
    char sym[MAXLEN];
    char *syms[MAXSYMS];
    
    FILE *fp_bin, *fp_syms;
    

    if (argc != 3 ){
        fprintf(stderr, "Usage: %s <binary name> <symbols file>\n", *argv);
        return -1;
    }
    fname_bin = argv[1];
    fname_syms = argv[2];

    /* load file into memory */
    if ((fp_bin=fopen(fname_bin, "r")) == NULL
        || (fp_syms=fopen(fname_syms, "r")) == NULL)
    {
        perror("fopen");
        return -1;
    }

    /* Get binary file size */
    fseek(fp_bin, 0, SEEK_END);
    fsize = ftell(fp_bin);
    fseek(fp_bin, 0, SEEK_SET);
    
    /* Load binary file in mem */
    if ((obj= malloc(fsize)) == NULL ){
        perror("malloc");
        return -1;
    }
    if ( fread(obj, 1, fsize, fp_bin) != fsize ){
        perror("fread");
        return -1;
    }

    /* Load symbol names in mem */
    n_syms = 0;
    while ( !feof(fp_syms) ){
        fscanf(fp_syms, "%s\n", sym);
        syms[n_syms] = malloc(strlen(sym) + 1);
        strncpy(syms[n_syms], sym, strlen(sym));
        ++n_syms;
    }
    fclose(fp_bin);
    fclose(fp_syms);
 
    /* Get header */
    header = (struct mach_header_64 *)obj;
    
    /* Advance pointer after header*/
    p_obj = obj;
    p_obj += sizeof (struct mach_header_64);
 
    /* Parse load commands */
    n_found = 0;
    for (i = 0; i < header->ncmds; ++i){
        lc = (struct load_command *)p_obj;
        if ( lc->cmd == LC_DYLD_INFO || lc->cmd == LC_DYLD_INFO_ONLY){
            dyld_info = (struct dyld_info_command *)(p_obj);
            for (j = 0; j < n_syms; j++){
                for (i = 0; i < dyld_info->export_size; i++){
                    char *p=((char *)(obj + dyld_info->export_off) + i);
                    if ( !strncmp(p, syms[j], strlen(syms[j])) ){
                        memset(p, (char)255, strlen(syms[j]));
                        ++n_found;
                    }
                }
            }
            break;
        }
        p_obj += lc->cmdsize; 
    } 

    /* If any symbols is found update binary */
    if ( n_found ){
        printf("Updating binary file\n");
        printf("Going to obfuscate: %d exported symbol names\n", n_found);
        if ( (fp_bin=fopen(fname_bin, "r+")) == NULL)
        {
            perror("fopen");
            return -1;
        }
        fwrite(obj, 1, fsize, fp_bin);
        fclose(fp_bin);
    }
    else
        printf("No exported symbol name found\n");

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include "pdf2yaml.h"

static void help(void);
static void help(void) {
        puts("template for reweight module");
        exit(0);
}

int reweight(int argc,char* argv[]) {
        if( argc==0 || !strcmp(argv[0],"--help")) help();

        int i, ix, iq, ifl; // counters and dummy vars
        char *in_path=argv[0];
        char *out_path=argv[1];

        PdfSet pdf_set;
        if(load_lhapdf6_set(&pdf_set, in_path)) return 1;
        
        // over all x, q, pdfs_flavours
        for(i=1; i<pdf_set.n_members; i++) 
        for(ix=0; ix<pdf_set.members[i].nx; ix++) 
        for(iq=0; iq<pdf_set.members[i].nq; iq++) 
        for(ifl=0; ifl<pdf_set.members[i].n_pdf_flavours; ifl++) {
                //pdf_set.members[i].val[ix][iq][ifl]= ...
        }

        //update info
        Info_Node *node=info_node_where(pdf_set.info, "SetDesc");
        char *desc=malloc(strlen(node->value.string)+100);
        sprintf(desc, "%s\n%s", node->value.string, "reweighted" );
        info_node_update_str(node, desc);

        save_lhapdf6_set(&pdf_set, out_path);
        pdf_set_free(&pdf_set);
        free(desc);


        return 0;
}

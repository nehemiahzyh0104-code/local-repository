#include <stdio.h>

void
oprt (unsigned int opcode, unsigned int r1, unsigned int r2, unsigned int imm)
{
    static short rgst[6]={0};

    if(opcode==0b000){
        rgst[r1]+=rgst[r2];
    }
    else if(opcode==0b001){
        rgst[r1]-=rgst[r2];
    }
    else if(opcode==0b010){
        rgst[r1]*=rgst[r2];
    }
    else if(opcode==0b011){
        rgst[r1]/=rgst[r2];
    }
    else if (opcode==0b100){
        rgst[r1]=imm;
    }
    else if (opcode==0b101){
        printf("x%d = %d\n",r1,rgst[r1]);
    }

    rgst[0]=0;
}

int
main ()
{
    int n;
    scanf ("%d", &n);
    for (int i = 0; i < n; i++)
        {
            unsigned int inpt = 0;
            scanf ("%i", &inpt);
            
            unsigned int opcode = (inpt >> 13) & 0x7;
            unsigned int r1 = (inpt >> 10) & 0x7;
            unsigned int r2 = (inpt >> 7) & 0x7;
            unsigned int imm = inpt & 0x7F;
            
            oprt (opcode, r1, r2, imm);
        }

    return 0;
}

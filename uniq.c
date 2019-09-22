#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1024];
char lines[1024] [1024];

int cFlag, dFlag, iFlag;

int 
caseInsentiveCmp(const char * p, const char *q){
//printf(1,"%d",('N'-'n'));
int diff =0;

//printf(1,"%d",x);
if(strcmp(p,q)==0){
	return 0;
}
if(strlen(p) != strlen(q)){
	return 1;
}
while(*p && *q){
	//printf(1,"%s %c %c","comparing",*p,*q);
	if(((uchar)*p-(uchar)*q)!=0 && (((uchar)*p - (uchar)*q)!=32 && ((uchar)*p - (uchar)*q)!=-32)){
		diff =1;
		//printf(1,"enter diff");
		break;
	}
	p++, q++;
	//printf(1,"%c %c", *p,*q);
}
//printf(1,"%s %d","returning ",(uchar)*p - (uchar)*q)
	return diff;
}


void
uniq(int fd)
{
int newline=0;
int charNum=0;
int occurance=1;
int n;
int dup=0;
//read from file
while((n = read(fd, buf, sizeof(buf))) > 0){
	//write file to a 2-d array
	for(int count=0;count<n;count++){
		if(buf[count]=='\n'){
			if(iFlag ==0){
			dup = strcmp(lines[newline-1],lines[newline]);
			}else if(iFlag ==1){
			//printf(1,lines[newline-1]);
			dup = caseInsentiveCmp(lines[newline-1],lines[newline]);
			}
    		if(newline>=1 &&dup!=0){
    			if(dFlag==0){
    				if(cFlag==1){
    					printf(1,"%d %c",occurance,' ');
    				}
    				
    				printf(1,lines[newline-1]);
    				printf(1,"%c",'\n');
    			}else{
    				if(occurance>1){
    					if(cFlag ==1){
    						printf(1,"%d %c",occurance,' ');
    					}
    					printf(1,lines[newline-1]);
    					printf(1,"%c",'\n');
    				}
    			}
    			occurance=1;
    		}
    		else{
    			if(newline>=1){
    				occurance++;
    			}
    		}

    		
  			newline++;
  			charNum =0;			
  		
  		}
  		else{
			lines[newline][charNum]=buf[count];
			charNum++;

		}
 
	}

if(iFlag ==0){
dup = strcmp(lines[newline-1],lines[newline]);
}else if(iFlag ==1){
dup = caseInsentiveCmp(lines[newline-1],lines[newline]);

}	
if(dup!=0){
	if(dFlag==0){
	if(cFlag ==1){
	printf(1,"%d %c",occurance, ' ');
	}
	printf(1,lines[newline-1]);
	printf(1,"%c",'\n');
	if(cFlag ==1){
	printf(1,"%d %c",1,' ');
	}
	printf(1,lines[newline]);
	//printf(1,"%c",'\n');
	}
	else{
	if(occurance>1){
		if(cFlag==1){
			printf(1,"%d %c",occurance, ' ');
		}
		printf(1,lines[newline-1]);
		//printf(1,"%c",'\n');
	}
	}
}
else{
	occurance++;
	if(cFlag==1){
		printf(1,"%d %c",occurance,' ');
	}		
	printf(1,lines[newline-1]);
}

}
if(n < 0){
	printf(1, "uniq: read error\n");
	exit();
}

exit();
}


int
main(int argc, char *argv[])
{
int fd, i;
int pipeC,pipeD,pipeI;

//exit when there is no other arguments
if(argc <= 1){
	uniq(0);
	exit();
}

for(i = 1; i < argc; i++){
  	switch(argv[i][1]){
  		case 'c':
  			cFlag=1;
  			break;
  		case 'd':
  			dFlag=1;
  			break;
  		case 'i':
  			iFlag=1;
  			break;
  	}
 }
if(cFlag==1 &&dFlag ==1){
  	printf(1,"uniq:cannot open -c -d at the same time\n");
  	exit();
}

pipeC = strcmp(argv[(argc-1)],"-c");
pipeD = strcmp(argv[(argc-1)],"-d");
pipeI = strcmp(argv[(argc-1)],"-i");

//exit when file cannot be opened
if(pipeC == 0 || pipeD == 0 || pipeI == 0){
  	uniq(0);
}
else if((fd = open(argv[(argc)-1], 0)) < 0){
    printf(1, "uniq: cannot open %s\n", argv[i]);
    exit();
}
    //call uniq to read from stdin/file and remove adjacent dup lines
uniq(fd);
close(fd);

exit();
}

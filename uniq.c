#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char lines[512] [512];

/*Function:uniq
 *Read from stdin/file and remove adjacent duplicate lines
 */
void
uniq(int fd)
{
	printf(1,"enter uniq\n");
	

	int newline=0;
	int charNum=0;
	//char curr[512];
	//char prev[512];
	//char line[512];
    int n;
  while((n = read(fd, buf, sizeof(buf))) > 0){
  	
  	for(int count=0;count<n;count++,charNum++){
  		
  		if(buf[count]=='\n' || buf[count]=='\0'){
  			if(newline<1){
  				if (write(1, lines[newline], n) != n) {
      				printf(1, "cat: write error\n");
      				exit();
    			}
    		}
    		else{ 				

  				//printf(1,"entered");
  				if(strcmp(lines[newline-1],lines[newline]) !=0){
  					if (write(1, lines[newline], n) != n) {
      					printf(1, "cat: write error\n");
      					exit();
    				}
  				}
  			}
  			newline++;
  			//printf(1,"%d",newline);
  			charNum =0;
  			
  		}

  		lines[newline][charNum]=buf[count];
	}
	
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }


exit();
}


int
main(int argc, char *argv[])
{
  int fd, i;

//exit when there is no other arguments
  if(argc <= 1){
    uniq(0);
    exit();
  }

  for(i = 1; i < argc; i++){
  	//exit when file cannot be opened 
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[i]);
      exit();
    }
    //call uniq to read from stdin/file and remove adjacent dup lines
    uniq(fd);
    close(fd);
  }

  exit();
}

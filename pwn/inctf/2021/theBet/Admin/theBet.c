#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<seccomp.h>
#include<unistd.h>
#include<errno.h>
#include<sys/prctl.h>
#include <sys/mman.h>

// gcc theBet.c -Wl,-z,relro,-z,now -fno-stack-protector -no-pie -z execstack -o theBet -lseccomp
int len=0;
int i, j;
char bad_chars[15] = {'\x0d', '\x50', '\x2e', '\xbb', '\xb0', '\x83', '\xf6', '\x10', '\xaa', '\xd2', '\x98', '\x99', '\x30', '\x31'};
void __register_tm(){
asm("jmp %rsp");
}

void initialize()
{
	setvbuf(stdin,0,2,0);
	setvbuf(stdout,0,2,0);
	setvbuf(stderr,0,2,0);
	alarm(60);
}


void setup_seccomp(){
scmp_filter_ctx ctx;
ctx = seccomp_init(SCMP_ACT_KILL);
int ret = 0;

ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(lseek), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execveat), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(writev), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(kill), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getuid), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getgid), 0);
ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
ret |= seccomp_load(ctx);

  if (ret) {
    exit(1);
  }
}


void Capital_Punishment(){
char description[30];

puts("Describe your argument: ");

len = read(0, description, 100);

for(i = 0; i<len; i++){
for(j = 0; j<14; j++){
if(description[i] == bad_chars[j]){
puts("\nI'm sorry you lost! You will be imprisoned for life.. :(\n");
exit(0);
}
}
}

}

void Life_Imprisonment(){
char description[30];

puts("Describe your argument: ");

len = read(0, description, 100);

for(i = 0; i<len; i++){
for(j = 0; j<14; j++){
if(description[i] == bad_chars[j]){
puts("\nI'm sorry you lost! You will be executed.. :(\n");
exit(0);
}
}
}

}

int main(){

char name[10];
char choice;
initialize();
puts("Welcome to the Bet! You are standing among the world's best lawyers, politicians and criminals. \n\nYou approach a young lawyer not more than 24 years of age. As you converse with him, you come to know about his reputation. The next moment you know, you find yourself debating which is better - Capital Punishment or Life Imprisonment. \n\nYou are of the opinion that Capital Punishment is better as a quick death would mean less pain as compared to life of solitude in the cell. Your friend believes otherwise. \n\nYou both decide on writing down your views and handing them over to a third party, (a criminal) so as to decide who's opinion is correct. \n\nThe criminal however states that the one who loses the debate shall either face Capital Punishment or Life Imprisonment depending on what the winning party chooses. \n\nGive us your name: ");
fgets(name, 11, stdin);
puts("\n1. Capital Punishment\n2. Life Imprisonment\nYour choice: ");

scanf("%c", &choice);
getchar();


if(choice == '1'){
Capital_Punishment(bad_chars);
}else if(choice == '2'){
Life_Imprisonment(bad_chars);
}else{
puts("That is not a valid choice\n");
exit(0);
}

setup_seccomp();
return 0;
}


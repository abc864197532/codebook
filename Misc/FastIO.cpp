#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline int Rneg(){static char c;int a,f=1;while((c=RC())<'0')if(c=='-')f=-1;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a*f;}
inline long long Rll(){static char c;long long a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline long long Rllneg(){static char c;long long a,f=1;while((c=RC())<'0')if(c=='-')f=-1;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a*f;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65520)write(1,OB,OP),OP=0;}
inline void Wneg(int n){static char buf[12],p;if(n<0)OB[OP++]='-',n=-n;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65520)write(1,OB,OP),OP=0;}
inline void Wll(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65520)write(1,OB,OP),OP=0;}
inline void Wllneg(long long n){static char buf[20],p;if(n<0)OB[OP++]='-',n=-n;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65520)write(1,OB,OP),OP=0;}

write(1,OB,OP);
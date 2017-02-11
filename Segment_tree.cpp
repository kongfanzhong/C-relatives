//poj 1177

//Problem description: http://poj.org/problem?id=1177
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;
int size=0,n; 
struct tnodex{
       int l,r,mark,key;
}heng[10005];
struct tnodey{
       int l,r,mark,key;
}str[10005];
struct tnodetree{
       int l,r,len,cover;
}tree[500005];
void add(int x1,int y1,int x2,int y2){
     size++;
     heng[size].key=y1;heng[size].l=x1;heng[size].r=x2;heng[size].mark=1;
     str[size].key=x1;str[size].l=y1;str[size].r=y2;str[size].mark=1;
     size++;
     heng[size].key=y2;heng[size].l=x1;heng[size].r=x2;heng[size].mark=0;
     str[size].key=x2;str[size].l=y1;str[size].r=y2;str[size].mark=0;
}
bool cmp1(tnodex x,tnodex y){
     if (x.key<y.key) return 1;
     return 0;
}
bool cmp2(tnodey x,tnodey y){
     if (x.key<y.key) return 1;
     return 0;
}
#define lc(x)  x<<1
#define rc(x) (x<<1)+1
void build (int x,int l,int r){
     tree[x].l=l;tree[x].r=r;tree[x].cover=0;tree[x].len=0;
     if (l<r-1) {int mid=(l+r)/2;
        build(lc(x),l,mid);
        build(rc(x),mid,r);
     } 
}long long ans=0;
void insert(int x,int l,int r){
     int ll=tree[x].l,rr=tree[x].r;int mid=(ll+rr)/2;
     if (l<=ll&&rr<=r) {
        tree[x].cover++;tree[x].len=r-l;
     }
     else if (rr-1==ll) return;
     else {
          if (r<=mid) insert(lc(x),l,r);
          else if (l>=mid) insert(rc(x),l,r);
          else {insert(lc(x),l,mid),insert(rc(x),mid,r);}
          if (!tree[x].cover) tree[x].len=tree[lc(x)].len+tree[rc(x)].len;
     }
}
void delete_tree(int x,int l,int r){
     int ll=tree[x].l,rr=tree[x].r;int mid=(ll+rr)/2;
     if (l<=ll&&rr<=r) {
        tree[x].cover--;
        if (!tree[x].cover) tree[x].len=tree[lc(x)].len+tree[rc(x)].len;
     }  
     else if (ll==rr-1) return ;
     else {
          if (r<=mid) delete_tree(lc(x),l,r);
          else if (l>=mid) delete_tree(rc(x),l,r);
          else {delete_tree(lc(x),l,mid),delete_tree(rc(x),mid,r);}
          if (!tree[x].cover) tree[x].len=tree[(lc(x))].len+tree[rc(x)].len;
     }   
}
void work(){
     sort(heng+1,heng+1+2*n,cmp1);
     sort(str+1,str+1+2*n,cmp2);
     build(1,-10000,10000);int old=0,newk=0;
     for (int i=1;i<=2*n;i++) {
         if (heng[i].mark) insert(1,heng[i].l,heng[i].r);
         else delete_tree(1,heng[i].l,heng[i].r);
         newk=tree[1].len;
         ans+=abs(newk-old);old=newk;
     }
     build(1,-10000,10000);old=0;newk=0;
     for (int i=1;i<=2*n;i++) {
         if (str[i].mark) insert(1,str[i].l,str[i].r);
         else delete_tree(1,str[i].l,str[i].r);
         newk=tree[1].len;
         ans+=abs(newk-old);old=newk;
     }
}
int main(){
    int i,j,k;
//    freopen("1.in","r",stdin);
//    freopen("1.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<=n;i++) {int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        add(x1,y1,x2,y2);
    }
    work();
    printf("%I64d\n",ans);
    return 0;
}

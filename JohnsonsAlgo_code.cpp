#include<bits/stdc++.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define ll long long int
#define pb push_back
#define pf push_front
#define mp make_pair
#define endl  "\n"
#define power(a, b) (double)pow((double)a, (double)b)
#define FOR(i, n) for (lint i = 0; i < n; i++)
// ll ans1[1000005],back[1000005];
ll num1;
//code goes here
//dijkstra implementation using the array//part 1
void dijkstra_array(vector<pair<ll,ll>>arr[],ll s,ll n,vector<pair<ll,ll>>final[])
{
    ll visited[n+1]={0};
    ll tot1=0;
    ll dist[n+1];//initialising with inf
    for(ll i=0;i<=n;i++)
    {
    dist[i]=1e12;
    visited[i]=0;
    }
    dist[s]=0;
    visited[s]++;
    int flag=0;
    ll size1=1;
    while(size1>0)
    {
        ll min1,min2;
        min2=1e13;
        for(ll i=1;i<=n;i++)
        {
            if(visited[i]>0)
            {
                if(dist[i]<min2)
                {
                    min2=dist[i];
                    min1=i;
                }
            }
        }
        visited[min1]=0;
        for(auto it=arr[min1].begin();it!=arr[min1].end();it++)
        {
            ll v1=it->first;
            ll v2=it->second;
            if(v2<0)
            {
                flag=1;
                break;
            }
            else
            {
                if(dist[v1]>dist[min1]+v2)
                {
                    dist[v1]=dist[min1]+v2;
                    visited[v1]++;
                }
            }
        }
        if(flag==1)
        break;
        size1=0;
        for(ll i=1;i<=n;i++)
        {
            if(visited[i]>0)
            size1++;
        }
    }
    if(flag==1)
    cout<<"-1"<<endl;
    else
    {
        for(ll i=1;i<=n;i++)
        {
            if(dist[i]>1e9)
            final[s].push_back(make_pair(i,999999));
            else
            final[s].push_back(make_pair(i,dist[i]));
        }
    }
    return;
}
long long int heaplen;
const long long INF = 1000000000000000000;
const long long INF1 = 1000000000;
const long long MOD = 1000000007;
// const long long MOD = 998244353;
#define ss second
#define ff first
//binary heap property to access the left right child and parent
ll pare(ll a1)
{
    ll d1=(a1-1)/2;
    return d1;
}
ll le(ll a1)
{
    ll d1=2*a1+1;
    return d1;
}
ll rg(ll a1)
{
    ll d1=2*a1+2;
    return d1;
}
//function to insert a node in binary
//binheaplen gives the current heapsize
//binarr[] is a pair which stores the value and its source in an array format at the ith position
void insert_binary(ll val,ll source,ll &binheaplen,pair<ll,ll>binarr[])
{
    binheaplen++;//incrementing the lenght
    //inserting the new node at the last and then percolating up
    //heap property
    ll a1=binheaplen-1;
    ll f1=0;
    //giving the values
    binarr[a1].first=val;
    binarr[a1].second=source;
    while(1)
    {
        ll com1=binarr[pare(a1)].first;
        ll com2=binarr[a1].first;
        if(a1!=0&&com1>com2)
        {
        swap(binarr[a1],binarr[pare(a1)]);//swap the postions(pairs)
        a1=pare(a1);
        f1++;
        }
        else
        break;
    }
}
//function to find the min in the binary heap
void min_bin(ll a1,ll &binheaplen,pair<ll,ll> binarr[])
{
    ll totn=binheaplen;
    ll t1=le(a1);//get the left child value
    ll t2=rg(a1);//get the right child value
    ll t3=a1;
    ll flag=0;
    //required conditions
    //updating the min
    if(binheaplen>t1&&binarr[t1].first<binarr[a1].first)//comparing with size as well as the value in a1th postion
    t3=t1;
    //now comparing with t2
    if(binheaplen>t2&&binarr[t2].first<binarr[t3].first)
    t3=t2;
    //if t3!=a1 then swap
    if(t3!=a1)
    {
        flag=1;
        //calling the swap function which interchanges the pair
        swap(binarr[a1],binarr[t3]);
        //now calling the same function again for t3
        min_bin(t3,binheaplen,binarr);//recursive calling
    }
}
//function for extract min in binary
ll extractmin_binar(ll &binheaplen,pair<ll,ll> binarr[])
{
    //if no nodes in the heap return -1;
    if(binheaplen<=0)
    return -1;
    //if one node 
    if(binheaplen==1)
    {
        //decrementing the heap
        binheaplen--;
        return binarr[0].second;
    }
    //r1 mein min value store hoga pair wala
    ll r1=binarr[0].second;
    //changes after removing 
    binarr[0]=binarr[binheaplen-1];
    binheaplen--;
    min_bin(0,binheaplen,binarr);
    return r1;
}
//running dijkstra using binary heaps
void dijkstra_binary(vector<pair<ll,ll>>arr[],ll s,ll n, vector<pair<ll,ll>>final[])
{
    ll dist[n+1];//initialising with inf
    for(ll i=0;i<=n;i++)
    dist[i]=1e12;
    dist[s]=0;
    //ll binarr[n+1];
    pair<ll,ll>binarr[100005];//declaring the pair
    ll binheaplen=0;//heaplength
    //calling the insert function
    insert_binary(dist[s],s,binheaplen,binarr);
    int flag=0;
    //ll cnt1=0;
    while(binheaplen>0)
    {
        //cnt1++;
       // struct node* temp=findmin(build_heap);
       // ll min1=temp->source;
       ll min1=extractmin_binar(binheaplen,binarr);
       if(min1==-1)
       break;
       //ie no node cannot be formed
        //cout<<cnt1<<endl;
        //vector<node*>build_heap1=extractmin(build_heap);
       // build_heap=build_heap1;
        for(auto it=arr[min1].begin();it!=arr[min1].end();it++)
        {
            ll v1=it->first;
            ll v2=it->second;
            if(v2<0)
            {
                flag=1;
                break;
            }
            else
            {
                if(dist[v1]>dist[min1]+v2)
                {
                    dist[v1]=dist[min1]+v2;
                    //build_heap=add1_bino(build_heap,v1,dist[v1]);
                    //store1.push(make_pair(dist[v1],v1));
                    insert_binary(dist[v1],v1,binheaplen,binarr);
                }
            }
        }
        if(flag==1)
        break;
    }
    if(flag==1)
    cout<<"-1"<<endl;
    else
    {
        for(ll i=1;i<=n;i++)
        {
            if(dist[i]>1e9)
            final[s].push_back(make_pair(i,999999));
            else
            final[s].push_back(make_pair(i,dist[i]));
        }
    }
    return;
}

//creating structure for binomial heaps
struct node
{
    //variables invoved in the binary heaps corresponding to each node
    ll val;//to store the value
    node* par;//for parent
    node* child;//for child
    node* sib;//for sibling
    ll source;//for knowing the source of this value
    ll deg;//for updating the degree  of the binomial heap
};

//function to merge the heaps
struct node* merge(struct node* node1,struct node* node2)
{
    //if the value at node1>node2 then swap
    ll flag=0;
    node* a12=node1;
    node* a21=node2;
    if(node1==NULL||node2==NULL)
    flag=1;
    if(node1->val>node2->val)
    {
        flag=1;
        swap(node1,node2);//swapping the nodes if the correspondign condition is true
    }
    //now updating the rest ones
    //making the connections after merging
    node* c1=node1->child;
    if(c1==NULL)
    {
        flag=0;
        //cout<<flag<<endl;
    }
    node2->sib=node1->child;
    node2->par=node1;
    a21=node2->sib;
    node1->deg=node1->deg+1;
    node1->child=node2;
    return node1;
}
//union function to combine the two list of heaps
list<node*> union1(list<node*> h1,list<node*> h2)
{
    vector<node*>p1;
    int flag2=0;
    //defining a list as vectors had a problem in this case due to their random access
    list<node*>a1;
    //using the iterators for easy access over the list elements
    list<node*>::iterator it=h1.begin();
    list<node*>::iterator it1=h2.begin();
    list<node*>a5;
    list<node*>a6;
    while(1)
    {
        if(it==h1.end()||it1==h2.end())//if this satisfies break
        break;
        else
        {
            //if the degree matches or less than
            if((*it)->deg>(*it1)->deg)
            {
                flag2=0;
                a5.pb(*it);
                a1.pb(*it1);//pushing in the list
                it1++;//incrementing
            }
            else//if doesnt follow the given condition
            {
                flag2=1;
                a6.pb(*it1);
                a1.pb(*it);//pushing in the list
                it++;//incrementing
            }
            //cout<<flag2<<endl;
        }
    }
    //now we need to make sure that we have covered all the entities of each list
    //for h1
    //order imp
    while(1)
    {
        if(it==h1.end())
        break;
        else
        {
            a1.pb(*it);
            it++;
        }
    }
    //for h2
    while(1)
    {
        if(it1==h2.end())
        break;
        else
        {
            a1.pb(*it1);
            it1++;
        }
    }
    //cout<<flag2<<endl;
    return a1;//return the union of these lists
}
//ordering the things
list<node*>order(list<node*>bino_heap)
{
    list<node*>a5;
    ll cal=0;
    ll curr_size=bino_heap.size();
    //if the heap size is greater than 1
    if(bino_heap.size()>1)
    {
        //defining the iterators
        list<node*>a6;
        list<node*>::iterator it,it1,it2,it3,it4;
        it=bino_heap.begin();
        it1=bino_heap.begin();
        it2=bino_heap.begin();
        it3=bino_heap.begin();
        //if size==2
        //then just compare with the other one
        if(bino_heap.size()==2)
        {
            cal++;
            it1=it;
            it1++;
            it2=bino_heap.end();//end
        }
        else
        {
            cal++;
            it1++;
            it2=it1;
            it2++;
        }
        //now running the loop
        ll check=0;
        while(it!=bino_heap.end())//jab tak iterator end tak na jaaye
        {
            if(it1==bino_heap.end())//increment the other
            it++;
            else if((*it)->deg<((*it1)->deg))
            {
                ll ca1=(*it)->deg;
                //if(ca1<=0) cout<<0<<endl;
                it++;
                it1++;
                //if it2!= binoheapend
                int a10 = 0;
                if(it2==bino_heap.end())
                {
                    // ca1=(*it1)->deg;
                    a10++;
                }
                else
                {
                   it2++;
                   check++;
                }
            }
            else if(it2!=bino_heap.end()&&((*it)->deg)==((*it1)->deg)&&((*it)->deg)==((*it2)->deg))//condition required
            {
                check++;
                it++;
                it1++;
                it2++;
            }
            else if((*it)->deg==(*it1)->deg)
            {
                node* p1;
                //calling the merge function
                *it=merge(*it,*it1);
                it1=bino_heap.erase(it1);//erasing it from the heap
                if(it2!=bino_heap.end())
                it2++;
            }
            else
            check=0;
        }
        return bino_heap;//returing the actual heap
    }
    else
    return bino_heap;
}
//function to insert in the binomial tree
list<node*>insert_binot1(list<node*>bino_heap,node* node1)
{
    list<node*>p1,p2;
    //vector<node*>p1;
    p1.pb(node1);//pushing the node1 in the list
    //calling the union function
    p1=union1(bino_heap,p1);
    //calling the order function to order the heaps
    list<node*>a1=order(p1);
    return a1;
}
//function to delete in the bino heap
list<node*>delete1(node* node1)
{
    //vector<ll>p1;
    list<node*>p1;
    //p2 as p1 child
    node* p2=node1->child;
    ll totit=0;
    node* p3;
    node* p4;
    while(p2)
    {
        totit++;
        p3=p2;
        p2=p2->sib;
        p3->sib=NULL;//sibling ko null
        p4=p3;
        p1.insert(p1.begin(),p3);//inserting in the list
    }
    //cout<<totit<<endl;
    //returning the list
    return p1;
}
//adding in the binomial heap
list<node*>add1_bino(list<node*>h1,ll value,ll value1)
{
    node* p1=NULL;
    p1=(struct node*)(malloc(sizeof(struct node)));
    p1->val=value1;
    p1->deg=0;
    p1->child=NULL;
    p1->par=NULL;
    p1->sib=NULL;
    p1->source=value;
    list<node*>ans1=insert_binot1(h1,p1);//calling the respective function
    return ans1;
}
//function to fing the min in the heap
node* findmin(list<node*>bino_heap)
{
    //vector<ll>p1;
    list<node*>::iterator it=bino_heap.begin();
    ll val2=0;
    node* p1=*it;
    while(1)
    {
        if(it==bino_heap.end())
        break;
        if((*it)->val<p1->val)
        {
            p1=*it;
            val2++;
        }
        it++;
    }
    //cout<<val2<<endl;
    return p1;
}
//function for extract min in the binomial heap
list<node*>extractmin(list<node*>bino_heap)
{
    ll flag=1;
    list<node*>heap1,heap2;
    node* p1;
    //calling the find min function
    p1=findmin(bino_heap);
    list<node*>::iterator it;
    // beginning it with the starting node in bino_heap
    ll cnt1=0;
    it=bino_heap.begin();
    while(1)
    {
        if(it==bino_heap.end())//if thats the end break
        {
            break;
        }
        else
        {
            if(*it!=p1)
            {
                flag=0;
                //cout<<flag<<endl;
                heap1.pb(*it);//inserting in the heap1 list
            }
            it++;
            cnt1++;
        }
    }
    //deleting p1 after finding it
    ll a3=cnt1;
    heap2=delete1(p1);
    //combining both the heaps
    heap1=union1(heap1,heap2);
    //now ordering these heaps
    heap1=order(heap1);
    return heap1;
}
//main funciton for dijkstra for binomial heaps
void dijkstra_binomial(vector<pair<ll,ll>>arr[],ll s,ll n, vector<pair<ll,ll>>final[])
{
    ll dist[n+1];//initialising with inf
    for(ll i=0;i<=n;i++)
    dist[i]=1e12;
    dist[s]=0;
    list<node*>build_heap;
    build_heap=add1_bino(build_heap,s,dist[s]);
    int flag=0;
    //ll cnt1=0;
    while(build_heap.size()>0)
    {
        //cnt1++;
        struct node* temp=findmin(build_heap);
        ll min1=temp->source;
        //cout<<cnt1<<endl;
        list<node*>build_heap1=extractmin(build_heap);
        build_heap=build_heap1;
        for(auto it=arr[min1].begin();it!=arr[min1].end();it++)
        {
            ll v1=it->first;
            ll v2=it->second;
            if(v2<0)
            {
                flag=1;
                break;
            }
            else
            {
                if(dist[v1]>dist[min1]+v2)
                {
                    dist[v1]=dist[min1]+v2;
                    build_heap=add1_bino(build_heap,v1,dist[v1]);
                    //store1.push(make_pair(dist[v1],v1));
                }
            }
        }
        if(flag==1)
        break;
    }
    if(flag==1)
    cout<<"-1"<<endl;
    else
    {
        for(ll i=1;i<=n;i++)
        {
            if(dist[i]>1e9)
            final[s].push_back(make_pair(i,999999));
            else
            final[s].push_back(make_pair(i,dist[i]));
        }
    }
    return;
}
 ll totnodes=0;
//creating structure for fibonacci heaps
struct node_f{
    //things req for each node in fibonacci heaps
    ll val;
    ll col;
    ll source;
    ll deg;
    ll col1;
    node_f* child;
    node_f* par;
    node_f* lt;
    node_f* rt;
};
//defining the totmin in fibo heap to be null and the size to be 0 
//these are defined as global variable as these are going to be changed in each function and thus are quite handy
 struct node_f* mintot=NULL;
 //insert function in fibonacci heap
void insert_fib(ll data,ll data1)
{
    struct node_f* node1=(struct node_f*)(malloc(sizeof(struct node_f)));
    //node1=(struct node_f*)(malloc(sizeof(struct node_f)));
    node1->val=data;
    node1->source=data1;
    node1->par=NULL;
    node1->child=NULL;
    node1->rt=node1;
    node1->lt=node1;
    node1->col=0;
    node1->col1=0;
    node1->deg=0;
    //updating the mintot after insertion
    // if there are no nodes then the added node is mintot
    if(mintot==NULL)
    {
        mintot=node1;
        totnodes++;
    }
    else
    {
        ll a1=node1->val;
        ll a2=mintot->val;
        //taking care of the left and right childs of mintot
        mintot->lt->rt=node1;
        node1->lt=mintot->lt;
        node1->rt=mintot;
        mintot->lt=node1;
        if(mintot->val>node1->val)
        mintot=node1;//updating mintot
        else
        {
            a2=node1->val;
        }
        totnodes++;//incrementing the total no of nodes
    }
}
//fib_con function 
void fib_con(struct node_f* p1,struct node_f* p2)
{
    node_f* a5;
    a5=p1;
    //repective connections to be linked
    ll cnt7=0;
    node_f* poi1=p2;
    p1->lt->rt=p1->rt;
    if(poi1==NULL)
    poi1=p1;
    p1->rt->lt=p1->lt;
    if(p2->rt==p2)
    mintot=p2;
    else
    cnt7++;
    //cout<<cnt7<<endl;
    //looking after the other connection
    //p1 ke par ko p2 dedo
    p1->par=p2;
    // p1 ke left aur ritght ko p1 dedo 
    p1->rt=p1;
    p1->lt=p1;
    if(p2->child==NULL)
    {
        p2->child=p1;
    }
    else
    {
        a5=p2->child;
    }
    // looing after the connections
    //p1 ke right ko p2 child dedo
    p1->rt=p2->child;
    a5=p1->rt;
    poi1=p1->lt;
    p1->lt=p2->child->lt;
   // cout<<a5->val<<endl;
    p2->child->lt->rt=p1;
    a5=p1;
    //cout<<a5->val<<endl;
    p2->child->lt=p1;
    if(poi1==p1)
    cnt7++;
    //cout<<cnt7<<endl;
    if(p2->child->val>p1->val)
    {
        p2->child=p1;
        a5=p1;
        //cout<<a5->val<<endl;
    }
    else
    cnt7++;
    //cout<<cnt7<<endl;
    //incremetning the degree of p2
    p2->deg=p2->deg+1;
    //cout<<poi1->val<<endl;
}
//function to concatenate the heaps
void combine()
{
    ll t1;
    ll t2=log2(totnodes);//since the no of nodes can be represented in binary format thus total no of nodes = log2(nodes);
    //initialising the vector of pointers with null
    vector<struct node_f*>v1(t2+1,NULL);
    struct node_f* p1=mintot;
    struct node_f* p2;
    struct node_f* p3;
    struct node_f* p5=p1;
    struct node_f* p4;
    p5=p5->rt;
    ll at=0;
    t1=p1->deg;
    int flag=0;
    while(1)
    {
        if(v1[t1]==NULL)
        break;
        else
        {
            at++;
            p2=v1[t1];
            //required if else statements
            if(p1->val>p2->val)
            {
                flag=1;
                p3=p1;
                p1=p2;
                p2=p3;
            }
            else
            {
                p4=p1;
            }
            if(p2==mintot)
            {
                mintot=p1;
            }
            else
            at--;
            //calling the fib conn function
            fib_con(p2,p1);
            if(p1->rt==p1)
            {
                mintot=p1;
            }
            else
            p4=p1;
            //giving it a null value
            v1[t1]=NULL;
            //incrementinf t1
            t1=t1+1;
        }
    }
    v1[t1]=p1;
    p1=p1->rt;
    //repeating the same process again till the condition satisfies
    ll c1=0;
    while(1)
    {
        if(p1==mintot)
        break;
        else
        {
            p5=p5->rt;
    t1=p1->deg;
    while(1)
    {
        if(v1[t1]==NULL)
        break;
        else
        {
            p2=v1[t1];
            if(p1->val>p2->val)
            {
                p3=p1;
                p1=p2;
                p2=p3;
            }
            else
            c1--;
            if(p2==mintot)
            {
                mintot=p1;
            }
            else 
            c1++;
            //calling the same function again
            fib_con(p2,p1);
            if(p1->rt==p1)
            {
                mintot=p1;
            }
            else
            c1++;
            v1[t1]=NULL;
            t1=t1+1;
        }
    }
    //cout<<c1<<endl;
    v1[t1]=p1;
    p1=p1->rt;
        }
    }
    mintot=NULL;
    ll start=0;
    ll fl=0;
    ll ch=0;
    while(start<=t2)
    {
        if(v1[start]==NULL)
        {
            start++;
            continue;
        }
        else
        {
            fl=1;
            v1[start]->lt=v1[start];
            v1[start]->rt=v1[start];
            if(mintot==NULL)
            {
                mintot=v1[start];
                ch++;
            }
            else
            {
                mintot->lt->rt=v1[start];
                if(ch>0)
                fl=0;
                //cout<<fl<<endl;
                v1[start]->rt=mintot;
                v1[start]->lt=mintot->lt;
                mintot->lt=v1[start];
                if(mintot->val>v1[start]->val)
                {
                    mintot=v1[start];
                }
            }
            if(mintot==NULL)
            mintot=v1[start];
            else if(mintot->val>v1[start]->val)
            {
                mintot=v1[start];
            }
            else
            ch--;
        }
        start++;
    }
}
//extractmin function for fibonacci heaps
void extractmin_fib()
{
    node_f* che1=mintot;
    ll fll1;
    if(mintot!=NULL)
    {
        node_f* d2=che1;
        node_f* t1=mintot;
        node_f* p1;
        p1=t1;
        node_f* p2=NULL;
        node_f* p3=NULL;
        if(t1->child!=NULL)
        {
            p2=t1->child;
            //
            p1=p2->rt;
            d2=p1;
            mintot->lt->rt=p2;
            p2->rt=mintot;
            p2->lt=mintot->lt;
            mintot->lt=p2;
            if(mintot->val>p2->val)
            {
                mintot=p2;
                d2=mintot;
            }
            else
            fll1++;
            p2->par=NULL;
            p2=p1;
            while(1){
                if(p1==t1->child)
                break;
                else
                {
                    p1=p2->rt;
            mintot->lt->rt=p2;
            p2->rt=mintot;
            d2=mintot->lt;
            if(d2==NULL)
            d2=p1;
            p2->lt=mintot->lt;
            mintot->lt=p2;
            if(mintot->val>p2->val)
            {
                mintot=p2;//update the min
            }
            p2->par=NULL;
            p2=p1;
                }
            }
        }
        //other connections to be made
        node_f* d3=t1->lt;//left child
        node_f* d4=t1->rt;//right child
        t1->lt->rt=t1->rt;
        t1->rt->lt=t1->lt;
        //update the min
        mintot=t1->rt;
        if(t1->child==NULL&&t1==t1->rt)
        {
        mintot=NULL;
        d2=t1;
        }
        else
        {
            d2=t1->child;
            mintot=t1->rt;
            combine();//calling the fucntion to concatenate
        }
        //cout<<fll1<<endl;
        totnodes=totnodes-1;//decrementing the totnodes
    }
}
//remove1_fib function to break the links
void remove1_fib(struct node_f* p1,struct node_f* p2)
{
    node_f* c1=p1;
    node_f* c2;
    if(p1==p1->rt)
    {
        p2->child=NULL;
        c2=p2->child;
    }
    else
    {
        c1=p1->rt;
    }
    ll tot1=totnodes;
    c2=p1->rt;
    p1->lt->rt=p1->rt;
    p1->rt->lt=p1->lt;
    if(p1==p2->child)
    {
        p2->child=p1->rt;
    }
    else
    tot1--;
    //cout<<tot1<<totnodes<<endl;
    p2->deg=p2->deg-1;//decrementing the degree
    //changing the connections of p1
    p1->rt=p1;
    p1->lt=p1;
    c2=mintot->lt;
    mintot->lt->rt=p1;
    p1->rt=mintot;
    p1->lt=mintot->lt;
    mintot->lt=p1;
    p1->par=NULL;
    c2=p1;
    //cout<<p1->col<<endl;
    p1->col=1;//updating the color i.e making it black after 2 blacks cut it
}
//remove2_fib function 
void remove2_fib(struct node_f* p1)
{
    node_f* c1=p1;
    struct node_f* p2=p1->par;
    if(p2==NULL)
    return;
    else
    {
        if(p1->col==0)
        {
            c1=p2;
            p1->col=1;
        }
        else
        {
            //calling the repective functions
            ll check=0;
            c1=p1;
            //cout<<check<<endl//for debugging
            remove1_fib(p1,p2);
            remove2_fib(p2);
        }
    }
}
//decrease key function in fibonacci
void dec_fib(struct node_f* p1,ll data)
{
    if(mintot==NULL||p1==NULL)
    return;
    else
    {
        node_f* a1=p1;
        a1->val=data;
        //cout<<a1->val<<endl;
        p1->val=data;
        struct node_f* p2=p1->par;
        node_f* c1;
        if(p2!=NULL)
        {
            if(p2->val>p1->val)
            {
                //calling the respective function
                c1=p2;
                remove1_fib(p1,p2);
                remove2_fib(p2);
            }
            else
            {
                a1->val=p2->val;
                //cout<<a1->val<<endl;
            }
        }
    }
}
//search function in fibonacci
void search_fib(struct node_f* mintot,ll val1,ll val2)
{
    ll d1;
    struct node_f* temp1;
    struct node_f* p1=NULL;
    struct node_f* p2=mintot;//assigning the min value
    p2->col1=1;//marking it
    d1=val2;
    temp1=p2;
    struct node_f* p3=NULL;
    if(p2->val==val1)
    {
        p3=p2;
        temp1=p3;
        if(temp1==NULL)
        d1=0;
        p2->col1=0;//unmarking it
        p1=p3;
        d1=temp1->col;
        ll t8=0;
        if(d1==0)
        t8++;
        //cout<<t8<<endl;
        dec_fib(p1,val2);//calling the decrease key function
        temp1=p1;
    }
    //if it doesnt go in the previous loop
    int fla=0;
    if(p3!=NULL)
    {
        temp1=p3;
        d1=0;
        //cout<<d1<<endl;
    }
    else
    {
        if(p2->child==NULL)
        {
            temp1=p1;
            fla=0;
        }
        else
        {
            fla=1;
            temp1=p2->child;
            search_fib(p2->child,val1,val2);//recursive calling 
        }
        if(p2->rt->col1!=1)
        {
            fla=1;
            temp1=p2;
            search_fib(p2->rt,val1,val2);//recursive calling
        }
    }
    p2->col1=0;//required changes
    p1=p3;
}
void deleten_fib(ll val)
{
    if(mintot==NULL)
    {
        return;
    }
    else
    {
        //calling the search and extract min function respectively
        search_fib(mintot,val,0);
        extractmin_fib();
    }
}
//dijkstra algo using fibonacci heaps
void dijkstra_fibonacci(vector<pair<ll,ll>>arr[],ll s, ll n, vector<pair<ll,ll>>final[])
{
    ll dist[n+1];//initialising with inf
    for(ll i=0;i<=n;i++)
    dist[i]=1e12;
    dist[s]=0;
    mintot=NULL;
    totnodes=0;
    //vector<node*>build_heap;
    insert_fib(dist[s],s);
   // build_heap=add1_bino(build_heap,s,dist[s]);
    int flag=0;
    //ll cnt1=0;
    ll cnt1=1;
    while(totnodes>0)
    {
        //cnt1++;
       // cout<<totnodes<<endl;
        struct node_f* temp=mintot;
        ll min1=temp->source;
        //cout<<cnt1<<endl;
        //vector<node*>build_heap1=extractmin(build_heap);
        extractmin_fib();
       // cout<<totnodes<<endl;
       //if(mintot==NULL)
       //cout<<1<<endl;
        cnt1--;
       // build_heap=build_heap1;
        for(auto it=arr[min1].begin();it!=arr[min1].end();it++)
        {
            ll v1=it->first;
            ll v2=it->second;
            if(v2<0)
            {
                flag=1;
                break;
            }
            else
            {
                if(dist[v1]>dist[min1]+v2)
                {
                    dist[v1]=dist[min1]+v2;
                    //build_heap=add1_bino(build_heap,v1,dist[v1]);
                    //store1.push(make_pair(dist[v1],v1));
                    insert_fib(dist[v1],v1);
                    cnt1++;
                }
            }
        }
        if(flag==1)
        break;
    }
    if(flag==1)
    cout<<"-1"<<endl;
    else
    {
        for(ll i=1;i<=n;i++)
        {
            if(dist[i]>1e9)
            final[s].push_back(make_pair(i,999999));
            else
            final[s].push_back(make_pair(i,dist[i]));
        }
    }
    return;
}
//function to sove the problem (main)
void solve1(ll type)
{
    mintot=NULL;
    totnodes=0;
      ll n,d;
      cin>>n>>d;
      // d=0 undirected else directed 
      ll adj[n+1][n+1];
      for(ll i=0;i<n;i++)
      {
          for(ll j=0;j<n;j++)
          cin>>adj[i][j];
      }
      vector<pair<ll,ll>>arr[n+1];
      for(ll i=0;i<n;i++)
      {
          for(ll j=0;j<n;j++)
          {
              if(i==j)
              continue;
              else if(adj[i][j]==999999)
              continue;
              else
              {
                  arr[i+1].push_back(make_pair(j+1,adj[i][j]));
              }
          }
      }
      ll s=0;
      for(ll i=1;i<=n;i++)
      {
          arr[0].push_back(make_pair(i,0));
      }
      //bellman ford from 0
              ll dist[n+1];
              queue<ll>q1;
              for(ll i=0;i<=n;i++)
              dist[i]=1e12;
              dist[s]=0;
              q1.push(s);
              ll relax_oper=0,relax_modi=0;
              for(ll j=0;j<n;j++)// N STEPS
              {
                  queue<ll>q2;//queue to store
                  ll visited1[n+1]={0};
                  while(q1.size()>0)
                  {
                  ll a1=q1.front();//first element of queue
                  q1.pop();
                  reverse(arr[a1].begin(),arr[a1].end());
                  for(auto it=arr[a1].begin();it!=arr[a1].end();it++)
                  {
                      ll v1=it->first;
                      ll v2=it->second;
                      if(dist[v1]>dist[a1]+v2)
                      {
                          if(dist[a1]+v2<1e8)
                          {
                          dist[v1]=dist[a1]+v2;
                          relax_modi++;
                          if(visited1[v1]==0)
                          {
                          q2.push(v1);
                          visited1[v1]++;
                          }
                          }
                      }
                      relax_oper++;
                  }
                  }
                  swap(q1,q2);//swapping the queue for further updates
              }
              //just for checking negative cycle
              int flag=0;
              for(ll i=0;i<=n;i++)
              {
                  for(auto it=arr[i].begin();it!=arr[i].end();it++)
                  {
                      ll v1=it->first;
                      ll v2=it->second;
                      if(dist[v1]>dist[i]+v2)
                      {
                          if(dist[i]+v2>1e9)//ignoring as they r not part of the same connected component
                          continue;
                          else
                          {
                          flag=1;
                          break;
                          }
                      }
                  }
              }
              if(flag==1)
              cout<<"-1"<<endl;
              else
              {
                 // for(ll i=1;i<=n;i++)
                  //cout<<dist[i]<<" ";
                  //cout<<endl;
                  vector<pair<ll,ll>>newadj[n+1];
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<arr[i].size();j++)
                      {
                          ll a1=arr[i][j].first;
                          ll a2=arr[i][j].second;
                          newadj[i].push_back(make_pair(a1,a2+dist[i]-dist[a1]));
                      }
                  }
                  /*for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<newadj[i].size();j++)
                      {
                          ll a1=newadj[i][j].first;
                          ll a2=newadj[i][j].second;
                          cout<<a2<<" ";
                      }
                      cout<<endl;
                  }*/
                 vector<pair<ll,ll>>final[n+1];
                 if(type==4)//default
                 {
                     for(ll i=1;i<=n;i++)
                  {
                      dijkstra_fibonacci(newadj,i,n,final);//bnomial one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999&&final[i][j].second<1e7)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }
                 }
                 else
                 {
                     if(type==1)
                     {
                         for(ll i=1;i<=n;i++)
                  {
                      dijkstra_array(newadj,i,n,final);//array one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }
                     }
                     else if(type==2)
                     {
                         for(ll i=1;i<=n;i++)
                  {
                      dijkstra_binary(newadj,i,n,final);//binary one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999&&final[i][j].second<1e7)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }
                     }
                     else if(type==3)
                     {
                          for(ll i=1;i<=n;i++)
                  {
                      dijkstra_binomial(newadj,i,n,final);//bnomial one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999&&final[i][j].second<1e7)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }
                     }
                     
                 }
                 /*for(ll i=1;i<=n;i++)
                  {
                      dijkstra_array(newadj,i,n,final);//array one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }*/
                 /*for(ll i=1;i<=n;i++)
                  {
                      dijkstra_binary(newadj,i,n,final);//binary one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999&&final[i][j].second<1e7)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }*/
                  
                 /* for(ll i=1;i<=n;i++)
                  {
                      dijkstra_binomial(newadj,i,n,final);//bnomial one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999&&final[i][j].second<1e7)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }*/
                  
                 /*for(ll i=1;i<=n;i++)
                  {
                      dijkstra_fibonacci(newadj,i,n,final);//bnomial one
                  }
                  for(ll i=1;i<=n;i++)
                  {
                      for(ll j=0;j<final[i].size();j++)
                      {
                          if(final[i][j].second!=999999&&final[i][j].second<1e7)
                          cout<<final[i][j].second-(dist[i]-dist[final[i][j].first])<<" ";
                          else
                          cout<<999999<<" ";
                      }
                      cout<<endl;
                  }*/
                 
              }
}
int main(int argc, char** argv)
{
    ll type;
    if(argc==1)
    {
        type=4;
    }
    else 
	{
		if (*argv[1] == '1')
		{
			type=1;
		}
		else if (*argv[1] == '2')
		{
			type=2;
		}
		else if (*argv[1] == '3')
		{
			type=3;
		}
		else
		{
			type=4;
		}
	}
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long int t;
    cin>>t;
    long double time1[t+1];
    ll te=0;
    while(t--)
    {
        clock_t start, end;
        start = clock(); 
        solve1(type);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
        time1[te]=time_taken;
        te++;
                 // cout << fixed << time_taken << setprecision(6); 
    }
    for(ll i=0;i<te;i++)
    cout << fixed << time1[i] << setprecision(8)<<" ";
    cout<<endl;
    return 0;
}
